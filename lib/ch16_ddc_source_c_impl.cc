/* -*- c++ -*- */
/* 
 * Copyright 2016 Innovative Integration, Inc..
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "ch16_ddc_source_c_impl.h"

#include <Ipp/ipps.h>
// #include <boost/thread/thread.hpp>

namespace gr {
  namespace II_K7_310R {

    unsigned  ch16_ddc_source_c_impl::BlockCount = 0;

    ch16_ddc_source_c::sptr
    ch16_ddc_source_c::make(float rf_gain, Ch16TriggerSource trigger_source,
                            const char*  ddc_filter_path, bool is_rf_tuner, float rf_center_freq,
                            float ch0_offset_freq, float ch1_offset_freq, float ch2_offset_freq,
                            float ch3_offset_freq, float ch4_offset_freq, float ch5_offset_freq,
                            float ch6_offset_freq, float ch7_offset_freq, float ch8_offset_freq,
                            float ch9_offset_freq, float ch10_offset_freq, float ch11_offset_freq,
                            float ch12_offset_freq, float ch13_offset_freq, float ch14_offset_freq,
                            float ch15_offset_freq,
                            float ch0_tune_freq, float ch1_tune_freq, float ch2_tune_freq,
                            float ch3_tune_freq, float ch4_tune_freq, float ch5_tune_freq,
                            float ch6_tune_freq, float ch7_tune_freq, float ch8_tune_freq,
                            float ch9_tune_freq, float ch10_tune_freq, float ch11_tune_freq,
                            float ch12_tune_freq, float ch13_tune_freq, float ch14_tune_freq,
                            float ch15_tune_freq)
    {
        float ch0_freq = is_rf_tuner ? ch0_offset_freq : ch0_tune_freq;
        float ch1_freq = is_rf_tuner ? ch1_offset_freq : ch1_tune_freq;
        float ch2_freq = is_rf_tuner ? ch2_offset_freq : ch2_tune_freq;
        float ch3_freq = is_rf_tuner ? ch3_offset_freq : ch3_tune_freq;
        float ch4_freq = is_rf_tuner ? ch4_offset_freq : ch4_tune_freq;
        float ch5_freq = is_rf_tuner ? ch5_offset_freq : ch5_tune_freq;
        float ch6_freq = is_rf_tuner ? ch6_offset_freq : ch6_tune_freq;
        float ch7_freq = is_rf_tuner ? ch7_offset_freq : ch7_tune_freq;
        float ch8_freq = is_rf_tuner ? ch8_offset_freq : ch8_tune_freq;
        float ch9_freq = is_rf_tuner ? ch9_offset_freq : ch9_tune_freq;
        float ch10_freq = is_rf_tuner ? ch10_offset_freq : ch10_tune_freq;
        float ch11_freq = is_rf_tuner ? ch11_offset_freq : ch11_tune_freq;
        float ch12_freq = is_rf_tuner ? ch12_offset_freq : ch12_tune_freq;
        float ch13_freq = is_rf_tuner ? ch13_offset_freq : ch13_tune_freq;
        float ch14_freq = is_rf_tuner ? ch14_offset_freq : ch14_tune_freq;
        float ch15_freq = is_rf_tuner ? ch15_offset_freq : ch15_tune_freq;

        return gnuradio::get_initial_sptr
          (new ch16_ddc_source_c_impl(rf_gain, trigger_source, ddc_filter_path, is_rf_tuner,
                                    rf_center_freq, ch0_freq, ch1_freq, ch2_freq,
                                    ch3_freq, ch4_freq, ch5_freq, ch6_freq,
                                    ch7_freq, ch8_freq, ch9_freq, ch10_freq,
                                    ch11_freq, ch12_freq, ch13_freq, ch14_freq,
                                    ch15_freq));
    }

    /*
     * The private constructor
     */
    ch16_ddc_source_c_impl::ch16_ddc_source_c_impl(float rf_gain, Ch16TriggerSource trigger_source,
                                                   const char* ddc_filter_path, bool is_rf_tuner, float rf_center_freq,
                                                   float ch0_freq, float ch1_freq, float ch2_freq,
                                                   float ch3_freq, float ch4_freq, float ch5_freq,
                                                   float ch6_freq, float ch7_freq, float ch8_freq,
                                                   float ch9_freq, float ch10_freq, float ch11_freq,
                                                   float ch12_freq, float ch13_freq, float ch14_freq,
                                                   float ch15_freq):
        Settings(rf_gain, static_cast<unsigned short>(trigger_source),
            ddc_filter_path,  // labeled as "DDC Bandwidth" in GR block
            is_rf_tuner,
            rf_center_freq, 16, // MaxChannels
            ch0_freq, ch1_freq, ch2_freq, ch3_freq,
            ch4_freq, ch5_freq, ch6_freq, ch7_freq,
            ch8_freq, ch9_freq, ch10_freq, ch11_freq,
            ch12_freq, ch13_freq, ch14_freq, ch15_freq
        ),
        gr::sync_block("ch16_ddc_source_c",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, 16*sizeof(gr_complex))), // Settings.MaxChannels
        BlockId(BlockCount++),
        SampleIndex(0)
        // , RxByteCountMin(INT_MAX), TxByteCountMin(INT_MAX), RxByteCountMax(0), TxByteCountMax(0)
    {
        IsNotEmpty.Clear();             // We are empty (not not empty).
        IsNotFull.Set();                // We are not full.
        // Ensure that LibraryIo is a singleton:
        if(!BlockId)
        {
            Io = new LibraryIo(this);
            GR_LOG_DEBUG(d_debug_logger, "Constructor called.");
            Io->SetSettings(Settings);
            // Requires hardware:
            Io->OpenDriver();
        }
    }

    /*
     * Our virtual destructor.
     */
    ch16_ddc_source_c_impl::~ch16_ddc_source_c_impl()
    {
        if(!BlockId)
        {
            GR_LOG_DEBUG(d_debug_logger, "destructor called.");
            delete Io;
        }
    }

    bool ch16_ddc_source_c_impl::start()
    {
        GR_LOG_DEBUG(d_debug_logger, "start() called.");
        // std::cout << "Start #" << BlockId << std::endl;
        // Start only once:
        if(!BlockId)
            {
            // Requires hardware:
            Io->StreamStart();
            }
        // TODO: return value?
    }

    // static size_t MaxDepth = 0;
    void  ch16_ddc_source_c_impl::DataPacketAvailable(unsigned int /* ordinal */,
                                                      VeloBuffer &buffer)
    {
        //  Wait for space:
        IsNotFull.WaitFor();

        PacketQ.push(buffer);

        // MaxDepth = max(MaxDepth, PacketQ.depth());

        // We are no longer empty, if someone is waiting:
        IsNotEmpty.Set();
        //  We may be full now:
        if (!(PacketQ.depth() < MaxPackets))
            {
            // Now full:
            GR_LOG_DEBUG(d_debug_logger, "II DDC packet queue full!");
            IsNotFull.Clear();
            }
    }

    int
    ch16_ddc_source_c_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
        gr_complex *out = (gr_complex *) output_items[0];
        int  Samples;

        for(int i = 0; i < noutput_items*Settings.MaxChannels;)
            {
            if (!CheckForData(Samples))
                {
                // TxByteCount += 2*sizeof(gr_complex)*i;

                // boost::this_thread::sleep(boost::posix_time::microseconds(16000)); // 1/(250/DF*MaxChannels*2*sizeof(short)/0x4000)-200

                return i/Settings.MaxChannels;
                }

            ShortDG  Sample(CurrentPacket);
            int CopyLen = min(Samples, 2*(noutput_items*Settings.MaxChannels-i));
            ippsConvert_16s32f(&Sample[SampleIndex], reinterpret_cast<Ipp32f *>(out+i), CopyLen);
            SampleIndex += CopyLen;
            i += CopyLen/2;
//            int CopyLim = min(i+Samples/2, noutput_items*Settings.MaxChannels);
//            for (;i < CopyLim; ++i)
//                {
//                out[i].real(static_cast<float>(Sample[SampleIndex++]));
//                out[i].imag(static_cast<float>(Sample[SampleIndex++]));
//                }
            }

        // TxByteCountMin = min(TxByteCountMin, noutput_items); // *sizeof(gr_complex)*Settings.MaxChannels
        // TxByteCountMax = max(TxByteCountMax, noutput_items); // *sizeof(gr_complex)*Settings.MaxChannels

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

    bool ch16_ddc_source_c_impl::stop()
    {
        if(!BlockId)
            {
            IsNotEmpty.Set();           // Release the work thread.
            // GR_LOG_DEBUG(d_debug_logger, "Max depth of packet queue: "+IntToString(MaxDepth));
            GR_LOG_DEBUG(d_debug_logger, "stop() called.");
            // std::cout << "Rx byte count (min, max):" << sizeof(short)*RxByteCountMin
            //           << ", " << sizeof(short)*RxByteCountMax << std::endl;
            // std::cout << "Tx byte count (min, max):" << TxByteCountMin*sizeof(gr_complex)*Settings.MaxChannels
            //           << ", " << TxByteCountMax*sizeof(gr_complex)*Settings.MaxChannels << std::endl;
            // Stop only once:
            Io->StreamStop();
            GR_LOG_DEBUG(d_debug_logger, "Depth of packet queue: "+IntToString(PacketQ.depth()));
            IsNotFull.Set();            // Release the receive thread.
            }
        return true;
    }

    // SampleIndex, CurrentPacket, and PacketQ may be changed:
    bool  ch16_ddc_source_c_impl::CheckForData(int &Samples)
    {
        ShortDG  Buffer(CurrentPacket);

        Samples = Buffer.size()-SampleIndex;
        if (!Samples)
            {
            if (!PacketQ.depth())
                {
                IsNotEmpty.Clear();     // We are empty (not not empty).
                IsNotEmpty.WaitFor();
                if (!PacketQ.depth())
                    {
                    return false;       // Abort since stopping
                    }
                }
            CurrentPacket = PacketQ.front();
            PacketQ.pop();
            //  We are no longer full, if someone is waiting
            IsNotFull.Set();
            SampleIndex = 0;

            ShortDG  NewBuffer(CurrentPacket);
            Samples = NewBuffer.size();
            // for debug
            // ShortDG  Buffer(buffer);
            // RxByteCountMin = min(RxByteCountMin, NewBuffer.size()); // CurrentPacket.SizeInBytes());
            // RxByteCountMax = max(RxByteCountMax, NewBuffer.size()); // CurrentPacket.SizeInBytes());

            }

        return true;
    }

  } /* namespace II_K7_310R */
} /* namespace gr */


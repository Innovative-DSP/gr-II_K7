/* -*- c++ -*- */
/* 
 * Copyright 2016 Innovative Integration, Inc.
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
#include "ch1_ddc_source_c_impl.h"

#include <Ipp/ipps.h>

namespace gr {
  namespace II_K7 {

    unsigned  ch1_ddc_source_c_impl::BlockCount = 0;

    ch1_ddc_source_c::sptr
    ch1_ddc_source_c::make(float rf_gain, Ch1TriggerSource trigger_source, const char*  ddc_filter_path,
                           bool is_rf_tuner, float rf_center_freq, float ch0_offset_freq, float ch0_tune_freq)
    {
        float ch0_freq = is_rf_tuner ? ch0_offset_freq : ch0_tune_freq;

        return gnuradio::get_initial_sptr
          (new ch1_ddc_source_c_impl(rf_gain, trigger_source, ddc_filter_path, is_rf_tuner, rf_center_freq, ch0_freq));
    }

    /*
     * The private constructor
     */
    ch1_ddc_source_c_impl::ch1_ddc_source_c_impl(float rf_gain, Ch1TriggerSource trigger_source,
                                                 const char*  ddc_filter_path, bool is_rf_tuner,
                                                 float rf_center_freq, float ch0_offset_freq) :
         Settings(rf_gain, static_cast<unsigned short>(trigger_source),
             ddc_filter_path,  // labeled as "DDC Bandwidth" in GR block
             is_rf_tuner,
             rf_center_freq, 1, // MaxChannels
             ch0_offset_freq, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
         ),
         gr::sync_block("ch1_ddc_source_c",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, 1*sizeof(gr_complex))), // Settings.MaxChannels
         BlockId(BlockCount++),
         SampleIndex(0)
         // , RxByteCount(0), TxByteCount(0)
     {
         IsNotEmpty.Clear();            // We are empty (not not empty).
         IsNotFull.Set();               // We are not full.
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
    ch1_ddc_source_c_impl::~ch1_ddc_source_c_impl()
    {
        if(!BlockId)
        {
            GR_LOG_DEBUG(d_debug_logger, "destructor called.");
            delete Io;
        }
    }

    bool ch1_ddc_source_c_impl::start()
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

    void  ch1_ddc_source_c_impl::DataPacketAvailable(unsigned int /* ordinal */,
                                                      VeloBuffer &buffer)
    {
        //  Wait for space:
        IsNotFull.WaitFor();

        PacketQ.push(buffer);

        // for debug
//        ShortDG  Buffer(buffer);
//        if (!(SampleIndex < Buffer.size()))
//        RxByteCount += sizeof(short)*Buffer.size();

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
    ch1_ddc_source_c_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
        gr_complex *out = (gr_complex *) output_items[0];
        int  Samples;

        for(int i = 0; i < noutput_items*Settings.MaxChannels;)
            {
            if (!CheckForData(Samples))
                {
//                TxByteCount += 2*sizeof(gr_complex)*i;
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

        // Tell runtime system how many output items we produced.
//        TxByteCount += sizeof(gr_complex)*noutput_items*Settings.MaxChannels;
        return noutput_items;
    }

    bool ch1_ddc_source_c_impl::stop()
    {
        if(!BlockId)
            {
            IsNotEmpty.Set();           // Release the work thread.
            GR_LOG_DEBUG(d_debug_logger, "stop() called.");
//            std::cout << "Rx byte count:" << RxByteCount << std::endl;
//            std::cout << "Tx byte count:" << TxByteCount << std::endl;
            // Stop only once:
            Io->StreamStop();
            GR_LOG_DEBUG(d_debug_logger, "Depth of packet queue: "+IntToString(PacketQ.depth()));
            IsNotFull.Set();            // Release the receive thread.
            }
         return true;
     }

    // SampleIndex, CurrentPacket, and PacketQ may be changed:
    bool  ch1_ddc_source_c_impl::CheckForData(int  &Samples)
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
            }

        return true;
    }

  } /* namespace II_K7 */
} /* namespace gr */


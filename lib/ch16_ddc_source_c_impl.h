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

#ifndef INCLUDED_II_K7_310R_CH16_DDC_SOURCE_C_IMPL_H
#define INCLUDED_II_K7_310R_CH16_DDC_SOURCE_C_IMPL_H

// #include <queue>

#include <II_K7_310R/ch16_ddc_source_c.h>
#include <LibraryIo.h>
#include <BufferDatagrams_Mb.h>
#include <ThreadSafeQueue_Mb.h>
#include <Event_Mb.h>

namespace gr {
  namespace II_K7_310R {

    class ch16_ddc_source_c_impl : public ch16_ddc_source_c, IManager_GUIInterface
    {
    private:
        LibraryIo::GpDspSettings  Settings;
        LibraryIo*  Io;
        static unsigned  BlockCount;
        unsigned  BlockId;
        ThreadSafeQueue<VeloBuffer>  PacketQ;
        static const queue<VeloBuffer>::size_type  MaxPackets = 128;
        size_t  SampleIndex;
        VeloBuffer CurrentPacket;
        // Status of PacketQ and CurrentPacket:
        Event  IsNotFull;
        Event  IsNotEmpty;

        //TODO: for debug
        size_t  RxByteCountMin, RxByteCountMax;
        int  TxByteCountMin, TxByteCountMax;

    public:
        ch16_ddc_source_c_impl(short max_ch, float rf_gain, Ch16TriggerSource trigger_source,
                               const char* ddc_filter_path, bool is_rf_tuner, float rf_center_freq,
                               float ch0_offset_freq, float ch1_offset_freq, float ch2_offset_freq,
                               float ch3_offset_freq, float ch4_offset_freq, float ch5_offset_freq,
                               float ch6_offset_freq, float ch7_offset_freq, float ch8_offset_freq,
                               float ch9_offset_freq, float ch10_offset_freq, float ch11_offset_freq,
                               float ch12_offset_freq, float ch13_offset_freq, float ch14_offset_freq,
                               float ch15_offset_freq);
        ~ch16_ddc_source_c_impl();

        // Where all the action really happens
        int work(int noutput_items,
                 gr_vector_const_void_star &input_items,
                 gr_vector_void_star &output_items);
        virtual bool start();
        virtual bool stop();

    private:
        bool  CheckForData(int  &Samples);
        //  IManager_GUIInterface members:
        virtual void  Log(const std::string & a_string)
            {  GR_LOG_NOTICE(d_logger, a_string);  } // Other logging levels are possible.
        virtual void  DataPacketAvailable(unsigned int ordinal, VeloBuffer &buffer);

        virtual void  PeriodicStatus(unsigned int ordinal) {}
        virtual void  BeforeStreamStart(unsigned int ordinal) {}
        virtual void  AfterStreamStart(unsigned int ordinal) {}
        virtual void  AfterStreamAutoStop(unsigned int ordinal) {}
        virtual void  Plot(unsigned int ordinal, VeloBuffer &buffer, int type) {}
        virtual void  BeforeDrcOpen() {}
        virtual void  AfterDrcOpen() {}
        virtual void  BeforeDrcClose() {}
        virtual void  AfterDrcClose() {}
        virtual void  AfterDrcStreamStart() {}
        virtual void  BeforeDrcStreamStart() {}
        virtual void  AfterDrcStreamStop() {}
        virtual void  BeforeDrcStreamStop() {}
     };

  } // namespace II_K7_310R
} // namespace gr

#endif /* INCLUDED_II_K7_310R_CH16_DDC_SOURCE_C_IMPL_H */


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

#include <II_K7_310R/ch16_ddc_source_c.h>
#include <GRGpK7Interface.h>

namespace gr {
  namespace II_K7_310R {

    class ch16_ddc_source_c_impl : public ch16_ddc_source_c, ILoggerInterface
    {
    private:
        GRGpK7Interface::GpDspSettings  Settings;
        GRGpK7Interface*  Io;
        static unsigned  BlockCount;
        unsigned  BlockId;

    public:
        ch16_ddc_source_c_impl(short max_ch, float rf_gain, Ch16TriggerSource trigger_source,
                               const char* ddc_filter_path, bool is_rf_tuner, float rf_center_freq,
                               float ch0_freq, float ch1_freq, float ch2_freq, float ch3_freq,
                               float ch4_freq, float ch5_freq, float ch6_freq, float ch7_freq,
                               float ch8_freq, float ch9_freq, float ch10_freq, float ch11_freq,
                               float ch12_freq, float ch13_freq, float ch14_freq, float ch15_freq,
                               Ch16Source ch0_source, Ch16Source ch1_source, Ch16Source ch2_source, Ch16Source ch3_source,
                               Ch16Source ch4_source, Ch16Source ch5_source, Ch16Source ch6_source, Ch16Source ch7_source,
                               Ch16Source ch8_source, Ch16Source ch9_source, Ch16Source ch10_source, Ch16Source ch11_source,
                               Ch16Source ch12_source, Ch16Source ch13_source, Ch16Source ch14_source, Ch16Source ch15_source);
        ~ch16_ddc_source_c_impl();

        // Where all the action really happens
        int work(int noutput_items,
                 gr_vector_const_void_star &input_items,
                 gr_vector_void_star &output_items);
        virtual bool start();
        virtual bool stop();

    private:
        virtual void  Log(const std::string & a_string)
        { GR_LOG_NOTICE(d_logger, a_string); }  // Other logging levels are possible.
        virtual void  DebugLog(const std::string & a_string)
        { GR_LOG_NOTICE(d_debug_logger, a_string); }  // Other logging levels are possible.
     };

  } // namespace II_K7_310R
} // namespace gr

#endif /* INCLUDED_II_K7_310R_CH16_DDC_SOURCE_C_IMPL_H */


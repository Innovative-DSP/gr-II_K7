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

#ifndef INCLUDED_II_K7_310R_DUC_SINK_IMPL_H
#define INCLUDED_II_K7_310R_DUC_SINK_IMPL_H

#include <II_K7_310R/duc_sink.h>
#include <GRGpK7Interface.h>

namespace gr {
  namespace II_K7_310R {

    class duc_sink_impl : public duc_sink, ILoggerInterface
    {
    private:
        GRGpK7Interface::GpDucSettings  Settings;
        GRGpK7Interface*  Io;

    public:
        duc_sink_impl(II_K7_310R::DucFmcModule fmc_module, short max_ch, const char*  duc_filter_path,
                      float ch0_offset_freq, float ch1_offset_freq, float ch2_offset_freq, float ch3_offset_freq,
                      float ch4_offset_freq, float ch5_offset_freq, float ch6_offset_freq, float ch7_offset_freq);
        ~duc_sink_impl();

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

#endif /* INCLUDED_II_K7_310R_DUC_SINK_IMPL_H */


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
#include <volk/volk.h>
#include "duc_sink_impl.h"

namespace gr {
  namespace II_K7 {

    duc_sink::sptr
    duc_sink::make(II_K7::DucFmcModule fmc_module, short max_ch, const char*  duc_filter_path,
                   float ch0_tune_freq, float ch1_tune_freq, float ch2_tune_freq, float ch3_tune_freq,
                   float ch4_tune_freq, float ch5_tune_freq, float ch6_tune_freq, float ch7_tune_freq)
    {
      return gnuradio::get_initial_sptr
        (new duc_sink_impl(fmc_module, max_ch, duc_filter_path,
                           ch0_tune_freq, ch1_tune_freq, ch2_tune_freq, ch3_tune_freq,
                           ch4_tune_freq, ch5_tune_freq, ch6_tune_freq, ch7_tune_freq));
    }

    /*
     * The private constructor
     */
    duc_sink_impl::duc_sink_impl(II_K7::DucFmcModule fmc_module, short max_ch, const char*  duc_filter_path,
                                 float ch0_tune_freq, float ch1_tune_freq, float ch2_tune_freq, float ch3_tune_freq,
                                 float ch4_tune_freq, float ch5_tune_freq, float ch6_tune_freq, float ch7_tune_freq)
      :
        Settings(duc_filter_path, // labeled as "DUC Bandwidth" in GR block
                 max_ch,
                 ch0_tune_freq, ch1_tune_freq, ch2_tune_freq, ch3_tune_freq,
                 ch4_tune_freq, ch5_tune_freq, ch6_tune_freq, ch7_tune_freq),
        gr::sync_block("duc_sink",
              gr::io_signature::make(1, gr::io_signature::IO_INFINITE, sizeof(gr_complex)),
              gr::io_signature::make(0, 0, 0))
    {
        GR_LOG_DEBUG(d_debug_logger, "Constructor called.");
        Io = new GRGpK7Interface(this, static_cast<GRGpK7Interface::LibIoSelector>(fmc_module));

        const int alignment_multiple = volk_get_alignment() / sizeof(float);
        set_alignment(std::max(1, alignment_multiple));

        Io->SetDucSettings(Settings);
        // TODO:GR_LOG_DEBUG(d_debug_logger, "Max channels: "+IntToString(Settings.MaxChannels));
        GR_LOG_DEBUG(d_debug_logger, "Constructor finished.");
    }

    /*
     * Our virtual destructor.
     */
    duc_sink_impl::~duc_sink_impl()
    {
        GR_LOG_DEBUG(d_debug_logger, "destructor called.");
        delete Io;
    }

    bool duc_sink_impl::start()
    {
        GR_LOG_DEBUG(d_debug_logger, "start() called.");
        // Requires hardware:
        Io->OpenDriver();
        GR_LOG_DEBUG(d_debug_logger, "open() finished.");
        // Requires hardware:
        Io->Start();
        // TODO: return value?
        GR_LOG_DEBUG(d_debug_logger, "start() finished.");
    }

    int
    duc_sink_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
        return Io->DucWork(noutput_items, input_items, output_items);
    }

    bool duc_sink_impl::stop()
    {
        return Io->Stop();
    }
  } /* namespace II_K7 */
} /* namespace gr */


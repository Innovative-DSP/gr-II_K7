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
#include <volk/volk.h>
#include <cstdio>
#include "fft_source_f_impl.h"

namespace gr {
  namespace II_K7 {

    fft_source_f::sptr
    fft_source_f::make(II_K7::FftFmcModule fmc_module, II_K7::FftSrc fft0_source,
                       II_K7::FftWindowing fft0_windowing, bool is_fft0_fasd, float fft0_fasd)
    {
      return gnuradio::get_initial_sptr
        (new fft_source_f_impl(fmc_module, fft0_source, fft0_windowing, is_fft0_fasd, fft0_fasd));
    }

    /*
     * The private constructor
     */
    fft_source_f_impl::fft_source_f_impl(II_K7::FftFmcModule fmc_module, II_K7::FftSrc fft0_source,
                                         II_K7::FftWindowing fft0_windowing, bool is_fft0_fasd, float fft0_fasd)
      :

        Settings(static_cast<unsigned short>(fft0_source), static_cast<unsigned short>(fft0_windowing),
                    is_fft0_fasd, fft0_fasd
        ),
        gr::sync_block("fft_source_f",
                       gr::io_signature::make(0, 0, 0),
                       gr::io_signature::make(1, gr::io_signature::IO_INFINITE, sizeof(float)))
    {
        GR_LOG_DEBUG(d_debug_logger, "FFT Constructor called.");
        Io = new GRGpK7Interface(this, static_cast<GRGpK7Interface::LibIoSelector>(fmc_module));

        const int alignment_multiple = volk_get_alignment() / sizeof(float);
        set_alignment(std::max(1, alignment_multiple));

        Io->SetFftSettings(Settings);
        GR_LOG_DEBUG(d_debug_logger, "FFT Constructor finished.");
    }

    /*
     * Our virtual destructor.
     */
    fft_source_f_impl::~fft_source_f_impl()
    {
        GR_LOG_DEBUG(d_debug_logger, "FFT destructor called.");
        delete Io;
    }

    bool fft_source_f_impl::start()
    {
        GR_LOG_DEBUG(d_debug_logger, "FFT start() called.");
        // Requires hardware:
        Io->OpenDriver();
        // Requires hardware:
        Io->Start();
        GR_LOG_DEBUG(d_debug_logger, "FFT start() finished.");
        // TODO: return value?
    }

    int
    fft_source_f_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
        static short  Count = 0;
        if (Count < 2)
            {
            if (2 == ++Count)
                {
                char  str[32];
                (void)sprintf(str, "%i", noutput_items);
                std::string  Str(str);
                GR_LOG_DEBUG(d_debug_logger, "FFT work() called: "+Str); // 8192
                }
            }
        // Tell runtime system how many output items we produced.
//        return Io->LibIoDesc->Io->FftWork(noutput_items, input_items, output_items);
        return Io->FftWork(noutput_items, input_items, output_items);
    }

    bool fft_source_f_impl::stop()
    {
        GR_LOG_DEBUG(d_debug_logger, "FFT stop() called.");
        return Io->Stop();
    }

  } /* namespace II_K7 */
} /* namespace gr */


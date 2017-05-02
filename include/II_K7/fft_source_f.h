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


#ifndef INCLUDED_II_K7_FFT_SOURCE_F_H
#define INCLUDED_II_K7_FFT_SOURCE_F_H

#include <II_K7/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace II_K7 {

    enum FftFmcModule {FftFmc250Module, FftFmc310Module}; // AKA LibIoSelector in GRGpK7Interface
    enum FftSrc {FftDdc0, FftDdc1, FftDdc2, FftDdc3, FftDdc4, FftDdc5, FftDdc6, FftDdc7,
                 FftDdc8, FftDdc9, FftDdc10, FftDdc11, FftDdc12, FftDdc13, FftDdc14, FftDdc15,
                 FftAdc0, FftAdc1, FftAdc2, FftAdc3, FftTest};
    enum FftWindowing {Rect, Hann, Cheby, Taylor, Blackman, Hamming, Gauss, Flattop};

    /*!
     * \brief source of FFT data
     * \ingroup II_K7
     *
     */
    class II_K7_API fft_source_f : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<fft_source_f> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of II_K7::fft_source_f.
       *
       * To avoid accidental use of raw pointers, II_K7::fft_source_f's
       * constructor is in a private implementation
       * class. II_K7::fft_source_f::make is the public interface for
       * creating new instances.
       */
      static sptr make(II_K7::FftFmcModule fmc_module, II_K7::FftSrc fft0_source, II_K7::FftWindowing fft0_windowing, bool is_fft0_fasd, float fft0_fasd);
    };

  } // namespace II_K7
} // namespace gr

#endif /* INCLUDED_II_K7_FFT_SOURCE_F_H */


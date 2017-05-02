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


#ifndef INCLUDED_II_K7_DUC_SINK_H
#define INCLUDED_II_K7_DUC_SINK_H

#include <II_K7/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace II_K7 {

    enum DucFmcModule {DucFmc250Module, DucFmc310Module}; // AKA LibIoSelector in GRGpK7Interface

    /*!
     * \brief sink for DUC data
     * \ingroup II_K7
     *
     */
    class II_K7_API duc_sink : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<duc_sink> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of II_K7::duc_sink.
       *
       * To avoid accidental use of raw pointers, II_K7::duc_sink's
       * constructor is in a private implementation
       * class. II_K7::duc_sink::make is the public interface for
       * creating new instances.
       */
      static sptr make(II_K7::DucFmcModule fmc_module, short max_ch, const char*  duc_filter_path,
                       float ch0_tune_freq, float ch1_tune_freq, float ch2_tune_freq, float ch3_tune_freq,
                       float ch4_tune_freq, float ch5_tune_freq, float ch6_tune_freq, float ch7_tune_freq);
    };

  } // namespace II_K7
} // namespace gr

#endif /* INCLUDED_II_K7_DUC_SINK_H */


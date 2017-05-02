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


#ifndef INCLUDED_II_K7_CH1_DDC_SOURCE_C_H
#define INCLUDED_II_K7_CH1_DDC_SOURCE_C_H

#include <II_K7/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace II_K7 {

    enum Ch1TriggerSource {Ch1Software, Ch1External};

    /*!
     * \brief source of DDC data
     * \ingroup II_K7
     *
     */
    class II_K7_API ch1_ddc_source_c : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<ch1_ddc_source_c> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of II_K7::ch1_ddc_source_c.
       *
       * To avoid accidental use of raw pointers, II_K7::ch1_ddc_source_c's
       * constructor is in a private implementation
       * class. II_K7::ch1_ddc_source_c::make is the public interface for
       * creating new instances.
       */
      static sptr make(float rf_gain, II_K7::Ch1TriggerSource trigger_source,
                       const char*  ddc_filter_path, bool is_rf_tuner, float rf_center_freq,
                       float ch0_offset_freq, float ch0_tune_freq);
    };

  } // namespace II_K7
} // namespace gr

#endif /* INCLUDED_II_K7_CH1_DDC_SOURCE_C_H */


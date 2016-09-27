/* -*- c++ -*- */
/* 
 * Copyright 2016 2016 Innovative Integration, Inc..
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


#ifndef INCLUDED_II_K7_310R_CH16_DDC_SOURCE_C_H
#define INCLUDED_II_K7_310R_CH16_DDC_SOURCE_C_H

#include <II_K7_310R/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace II_K7_310R {

    enum Ch16TriggerSource {Ch16Software, Ch16External};

    /*!
     * \brief source of DDC data
     * \ingroup II_K7_310R
     *
     */
    class II_K7_310R_API ch16_ddc_source_c : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<ch16_ddc_source_c> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of II_K7_310R::ch16_ddc_source_c.
       *
       * To avoid accidental use of raw pointers, II_K7_310R::ch16_ddc_source_c's
       * constructor is in a private implementation
       * class. II_K7_310R::ch16_ddc_source_c::make is the public interface for
       * creating new instances.
       */
        static sptr make(float rf_gain, II_K7_310R::Ch16TriggerSource trigger_source, const char*  ddc_filter_path, float rf_center_freq, float ch0_offset_freq, float ch1_offset_freq, float ch2_offset_freq, float ch3_offset_freq, float ch4_offset_freq, float ch5_offset_freq, float ch6_offset_freq, float ch7_offset_freq, float ch8_offset_freq, float ch9_offset_freq, float ch10_offset_freq, float ch11_offset_freq, float ch12_offset_freq, float ch13_offset_freq, float ch14_offset_freq, float ch15_offset_freq);
    };

  } // namespace II_K7_310R
} // namespace gr

#endif /* INCLUDED_II_K7_310R_CH16_DDC_SOURCE_C_H */


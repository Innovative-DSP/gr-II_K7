#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2016 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import II_K7_310R_swig as II_K7_310R

class qa_duc_sink (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # set up fg
        II_K7_310R_duc_sink_0 = II_K7_310R.duc_sink(II_K7_310R.DucFmc250Module, 2, 
              '/home/user/Config/ddc/ddc_Fs250MHz_BW2MHz.ini',
              -0.5, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)

        self.tb.run ()
        # check data


if __name__ == '__main__':
    gr_unittest.run(qa_duc_sink, "qa_duc_sink.xml")

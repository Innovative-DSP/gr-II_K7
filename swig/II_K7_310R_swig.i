/* -*- c++ -*- */

#define II_K7_310R_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "II_K7_310R_swig_doc.i"

%{
#include "II_K7_310R/ch16_ddc_source_c.h"
#include "II_K7_310R/ch1_ddc_source_c.h"
%}


%include "II_K7_310R/ch16_ddc_source_c.h"
GR_SWIG_BLOCK_MAGIC2(II_K7_310R, ch16_ddc_source_c);
%include "II_K7_310R/ch1_ddc_source_c.h"
GR_SWIG_BLOCK_MAGIC2(II_K7_310R, ch1_ddc_source_c);

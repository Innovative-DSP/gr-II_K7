/* -*- c++ -*- */

#define II_K7_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "II_K7_swig_doc.i"

%{
#include "II_K7/ch16_ddc_source_c.h"
#include "II_K7/fft_source_f.h"
#include "II_K7/duc_sink.h"
//#include "II_K7/ch1_ddc_source_c.h"
%}


%include "II_K7/ch16_ddc_source_c.h"
GR_SWIG_BLOCK_MAGIC2(II_K7, ch16_ddc_source_c);
//%include "II_K7/ch1_ddc_source_c.h"
//GR_SWIG_BLOCK_MAGIC2(II_K7, ch1_ddc_source_c);

%include "II_K7/fft_source_f.h"
GR_SWIG_BLOCK_MAGIC2(II_K7, fft_source_f);
%include "II_K7/duc_sink.h"
GR_SWIG_BLOCK_MAGIC2(II_K7, duc_sink);

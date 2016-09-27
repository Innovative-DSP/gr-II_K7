#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/user/Documents/GnuRadio/gr-II_K7_310R/lib
export GR_CONF_CONTROLPORT_ON=False
export PATH=/home/user/Documents/GnuRadio/gr-II_K7_310R/build/lib:$PATH
export LD_LIBRARY_PATH=/home/user/Documents/GnuRadio/gr-II_K7_310R/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-II_K7_310R 

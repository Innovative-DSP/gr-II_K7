# Copyright 2011,2012 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

find_package(Innovative)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
list(APPEND II_K7_sources
    ch16_ddc_source_c_impl.cc
    #ch1_ddc_source_c_impl.cc
    fft_source_f_impl.cc
    duc_sink_impl.cc )

set(II_K7_sources "${II_K7_sources}" PARENT_SCOPE)
if(NOT II_K7_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT II_K7_sources)

add_library(gnuradio-II_K7 SHARED ${II_K7_sources})
#target_include_directories(gnuradio-II_K7 PUBLIC
#    ${INNOVATIVE_LIBRARY_IO_INCLUDE_DIR} ${INNOVATIVE_GP_LIB_INCLUDE_DIR}
#    ${INNOVATIVE_GP_LIB_GUI_INCLUDE_DIR} ${INNOVATIVE_MALIBU_INCLUDE_DIR}
#    ${INNOVATIVE_MALIBU_POCO_INCLUDE_DIR} ${INNOVATIVE_COMMON_INCLUDE_DIR}
#)
set(II_libs "${Innovative}/Lib/Gcc")
set(II_config "$<$<CONFIG:DEBUG>:${II_libs}/Debug>$<$<CONFIG:RELEASE>:${II_libs}/Release>$<$<CONFIG:RELWITHDEBINFO>:${II_libs}/Release>")
set(INNOVATIVE_LIBRARIES
    ${II_config}/libGP-K7-FMC-310.a      ${II_config}/libGP-K7-FMC-250.a  ${II_config}/libGPDDC.a
    ${II_config}/libGRGpK7Interface.a    ${II_config}/libAnalysis_Mb.a    ${II_config}/libApplication_Mb.a
    ${II_config}/libFicl_Mb.a            ${II_config}/libFramework_Mb.a   ${II_config}/libFramework_Con.a
    ${II_config}/libHardware_Mb.a        ${II_config}/libOs_Mb.a          ${II_config}/libPci_Mb.a
    ${II_config}/libPoco_Foundation_Mb.a ${II_config}/libPoco_Net_Mb.a    ${II_config}/libUtility_Mb.a
    ${II_config}/libVpx_Mb.a
)
set(IPP_LIBRARIES
    ${II_libs}/libippac_l-7.0.a    ${II_libs}/libippcc_l-7.0.a    ${II_libs}/libippch_l-7.0.a
    ${II_libs}/libippcore_l-7.0.a  ${II_libs}/libippcv_l-7.0.a    ${II_libs}/libippdc_l-7.0.a
    ${II_libs}/libippdi_l-7.0.a    ${II_libs}/libippi_l-7.0.a     ${II_libs}/libippj_l-7.0.a
    ${II_libs}/libippm_l-7.0.a     ${II_libs}/libippr_l-7.0.a     ${II_libs}/libipps_l-7.0.a
    ${II_libs}/libippsc_l-7.0.a    ${II_libs}/libippvc_l-7.0.a    ${II_libs}/libippvm_l-7.0.a
)
target_link_libraries(gnuradio-II_K7 PRIVATE ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES} -Wl,--whole-archive -Wl,--start-group  ${INNOVATIVE_LIBRARIES} -Wl,--end-group -Wl,--no-whole-archive PUBLIC ${IPP_LIBRARIES} /usr/lib/x86_64-linux-gnu/libdl.so /usr/lib/libwdapi.so)
set_target_properties(gnuradio-II_K7 PROPERTIES DEFINE_SYMBOL "gnuradio_II_K7_EXPORTS")
target_compile_definitions(gnuradio-II_K7 PUBLIC Foundation_EXPORTS DRC GCC LINUX _MT)
# set_target_properties(gnuradio-II_K7 PROPERTIES LINK_INTERFACE_MULTIPLICITY 15)
# set_target_properties(gnuradio-II_K7 PROPERTIES LINK_FLAGS "-Wl,-ldl")

if(APPLE)
    set_target_properties(gnuradio-II_K7 PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
install(TARGETS gnuradio-II_K7
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so/.dylib file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS} ${INNOVATIVE_INCLUDE_DIRS})
list(APPEND test_II_K7_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_II_K7.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_II_K7.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_duc_sink.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_fft_source_f.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_ch16_ddc_source_c.cc
)

add_executable(test-II_K7 ${test_II_K7_sources})

target_link_libraries(
  test-II_K7
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-II_K7
)

GR_ADD_TEST(test_II_K7 test-II_K7)

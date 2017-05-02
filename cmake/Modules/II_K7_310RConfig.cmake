INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_II_K7 II_K7)

FIND_PATH(
    II_K7_INCLUDE_DIRS
    NAMES II_K7/api.h
    HINTS $ENV{II_K7_DIR}/include
        ${PC_II_K7_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    II_K7_LIBRARIES
    NAMES gnuradio-II_K7
    HINTS $ENV{II_K7_DIR}/lib
        ${PC_II_K7_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(II_K7 DEFAULT_MSG II_K7_LIBRARIES II_K7_INCLUDE_DIRS)
MARK_AS_ADVANCED(II_K7_LIBRARIES II_K7_INCLUDE_DIRS)


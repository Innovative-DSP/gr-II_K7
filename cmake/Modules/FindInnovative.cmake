#
# Find the Innovative Integration includes and library
#
# This module defines
# INNOVATIVE_INCLUDE_DIR, where to find Malibu and GP includes
# INNOVATIVE_LIBRARY, one of the Malibu and GP libraries to link against
# INNOVATIVE_FOUND, If false, do not try to use Malibu/GP.

set(Innovative /usr/Innovative)

FIND_PATH(INNOVATIVE_LIBRARY_IO_INCLUDE_DIR
    LibraryIo.h
    HINTS
    ${Innovative}/Digital_Receiver_K707-1.0/Digital_Receiver_K707/GP-K7-LIB/Common
)

FIND_PATH(INNOVATIVE_GP_LIB_INCLUDE_DIR
    GpDspManager_Gp.h Filter.h
    HINTS
    ${Innovative}/Digital_Receiver_K707-1.0/Digital_Receiver_K707/GP-LIB/GpDsp
)

FIND_PATH(INNOVATIVE_GP_LIB_GUI_INCLUDE_DIR
    Filter.h
    HINTS
    ${Innovative}/Digital_Receiver_K707-1.0/Digital_Receiver_K707/GP-LIB/Common
)

FIND_PATH(INNOVATIVE_MALIBU_INCLUDE_DIR
    Malibu_Mb.h
    HINTS
    ${Innovative}/Malibu
)

FIND_PATH(INNOVATIVE_MALIBU_POCO_INCLUDE_DIR
    Poco/Poco.h
    HINTS
    ${Innovative}/Malibu/Poco/Foundation/include
)

FIND_LIBRARY(INNOVATIVE_LIBRARY
    libGP-K7.a
    HINTS
    ${Innovative}/Lib/Gcc/Release
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(INNOVATIVE DEFAULT_MSG INNOVATIVE_LIBRARY
    INNOVATIVE_LIBRARY_IO_INCLUDE_DIR INNOVATIVE_GP_LIB_INCLUDE_DIR INNOVATIVE_GP_LIB_GUI_INCLUDE_DIR
    INNOVATIVE_MALIBU_INCLUDE_DIR INNOVATIVE_MALIBU_POCO_INCLUDE_DIR
)
MARK_AS_ADVANCED(INNOVATIVE_LIBRARY
    INNOVATIVE_LIBRARY_IO_INCLUDE_DIR INNOVATIVE_GP_LIB_INCLUDE_DIR INNOVATIVE_GP_LIB_GUI_INCLUDE_DIR
    INNOVATIVE_MALIBU_INCLUDE_DIR INNOVATIVE_MALIBU_POCO_INCLUDE_DIR
)

#
# Find the Innovative Integration includes and library
#
# This module defines
# (OBE) INNOVATIVE_INCLUDE_DIR, where to find Malibu and GP includes
# INNOVATIVE_LIBRARY, some of the Malibu/GP libraries to link against
# INNOVATIVE_FOUND, If false, do not try to use Malibu/GP.

set(Innovative ${CMAKE_BINARY_DIR}/../Innovative)

FIND_LIBRARY(INNOVATIVE_LIBRARY
    libGP-K7.a libGP-K7-FMC-250.a libGPDDC.a
    HINTS
    ${Innovative}/Lib/Gcc/Release
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(INNOVATIVE DEFAULT_MSG INNOVATIVE_LIBRARY
)
MARK_AS_ADVANCED(INNOVATIVE_LIBRARY
)

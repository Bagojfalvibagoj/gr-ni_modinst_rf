find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_NI_MODINST_RF gnuradio-ni_modinst_rf)

FIND_PATH(
    GR_NI_MODINST_RF_INCLUDE_DIRS
    NAMES gnuradio/ni_modinst_rf/api.h
    HINTS $ENV{NI_MODINST_RF_DIR}/include
        ${PC_NI_MODINST_RF_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_NI_MODINST_RF_LIBRARIES
    NAMES gnuradio-ni_modinst_rf
    HINTS $ENV{NI_MODINST_RF_DIR}/lib
        ${PC_NI_MODINST_RF_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-ni_modinst_rfTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_NI_MODINST_RF DEFAULT_MSG GR_NI_MODINST_RF_LIBRARIES GR_NI_MODINST_RF_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_NI_MODINST_RF_LIBRARIES GR_NI_MODINST_RF_INCLUDE_DIRS)

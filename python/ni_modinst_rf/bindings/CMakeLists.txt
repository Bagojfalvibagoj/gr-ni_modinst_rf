# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT ni_modinst_rf_sources)
    MESSAGE(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT ni_modinst_rf_sources)

########################################################################
# Check for pygccxml
########################################################################
GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND ni_modinst_rf_python_files
    ni_rfsa_source_python.cc python_bindings.cc)

GR_PYBIND_MAKE_OOT(ni_modinst_rf
   ../../..
   gr::ni_modinst_rf
   "${ni_modinst_rf_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(TARGET ni_modinst_rf_python POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ni_modinst_rf_python>
    ${PROJECT_BINARY_DIR}/test_modules/gnuradio/ni_modinst_rf/
)

install(TARGETS ni_modinst_rf_python DESTINATION ${GR_PYTHON_DIR}/gnuradio/ni_modinst_rf COMPONENT pythonapi)

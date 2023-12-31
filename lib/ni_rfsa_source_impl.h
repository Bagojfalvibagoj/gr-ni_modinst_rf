/* -*- c++ -*- */
/*
 * Copyright 2023 mtEM.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_NI_MODINST_RF_NI_RFSA_SOURCE_IMPL_H
#define INCLUDED_NI_MODINST_RF_NI_RFSA_SOURCE_IMPL_H

#include <gnuradio/ni_modinst_rf/ni_rfsa_source.h>

namespace gr {
  namespace ni_modinst_rf {

    class ni_rfsa_source_impl : public ni_rfsa_source
    {
     private:
      // Nothing to declare in this block.

     public:
      ni_rfsa_source_impl(char* resourceName);
      ~ni_rfsa_source_impl();

      // Where all the action really happens
      int work(
              int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items
      );
    };

  } // namespace ni_modinst_rf
} // namespace gr

#endif /* INCLUDED_NI_MODINST_RF_NI_RFSA_SOURCE_IMPL_H */

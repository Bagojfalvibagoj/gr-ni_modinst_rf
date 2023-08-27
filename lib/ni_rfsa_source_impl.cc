/* -*- c++ -*- */
/*
 * Copyright 2023 mtEM.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <gnuradio/io_signature.h>
#include <niRFSA.h>
#include "ni_rfsa_source_impl.h"

namespace gr {
  namespace ni_modinst_rf {

    #pragma message("set the following appropriately and remove this warning")
    using output_type = float;
    ni_rfsa_source::sptr
    ni_rfsa_source::make(char* resourceName)
    {
      niRFSA_init(0,0,0,0);
      return gnuradio::make_block_sptr<ni_rfsa_source_impl>(char* resourceName);
    }


    /*
     * The private constructor
     */
    ni_rfsa_source_impl::ni_rfsa_source_impl(char* resourceName)
      : gr::sync_block("ni_rfsa_source",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)))
    {}

    /*
     * Our virtual destructor.
     */
    ni_rfsa_source_impl::~ni_rfsa_source_impl()
    {
    }

    int
    ni_rfsa_source_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      auto out = static_cast<output_type*>(output_items[0]);

      #pragma message("Implement the signal processing in your block and remove this warning")
      // Do <+signal processing+>

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace ni_modinst_rf */
} /* namespace gr */

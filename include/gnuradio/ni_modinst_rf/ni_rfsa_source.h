/* -*- c++ -*- */
/*
 * Copyright 2023 mtEM.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_NI_MODINST_RF_NI_RFSA_SOURCE_H
#define INCLUDED_NI_MODINST_RF_NI_RFSA_SOURCE_H

#include <gnuradio/ni_modinst_rf/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace ni_modinst_rf {

    /*!
     * \brief <+description of block+>
     * \ingroup ni_modinst_rf
     *
     */
    class NI_MODINST_RF_API ni_rfsa_source : virtual public gr::sync_block
    {
     public:
      typedef std::shared_ptr<ni_rfsa_source> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ni_modinst_rf::ni_rfsa_source.
       *
       * To avoid accidental use of raw pointers, ni_modinst_rf::ni_rfsa_source's
       * constructor is in a private implementation
       * class. ni_modinst_rf::ni_rfsa_source::make is the public interface for
       * creating new instances.
       */
      static sptr make(char* resourceName);
    };

  } // namespace ni_modinst_rf
} // namespace gr

#endif /* INCLUDED_NI_MODINST_RF_NI_RFSA_SOURCE_H */

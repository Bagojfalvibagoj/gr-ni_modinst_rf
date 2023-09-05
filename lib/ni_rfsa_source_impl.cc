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
    using output_type = short;
    ni_rfsa_source::sptr
    ni_rfsa_source::make(std::string resourceName, float centerFreq, float sampleRate, float refLevel, std::string bitfile)
    {
      return gnuradio::make_block_sptr<ni_rfsa_source_impl>(resourceName, centerFreq, sampleRate, refLevel, bitfile);
    }


    /*
     * The private constructor
     */
    ni_rfsa_source_impl::ni_rfsa_source_impl(std::string resourceName, float centerFreq, float sampleRate, float refLevel, std::string bitfile)
      : gr::sync_block("ni_rfsa_source",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)))
    {

      strcpy(viResourceName, resourceName.c_str());
      if (bitfile.empty() || !bitfile.compare("None"))
        strcpy(viOptionString,"");
      else
        strcpy(viOptionString, ("DriverSetup=Bitfile: " + bitfile).substr(0,1023).c_str());
      

      ViStatus status = niRFSA_InitWithOptions(viResourceName, TRUE, FALSE, viOptionString, &rfsaSession);

      if (status)
      {
        niRFSA_GetError(rfsaSession, &status, 1023, viErrorDescription);
        std::string errorString(viErrorDescription);
        d_logger->error("Can not open RFSA device " + resourceName + " - " + errorString);
        rfsaSession = 0;
        return;
      }

      status = niRFSA_ConfigureAcquisitionType(rfsaSession, NIRFSA_VAL_IQ);
      status |= niRFSA_ConfigureIQRate(rfsaSession, "", sampleRate);
      status |= niRFSA_ConfigureIQCarrierFrequency(rfsaSession, "", centerFreq);
      status |= niRFSA_ConfigureReferenceLevel(rfsaSession, "", refLevel);
      status |= niRFSA_ConfigureNumberOfSamples(rfsaSession, "", VI_FALSE, 0);
      status |= niRFSA_ConfigureNumberOfRecords(rfsaSession, "", VI_TRUE, 1);
      status |= niRFSA_Commit(rfsaSession);

      if (status)
      {
        d_logger->error("Cound not properly configure RFSA device " + resourceName);
        return;
      }
      else 
        rfsaConfigured = true;
    }

    /*
     * Our virtual destructor.
     */
    ni_rfsa_source_impl::~ni_rfsa_source_impl()
    {
      if (rfsaSession)
        niRFSA_close(rfsaSession);
    }

    int
    ni_rfsa_source_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      auto out = static_cast<output_type*>(output_items[0]);

      if (rfsaAcquiring)
      {
        ViStatus status;
        ViInt64 backlog = 0;
        status = niRFSA_GetFetchBacklog(rfsaSession, "", 0, &backlog);

        int samplesToFetch = backlog * 2 > noutput_items ? noutput_items / 2 : backlog;
        
        niRFSA_wfmInfo info;
        status = niRFSA_FetchIQSingleRecordComplexI16(rfsaSession, "", 0, samplesToFetch, 1000, (NIComplexI16*)out, &info);

        if (status) //warnings
        {
          niRFSA_GetError(rfsaSession, &status, 1023, viErrorDescription);
          std::string errorString(viErrorDescription);

          if (status > 0) //warnings 
            d_logger->warn("Warning while fetching RFSA seamples " + errorString);
          else 
          if (status < 0) //errors
            d_logger->error("Error while fetching RFSA seamples " + errorString);

        }
        
        //if samples were fetched and gain changed since last time
        if (info.actualSamples && info.gain != wfmGainFromLastFetch)
        {
          pmt::pmt_t key = pmt::intern("WfmGain");
          pmt::pmt_t value = pmt::from_float(info.gain);

          int index = this->nitems_written(0);

          this->add_item_tag(0,0, key, value);

          wfmGainFromLastFetch = info.gain;
        }

        return info.actualSamples * 2;
      }

      return 0;
      // Tell runtime system how many output items we produced.
      //return noutput_items;
    }


    bool ni_rfsa_source_impl::start()
    {
      if (rfsaConfigured)
      {
        ViStatus status = niRFSA_Initiate(rfsaSession);
        if (status)
        {
          d_logger->error("Could not initiate acquisition.");
          return false;
        }
        rfsaAcquiring = true;
        return true;
      }
      return false;
    }

    bool ni_rfsa_source_impl::stop()
    {
      if (rfsaAcquiring)
      {
        niRFSA_Abort(rfsaSession);
      }
      return true;
    }

  } /* namespace ni_modinst_rf */
} /* namespace gr */

/* -*- c++ -*- */
/*
 * Copyright 2023 mtEM.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_NI_MODINST_RF_NI_FPGA_INTERFACE_H
#define INCLUDED_NI_MODINST_RF_NI_FPGA_INTERFACE_H

#ifdef _WIN32

#include <windows.h>


namespace gr 
{
    namespace ni_modinst_rf
    {
        
        class ni_FPGA_interface
        {
            private:
                HMODULE dllHandle;

            public:
                ni_FPGA_interface();
                ~ni_FPGA_interface();

                int (*fpgaOpen)();
                int (*fpgaClose)();

                int (*fpgaReadBool)();
                int (*fpgaWriteBool)();

                int (*fpgaReadI32)();
                int (*fpgaWriteI32)();

                int (*fpgaConfigFifo)();
                int (*fpgaSetFifoProperty)();
                int (*fpgaGetFifoProperty)();
                int (*fpgaCommitFifoConfig)();
                int (*fpgaStartFifo)();
                int (*fpgaStopFifo)();

                int (*fpgaAquireFifoReadElements)();
                int (*fpgaAquireFifoWriteElements)();

        };


    } 
}

#endif
#endif
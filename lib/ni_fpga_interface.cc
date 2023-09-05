/* -*- c++ -*- */
/*
 * Copyright 2023 mtEM.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */


#include "ni_fpga_interface.h"
#include <windows.h>


namespace gr {
  namespace ni_modinst_rf {

    ni_FPGA_interface::ni_FPGA_interface()
    {
        dllHandle = LoadLibraryA("niFpga.dll");

        if (!dllHandle) return;

        fpgaOpen = (decltype(fpgaOpen))GetProcAddress(dllHandle, "NiFpgaDll_Open");
        fpgaClose = (decltype(fpgaClose))GetProcAddress(dllHandle, "NiFpgaDll_Close");

        fpgaReadBool = (decltype(fpgaReadBool))GetProcAddress(dllHandle, "");
        fpgaWriteBool = (decltype(fpgaWriteBool))GetProcAddress(dllHandle, "");

        fpgaReadI32 = (decltype(fpgaReadI32))GetProcAddress(dllHandle, "");
        fpgaWriteI32 = (decltype(fpgaWriteI32))GetProcAddress(dllHandle, "");

        fpgaConfigFifo = (decltype(fpgaConfigFifo))GetProcAddress(dllHandle, "");
        fpgaSetFifoProperty = (decltype(fpgaSetFifoProperty))GetProcAddress(dllHandle, "");
        fpgaGetFifoProperty = (decltype(fpgaGetFifoProperty))GetProcAddress(dllHandle, "");
        fpgaCommitFifoConfig = (decltype(fpgaCommitFifoConfig))GetProcAddress(dllHandle, "");
        fpgaStartFifo = (decltype(fpgaStartFifo))GetProcAddress(dllHandle, "");
        fpgaStopFifo = (decltype(fpgaStopFifo))GetProcAddress(dllHandle, "");

        fpgaAquireFifoReadElements = (decltype(fpgaAquireFifoReadElements))GetProcAddress(dllHandle, "");
        fpgaAquireFifoWriteElements = (decltype(fpgaAquireFifoWriteElements))GetProcAddress(dllHandle, "");



    }



  }
}

/*
    CYW43 firmware location
    Copyright (c) 2026 Michael Graff

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#if defined(PICO_CYW43_SUPPORTED)

#include <stdint.h>

// The driver is built with cyw43_partition_firmware.h, so it reads the WiFi firmware and
// CLM blob through these.  They are set before the chip is brought up.
extern "C" {
    int cyw43_wifi_fw_len;
    int cyw43_clm_len;
    uintptr_t fw_data;
}

#ifndef CYW43_RESOURCE_ATTRIBUTE
#define CYW43_RESOURCE_ATTRIBUTE __attribute__((aligned(4)))
#endif
#define fw_data cyw43_builtin_fw_data
#if CYW43_ENABLE_BLUETOOTH
#include "../../pico-sdk/lib/cyw43-driver/firmware/wb43439A0_7_95_49_00_combined.h"
#else
#include "../../pico-sdk/lib/cyw43-driver/firmware/w43439A0_7_95_49_00_combined.h"
#endif
#undef fw_data

// Where the driver finds its firmware: the WiFi image, then the CLM blob at the next 512-byte
// boundary, as in the combined blobs.  The default is the blob built into the sketch.  Weak:
// a sketch that keeps the firmware elsewhere in flash (to update it apart from the sketch)
// defines its own, and returns false when there is none, which leaves WiFi and Bluetooth off.
extern "C" bool __attribute__((weak)) cyw43_firmware_locate(uintptr_t *data, int *wifi_fw_len, int *clm_len) {
    *data = cyw43_builtin_fw_data;
    *wifi_fw_len = CYW43_WIFI_FW_LEN;
    *clm_len = CYW43_CLM_LEN;
    return true;
}

#endif

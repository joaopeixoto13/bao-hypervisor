/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

// /home/joaopeixoto13/Desktop/NVIDIA-Jetson-Orin/tegra234-p3768-0000+p3767-0005.dts

struct platform platform = {
    //.cpu_num = 6,
    .cpu_num = 1,
    //.cpu_num = 5,
    .region_num = 1,
    .regions =  (struct mem_region[]) {
        {
            .base = 0x80000000,     // TRM page 45 (3.2.1.2 AMAP and Aperture) or TRM page 81
            .size = 0x200000000,
        },
    },

    .console = {
        //.base = 0x03100000,        // TRM page 68
        .base = 0x0C198000,
    },

    .arch = {
        .gic = {
            .gicd_addr = 0x0f400000,    // TRM page 75
            .gicr_addr = 0x0f440000,    // TRM page 75
            .maintenance_id = 25,
        },

        // Data sheet page 1 (Overview)
        .clusters = {
            //.num = 2,
            //.core_num = (size_t[]){ 4, 2 },
            .num = 1,
            .core_num = (size_t[]){ 1 },
        },

        .mpidr_table = {
            .table = (unsigned long []) {
                0x81000000,
                /*
                0x81000100,
                0x81000200,
                0x81000300,
                0x81010200,
                0x81010300,
                */
            },
           //.affinity_lvls = 3, 
        },
        .affinity_lvls = 3,

        /*
        // smmu_niso1
        .smmu = {
            .base = 0x8000000,
            .interrupt_id = 187,        // ???
            .global_mask = 0x7f80,
        },

        // smmu_iso
        .smmu = {
            .base = 0x10000000,
            .interrupt_id = 187,        // ???
            .global_mask = 0x7f80,
        },

        // smmu_niso0
        .smmu = {
            .base = 0x12000000,
            .interrupt_id = 187,        // ???
            .global_mask = 0x7f80,
        },
        */
    },

};

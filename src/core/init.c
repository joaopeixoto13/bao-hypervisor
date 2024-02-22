/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <bao.h>

#include <cpu.h>
#include <mem.h>
#include <interrupts.h>
#include <console.h>
#include <printk.h>
#include <platform.h>
#include <vmm.h>

void init(cpuid_t cpu_id, paddr_t load_addr)
{
    psci_cpu_on(0x80000000, load_addr, 0xa);
    /**
     * These initializations must be executed first and in fixed order.
     */

    cpu_init(cpu_id, load_addr);
    // NÃO CHEGA AQUI!
    psci_cpu_on(0x80000000, load_addr, 0xb);
    mem_init(load_addr);
    psci_cpu_on(0x80000000, load_addr, 0xc);

    /* -------------------------------------------------------------- */

    console_init();

    psci_cpu_on(0x80000000, load_addr, 0xa3);

    if (cpu_is_master()) {
        psci_cpu_on(0x80000000, load_addr, 0xa4);
        console_printk("Bao Hypervisor\n\r");
    }

    psci_cpu_on(0x80000000, load_addr, 0xa5);

    interrupts_init();

    vmm_init();

    /* Should never reach here */
    while (1) { }
}

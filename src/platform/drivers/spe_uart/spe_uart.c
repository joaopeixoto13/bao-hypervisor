/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <drivers/spe_uart.h>
#include <arch/psci.h>

void uart_init(volatile struct uartspe_hw* uart)
{
    /* Do nothing */
    psci_cpu_on(0x80000000, 0x0, 0xa1);
}

void uart_enable(volatile struct uartspe_hw* uart)
{
    /* Do nothing */
    psci_cpu_on(0x80000000, 0x0, 0xa2);
}

void uart_putc(volatile struct uartspe_hw* uart, int8_t c)
{
    uint32_t msg = UARTSPE_RING_DOORBELL | UARTSPE_NUM_BYTES_SHIFT | c;
    psci_cpu_on(0x80000000, 0x0, 0x88);
    asm volatile("str %0, [%1]" : : "r" (msg), "r" (uart->base) : "memory");    // Em x0 vai o valor de msg (No caso flags + 0x42 -> 'B')
    //*(volatile uint32_t *)uart = UARTSPE_RING_DOORBELL | UARTSPE_NUM_BYTES_SHIFT | c;
    //while (uart->base & UARTSPE_IS_BUSY) { }
    psci_cpu_on(0x80000000, 0x0, 0x89);
    //uart->base = UARTSPE_RING_DOORBELL | UARTSPE_NUM_BYTES_SHIFT | c;
}

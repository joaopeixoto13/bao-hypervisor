/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <drivers/8250_uart.h>
#include <arch/psci.h>

void uart_init(volatile struct uart8250_hw* uart)
{
    /* set baudrate */
    //psci_cpu_on(0x80000000, 0x0, 0xa3);
    uart->lcr |= UART8250_LCR_DLAB;
    /**
     * should set dll and dlh, to simplify instead lets assume the firmware did this for us.
     * TODO: we should add uart clk and baudrate info to platform descrption and use this to
     * calculate this values in runtime.
     */
    //psci_cpu_on(0x80000000, 0x0, 0xa4);
    uart->lcr &= ~UART8250_LCR_DLAB;

    /* configure 8n1 */
    //psci_cpu_on(0x80000000, 0x0, 0xa5);
    uart->lcr = UART8250_LCR_8BIT;

    /* disable interrupts */
    //psci_cpu_on(0x80000000, 0x0, 0xa6);
    uart->ier = 0;

    /* no modem */
    //psci_cpu_on(0x80000000, 0x0, 0xa7);
    uart->mcr = 0;

    /* clear status */
    //psci_cpu_on(0x80000000, 0x0, 0xa8);
    (void)uart->lsr;
    //psci_cpu_on(0x80000000, 0x0, 0xa9);
    uart->msr = 0;
}

void uart_enable(volatile struct uart8250_hw* uart)
{
    uart->fcr = UART8250_FCR_EN;
}

void uart_putc(volatile struct uart8250_hw* uart, int8_t c)
{
    while (!(uart->lsr & UART8250_LSR_THRE)) { }
    uart->thr = c;
}

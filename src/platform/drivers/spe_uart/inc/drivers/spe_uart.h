/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef UARTSPE_H
#define UARTSPE_H

#include <bao.h>
#include <plat/platform.h>

#ifndef UARTSPE_PAGE_OFFSET
#define UARTSPE_PAGE_OFFSET 0
#endif

typedef uint32_t uartspe_reg_t;

struct uartspe_hw {
    uint8_t offset[UARTSPE_PAGE_OFFSET];
    uartspe_reg_t base;
};

#define UARTSPE_NUM_BYTES_SHIFT		(1 << 24)   /* Indicates that we're only sending one byte at a time. */
#define UARTSPE_FLUSH_DATA_TO_PORT	(1 << 26)
#define UARTSPE_RING_DOORBELL		(1 << 31)   /* Triggers an interrupt. Also indicates that the remote processor is busy when set. */
#define UARTSPE_IS_BUSY			(1 << 31)
#define UARTSPE_TIMEOUT			0xC000		/* 50 ms */
#define UARTSPE_BAUDRATE		115200

// Base addr = 0x0c190000 + 0x8000

typedef struct uartspe_hw bao_uart_t;

void uart_enable(volatile struct uartspe_hw* uart);
void uart_init(volatile struct uartspe_hw* uart);
void uart_putc(volatile struct uartspe_hw* uart, int8_t c);

#endif /* UARTSPE_H */

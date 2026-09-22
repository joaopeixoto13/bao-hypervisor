/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef VM_SUBARCH_H
#define VM_SUBARCH_H

#include <bao.h>

struct arch_regs {
    uint64_t x[31];
    uint64_t elr_el2;
    uint64_t spsr_el2;
} __attribute__((aligned(16))); // makes size always aligned to 16 to respect stack alignment

_Static_assert(offsetof(struct arch_regs, elr_el2) == 31 * 8 &&
        offsetof(struct arch_regs, spsr_el2) == 32 * 8 && (sizeof(struct arch_regs) % 16) == 0,
    "VM_EXIT and VM_ENTRY keep elr and spsr in slots 31 and 32 of a 16-byte aligned frame");

#endif /* VM_SUBARCH_H */

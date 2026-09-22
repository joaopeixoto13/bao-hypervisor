/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#ifndef VM_SUBARCH_H
#define VM_SUBARCH_H

#include <bao.h>

struct arch_regs {
    uint32_t elr_hyp;
    uint32_t spsr_hyp;
    uint32_t x[15];
};

_Static_assert(offsetof(struct arch_regs, x) == 8 && sizeof(struct arch_regs) == 17 * 4,
    "VM_ENTRY pops elr, spsr, r0-r12, the sp slot and r14 in this order");

#endif /* VM_SUBARCH_H */

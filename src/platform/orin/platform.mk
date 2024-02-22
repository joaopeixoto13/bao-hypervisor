## SPDX-License-Identifier: Apache-2.0
## Copyright (c) Bao Project and Contributors. All rights reserved.

# Architecture definition
ARCH:=armv8
# CPU definition
CPU:=cortex-a78ae

GIC_VERSION:=GICV3

# TODO: Driver missing, should be 8250 compatible
drivers = spe_uart

platform_description:=orin_desc.c

platform-cppflags =
platform-cflags = -mtune=$(CPU)
platform-asflags =
platform-ldflags =

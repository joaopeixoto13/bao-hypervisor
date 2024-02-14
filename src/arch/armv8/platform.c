/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>
#include <arch/sysregs.h>

/*
    TODO:
    Esta função não faz muito sentido pois estou a construir o mpidr com base no cpuid
    e sabendo que eu posso ler o mesmo registo através da função sysreg_mpidr_el1_read().
    Ou seja, mais vale eliminar esta função, adicionar na interface do cpu (struct cpuif)
    o um campo mipdr e atualizar este campo na função cpu_arch_init(). Desta forma evitamos
    estar a fazer a conversão de cpuid para mpidr sempre que precisamos do mpidr.

    NOTA: Este ficheiro pode ser eliminado uma vez que só contém a função platform_arch_cpuid_to_mpidr()
*/
//__attribute__((weak))
// unsigned long platform_arch_cpuid_to_mpidr(const struct platform* plat, cpuid_t cpuid)
// {
//     if (cpuid > plat->cpu_num) {
//         return ~(~MPIDR_RES1 & MPIDR_RES0_MSK); // return an invlid mpidr by inverting res bits
//     }

//     unsigned long mpidr = 0;
//     bool found = false;
//     //unsigned long cluster_shift = (plat->arch.affinity_lvls-1) * MPIDR_AFFINITY_BITS;
//     //unsigned long cpuid_shift = (plat->arch.affinity_lvls-2) * MPIDR_AFFINITY_BITS;

//     if (plat->arch.clusters.num > 0) {
//         for (size_t i = 0, j = 0; i < plat->arch.clusters.num; i++) {
//             if (cpuid < (j + plat->arch.clusters.core_num[i])) {
//                 //AFF_LVL = 3 => mpidr = (i << 16) | (((cpuid - j) << 8) & 0xff00);
//                 unsigned long res = 0;
//                 if (cpuid == 4) {
//                     cpuid += 2;
//                 }
//                 else 
//                     res = (cpuid - j);
//                 mpidr = (i << 16) | ((res & 0xff) << 8);
//                 //mpidr = (i << cluster_shift) | (((cpuid - j) << cpuid_shift) & (0x00ff << cpuid_shift));
//                 found = true;
//                 break;
//             }

//             j += plat->arch.clusters.core_num[i];
//         }

//         if (!found) {
//             ERROR("failed cpuid to mpidr translation");
//         }
//     } else {
//         /**
//          * No cluster information in configuration. Assume a singl cluster.
//          */
//         //mpidr = cpuid << cpuid_shift;
//         mpidr = cpuid << 8;
//     }

//     mpidr |= MPIDR_RES1;
//     if (plat->cpu_num == 1) {
//         mpidr |= MPIDR_U_BIT;
//     }

//     return mpidr;
// }

unsigned long platform_arch_cpuid_to_mpidr(const struct platform* plat, cpuid_t cpuid)
{
    if (cpuid > plat->cpu_num) {
        return ~(~MPIDR_RES1 & MPIDR_RES0_MSK); // return an invlid mpidr by inverting res bits
    }

    unsigned long mpidr = 0;
    bool found = false;
    //unsigned long cluster_shift = (plat->arch.affinity_lvls-1) * MPIDR_AFFINITY_BITS;
    //unsigned long cpuid_shift = (plat->arch.affinity_lvls-2) * MPIDR_AFFINITY_BITS;

    if (plat->arch.mpidr_table.table) {
        mpidr = plat->arch.mpidr_table.table[cpuid];
    }
    else {
        if (plat->arch.clusters.num > 0) {
            for (size_t i = 0, j = 0; i < plat->arch.clusters.num; i++) {
                if (cpuid < (j + plat->arch.clusters.core_num[i])) {
                    mpidr = (i << 8) | ((cpuid - j) & 0xff);
                    found = true;
                    break;
                }

                j += plat->arch.clusters.core_num[i];
            }
        if (!found) {
            ERROR("failed cpuid to mpidr translation");
        }
    } else {
        /**
         * No cluster information in configuration. Assume a singl cluster.
         */
            mpidr = cpuid;
        }
    }

    mpidr |= MPIDR_RES1;
    if (plat->cpu_num == 1) {
        mpidr |= MPIDR_U_BIT;
    }

    return mpidr;
}

// unsigned long platform_arch_mpidr_to_cpuid(const struct platform* plat, unsigned long mpidr_el1)
// {
//     if (plat->arch.mpidr_table.table) {
//         for (int i = 0; i < plat->cpu_num; i++) {
//             if (plat->arch.mpidr_table.table[i] == mpidr_el1) {
//                 return i;
//             }
//         }
//         return 0xff;
//     }
//     return 0xff;
// }

// unsigned long platform_arch_cpuid_to_mpidr(const struct platform* plat, cpuid_t cpuid)
// {
//     if (cpuid > plat->cpu_num) {
//         return ~(~MPIDR_RES1 & MPIDR_RES0_MSK); // return an invlid mpidr by inverting res bits
//     }

//     unsigned long mpidr = 0;
//     bool found = false;
//     if (plat->arch.clusters.num > 0) {
//         for (size_t i = 0, j = 0; i < plat->arch.clusters.num; i++) {
//             if (cpuid < (j + plat->arch.clusters.core_num[i])) {
//                 mpidr = (i << 8) | ((cpuid - j) & 0xff);
//                 found = true;
//                 break;
//             }

//             j += plat->arch.clusters.core_num[i];
//         }

//         if (!found) {
//             ERROR("failed cpuid to mpidr translation");
//         }
//     } else {
//         /**
//          * No cluster information in configuration. Assume a singl cluster.
//          */
//         mpidr = cpuid;
//     }

//     mpidr |= MPIDR_RES1;
//     if (plat->cpu_num == 1) {
//         mpidr |= MPIDR_U_BIT;
//     }

//     return mpidr;
// }

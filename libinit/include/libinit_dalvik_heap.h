/*
 * Copyright (C) 2021 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef LIBINIT_DALVIK_HEAP_H
#define LIBINIT_DALVIK_HEAP_H

#include <string>

typedef struct dalvik_heap_info {
    std::string heapstartsize;
    std::string heapgrowthlimit;
    std::string heapsize;
    std::string heapminfree;
    std::string heapmaxfree;
    std::string heaptargetutilization;
    std::string foreground-heap-growth-multiplier;
    std::string usejit;
    std::string jitmaxsize;
    std::string jitinitialsize;
    std::string jitthreshold;
    std::string madvise.vdexfile.size;
    std::string madvise.odexfile.size;
    std::string usap_pool_enabled;
    std::string usap_pool_size_min;
    std::string usap_pool_size_max;
    std::string usap_refill_threshold;
    std::string usap_pool_refill_delay_ms;
} dalvik_heap_info_t;

void set_dalvik_heap(void);

#endif // LIBINIT_DALVIK_HEAP_H

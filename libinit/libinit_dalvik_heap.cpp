/*
 * Copyright (C) 2021 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <sys/sysinfo.h>
#include <libinit_utils.h>

#include <libinit_dalvik_heap.h>

#define HEAPSTARTSIZE_PROP "dalvik.vm.heapstartsize"
#define HEAPGROWTHLIMIT_PROP "dalvik.vm.heapgrowthlimit"
#define HEAPSIZE_PROP "dalvik.vm.heapsize"
#define HEAPMINFREE_PROP "dalvik.vm.heapminfree"
#define HEAPMAXFREE_PROP "dalvik.vm.heapmaxfree"
#define HEAPTARGETUTILIZATION_PROP "dalvik.vm.heaptargetutilization"
#define FOREGROUND_HEAP_GROWTH_MULTIPLIER_PROP "dalvik.vm.foreground-heap-growth-multiplier"
#define USEJIT_PROP "dalvik.vm.usejit"
#define JITMAXSIZE_PROP "dalvik.vm.jitmaxsize"
#define JITINITIALSIZE_PROP "dalvik.vm.jitinitialsize"
#define JITTHRESHOLD_PROP "dalvik.vm.jitthreshold"
#define MADVISE_VDEXFILE_SIZE_PROP "dalvik.vm.madvise.vdexfile.size"
#define MADVISE_ODEXFILE_SIZE_PROP "dalvik.vm.madvise.odexfile.size"
#define USAP_POOL_ENABLED_PROP "dalvik.vm.usap_pool_enabled"
#define USAP_POOL_SIZE_MIN_PROP "dalvik.vm.usap_pool_size_min"
#define USAP_POOL_SIZE_MAX_PROP "dalvik.vm.usap_pool_size_max"
#define USAP_REFILL_THRESHOLD_PROP "dalvik.vm.usap_refill_threshold"
#define USAP_REFILL_DELAY_MS_PROP "dalvik.vm.usap_pool_refill_delay_ms"

#define GB(b) (b * 1024ull * 1024 * 1024)

static const dalvik_heap_info_t dalvik_heap_info_6144 = {
    .heapstartsize = "16m",
    .heapgrowthlimit = "256m",
    .heapsize = "512m",
    .heapminfree = "8m",
    .heapmaxfree = "32m",
    .heaptargetutilization = "0.5",
};

static const dalvik_heap_info_t dalvik_heap_info_4096 = {
    .heapstartsize = "8m",
    .heapgrowthlimit = "192m",
    .heapsize = "512m",
    .heapminfree = "8m",
    .heapmaxfree = "16m",
    .heaptargetutilization = "0.6",
};

void set_dalvik_heap() {
    struct sysinfo sys;
    const dalvik_heap_info_t *dhi;

    sysinfo(&sys);

    if (sys.totalram > GB(5))
        dhi = &dalvik_heap_info_6144;
    else if (sys.totalram > GB(3))
        dhi = &dalvik_heap_info_4096;

    property_override(HEAPSTARTSIZE_PROP, dhi->heapstartsize);
    property_override(HEAPGROWTHLIMIT_PROP, dhi->heapgrowthlimit);
    property_override(HEAPSIZE_PROP, dhi->heapsize);
    property_override(HEAPTARGETUTILIZATION_PROP, dhi->heaptargetutilization);
    property_override(HEAPMINFREE_PROP, dhi->heapminfree);
    property_override(HEAPMAXFREE_PROP, dhi->heapmaxfree);
    property_override(FOREGROUND_HEAP_GROWTH_MULTIPLIER_PROP, dhi->foreground-heap-growth-multiplier);
    property_override(USEJIT_PROP, dhi->usejit);
    property_override(JITMAXSIZE_PROP, dhi->jitmaxsize);
    property_override(JITINITIALSIZE_PROP, dhi->jitinitialsize);
    property_override(JITTHRESHOLD_PROP, dhi->jitthreshold);
    property_override(MADVISE_VDEXFILE_SIZE_PROP, dhi->madvise.vdexfile.size);
    property_override(MADVISE_ODEXFILE_SIZE_PROP, dhi->madvise.odexfile.size);
    property_override(USAP_POOL_ENABLED_PROP, dhi->usap_pool_enabled);
    property_override(USAP_POOL_SIZE_MIN_PROP, dhi->usap_pool_size_min);
    property_override(USAP_POOL_SIZE_MAX_PROP, dhi->usap_pool_size_max);
    property_override(USAP_REFILL_THRESHOLD_PROP, dhi->usap_refill_threshold);
    property_override(USAP_REFILL_DELAY_MS_PROP, dhi->usap_pool_refill_delay_ms);
}

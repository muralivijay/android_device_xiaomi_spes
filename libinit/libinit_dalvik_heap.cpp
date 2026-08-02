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
#define MADVISE_VDEXFILE_SIZE_PROP "dalvik.vm.madvise.vdexfile.size"
#define MADVISE_ODEXFILE_SIZE_PROP "dalvik.vm.madvise.odexfile.size"
#define MADVISE_ARTFILE_SIZE_PROP "dalvik.vm.madvise.artfile.size"

#define GB(b) (b * 1024ull * 1024 * 1024)

static const dalvik_heap_info_t dalvik_heap_info_8192 = {
    .heapstartsize = "16m",
    .heapgrowthlimit = "256m",
    .heapsize = "512m",
    .heapminfree = "8m",
    .heapmaxfree = "32m",
    .heaptargetutilization = "0.5",
    .madvise_vdexfile_size = "31457280",
    .madvise_odexfile_size = "31457280",
    .madvise_artfile_size = "0",
};

static const dalvik_heap_info_t dalvik_heap_info_6144 = {
    .heapstartsize = "16m",
    .heapgrowthlimit = "256m",
    .heapsize = "512m",
    .heapminfree = "8m",
    .heapmaxfree = "32m",
    .heaptargetutilization = "0.5",
    .madvise_vdexfile_size = "31457280",
    .madvise_odexfile_size = "31457280",
    .madvise_artfile_size = "0",
};

static const dalvik_heap_info_t dalvik_heap_info_4096 = {
    .heapstartsize = "8m",
    .heapgrowthlimit = "192m",
    .heaptargetutilization = "0.6",
    .heapsize = "512m",
    .heapminfree = "8m",
    .heapmaxfree = "16m",
    .madvise_vdexfile_size = "31457280",
    .madvise_odexfile_size = "31457280",
    .madvise_artfile_size = "0",
};

void set_dalvik_heap() {
    struct sysinfo sys;
    const dalvik_heap_info_t *dhi;

    sysinfo(&sys);

    if (sys.totalram > GB(7))
        dhi = &dalvik_heap_info_8192;
    else if (sys.totalram > GB(5))
        dhi = &dalvik_heap_info_6144;
    else
        dhi = &dalvik_heap_info_4096;

    property_override(HEAPSTARTSIZE_PROP, dhi->heapstartsize);
    property_override(HEAPGROWTHLIMIT_PROP, dhi->heapgrowthlimit);
    property_override(HEAPSIZE_PROP, dhi->heapsize);
    property_override(HEAPTARGETUTILIZATION_PROP, dhi->heaptargetutilization);
    property_override(HEAPMINFREE_PROP, dhi->heapminfree);
    property_override(HEAPMAXFREE_PROP, dhi->heapmaxfree);
    property_override(MADVISE_VDEXFILE_SIZE_PROP, dhi->madvise_vdexfile_size);
    property_override(MADVISE_ODEXFILE_SIZE_PROP, dhi->madvise_odexfile_size);
    property_override(MADVISE_ARTFILE_SIZE_PROP, dhi->madvise_artfile_size);
}

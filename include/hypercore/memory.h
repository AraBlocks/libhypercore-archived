#ifndef HC_MEMORY_H
#define HC_MEMORY_H

#include "common.h"

typedef struct HCMemory HCMemory;

#ifndef HC_MEMORY_PAGE_SIZE
#define HC_MEMORY_PAGE_SIZE (4 * sizeof(HCMemory))
#endif

#ifndef HC_MEMORY_ALIGNMENT
#define HC_MEMORY_ALIGNMENT 16
#endif

#define hc_align(d, a) (((d) + (a - 1)) & ~(a - 1))
#define hc_align_ptr(p, a) (HCvoid *) hc_align((uintptr_t) (p), (uintptr_t) (a))

struct HCMemory {
  HCMemory *next;
  HCubyte *region;
  HCsizei offset;
  HCsizei size;
};


HC_EXPORT HCMemory *
hc_memory_new();

HC_EXPORT HCMemory *
hc_memory_alloc_region(HCsizei size);

HC_EXPORT HCvoid *
hc_memory_alloc(HCMemory *self, HCsizei size);

HC_EXPORT HCMemory *
hc_memory_copy(HCMemory *self, HCMemory *src, HCsizei size);

HC_EXPORT HCvoid
hc_memory_free(HCvoid *self);

HC_EXPORT HCvoid
hc_memory_destroy(HCMemory *self);

#endif

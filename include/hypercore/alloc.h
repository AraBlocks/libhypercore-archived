#ifndef HC_ALLOC_H
#define HC_ALLOC_H

#include "common.h"

HC_EXPORT HCvoid *
hc_alloc(HCsizei size);

HC_EXPORT HCvoid *
hc_calloc(HCsizei size);

HC_EXPORT HCvoid
hc_free(HCvoid *ptr);

HC_EXPORT HCvoid *
hc_memalign(HCsizei alignment, HCsizei size);

#endif

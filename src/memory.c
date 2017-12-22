#include <hypercore/common.h>
#include <hypercore/memory.h>
#include <hypercore/alloc.h>
#include <string.h>
#include <stdlib.h>

HCMemory *
hc_memory_new() {
  return hc_memory_alloc_region(HC_MEMORY_PAGE_SIZE);
}

HCMemory *
hc_memory_alloc_region(HCsizei size) {
  HCMemory	*self = (HCMemory *) hc_calloc(sizeof(HCMemory));
  if (!self) { return 0; }
  HCubyte *region = (HCubyte *) hc_calloc(size *  sizeof(HCubyte));
  if (!region) {
    free(self);
    return 0;
  }
  self->size = size;
  self->region = region;
  return self;
}

void *
hc_memory_alloc(HCMemory *self, HCsizei size) {
  HCMemory *current;
  HCMemory *prev;
  HCMemory *next;
  HCvoid *region = 0;
  HCsizei offset = 0;
  HCsizei asize = 0;
  HCsizei msize = 0;
  HCsizei max = 0;
  HCvoid *ptr = 0;

  if (0 == self || 0 == size) {
    return 0;
  }

  current = self;
  region = self->region;
  offset = self->offset;
  msize = self->size;
  prev = self;
  max = HC_MEMORY_PAGE_SIZE;

  if (0 == region) {
    return 0;
  }

  // small allocs
  do {
    // TODO(werle,vipyne): Make this optional?
    if (prev->region) {
      prev->region = hc_align_ptr(prev->region, HC_ALIGNMENT);
    }
    if (size <= msize - offset) {
      offset += size;
      ptr = current->region + (offset - size);
      break;
    }
    prev = current;
  } while ((current = current->next));

  self->offset = offset;

  if (ptr) {
    return ptr;
  }

  if (size < max) {
    asize = size;
  } else {
    asize = max;
  }

  next = hc_memory_alloc_region(asize);
  if (next) {
    next = hc_align_ptr(next, HC_ALIGNMENT);
    next->offset += size;
    prev->next = next;
    return next->region;
  }

  return 0;
}

HCMemory *
hc_memory_copy(HCMemory *dest, HCMemory *src, HCsizei size) {
  if (dest && src && size) {
    memmove(dest->region, src->region, size);
  }
  return dest;
}

void
hc_memory_free(HCvoid *memory) {
  hc_free(memory);
}

void
hc_memory_destroy(HCMemory *self) {
  HCMemory *prev = self;
  HCMemory *next;
  while (prev) {
    next = prev->next;
    hc_free(prev->region);
    prev->region = 0;
    hc_free(prev);
    prev = 0;
    prev = next;
  }
  prev = 0;
  next = 0;
  self = 0;
}

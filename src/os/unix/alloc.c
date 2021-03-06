#include <hypercore/targets.h>
#include <hypercore/alloc.h>
#include <string.h>
#include <stdlib.h>

#if defined(HC_HAVE_MEMALIGN)
  #if defined(HC_HAVE_MALLOC_H)
    #include <malloc.h>
  #elif defined(HC_HAVE_MALLOC_MALLOC_H)
    #include <malloc/malloc.h>
  #endif
#endif

HCvoid *
hc_alloc(HCsizei size) {
  HCvoid *ptr = 0;
  if (size) {
    ptr = malloc(size);
  }
  return ptr;
}

HCvoid *
hc_calloc(HCsizei size) {
  HCvoid *ptr = 0;
  if (size) {
    ptr = hc_alloc(size);
    if (ptr) {
      (HCvoid) memset(ptr, 0, size);
    }
  }
  return ptr;
}

HCvoid
hc_free(HCvoid *ptr) {
  if (ptr) { free(ptr); }
}

HCvoid *
hc_memalign(HCsizei alignment, HCsizei size) {
  HCvoid *ptr = 0;
#if defined(HC_HAVE_POSIX_MEMALIGNED)
  HCint err = 0;
  if (alignment && size) {
    err = posix_memalign(&ptr, alignment, size);
    if (err) {
      ptr = 0;
      // @TODO(werle): Do something with `err`
    }
  }
#elif defined(HC_HAVE_MEMALIGNED)
  if (alignment && size) {
    ptr = memalign(alignment, size);
  }
#else /** windows */
  (HCvoid) alignment;
  ptr = hc_alloc(size);
#endif
  return ptr;
}

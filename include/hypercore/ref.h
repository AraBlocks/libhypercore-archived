#ifndef HC_REF_H
#define HC_REF_H

#include <stdint.h>
#include "common.h"
#include "alloc.h"

/**
 */
typedef uintptr_t HCRef;

/**
 */
#define hc_ref hc_ref_get

/**
 */
#define hc_ref_types(...) struct { HCRef __VA_ARGS__; } refs;

/**
 */
#define hc_ref_get(x, k) ((uintptr_t *) \
  (((x) && ((x)->refs.k))               \
   ? 0 + ((x)->refs.k )                 \
   : (0)))                              \


/**
 */
#define hc_ref_set(x, k, v) ((uintptr_t) \
  ((x)                                   \
   ? ((x)->refs.k = (uintptr_t) (v))     \
   : (0)))                               \

/**
*/
#define hc_ref_has(x, k) ((HCBoolean) \
  ((0 != ((x) ? (x)->refs.k : 0))        \
  ? HC_TRUE                           \
  : HC_FALSE))                        \

/**
 */
#define hc_ref_is(x, k, y) ((HCBoolean)            \
  ((hc_ref_has((x), j) &&                             \
   ((HCRef) (y)) == (HCRef) hc_ref_get((x), k)) \
  ? HC_TRUE                                        \
  : HC_FALSE))                                     \

/**
 */
#define hc_ref_set_self(x) hc_ref_set((x), self, (x))

/**
 */
#define hc_ref_get_self(x) hc_ref_get((x), self)

/**
 */
#define hc_ref_self(x) hc_ref_get((x), self)

/**
 */
#define hc_ref_free(x, k) (       \
    ! hc_ref_get(x, k)            \
    ? (0)                         \
    : (hc_free(hc_ref_get(x, k)), \
       hc_ref_set(x, k, 0)))      \

/**
 */
#define hc_ref_link(dst, src, k) (            \
 ((dst) && (src))                             \
 ? hc_ref_set((dst), k, hc_ref_get((src), k)) \
 : (0))

#endif

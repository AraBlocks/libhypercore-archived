#ifndef HC_HASH_H
#define HC_HASH_H

#include "memory.h"
#include "ref.h"

typedef struct HCHash HCHash;
typedef struct HCHashIterator HCHashIterator;
typedef HCint HCHashIteratorRange;

struct HCHash {
  hc_ref_types(self, ctx, alloc, internal);
};

struct HCHashIterator {

  /**
   * Internal range offset applied to index, begin, and end ranges
   * where (0 <= (index - begin) <= (end - begin)
   */
  HCHashIteratorRange offset;

  /**
   * Current iteration index (begin <= i <= end).
   */
  HCHashIteratorRange index;
  HCHashIteratorRange begin;
  HCHashIteratorRange end;
  HCBoolean done;

  hc_ref_types(self, alloc, hash);
};

/**
 */
HC_EXPORT HCBoolean
hc_hash_init(HCHash *self);

/**
 */
HC_EXPORT HCBoolean
hc_hash_is_initialized(HCHash *self);

/**
 */
HC_EXPORT HCvoid
hc_hash_destroy(HCHash *self);

/**
 */
HC_EXPORT HCBoolean
hc_hash_set(HCHash *self, const HCchar *key, HCvoid *value);

/**
 */
HC_EXPORT HCvoid *
hc_hash_get(HCHash *self, const HCchar *key);

/**
 */
HC_EXPORT HCBoolean
hc_hash_has(HCHash *self, const HCchar *key);

/**
 */
HC_EXPORT HCBoolean
hc_hash_delete(HCHash *self, const HCchar *key);

/**
 */
HC_EXPORT HCHashIteratorRange
hc_hash_length(HCHash *self);

/**
 */
HC_EXPORT HCHashIteratorRange
hc_hash_copy(HCHash *dest, HCHash *src);

/**
 */
HC_EXPORT HCHashIteratorRange
hc_hash_clear(HCHash *self);

/**
 */
HC_EXPORT HCHashIterator *
hc_hash_iterator_new(HCHash *hash);

/**
 */
HC_EXPORT HCBoolean
hc_hash_iterator_init(HCHashIterator *self);

HC_EXPORT HCvoid
hc_hash_iterator_destroy(HCHashIterator *self);

/**
 */
HC_EXPORT HCHashIteratorRange
hc_hash_iterator_begin(HCHashIterator *self);

HC_EXPORT HCHashIteratorRange
hc_hash_iterator_offset(HCHashIterator *self);

HC_EXPORT HCHashIteratorRange
hc_hash_iterator_next(HCHashIterator *self);

HC_EXPORT HCHashIteratorRange
hc_hash_iterator_prev(HCHashIterator *self);

HC_EXPORT HCBoolean
hc_hash_iterator_range_exists(HCHashIterator *self,
                              HCHashIteratorRange range);

HC_EXPORT HCHashIteratorRange
hc_hash_iterator_end(HCHashIterator *self);

HC_EXPORT HCchar *
hc_hash_iterator_key(HCHashIterator *self);

HC_EXPORT HCvoid *
hc_hash_iterator_value(HCHashIterator *self);

/**
 * Iterates over each key value pair in hash where
 * `self` is the hash, `key` is a variable that
 * holds the value returned by `hc_hash_iterator_key()`,
 * and `value` is a variable that holds the value returned
 * by `hc_hash_iterator_value()`. The proceeding block given
 * will be appended to a loop that is executed for each entry
 * in the hash.
 */
#define hc_hash_each(self, key, value)                          \
  /**                                                           \
   * Enter into iteration if hash given and has entries.        \
   */                                                           \
  if ((self) && hc_hash_length((self)) > 0) for (               \
    HCHashIterator *it = hc_hash_iterator_new((self));          \
    hc_hash_iterator_init(it);                                  \
    hc_hash_iterator_next(it)                                   \
  ) /**                                                         \
     * Destroy iterator and break here. The iteration will      \
     * run forever if we didn't do this since                   \
     * hc_hash_iterator_init() returns something truthy.        \
     */                                                         \
    if (HC_TRUE == it->done) {                                  \
      hc_hash_iterator_destroy(it);                             \
      break;                                                    \
    }                                                           \
    /**                                                         \
     * We leverage `i` and `j` counters and some extra `for`    \
     * loops to create a place for use to declare variables     \
     * scoped to the supplied iteration block that would        \
     * normally be the body of a for/while loop.                \
     */                                                         \
    else for (HCuint i = 0, j = 0; i < 1 && j < 1 ;)            \
      for (HCchar *_key = hc_hash_iterator_key(it); i < 1;)     \
      for (HCchar *_value = hc_hash_iterator_value(it); j < 1;) \
      if (_key && _key[0] && _value && _value[0])               \
        for (key = _key; i < 1; ++i)                            \
        for (value = _value; j < 1; ++j)                        \
          /** block */                                          \


#endif

#include <hypercore/hypercore.h>
#include <describe/describe.h>
#include <stdio.h>

int
main(void) {
  describe("HCMemory") {
    return 0;
    it("should reate new HCMemory region") {
      HCMemory *hc_memory_ptr;
      hc_memory_ptr = hc_memory_new();
      assert(0 != hc_memory_ptr);
    }
    it("should alloc a new HCMemory region") {
      HCMemory *hc_memory_ptr;
      hc_memory_ptr = hc_memory_alloc_region(1000);
      assert(0 != hc_memory_ptr);
      assert(1000 == hc_memory_ptr->size);
    }
    it("should alloc memory") {
      HCMemory *hc_memory_ptr_sm;
      hc_memory_ptr_sm = hc_memory_new();
      // small alloc
      HCvoid *ptr = hc_memory_alloc(hc_memory_ptr_sm, 1000);
      assert(0 != ptr);
      assert(HC_MEMORY_PAGE_SIZE == hc_memory_ptr_sm->size);
      printf("D=%d\n", hc_memory_ptr_sm->offset);
      assert(1000 == hc_memory_ptr_sm->offset);
      assert(ptr == hc_memory_ptr_sm->region);

      // region
      HCMemory *hc_memory_ptr;
      hc_memory_ptr = hc_memory_new();
      HCvoid *ptr_2 = hc_memory_alloc(hc_memory_ptr, 5000);
      assert(0 != ptr_2);
      assert(5000 == hc_memory_ptr->next->size);
      assert(5000 == hc_memory_ptr->next->offset);
      assert(ptr_2 == hc_memory_ptr->next->region);
    }
    it("should copy a HCMemory region") {
      HCMemory *hc_memory_ptr;
      HCMemory *hc_memory_ptr_dest;
      hc_memory_ptr = hc_memory_new();
      hc_memory_ptr_dest = hc_memory_new();
      hc_memory_copy(hc_memory_ptr_dest, hc_memory_ptr, 1000);
      assert(hc_memory_ptr_dest && hc_memory_ptr_dest && 1000);
      assert(sizeof(hc_memory_ptr_dest->region) == sizeof(hc_memory_ptr->region));
      for (int i = 0; i < 1000; ++i) {
        assert((hc_memory_ptr->region)[i] == (hc_memory_ptr_dest->region)[i]);
      }
    }
    it("should free memory") {
      HCMemory *hc_memory_ptr;
      hc_memory_ptr = hc_memory_alloc_region(1000);
      hc_memory_free(hc_memory_ptr->region);
      for (int i = 0; i < 3; ++i) {
        assert(hc_memory_ptr->region[i] == 0);
      }
    }
    it("should destory HCMemory pointers") {
      HCMemory *it = hc_memory_new();
      for (int i = 0; i < 4; ++i) {
        void *i = hc_memory_alloc(it, 4096);
        memset(i, 'v', 4096);
      }
      HCMemory * test;
      assert('v' == it->region[348]);
      assert('v' == it->next->region[1111]);
      hc_memory_destroy(it);
      /*assert(0 == hc_memory_alloc(it, 10));*/
    }
  }

  return assert_failures();
}

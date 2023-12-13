#include "kheap.h"
#include "config.h"
#include "kernel.h"
#include "heap.h"
struct heap kernel_heap;
// 1024*1024 = 1Mb*100/4096 =
struct heap_table kernel_heap_table;

void kheap_init() {
  int total_table_entries = PRACOS_HEAP_SIZE_BYTES / PRACOS_HEAP_BLOCK_SIZE;
  kernel_heap_table.entries = (HEAP_BLOCK_TABLE_ENTRY *)(PRACOS_TABLE_ADDRESS);
  kernel_heap_table.total = total_table_entries;

  void *end = (void *)(PRACOS_HEAP_ADDRESS + PRACOS_HEAP_SIZE_BYTES);
  int res = heap_create(&kernel_heap, (void *)(PRACOS_HEAP_ADDRESS), end,
                        &kernel_heap_table);
  if (res < 0) {
    print("Failed to create heap\n");
  }
}

void* kmalloc(size_t size) {
    return heap_malloc(&kernel_heap, size);
}

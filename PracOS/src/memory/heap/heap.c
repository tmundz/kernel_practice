#include "heap.h"
#include "kernel.h"
#include "memory/memory.h"
#include "status.h"
#include <stdbool.h>

// nmeed this because I am creating a table there could be better ways
static int heap_validate_table(void *ptr, void *end, struct heap_table *table) {
  int res = 0;
  size_t table_size = (size_t)(end - ptr);
  size_t total_blocks = table_size / PRACOS_HEAP_BLOCK_SIZE;
  if (table->total != total_blocks) {
    res = -EINVARG;
    goto out;
  }
out:
  return res;
}

static bool heap_validate_alignment(void *ptr) {
  return ((unsigned int)ptr % PRACOS_HEAP_BLOCK_SIZE) == 0;
}

int heap_create(struct heap *heap, void *ptr, void *end,
                struct heap_table *table) {
  int res = 0;

  if (!heap_validate_alignment(ptr) || !heap_validate_alignment(end)) {
    res = -EINVARG;
    goto out;
  }

  memset(heap, 0, sizeof(struct heap));
  heap->saddr = ptr; // start of the heap
  heap->table = table;

out:
  return res;
}

// Two Sum | Optimal expected time: one-pass hash map
// See ../README.md for reasoning, complexity, and ownership.
#include <stdint.h>
#include <stdlib.h>

typedef struct { int key, index, used; } Entry;
static size_t bucket(int key, size_t capacity) {
    // Mix signed keys as unsigned values, then use a power-of-two table.
    uint32_t x = (uint32_t)key;
    x ^= x >> 16;
    x *= UINT32_C(0x7feb352d);
    x ^= x >> 15;
    return (size_t)x & (capacity - 1);
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    size_t capacity = 1;
    while (capacity < (size_t)numsSize * 2) capacity *= 2;
    Entry* table = calloc(capacity, sizeof(*table));
    *returnSize = 0;
    for (int i = 0; i < numsSize; ++i) {
        int need = target - nums[i]; // Within int for the stated constraints.
        size_t slot = bucket(need, capacity);
        while (table[slot].used && table[slot].key != need)
            slot = (slot + 1) & (capacity - 1);
        if (table[slot].used) {
            int* answer = malloc(2 * sizeof(*answer));
            answer[0] = table[slot].index;
            answer[1] = i;
            *returnSize = 2;
            free(table);
            return answer;
        }
        // Insert after querying so an element cannot match itself.
        slot = bucket(nums[i], capacity);
        while (table[slot].used && table[slot].key != nums[i])
            slot = (slot + 1) & (capacity - 1);
        table[slot] = (Entry){nums[i], i, 1};
    }
    free(table);
    return NULL;
}

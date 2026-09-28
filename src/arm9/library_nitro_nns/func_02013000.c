/* Inserts a freed region in address order and coalesces adjacent free blocks.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/RecycleRegion.c.
 * Original routine: RecycleRegion. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned short u16;

struct NNSiFndExpHeapMBlockHead {
    u16 signature;
    u16 attribute;
    u32 block_size;
    struct NNSiFndExpHeapMBlockHead *prev_block;
    struct NNSiFndExpHeapMBlockHead *next_block;
};

struct NNSiFndExpMBlockList {
    struct NNSiFndExpHeapMBlockHead *head;
    struct NNSiFndExpHeapMBlockHead *tail;
};

struct NNSiFndExpHeapHead {
    struct NNSiFndExpMBlockList free_list;
    struct NNSiFndExpMBlockList used_list;
    u16 group_id;
    u16 feature;
};

struct NNSiMemRegion {
    void *start;
    void *end;
};

extern struct NNSiFndExpHeapMBlockHead *RemoveMBlock(
    struct NNSiFndExpMBlockList *list,
    struct NNSiFndExpHeapMBlockHead *block);
extern struct NNSiFndExpHeapMBlockHead *InitMBlock(
    const struct NNSiMemRegion *region,
    u16 signature);
extern struct NNSiFndExpHeapMBlockHead *InsertMBlock(
    struct NNSiFndExpMBlockList *list,
    struct NNSiFndExpHeapMBlockHead *target,
    struct NNSiFndExpHeapMBlockHead *previous);

static inline void *GetMemoryForBlock(struct NNSiFndExpHeapMBlockHead *block)
{
    return (char *)block + sizeof(struct NNSiFndExpHeapMBlockHead);
}

static inline void *GetBlockEnd(struct NNSiFndExpHeapMBlockHead *block)
{
    return (void *)((u32)GetMemoryForBlock(block) + block->block_size);
}

static inline u32 GetOffsetFromPointers(const void *start, const void *end)
{
    return (u32)end - (u32)start;
}

s32 RecycleExpandedHeapRegion_02013000(
    struct NNSiFndExpHeapHead *expHeapHead,
    const struct NNSiMemRegion *region)
{
    struct NNSiFndExpHeapMBlockHead *previousFreeBlock = 0;
    struct NNSiMemRegion freeRegion = *region;
    struct NNSiFndExpHeapMBlockHead *block;

    for (block = expHeapHead->free_list.head; block; block = block->next_block) {
        if (block < (struct NNSiFndExpHeapMBlockHead *)region->start) {
            previousFreeBlock = block;
            continue;
        }
        if (block == region->end) {
            freeRegion.end = GetBlockEnd(block);
            RemoveMBlock(&expHeapHead->free_list, block);
        }
        break;
    }

    if (previousFreeBlock && GetBlockEnd(previousFreeBlock) == region->start) {
        freeRegion.start = previousFreeBlock;
        previousFreeBlock = RemoveMBlock(&expHeapHead->free_list, previousFreeBlock);
    }

    if (GetOffsetFromPointers(freeRegion.start, freeRegion.end) <
        sizeof(struct NNSiFndExpHeapMBlockHead)) {
        return 0;
    }

    InsertMBlock(
        &expHeapHead->free_list,
        InitMBlock(&freeRegion, 0x4652),
        previousFreeBlock);
    return 1;
}

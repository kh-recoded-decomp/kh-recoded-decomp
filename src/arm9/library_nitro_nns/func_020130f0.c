/* Aligns a range and creates an expanded heap when minimum header space is available.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/NNS_FndCreateExpHeapEx.c.
 * Original routine: NNS_FndCreateExpHeapEx. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef unsigned int u32;
typedef unsigned short u16;

struct NNSiFndHeapHead;

extern struct NNSiFndHeapHead *InitExpHeap(
    void *startAddress,
    void *endAddress,
    u16 optionFlag);

static inline void *AddToPointer(void *pointer, u32 value)
{
    return (void *)(value + (u32)pointer);
}

static inline void *RoundDownPointer(void *pointer, u32 alignment)
{
    return (void *)((u32)pointer & ~(alignment - 1));
}

static inline void *RoundUpPointer(void *pointer, u32 alignment)
{
    return (void *)(((u32)pointer + (alignment - 1)) & ~(alignment - 1));
}

static inline u32 GetOffsetFromPointers(const void *start, const void *end)
{
    return (u32)end - (u32)start;
}

struct NNSiFndHeapHead *CreateExpandedHeap_020130f0(
    void *startAddress,
    u32 size,
    u16 optionFlag)
{
    void *endAddress = RoundDownPointer(AddToPointer(startAddress, size), 4);
    startAddress = RoundUpPointer(startAddress, 4);
    if ((u32)startAddress > (u32)endAddress ||
        GetOffsetFromPointers(startAddress, endAddress) < 0x4c) {
        return 0;
    }
    return InitExpHeap(startAddress, endAddress, optionFlag);
}

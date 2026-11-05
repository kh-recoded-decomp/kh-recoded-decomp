#include "src/overlays/ov027/PackedResource.h"

u16 *FormatPackedWideText(const PackedResourceView *view, s32 index,
                          u16 *dest, u32 capacity, ...)
{
    PackedWideFormatArgs args;

    /* Preserve the recovered DS ABI: four fixed register arguments, then
     * stack argument words. A host port must use its own va_start/va_list.
     */
    args = (char *)(((u32)&capacity & ~3U) + 4);
    VFormatPackedWideText(view, index, dest, capacity, args);
    return dest;
}

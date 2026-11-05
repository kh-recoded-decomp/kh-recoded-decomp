#include "src/overlays/ov027/PackedResource.h"

extern int Text_VSNPrintfWide(u16 *dest, u32 capacity, const u16 *format,
                              PackedWideFormatArgs args);

u16 *VFormatPackedWideText(const PackedResourceView *view, s32 index,
                           u16 *dest, u32 capacity, PackedWideFormatArgs args)
{
    Text_VSNPrintfWide(dest, capacity, GetPackedFileEntry(view, index), args);
    return dest;
}

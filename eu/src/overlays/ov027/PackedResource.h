#ifndef EU_PACKED_RESOURCE_H
#define EU_PACKED_RESOURCE_H

#include "nitro/types.h"

typedef struct PackedResourceHeader {
    u32 payloadOffset;
    u32 count;
} PackedResourceHeader;

typedef struct PackedResourceView {
    void *file; /* Owning buffer pointer; loader interprets its header. */
    u32 count;
    u8 *payload;
} PackedResourceView;

typedef char PackedResourceHeaderSizeCheck[sizeof(PackedResourceHeader) == 8 ? 1 : -1];
typedef char PackedResourceViewSizeCheck[sizeof(PackedResourceView) == 12 ? 1 : -1];

/* Native DS argument-word stream, not a portable C va_list. */
typedef char *PackedWideFormatArgs;

/* fileOrPath is the existing 32-bit DS encoded file ID/path-address word. */
void LoadPackedFileView(PackedResourceView *view, u32 fileOrPath, BOOL fromTail);
/* Borrowed generic payload; its encoding/type is determined by its consumer. */
void *GetPackedFileEntry(const PackedResourceView *view, s32 index);
/* Capacity counts 16-bit units, including space for termination. Both
 * wrappers return dest and discard the underlying formatter's length result.
 */
u16 *FormatPackedWideText(const PackedResourceView *view, s32 index,
                          u16 *dest, u32 capacity, ...);
u16 *VFormatPackedWideText(const PackedResourceView *view, s32 index,
                           u16 *dest, u32 capacity, PackedWideFormatArgs args);

#endif

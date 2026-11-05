#ifndef EU_INDEXED_RECORD_STATE_H
#define EU_INDEXED_RECORD_STATE_H

#include "nitro/types.h"

/* DS memory view with the observed 0x8c record stride. The bytes beginning at
 * 0x18 contain the SDK animation/controller; their complete type is not
 * recovered here. A host implementation needs its native SDK replacement.
 */
typedef struct IndexedRecordStateView {
    u8 unknown00[0x18];
    u8 animationAndUnknown18[0x74 - 0x18];
    s32 mode;
    u8 unknown78[4];
    u32 flags;
    u8 unknown80[0x8c - 0x80];
} IndexedRecordStateView;

enum { INDEXED_RECORD_ANIMATION_OFFSET = 0x18 };

typedef char IndexedRecordStrideCheck[sizeof(IndexedRecordStateView) == 0x8c ? 1 : -1];

int GetIndexedRecordAnimationFrame(const IndexedRecordStateView *records, int index);
void SetIndexedRecordAnimationFrame(IndexedRecordStateView *records, int index, int frame);
void SetIndexedRecordMode(IndexedRecordStateView *records, int index, int mode);
void IndexedRecord_ClearActive(IndexedRecordStateView *records, int index);
/* Native word return: the base address for a negative index, otherwise the
 * updated flags. Widget wrappers discard it; it is not a boolean success API.
 */
int IndexedRecord_SetActive(IndexedRecordStateView *records, int index);

#endif

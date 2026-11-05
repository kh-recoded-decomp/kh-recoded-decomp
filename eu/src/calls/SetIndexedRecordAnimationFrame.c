#include "src/indexed_records/IndexedRecordState.h"

struct NNSG2dCellAnimation;
extern void NNS_G2dSetCellAnimationCurrentFrame(struct NNSG2dCellAnimation *animation, s32 frame);

void SetIndexedRecordAnimationFrame(IndexedRecordStateView *records, int index, int frame)
{
    if (index < 0) {
        return;
    }
    NNS_G2dSetCellAnimationCurrentFrame(
        (struct NNSG2dCellAnimation *)((u8 *)records +
            INDEXED_RECORD_ANIMATION_OFFSET + index * sizeof(*records)), frame);
}

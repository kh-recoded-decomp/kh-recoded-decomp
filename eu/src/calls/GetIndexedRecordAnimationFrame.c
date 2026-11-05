#include "src/indexed_records/IndexedRecordState.h"

struct NNSG2dAnimController;
extern u16 NNS_G2dGetAnimCtrlCurrentFrame(const struct NNSG2dAnimController *controller);

int GetIndexedRecordAnimationFrame(const IndexedRecordStateView *records, int index)
{
    if (index < 0) {
        return 0;
    }
    return NNS_G2dGetAnimCtrlCurrentFrame(
        (const struct NNSG2dAnimController *)((const u8 *)records +
            INDEXED_RECORD_ANIMATION_OFFSET + index * sizeof(*records)));
}

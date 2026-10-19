#ifndef KH_RECODED_RECORD_SELECTION_VIEW_H
#define KH_RECODED_RECORD_SELECTION_VIEW_H

#include "nitro/types.h"
#include "src/overlays/ov027/WidgetPosition.h"

enum {
    RECORD_SELECTION_GROUP_COUNT = 22,
    RECORD_SELECTION_GROUP_CAPACITY = 16
};

typedef struct RecordSelectionView {
    WidgetPoint position;
    WidgetPoint offset;
    WidgetPoint scale;
    void *selection;
    s32 recordIds[RECORD_SELECTION_GROUP_COUNT];
    u8 objSlots[RECORD_SELECTION_GROUP_COUNT][RECORD_SELECTION_GROUP_CAPACITY];
    u8 recordSlots[RECORD_SELECTION_GROUP_COUNT][RECORD_SELECTION_GROUP_CAPACITY];
    u8 priorities[RECORD_SELECTION_GROUP_COUNT][RECORD_SELECTION_GROUP_CAPACITY];
    u8 counts[RECORD_SELECTION_GROUP_COUNT];
    u8 basePriority;
    struct {
        u8 mode : 2;
        u8 flag2 : 1;
        u8 visible : 1;
        u8 flag4 : 1;
        u8 flag5 : 1;
        u8 flag6 : 1;
        u8 flag7 : 1;
    } flags;
} RecordSelectionView;

typedef char RecordSelectionViewSizeCheck[
    sizeof(RecordSelectionView) == 0x4ac ? 1 : -1];

void BuildSelectionViewRecords(void *manager, RecordSelectionView *view);

#endif

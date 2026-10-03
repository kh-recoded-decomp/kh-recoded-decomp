#include "nitro/types.h"

typedef struct ItemRecord {
    u16 active;
    u16 pad_02;
    u16 recordIndex;
} ItemRecord;

typedef struct ItemPicker {
    u8 pad_0000[0xc];
    u8 keepRecord;
    u8 pad_000d[0x3c18 - 0xd];
    ItemRecord *records[1];
    u8 pad_3c1c[0x4d86 - 0x3c1c];
    s16 selected;
    u8 pad_4d88[0x7f9c - 0x4d88];
    int state;
} ItemPicker;

extern void ReleaseRecordEntry_02029388(int index);
extern BOOL ClearBg1AndRedraw_020ceae8(ItemPicker *picker);

void DiscardSelectedItem_020ce588(ItemPicker *picker)
{
    if (picker->keepRecord == 0) {
        ItemRecord *record = picker->records[picker->selected];
        record->active = 0;
        ReleaseRecordEntry_02029388(record->recordIndex);
    }
    picker->state = 4;
    ClearBg1AndRedraw_020ceae8(picker);
}
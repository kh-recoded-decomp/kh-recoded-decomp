#include "nitro/types.h"

typedef struct FieldMenu {
    u8 pad_000[0xd8];
    s32 listedCount;
} FieldMenu;

typedef struct FieldSelectionState {
    u8 pad_0000[0x2878];
    u32 lowFlags : 9;
    u32 alternateSet : 1;
    u32 highFlags : 22;
} FieldSelectionState;

extern FieldSelectionState *data_0205fe0c;
extern void *FindLoadedElementById(void *tracker, u32 id);
extern void SetTagRecordArmed(void *tracker, void *record, BOOL armed);
extern void *FindActiveRecordById(void *tracker, u16 id);
extern void InvokeCallback40(void *tracker, void *record);

static inline int SetSelectionTagArmed(void *tracker, u32 id, BOOL armed)
{
    void *record = FindLoadedElementById(tracker, id);
    SetTagRecordArmed(tracker, record, armed);
    return id;
}

void UpdateFieldMenuSelectionTags(FieldMenu *menu, void *tracker, int mode)
{
    int selected = -1;
    int firstId;
    int secondId;

    firstId = SetSelectionTagArmed(tracker, 10, FALSE);
    SetSelectionTagArmed(tracker, 11, FALSE);
    secondId = SetSelectionTagArmed(tracker, 12, FALSE);
    SetSelectionTagArmed(tracker, 17, FALSE);
    SetSelectionTagArmed(tracker, 18, FALSE);
    InvokeCallback40(tracker, FindActiveRecordById(tracker, 0x55));
    if (mode == 2) {
        selected = 18;
    } else if (menu->listedCount > 0) {
        if (data_0205fe0c->alternateSet == 1) {
            if (mode != 1) {
                firstId = 11;
            }
            selected = firstId;
        } else {
            if (mode != 1) {
                secondId = 17;
            }
            selected = secondId;
        }
    }
    if (selected >= 0) {
        SetSelectionTagArmed(tracker, (u16)selected, TRUE);
    }
}

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TouchSample {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TouchSample;

typedef struct BoardState {
    char pad0000[8];
    void *widget;
    char pad000c[0x28 - 0xc];
    char animSet[0x74 - 0x28];
    char objectSet[0x64f4 - 0x74];
    int updated;
    char pad64f8[0x6558 - 0x64f8];
    s16 originX;
    s16 originY;
    int markerSlots[4];
    int cellIds[18];
    int itemSlots[32];
    int nodeIds[20];
    int digitsA[10];
    int digitsB[10];
    char pad66d4[4];
    int goalSlots[2];
    int useChannel;
    int goalShown;
    int menuShown;
    int showTutorial;
    TouchSample prevTouch;
    s8 shownItems[6];
} BoardState;

typedef struct BoardCursor {
    char pad00[0x10];
    s16 score;
    s16 moves;
    char pad14[0x24 - 0x14];
    u8 progress;
    u8 goal;
    char pad26[2];
    s8 nodeIndex;
    char pad29[0x31 - 0x29];
    s8 slotValues[6];
    s8 directions[0x55 - 0x37];
    s8 index;
    s8 items[6];
    char pad5c[0x5f - 0x5c];
    u8 rareMask;
    char pad60[0x74 - 0x60];
    int bonusActive;
    char pad78[0x80 - 0x78];
    int visible;
    char pad84[0x88 - 0x84];
    int finished;
} BoardCursor;

typedef struct BoardGlobals {
    BoardState *state;
    int unk04;
    BoardCursor *cursor;
} BoardGlobals;

typedef struct CellOffset {
    int x;
    int y;
} CellOffset;

typedef struct EventTargetInfo {
    u16 id;
    u16 isAlt : 1;
    u16 bits1 : 3;
    u16 hidden : 1;
    u16 bits5 : 11;
    char pad04[4];
    VecFx32 pos;
    char pad14[0x24 - 0x14];
} EventTargetInfo;

typedef struct NodeObject {
    char pad00[0x40];
    VecFx32 offset;
} NodeObject;

extern BoardGlobals data_ov024_020b7520;
extern CellOffset data_ov024_020b7384[];

extern void func_0204f378(void *manager, int slot, int value);
extern void func_0204f13c(void *manager, int slot, void *pos);
extern void SetEntryRotation_0204f308(void *manager, int slot, u16 rotation);
extern int func_ov001_0206dc38(void);
extern void *func_ov001_0206dc4c(int index);
extern u16 GetBiasAdjustedField_0206dc80(int index);
extern void GetCursorScreenPos_020b7288(fx32 *pos, void *offset);
extern void ApplyDirectionOffset_020b7228(fx32 *pos, VecFx32 *offset, int direction);
extern void *func_ov001_02087928(void);
extern void *func_ov001_02087944(void *event);
extern BOOL GetStageEventTargetInfo_02087960(void *event, EventTargetInfo *info);
extern NodeObject *func_ov001_0207f038(int kind, int value);
extern void DrawWidgetNumber_020b5de4(void *manager, int widgetId, int layer, int value, int spacing, int *slots, BOOL reset);
extern BOOL CanOpenFieldMenu_020735d8(void);
extern BOOL func_ov001_0207b5f4(void);
extern void *FindWidgetById_020b90a4(void *manager, int widgetId);
extern void SetEntrySlotsVisible_020b9580(void *manager, void *widget, int visible);
extern void CopySourceBlock_020b9f7c(TouchSample *sample);
extern void func_ov001_0207b6b4(void);
extern void RequestPanelModeWithStyle2_0207b320(int value);
extern void PlaySoundEffect_0204d924(int channel, int sound);
extern void func_ov001_0207b6c4(void);
extern void func_01ff89a8(const void *src, void *dest, int size);
extern void *FindActiveRecordById_020b8184(void *animSet, u16 id);
extern void func_ov027_020b8284(void *animSet, void *record, u8 sequence);
extern void TagTracker_InvokeCallback_020b8210(void *animSet, void *record);
extern void func_ov024_020b6bb0(void);
extern void FlushDirtyTileTableRows_020b9e60(void *widget);

int UpdateBoardScreen_020b6df4(void)
{
    EventTargetInfo info;
    fx32 pos[2];
    fx32 goalPos[2];
    TouchSample touch;
    BoardCursor *cursor;
    BoardState *state;
    NodeObject *node;
    void *event;
    int i;
    int count;
    int sequence;
    int goalIndex;

    for (i = 0; i < 2; i++) {
        func_0204f378(data_ov024_020b7520.state->objectSet, data_ov024_020b7520.state->markerSlots[i], data_ov024_020b7520.cursor->visible);
        if (data_ov024_020b7520.state->markerSlots[i + 2] != 0) {
            func_0204f378(data_ov024_020b7520.state->objectSet, data_ov024_020b7520.state->markerSlots[i + 2], data_ov024_020b7520.cursor->visible);
        }
    }
    if (data_ov024_020b7520.cursor->visible == 0) {
        goto done;
    }
    if (func_ov001_0206dc38() > 0) {
        GetCursorScreenPos_020b7288(pos, func_ov001_0206dc4c(0));
        func_0204f13c(data_ov024_020b7520.state->objectSet, data_ov024_020b7520.state->markerSlots[0], pos);
        func_0204f13c(data_ov024_020b7520.state->objectSet, data_ov024_020b7520.state->markerSlots[1], pos);
        cursor = data_ov024_020b7520.cursor;
        state = data_ov024_020b7520.state;
        SetEntryRotation_0204f308(state->objectSet, state->markerSlots[0], GetBiasAdjustedField_0206dc80(0) - cursor->directions[cursor->index] * 0x4000);
    }
    for (i = 0; i < 2; i++) {
        if (data_ov024_020b7520.state->markerSlots[i + 2] != 0) {
            GetCursorScreenPos_020b7288(pos, func_ov001_0206dc4c(i + 1));
            func_0204f13c(data_ov024_020b7520.state->objectSet, data_ov024_020b7520.state->markerSlots[i + 2], pos);
        }
    }
    event = func_ov001_02087928();
    for (i = 0; i < 32; i++) {
        func_0204f378(data_ov024_020b7520.state->objectSet, data_ov024_020b7520.state->itemSlots[i], 0);
    }
    count = 0;
    while (event != NULL) {
        if (!GetStageEventTargetInfo_02087960(event, &info)) {
            event = func_ov001_02087944(event);
            continue;
        }
        if (info.hidden) {
            event = func_ov001_02087944(event);
            continue;
        }
        GetCursorScreenPos_020b7288(pos, &info.pos);
        if (data_ov024_020b7520.cursor->bonusActive) {
            count = 0x1f;
        } else if (data_ov024_020b7520.cursor->rareMask & (1 << data_ov024_020b7520.cursor->index)) {
            count = 0x1e;
        }
        func_0204f13c(data_ov024_020b7520.state->objectSet, data_ov024_020b7520.state->itemSlots[count], pos);
        func_0204f378(data_ov024_020b7520.state->objectSet, data_ov024_020b7520.state->itemSlots[count], 1);
        count++;
        if (count >= 30) {
            break;
        }
        event = func_ov001_02087944(event);
    }
    if (data_ov024_020b7520.cursor->finished && !data_ov024_020b7520.state->goalShown) {
        goalIndex = 0;
        node = func_ov001_0207f038(0, data_ov024_020b7520.cursor->slotValues[data_ov024_020b7520.cursor->nodeIndex]);
        goalPos[0] = (data_ov024_020b7520.state->originX + data_ov024_020b7384[data_ov024_020b7520.cursor->nodeIndex].x) << 12;
        goalPos[1] = (data_ov024_020b7520.state->originY + data_ov024_020b7384[data_ov024_020b7520.cursor->nodeIndex].y) << 12;
        ApplyDirectionOffset_020b7228(goalPos, &node->offset, data_ov024_020b7520.cursor->directions[data_ov024_020b7520.cursor->nodeIndex]);
        if (data_ov024_020b7520.cursor->progress == data_ov024_020b7520.cursor->goal) {
            goalIndex = 1;
        }
        func_0204f13c(data_ov024_020b7520.state->objectSet, data_ov024_020b7520.state->goalSlots[goalIndex], goalPos);
        if (data_ov024_020b7520.cursor->progress == data_ov024_020b7520.cursor->goal) {
            goalIndex = 1;
        } else {
            goalIndex = 0;
        }
        func_0204f378(data_ov024_020b7520.state->objectSet, data_ov024_020b7520.state->goalSlots[goalIndex], 1);
        data_ov024_020b7520.state->goalShown = 1;
    }
    DrawWidgetNumber_020b5de4(data_ov024_020b7520.state->objectSet, 5, 8, data_ov024_020b7520.cursor->score, 0xd, data_ov024_020b7520.state->digitsA, 0);
    DrawWidgetNumber_020b5de4(data_ov024_020b7520.state->objectSet, 7, 9, data_ov024_020b7520.cursor->moves, 8, data_ov024_020b7520.state->digitsB, 0);
    if (data_ov024_020b7520.state->showTutorial) {
        if (!data_ov024_020b7520.state->menuShown && CanOpenFieldMenu_020735d8() && func_ov001_0207b5f4()) {
            data_ov024_020b7520.state->menuShown = 1;
            SetEntrySlotsVisible_020b9580(data_ov024_020b7520.state->objectSet, FindWidgetById_020b90a4(data_ov024_020b7520.state->objectSet, 8), 1);
        } else if ((data_ov024_020b7520.state->menuShown && !CanOpenFieldMenu_020735d8()) || !func_ov001_0207b5f4()) {
            data_ov024_020b7520.state->menuShown = 0;
            SetEntrySlotsVisible_020b9580(data_ov024_020b7520.state->objectSet, FindWidgetById_020b90a4(data_ov024_020b7520.state->objectSet, 8), 0);
        }
    }
    CopySourceBlock_020b9f7c(&touch);
    if (data_ov024_020b7520.state->menuShown) {
        if (touch.touch == 1) {
            if (data_ov024_020b7520.state->prevTouch.touch == 0 && touch.validity == 0 && touch.x >= 0xc0 && touch.x <= 0xff && touch.y >= 0x8b && touch.y <= 0xab) {
                func_ov001_0207b6b4();
                RequestPanelModeWithStyle2_0207b320(2);
                PlaySoundEffect_0204d924(0, 0x3b);
            }
        } else {
            func_ov001_0207b6c4();
        }
    }
    func_01ff89a8(&touch, &data_ov024_020b7520.state->prevTouch, sizeof(TouchSample));
    for (i = 0; i < 6; i++) {
        s8 item = data_ov024_020b7520.cursor->items[i];
        s8 shown = data_ov024_020b7520.state->shownItems[i];
        if (shown != item) {
            sequence = item == 0 ? 0xe : 0xd;
            func_ov027_020b8284(data_ov024_020b7520.state->animSet, FindActiveRecordById_020b8184(data_ov024_020b7520.state->animSet, i + 0x3e9), sequence);
            TagTracker_InvokeCallback_020b8210(data_ov024_020b7520.state->animSet, FindActiveRecordById_020b8184(data_ov024_020b7520.state->animSet, i + 0x3e9));
            data_ov024_020b7520.state->shownItems[i] = data_ov024_020b7520.cursor->items[i];
        }
    }
done:
    func_ov024_020b6bb0();
    data_ov024_020b7520.state->updated = 1;
    FlushDirtyTileTableRows_020b9e60(data_ov024_020b7520.state->widget);
    return 0;
}

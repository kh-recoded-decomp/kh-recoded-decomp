#include "nitro/types.h"

typedef struct ListEntry {
    u16 unk_0;
    u16 column;
    u32 unk_4;
} ListEntry;

typedef struct ListTable {
    u8 pad_00[8];
    ListEntry entries[1];
} ListTable;

typedef struct ListData {
    u8 pad_00[4];
    ListTable *table;
} ListData;

typedef struct ListView {
    u8 pad_00[4];
    ListData *data;
    u8 pad_08[0x94 - 0x08];
    int scrollX;
    int targetX;
    BOOL scrolling;
    u8 pad_a0[8];
    int selectedIndex;
} ListView;

typedef BOOL (*CompareFunc)(int a, int b);

extern int func_ov001_02064784(void);
extern BOOL func_ov001_020645c8(u32 value);
extern int FindVerticalNeighbor_020c37f0(ListView *list, CompareFunc rejectFunc, CompareFunc closerFunc);
extern int FindHorizontalNeighbor_020c386c(ListView *list, int direction);
extern BOOL IsGreaterOrEqual_020c37c0(int a, int b);
extern BOOL IsGreaterThan_020c37cc(int a, int b);
extern BOOL IsLessOrEqual_020c37d8(int a, int b);
extern BOOL IsLessThan_020c37e4(int a, int b);
extern void SelectListEntry_020c3718(ListView *list, int entryIndex);
extern BOOL func_ov073_020c3788(ListView *list, int entryIndex);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void HandleListCursorInput_020c39f0(ListView *list, u32 input)
{
    ListTable *table = list->data->table;
    int next = -1;
    int position;
    int offset;

    if (func_ov001_02064784() == 0 && func_ov001_020645c8(0x370b)) {
        return;
    }
    if (input & 0x40) {
        next = FindVerticalNeighbor_020c37f0(list, IsGreaterOrEqual_020c37c0, IsGreaterThan_020c37cc);
    } else if (input & 0x80) {
        next = FindVerticalNeighbor_020c37f0(list, IsLessOrEqual_020c37d8, IsLessThan_020c37e4);
    } else if (input & 0x20) {
        next = FindHorizontalNeighbor_020c386c(list, -0x10);
    } else if (input & 0x10) {
        next = FindHorizontalNeighbor_020c386c(list, 0x10);
    }
    if (next >= 0) {
        SelectListEntry_020c3718(list, next);
        offset = (table->entries[list->selectedIndex].column - 2) * 8;
        position = offset + list->scrollX;
        if (position < 0) {
            list->targetX = -offset;
            list->scrolling = TRUE;
        }
        if (position > 0x80) {
            list->targetX = -(offset - 0x80);
            list->scrolling = TRUE;
        }
        PlaySoundEffect_0204d924(0, 0);
    }
    if (input & 1) {
        if (!func_ov073_020c3788(list, list->selectedIndex)) {
            PlaySoundEffect_0204d924(0, 4);
            return;
        }
        PlaySoundEffect_0204d924(0, 0x4d);
    }
}

#include "nitro/types.h"

typedef struct RowEntry {
    u16 value;
    u16 y;
    u32 unk_4;
} RowEntry;

typedef struct RowTable {
    u8 pad_00[8];
    RowEntry entries[1];
} RowTable;

typedef struct RowList {
    u8 pad_00[4];
    RowTable *table;
} RowList;

typedef struct ListView {
    void (*onChange)(void);
    RowList *rows;
    u8 pad_08[0x8c];
    int scrollPos;
    int scrollTarget;
    BOOL scrolling;
    u8 pad_a0[8];
    int cursorIndex;
} ListView;

typedef BOOL (*CompareFunc)(int a, int b);

extern int func_ov001_02064784(void);
extern BOOL func_ov001_020645c8(u32 value);
extern int FindVerticalNeighbor_020b6d78(ListView *list, CompareFunc rejectFunc, CompareFunc closerFunc);
extern int func_ov025_020b6df4(ListView *list, int columnOffset);
extern BOOL func_ov025_020b6d48(int a, int b);
extern BOOL func_ov025_020b6d54(int a, int b);
extern BOOL IsLessOrEqual_020b6d60(int a, int b);
extern BOOL IsLessThan_020b6d6c(int a, int b);
extern void func_ov025_020b6ca0(ListView *list, int entryIndex);
extern BOOL TrySelectListEntry_020b6d10(ListView *list, int entryIndex);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void HandleListInput_020b6f78(ListView *list, u32 keys)
{
    RowTable *table = list->rows->table;
    int next = -1;
    int top;
    int offset;

    if (func_ov001_02064784() == 0 && func_ov001_020645c8(0x370b)) {
        return;
    }
    if (keys & 0x40) {
        next = FindVerticalNeighbor_020b6d78(list, func_ov025_020b6d48, func_ov025_020b6d54);
    } else if (keys & 0x80) {
        next = FindVerticalNeighbor_020b6d78(list, IsLessOrEqual_020b6d60, IsLessThan_020b6d6c);
    } else if (keys & 0x20) {
        next = func_ov025_020b6df4(list, -16);
    } else if (keys & 0x10) {
        next = func_ov025_020b6df4(list, 16);
    }
    if (next >= 0) {
        func_ov025_020b6ca0(list, next);
        offset = (table->entries[list->cursorIndex].y - 2) * 8;
        top = offset + list->scrollPos;
        if (top < 0) {
            list->scrollTarget = -offset;
            list->scrolling = TRUE;
        }
        if (top > 0x80) {
            list->scrollTarget = -(offset - 0x80);
            list->scrolling = TRUE;
        }
        PlaySoundEffect_0204d924(0, 0);
    }
    if (keys & 1) {
        if (!TrySelectListEntry_020b6d10(list, list->cursorIndex)) {
            PlaySoundEffect_0204d924(0, 4);
            return;
        }
        PlaySoundEffect_0204d924(0, 0x4d);
    }
}

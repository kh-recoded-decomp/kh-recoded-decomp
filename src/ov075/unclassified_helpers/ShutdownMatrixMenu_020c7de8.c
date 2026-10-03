#include "nitro/types.h"

typedef struct OverlaySelectionRecord {
    u8 pad_00[4];
    u16 count;
} OverlaySelectionRecord;

extern u8 *data_0205fe0c;
extern char data_ov075_020d184c[];
extern u32 data_ov075_020d18e0;

extern void NotifyBothOrOne_02001154(int mode, const char *name, int arg);
extern int ZeroHalfThenFree_0202cd78(void *arg0);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern void DestroyFndObjectList_020014f0(void *list);
extern void DestroyItemPicker_020cffb8(void *picker);
extern void func_02050a44(void);
extern void ReleaseResourceAndDetach_0202eee8(u8 *object);
extern int ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);
extern u8 *func_0205125c(void);
extern void WriteSessionPackedBits_0206459c(int bitOffset, u32 bitCount, u32 value);
extern int func_ov001_020644b0(void);
extern BOOL func_ov001_020645c8(u32 flagIndex);
extern void func_ov001_020645e8(int flagIndex);
extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);
extern void SetupAllSelectionRecords_0204f85c(void);
extern void func_0204fba0(void);
extern void func_ov045_020be6a0(void);
extern void NNS_GfdResetFrmTexVramState_0201391c(void);
extern void func_02013d74(void);

void ShutdownMatrixMenu_020c7de8(u8 *menu)
{
    int storedLevel;
    int currentLevel;
    int rank;
    int storedRank;

    *(u16 *)(data_0205fe0c + 0x2d36) = **(u16 **)(menu + 0x12dd4);
    NotifyBothOrOne_02001154(1, data_ov075_020d184c, 0);
    ZeroHalfThenFree_0202cd78(*(void **)(menu + 0x12db8));
    ZeroHalfThenFree_0202cd78(*(void **)(menu + 0x12db4));
    NNSi_FndFreeFromDefaultHeap_0202a1c4(*(void **)(menu + 0x174e0));
    NNSi_FndFreeFromDefaultHeap_0202a1c4(*(void **)(menu + 0x13ed0));
    NNSi_FndFreeFromDefaultHeap_0202a1c4(*(void **)(menu + 0x12dbc));
    DestroyFndObjectList_020014f0(menu + 0x11f44);
    DestroyFndObjectList_020014f0(menu + 0x11f78);
    DestroyItemPicker_020cffb8(menu + 0x84);
    func_02050a44();
    ReleaseResourceAndDetach_0202eee8(menu + 0x13464);
    ReleaseResourceAndDetach_0202eee8(menu + 0x13568);
    ReleaseResourceAndDetach_0202eee8(menu + 0x13678);
    ReleaseResourceAndDetach_0202eee8(menu + 0x1377c);
    ReleaseResourceAndDetach_0202eee8(menu + 0x138f0);
    ReleaseResourceAndDetach_0202eee8(menu + 0x139f4);
    ReleaseResourceAndDetach_0202eee8(menu + 0x13af8);
    ReleaseResourceAndDetach_0202eee8(menu + 0x13bfc);
    ReleaseResourceAndDetach_0202eee8(menu + 0x13d00);

    storedLevel = ReadSessionPackedBits_02064574(0x35cb, 7);
    currentLevel = func_0205125c()[1];
    storedRank = ReadSessionPackedBits_02064574(0x35c7, 2);
    rank = data_0205fe0c[0x2c62];
    if (storedRank > rank) {
        WriteSessionPackedBits_0206459c(0x35c7, 2, rank);
    }
    if ((s8)data_0205fe0c[0x28d4] == 3 && func_ov001_020644b0() == 400
        && ReadSessionPackedBits_02064574(0x3633, 2) > rank) {
        WriteSessionPackedBits_0206459c(0x3633, 2, rank);
    }
    if (storedLevel < currentLevel) {
        WriteSessionPackedBits_0206459c(0x35cb, 7, currentLevel);
    }
    if (func_ov001_020645c8(0x35c9) && GetOverlaySelectionRecord(0)->count > 1) {
        func_ov001_020645e8(0x35c9);
    }
    SetupAllSelectionRecords_0204f85c();
    func_0204fba0();
    func_ov045_020be6a0();
    *(vu32 *)0x0400001c = 0;
    *(vu16 *)0x04000060 = *(vu16 *)0x04000060 & ~0x3002;
    NNS_GfdResetFrmTexVramState_0201391c();
    func_02013d74();
    data_ov075_020d18e0 = 0;
}

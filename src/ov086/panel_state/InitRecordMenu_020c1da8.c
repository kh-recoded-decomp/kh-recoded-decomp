#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x138];
    int defaultPage;
    u8 pad_13c[0x148 - 0x13c];
    int selectedRow;
    u8 pad_14c[0x1dc - 0x14c];
    void *listEntry;
} Ov086Menu;

extern Ov086Menu *data_ov086_020c3000;
extern void SetSecondaryElementEnabled_020bc084(BOOL enabled);
extern u32 ReadGlobalPackedBits_02027348(u32 bitOffset, u32 bitCount);
extern BOOL AcquireRecordManager_02051c80(void);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern void func_ov086_020c0e4c(void);
extern void func_ov086_020c1024(Ov086Menu *menu);
extern void func_ov086_020c0f08(Ov086Menu *menu);
extern void func_ov086_020c1ba8(Ov086Menu *menu);
extern void func_ov086_020c1078(Ov086Menu *menu);
extern void func_ov086_020c080c(Ov086Menu *menu);
extern void *AllocateListEntry_020bc6b0(void *callback);
extern BOOL func_ov086_020beaa0(void);

BOOL InitRecordMenu_020c1da8(Ov086Menu *menu)
{
    SetSecondaryElementEnabled_020bc084(FALSE);
    menu->defaultPage = ReadGlobalPackedBits_02027348(0x330b, 10) / 100 - 1;
    AcquireRecordManager_02051c80();
    AcquireRecordSlot_02051d3c(0, 0);
    data_ov086_020c3000 = menu;
    menu->selectedRow = -1;
    func_ov086_020c0e4c();
    func_ov086_020c1024(menu);
    func_ov086_020c0f08(menu);
    func_ov086_020c1ba8(menu);
    func_ov086_020c1078(menu);
    func_ov086_020c080c(menu);
    menu->listEntry = AllocateListEntry_020bc6b0(func_ov086_020beaa0);
    return TRUE;
}

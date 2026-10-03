#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
} MovieState;

typedef struct {
    u8 pad_00[0x6f];
    u8 releasePxi;
} MovieConfig;

extern struct { MovieConfig *config; MovieState *state; } contextData_020c0060;
extern BOOL UpdateMenuItemLoading_02067750(void);
extern void func_ov001_020687b8(void);
extern void HighlightSelectedMenuPanels_0206781c(void);
extern void InvokeSceneCallback_020677fc(void);
extern int func_ov001_02067ed4(void);
extern int GetSlotEntryValue_02068000(int index);
extern int GetMenuItemValue_0206802c(int index);
extern void SetCachedSoundParams_0204dcec(u32 param1, u32 param2, u16 param3);
extern void InvokeListNodeCallbacks_0207eff0(void);
extern void func_ov001_02067870(void);
extern u32 func_ov001_020681d4(int index);
extern u32 func_ov001_020681c4(void);
extern void func_ov001_0207b0c0(u32 first, u32 second);
extern void PXI_Init_02088248(int size);
extern void func_ov032_020ba604(void);

int FinishMovieMenuLoad_020ba984(void)
{
    int slotValue;
    u32 entryValue;

    if (UpdateMenuItemLoading_02067750() == FALSE) {
        return -1;
    }
    func_ov001_020687b8();
    HighlightSelectedMenuPanels_0206781c();
    InvokeSceneCallback_020677fc();
    slotValue = GetSlotEntryValue_02068000(func_ov001_02067ed4());
    SetCachedSoundParams_0204dcec(slotValue, GetMenuItemValue_0206802c(func_ov001_02067ed4()), 0x7f);
    InvokeListNodeCallbacks_0207eff0();
    func_ov001_02067870();
    entryValue = func_ov001_020681d4(func_ov001_02067ed4());
    func_ov001_0207b0c0(func_ov001_020681c4(), entryValue);
    if (contextData_020c0060.config->releasePxi == 1) {
        PXI_Init_02088248(0x96000);
    }
    func_ov032_020ba604();
    contextData_020c0060.state->flags |= 0x8000;
    return 5;
}

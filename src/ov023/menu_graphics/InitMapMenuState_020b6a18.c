#include "nitro/types.h"

typedef struct MapMenuState {
    u8 pad_00[0x8];
    void *mapImage;
    void *markerImage;
    u8 pad_10[0x10];
    int mode;
    u8 pad_24[0x18];
    BOOL routeOpen;
    u8 pad_40[0x4];
    void *listener;
} MapMenuState;

extern MapMenuState *data_ov023_020b6f64;
extern char data_ov023_020b6f20[];
extern char data_ov023_020b6f30[];

extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_01ff8830(void *dst, u32 val, u32 size);
extern BOOL func_ov001_020645c8(u32 value);
extern BOOL IsFieldFlag13OrSessionFlagSet_020728e4(void);
extern BOOL IsFieldFlag8Set_020728a4(void);
extern u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);
extern int func_ov001_02064784(void);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *path, int arg1, int arg2);
extern void InitMapScreen_020b5de0(MapMenuState *state);
extern void *AddFieldListener_0207157c(int value);
extern u8 func_ov001_0207b45c(void);
extern void ApplyFormationSlots_020b6d90(int formationType);
extern void RefreshScaledMenuScreen_020b5a80(void);
extern void *UpdateMapMenuState_020b6afc(void);

void *InitMapMenuState_020b6a18(void)
{
    MapMenuState *state = NNSi_FndGetCurrentRootHeap_0202a764();
    data_ov023_020b6f64 = state;
    func_01ff8830(state, 0, 0x7fc4);
    if (func_ov001_020645c8(0x3520) || IsFieldFlag13OrSessionFlagSet_020728e4() || IsFieldFlag8Set_020728a4()) {
        if (func_ov001_020645c8(0x3520) && ReadSessionPackedBits_02064574(0x1a00, 2) == 1 && !func_ov001_02064784()) {
            state->routeOpen = TRUE;
        } else {
            state->routeOpen = FALSE;
        }
    } else {
        state->routeOpen = TRUE;
    }
    state->mode = 1;
    state->mapImage = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov023_020b6f20, 0xe, 0);
    state->markerImage = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov023_020b6f30, 0xe, 0);
    InitMapScreen_020b5de0(state);
    state->listener = AddFieldListener_0207157c((int)RefreshScaledMenuScreen_020b5a80);
    ApplyFormationSlots_020b6d90(func_ov001_0207b45c());
    return UpdateMapMenuState_020b6afc;
}

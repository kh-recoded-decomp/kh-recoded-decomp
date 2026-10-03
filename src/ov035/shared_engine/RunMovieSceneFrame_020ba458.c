#include "nitro/types.h"

typedef int (*SceneStateFunc)(void);

typedef struct SceneWork {
    u8 unknown_00[6];
    u16 flags;
    u8 unknown_08[0x10];
    int state;
    u8 unknown_1c[0x10];
    s16 sideCount;
} SceneWork;

extern SceneWork *data_ov035_020bc4e0;
extern SceneStateFunc data_ov035_020bc478[];
extern void SaveSlotEntriesToBits_02050194(void);
extern int func_ov035_020bae74(void);
extern int func_ov035_020baf88(void);
extern int func_ov035_020baf94(void);
extern u32 GetBoundedEntryField_0206db5c(int index);
extern int func_ov035_020bafc4(int side);
extern int func_ov035_020bb054(int side);
extern int func_ov035_020bb0a0(int side);
extern void func_ov001_0207162c(int side, u16 value, int level, int scaled);
extern BOOL IsHudFlag9Set_02072884(void);
extern void func_ov035_020bc250(int side, u16 level);
extern void func_ov001_02074fa8(int side, u16 level, int mode);
extern void RefreshActiveMenuEntry_02074f7c(int side, u16 level, int mode);
extern void func_ov035_020ba7dc(int paused);
extern void func_ov035_020ba75c(void);

int RunMovieSceneFrame_020ba458(void) {
    int side;
    int result;

    SaveSlotEntriesToBits_02050194();
    do {
        data_ov035_020bc4e0->flags &= 0x7fff;
        result = data_ov035_020bc478[data_ov035_020bc4e0->state]();
        if (result >= 0) {
            data_ov035_020bc4e0->state = result;
        }
    } while (data_ov035_020bc4e0->flags & 0x8000);

    if (func_ov035_020bae74() == 0 && data_ov035_020bc4e0->sideCount > 0) {
        for (side = 0; side < 2; side++) {
            if (side == 0) {
                result = func_ov035_020baf88();
            } else {
                result = func_ov035_020baf94();
            }
            if (result != 0) {
                int value;
                int level;
                GetBoundedEntryField_0206db5c(0);
                value = func_ov035_020bafc4(side + 1);
                level = func_ov035_020bb054(side + 1);
                func_ov001_0207162c(side + 1, value, level, func_ov035_020bb0a0(side + 1));
                if (IsHudFlag9Set_02072884()) {
                    func_ov035_020bc250(side + 1, level);
                    func_ov001_02074fa8(side + 1, level, 7);
                } else {
                    RefreshActiveMenuEntry_02074f7c(side + 1, level, 7);
                }
            }
        }
    }
    if (data_ov035_020bc4e0->flags & 8) {
        func_ov035_020ba7dc(0);
    }
    if (data_ov035_020bc4e0->flags & 4) {
        func_ov035_020ba75c();
    }
    return 0;
}

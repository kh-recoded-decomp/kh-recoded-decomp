#include "nitro/types.h"

extern u32 data_ov035_020bc500;
extern int func_ov001_02063620(void);
extern void PushVramState(void);
extern void LoadMovieClipHeader(void);
extern void func_ov035_020bab4c(void);
extern void CreateMaterialFadeWork(int width, int height, u8 mode);

u32 func_ov035_020ba594(void) {
    if (func_ov001_02063620() != 0) {
        return 0xffffffff;
    }
    PushVramState();
    LoadMovieClipHeader();
    func_ov035_020bab4c();
    CreateMaterialFadeWork((int)*(s16 *)(data_ov035_020bc500 + 0x46),
                        (int)*(s16 *)(data_ov035_020bc500 + 0x48),
                        *(u8 *)(data_ov035_020bc500 + 0x42));
    *(u16 *)(data_ov035_020bc500 + 6) = *(u16 *)(data_ov035_020bc500 + 6) | 0x8000;
    return 1;
}

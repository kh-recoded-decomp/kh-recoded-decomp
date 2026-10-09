#include "nitro/types.h"

extern u32 gMovieContextState;
extern int func_ov001_02063620(void);
extern void PushVramState(void);
extern void LoadMovieClipHeader(void);
extern void InitEventGroupTable(void);
extern void CreateMaterialFadeWork(int width, int height, u8 mode);

u32 func_ov035_020ba594(void) {
    if (func_ov001_02063620() != 0) {
        return 0xffffffff;
    }
    PushVramState();
    LoadMovieClipHeader();
    InitEventGroupTable();
    CreateMaterialFadeWork((int)*(s16 *)(gMovieContextState + 0x46),
                        (int)*(s16 *)(gMovieContextState + 0x48),
                        *(u8 *)(gMovieContextState + 0x42));
    *(u16 *)(gMovieContextState + 6) = *(u16 *)(gMovieContextState + 6) | 0x8000;
    return 1;
}

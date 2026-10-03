#include "nitro/types.h"

extern void MovieScene_FadeInBgPlanes_02064154(void);
extern void MovieScene_FadeOutBgPlanes_02064230(void);
extern void MovieScene_LoadBgChar_02064028(void);
extern void MovieScene_LoadBgScreen_0206409c(void);
extern void MovieScene_LoadSlotBuffer_02064110(void);
extern void MovieScene_SetBgPriority_02064304(void);
extern void func_ov003_020642fc(void);

void (*data_ov003_020650c4[7])(void) = {
    MovieScene_LoadBgChar_02064028,
    MovieScene_LoadBgScreen_0206409c,
    MovieScene_LoadSlotBuffer_02064110,
    MovieScene_FadeInBgPlanes_02064154,
    MovieScene_FadeOutBgPlanes_02064230,
    func_ov003_020642fc,
    MovieScene_SetBgPriority_02064304,
};

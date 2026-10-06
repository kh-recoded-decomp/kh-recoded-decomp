#include "nitro/types.h"

typedef struct Session {
    u8 pad_0000[0x280c];
    u8 overlayWork[0x10];
} Session;

typedef void (*OverlayWorkFunc)(void *work);

extern Session *data_ov001_020a0480;
extern u8 InstallSceneHandlers_020bb288[];

void func_ov001_02062ad8(void) {
    ((OverlayWorkFunc)InstallSceneHandlers_020bb288)(data_ov001_020a0480->overlayWork);
}

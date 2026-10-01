#include "nitro/types.h"

typedef struct Session {
    u8 pad_0000[0x280c];
    u8 overlayWork[0x10];
} Session;

typedef void (*OverlayWorkFunc)(void *work);

extern Session *data_ov001_020a0460;
extern u8 data_ov030_020bb269[];

void func_ov001_02062ad8(void) {
    ((OverlayWorkFunc)data_ov030_020bb269)(data_ov001_020a0460->overlayWork);
}

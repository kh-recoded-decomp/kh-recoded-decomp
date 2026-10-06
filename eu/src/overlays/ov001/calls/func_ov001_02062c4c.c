#include "nitro/types.h"

typedef struct Session {
    u8 pad_0000[0x280c];
    u8 overlayWork[0x10];
} Session;

typedef void (*OverlayWorkFunc)(void *work);

extern Session *data_ov001_020a0480;
extern u8 InitOv038HandlerTable[];

void func_ov001_02062c4c(void) {
    ((OverlayWorkFunc)InitOv038HandlerTable)(data_ov001_020a0480->overlayWork);
}

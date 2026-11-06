#include "nitro/types.h"

typedef struct Session {
    u8 pad_0000[0x280c];
    u8 overlayWork[0x10];
} Session;

typedef void (*OverlayWorkFunc)(void *work);

extern Session *gFieldSessionWork;
extern u8 InstallSceneHandlers[];

void InstallSessionOv028Handlers(void) {
    ((OverlayWorkFunc)InstallSceneHandlers)(gFieldSessionWork->overlayWork);
}

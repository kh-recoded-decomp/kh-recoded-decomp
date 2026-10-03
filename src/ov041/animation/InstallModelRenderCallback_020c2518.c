#include "nitro/types.h"

typedef struct {
    u8 kind;
    u8 pad_001[0x18f];
    u8 renderObj[1];
} ModelActor;

extern void ClearSbcCallback_020188b8(void *renderObj);
extern void RegisterSbcCallback_020188a4(void *renderObj, void (*func)(void *), u8 *addr, u8 cmd, int timing);
extern void func_ov041_020c25cd(void *rs);
extern void func_ov041_020c261d(void *rs);
extern void func_ov041_020c2661(void *rs);
extern void func_ov041_020c2671(void *rs);

void InstallModelRenderCallback_020c2518(ModelActor *actor) {
    switch (actor->kind) {
    case 0xff:
        ClearSbcCallback_020188b8(actor->renderObj);
        RegisterSbcCallback_020188a4(actor->renderObj, func_ov041_020c25cd, NULL, 6, 3);
        break;
    case 0xfd:
        ClearSbcCallback_020188b8(actor->renderObj);
        RegisterSbcCallback_020188a4(actor->renderObj, func_ov041_020c261d, NULL, 6, 3);
        break;
    case 0x12:
    case 0x16:
    case 0x17:
        ClearSbcCallback_020188b8(actor->renderObj);
        RegisterSbcCallback_020188a4(actor->renderObj, func_ov041_020c2661, NULL, 6, 3);
        break;
    case 0xc:
    case 0xfe:
        ClearSbcCallback_020188b8(actor->renderObj);
        RegisterSbcCallback_020188a4(actor->renderObj, func_ov041_020c2671, NULL, 6, 3);
        break;
    }
}

#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u8 handlers[0xac - 0xc];
    int active;
    int stageId;
    u8 modeFlag;
} ModeBlock;

typedef struct {
    u8 pad_000[0x214];
    u32 lowFlags : 11;
    u32 modeFlag : 1;
    u32 highFlags : 20;
    u8 pad_218[4];
    int stageId;
    u8 pad_220[0x2800 - 0x220];
    ModeBlock mode;
} Session;

extern Session *data_ov001_020a0460;
extern void func_ov034_020be548(void *handlers);

void ActivateSubModeHandlers_02062b48(void) {
    Session *session = data_ov001_020a0460;
    ModeBlock *mode = &session->mode;
    mode->active = 1;
    mode->stageId = session->stageId;
    mode->modeFlag = session->modeFlag;
    func_ov034_020be548(mode->handlers);
}

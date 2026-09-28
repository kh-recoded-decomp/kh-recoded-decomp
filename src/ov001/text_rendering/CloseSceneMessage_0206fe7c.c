#include "nitro/types.h"

typedef struct SceneMessage {
    s32 state;
    u8 pad_04[0x24];
    s64 closeTick;
    u8 pad_30[0x38];
    u16 *textBuffer;
    u16 *textCursor;
    u8 pad_70[0x8];
    s32 refreshOnClose;
} SceneMessage;

typedef struct SceneGlobals {
    u32 unk_00;
    void *scene;
} SceneGlobals;

extern SceneGlobals data_ov001_020a04a4;
extern s64 func_02003fd4(void);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern u32 func_ov001_0207b3cc(void);
extern void func_ov001_0206ed30(void *scene);

void CloseSceneMessage_0206fe7c(SceneMessage *message)
{
    message->closeTick = func_02003fd4();
    message->state = 3;
    NNSi_FndFreeFromDefaultHeap_0202a1c4(message->textBuffer);
    message->textBuffer = NULL;
    message->textCursor = NULL;
    if (message->refreshOnClose != 0 && func_ov001_0207b3cc() == 0) {
        func_ov001_0206ed30(data_ov001_020a04a4.scene);
    }
}

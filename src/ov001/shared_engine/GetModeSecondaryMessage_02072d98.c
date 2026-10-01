#include "nitro/types.h"

typedef struct {
    u8 pad[0x2cc];
    u8 messages[4];
} Scene;

typedef struct {
    void *unk0;
    Scene *scene;
} SceneHolder;

extern const u16 *data_ov001_0209ec70[2];
extern SceneHolder data_ov001_020a04a4;
extern const u16 *func_ov027_020ba2a8(void *messages, int index);

const u16 *GetModeSecondaryMessage_02072d98(int mode) {
    const u16 *message = data_ov001_0209ec70[0];
    switch (mode) {
    case 2:
        message = func_ov027_020ba2a8(data_ov001_020a04a4.scene->messages, 0xf);
        break;
    case 3:
        message = func_ov027_020ba2a8(data_ov001_020a04a4.scene->messages, 0x10);
        break;
    }
    return message;
}

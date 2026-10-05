#include "nitro/types.h"

typedef struct SceneMessage {
    u8 data[4];
} SceneMessage;

typedef struct SceneTextOwner {
    u8 pad_000[0x550];
    SceneMessage message;
} SceneTextOwner;

extern BOOL DrawNextTypewriterGlyph_0206feb4(SceneMessage *writer);
extern void CloseSceneMessage_0206fe7c(SceneMessage *message);

void FlushAndCloseSceneMessage_0206fef4(SceneTextOwner *owner)
{
    SceneMessage *message = &owner->message;

    while (DrawNextTypewriterGlyph_0206feb4(message)) {
    }
    CloseSceneMessage_0206fe7c(message);
}

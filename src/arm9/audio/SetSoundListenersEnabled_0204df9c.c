#include "nitro/types.h"

typedef struct SoundListenerNode {
    struct SoundListenerNode *next;
    u8 pad_04[0x10];
    u16 flags;
} SoundListenerNode;

extern u8 *g_soundWork_0206084c;

void SetSoundListenersEnabled_0204df9c(int enabled)
{
    u8 *work = g_soundWork_0206084c;
    SoundListenerNode *node;

    *(u8 *)(work + 0xb47d4) = (u8)enabled;
    node = *(SoundListenerNode **)(work + 0xb471c);

    if (enabled != 0) {
        for (; node != NULL; node = node->next) {
            node->flags |= 4;
        }
    } else {
        for (; node != NULL; node = node->next) {
            node->flags &= 0xfffb;
        }
    }
}

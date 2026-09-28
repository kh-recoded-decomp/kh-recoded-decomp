#include "nitro/types.h"

typedef struct {
    s32 x;
    s32 y;
    u16 *text;
    s32 param;
} PopupMessage;

typedef struct {
    u8 pad_00[0x8c];
    PopupMessage queue[30];
    s32 queueCount;
} PopupManager;

extern PopupManager *g_popupManager_020c373c;
extern int LengthTerminatedHalfwords(const u16 *text);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern u16 *copy_padded_utf16_string_02022a74(u16 *destination, const u16 *source, int unitCount);

void QueuePopupMessage_020c21d0(s32 x, s32 y, const u16 *text, s32 param)
{
    PopupMessage *entry;
    int length;
    u16 *buffer;

    entry = &g_popupManager_020c373c->queue[g_popupManager_020c373c->queueCount];
    entry->x = x;
    entry->y = y;
    entry->param = param;
    if (text != NULL) {
        length = LengthTerminatedHalfwords(text);
        buffer = NNSi_FndAllocFromDefaultHeapEx_0202a19c((LengthTerminatedHalfwords(text) + 1) * 2, -4);
        entry->text = buffer;
        copy_padded_utf16_string_02022a74(buffer, text, length);
        entry->text[length] = 0;
    }
    g_popupManager_020c373c->queueCount++;
}

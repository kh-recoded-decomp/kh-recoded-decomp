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

extern PopupManager *data_ov091_020c375c;
extern int Utf16Length(const u16 *text);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern u16 *Utf16CopyPadded(u16 *destination, const u16 *source, int unitCount);

void QueuePopupMessage(s32 x, s32 y, const u16 *text, s32 param)
{
    PopupMessage *entry;
    int length;
    u16 *buffer;

    entry = &data_ov091_020c375c->queue[data_ov091_020c375c->queueCount];
    entry->x = x;
    entry->y = y;
    entry->param = param;
    if (text != NULL) {
        length = Utf16Length(text);
        buffer = NNS_FndAllocFromDefaultExpHeapEx((Utf16Length(text) + 1) * 2, -4);
        entry->text = buffer;
        Utf16CopyPadded(buffer, text, length);
        entry->text[length] = 0;
    }
    data_ov091_020c375c->queueCount++;
}

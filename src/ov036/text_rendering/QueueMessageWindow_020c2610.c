#include "nitro/types.h"

typedef struct WindowSize {
    s32 width;
    s32 height;
} WindowSize;

typedef struct MessageRequest {
    s32 x;
    s32 y;
    WindowSize *size;
    s32 style;
    u16 *text;
    s32 portraitId;
    s32 portraitPose;
    s32 kind;
} MessageRequest;

typedef struct MessageEntry {
    s32 kind;
    s32 x;
    s32 y;
    s32 width;
    s32 height;
    s32 style;
    u16 *text;
    s32 portraitId;
    s32 portraitPose;
    s32 phase;
} MessageEntry;

typedef struct OverlayWork {
    u8 pad_0000[0x6458];
    s32 phase;
    u8 pad_645c[0x684c - 0x645c];
    MessageEntry messages[2];
    s32 messageCount;
} OverlayWork;

extern OverlayWork *data_ov036_020c3844;
extern int LengthTerminatedHalfwords(u16 *text);
extern u16 *copy_padded_utf16_string_02022a74(u16 *destination, u16 *source, int unitCount);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern void PushTextWindowHistory_020be928(void);

void QueueMessageWindow_020c2610(MessageRequest *request)
{
    MessageEntry *entry;
    u16 *text;
    int length;

    data_ov036_020c3844->phase++;
    data_ov036_020c3844->phase %= 2;
    entry = &data_ov036_020c3844->messages[data_ov036_020c3844->messageCount];
    entry->kind = request->kind;
    entry->x = request->x;
    entry->y = request->y;
    entry->style = request->style;
    entry->text = NULL;
    entry->phase = data_ov036_020c3844->phase;
    if (entry->kind == 1) {
        entry->portraitId = request->portraitId;
        entry->portraitPose = request->portraitPose;
    } else {
        entry->portraitId = 0;
        entry->portraitPose = 0;
    }
    if (request->size != NULL) {
        entry->width = request->size->width;
        entry->height = request->size->height;
    } else {
        entry->width = 0x80;
        entry->height = 0x60;
    }
    text = request->text;
    if (text != NULL) {
        length = LengthTerminatedHalfwords(text);
        entry->text = NNSi_FndAllocFromDefaultHeapEx_0202a19c((LengthTerminatedHalfwords(text) + 1) * 2, -4);
        copy_padded_utf16_string_02022a74(entry->text, request->text, length);
        entry->text[length] = 0;
    }
    data_ov036_020c3844->messageCount++;
    if (entry->kind != 1) {
        PushTextWindowHistory_020be928();
    }
}

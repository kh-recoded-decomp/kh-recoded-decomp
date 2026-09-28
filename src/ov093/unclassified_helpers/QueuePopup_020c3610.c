#include "nitro/types.h"

typedef struct {
    int x;
    int y;
    u16 *text;
    int charBase;
} PopupRequest;

typedef struct {
    u8 pad_00[0x8c];
    PopupRequest queue[30];
    int queueCount;
} PopupWork;

extern PopupWork *g_popupWork_020c50e4;
extern int LengthTerminatedHalfwords(const u16 *text);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern u16 *copy_padded_utf16_string_02022a74(u16 *destination, const u16 *source, int unitCount);

void QueuePopup_020c3610(int x, int y, const u16 *text, int charBase)
{
    PopupRequest *request = &g_popupWork_020c50e4->queue[g_popupWork_020c50e4->queueCount];

    request->x = x;
    request->y = y;
    request->charBase = charBase;
    if (text != NULL) {
        int length = LengthTerminatedHalfwords(text);
        u16 *copy = NNSi_FndAllocFromDefaultHeapEx_0202a19c((LengthTerminatedHalfwords(text) + 1) * 2, -4);

        request->text = copy;
        copy_padded_utf16_string_02022a74(copy, text, length);
        request->text[length] = 0;
    }
    g_popupWork_020c50e4->queueCount++;
}

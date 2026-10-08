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

extern PopupWork *data_ov093_020c5104;
extern int Utf16Length(const u16 *text);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern u16 *Utf16CopyPadded(u16 *destination, const u16 *source, int unitCount);

void QueuePopup(int x, int y, const u16 *text, int charBase)
{
    PopupRequest *request = &data_ov093_020c5104->queue[data_ov093_020c5104->queueCount];

    request->x = x;
    request->y = y;
    request->charBase = charBase;
    if (text != NULL) {
        int length = Utf16Length(text);
        u16 *copy = NNS_FndAllocFromDefaultExpHeapEx((Utf16Length(text) + 1) * 2, -4);

        request->text = copy;
        Utf16CopyPadded(copy, text, length);
        request->text[length] = 0;
    }
    data_ov093_020c5104->queueCount++;
}

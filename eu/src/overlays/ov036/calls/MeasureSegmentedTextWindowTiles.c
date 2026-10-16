#include "src/overlays/ov036/Ov036TextWindowState.h"

extern int Utf16Length(const u16 *text);
extern u16 *Utf16CopyPadded(u16 *destination, const u16 *source, int count);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 bytes, s32 alignment);
extern void NNSi_FndFreeFromDefaultHeap(void *buffer);
extern Ov036TextWindowSize NNSi_G2dFontGetTextRect(const void *font, int horizontalSpacing, int verticalSpacing, const u16 *text);

static inline u16 *CopyWindowText(const u16 *text)
{
    int unitCount = Utf16Length(text);
    u16 *copy = NNS_FndAllocFromDefaultExpHeapEx((Utf16Length(text) + 1) * sizeof(u16), -4);
    Utf16CopyPadded(copy, text, unitCount);
    copy[unitCount] = 0;
    return copy;
}

void MeasureSegmentedTextWindowTiles(Ov036TextWindowSize *outTiles, int screen, const u16 *text, int padX, int padY)
{
    u16 *copy;
    u16 *segments[10];
    int count;
    u16 *cursor;
    void *font;
    int i;
    Ov036TextWindowSize tiles;
    Ov036TextWindowSize measured;

    font = &gTextWindowResourceTable->mainFont;
    if (screen == 1) {
        font = &gTextWindowResourceTable->subFont;
    }
    copy = CopyWindowText(text);
    count = 0;
    if (copy != NULL) {
        segments[count++] = copy;
        for (cursor = copy; *cursor != 0; cursor++) {
            if (*cursor == 3) {
                *cursor++ = 0;
                segments[count] = cursor;
                count += 1;
            }
        }
    }
    int maxWidth = 0;
    int maxHeight = 0;
    for (i = 0; i < count; i++) {
        measured = NNSi_G2dFontGetTextRect(font, 0, 2, segments[i]);
        tiles = measured;
        if (tiles.width < 16) {
            tiles.width = 16;
        }
        tiles.width += padX;
        tiles.height += padY;
        tiles.width = (tiles.width + 7) / 8 < 28 ? (tiles.width + 7) / 8 : 28;
        tiles.height = (tiles.height + 7) / 8;
        if (tiles.width > 30) {
            tiles.width = 30;
        }
        if (tiles.height > 22) {
            tiles.height = 22;
        }
        if (maxWidth < tiles.width) {
            maxWidth = tiles.width;
        }
        if (maxHeight < tiles.height) {
            maxHeight = tiles.height;
        }
    }
    tiles.width = maxWidth;
    tiles.height = maxHeight;
    NNSi_FndFreeFromDefaultHeap(copy);
    *outTiles = tiles;
}

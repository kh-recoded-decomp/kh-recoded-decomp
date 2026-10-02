#include "nitro/types.h"

typedef struct {
    u8 data[0xc];
} DigitGlyph;

typedef struct {
    u8 data[8];
} DigitSprite;

typedef struct {
    u8 pad_000[0x28];
    DigitGlyph frameGlyph;
    DigitGlyph digits[10];
    u8 pad_0ac[0x30];
    DigitGlyph slashGlyph;
    DigitSprite frame;
    u8 pad_0f0[0x24];
    DigitSprite currentTens;
    DigitSprite currentOnes;
    DigitSprite slash;
    DigitSprite maximumTens;
    DigitSprite maximumOnes;
    u32 maximum;
    u32 current;
} CounterDisplay;

extern u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);
extern u32 func_0200d594(u32 value);
extern void func_ov001_0207ca04(DigitSprite *sprite, int scale, DigitGlyph *glyph, int color);

void RefreshCounterDigits_0207c1a8(CounterDisplay *display)
{
    u32 value;

    display->current = func_0200d594(ReadSessionPackedBits_02064574(0x3700, 16));
    func_ov001_0207ca04(&display->frame, 0x1000, &display->frameGlyph, 0x7fff);
    value = display->current;
    func_ov001_0207ca04(&display->currentOnes, 0x1000, &display->digits[value % 10], 0x7fff);
    func_ov001_0207ca04(&display->currentTens, 0x1000, &display->digits[value / 10 % 10], 0x7fff);
    func_ov001_0207ca04(&display->slash, 0x1000, &display->slashGlyph, 0x7fff);
    value = display->maximum;
    func_ov001_0207ca04(&display->maximumOnes, 0x1000, &display->digits[value % 10], 0x7fff);
    func_ov001_0207ca04(&display->maximumTens, 0x1000, &display->digits[value / 10 % 10], 0x7fff);
}

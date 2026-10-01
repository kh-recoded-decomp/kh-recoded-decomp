#include "nitro/types.h"

typedef struct Point {
    s32 x;
    s32 y;
} Point;

typedef struct TweenFlags {
    u32 started : 1;
    u32 paused : 1;
    u32 finished : 1;
    u32 reserved : 29;
} TweenFlags;

typedef struct Tween {
    s32 mode;
    s32 duration;
    s32 from;
    s32 to;
    s64 startTick;
    TweenFlags flags;
} Tween;

typedef struct Sprite {
    u8 data[0xc];
} Sprite;

typedef struct CounterHud {
    u8 pad_000[4];
    s32 state;
    u8 pad_008[0x2c];
    Sprite digits[10];
    u8 pad_0ac[0xc];
    Sprite signs[2];
    u8 pad_0d0[0x18];
    Point iconPos;
    u8 pad_0f0[0x70];
    u32 displayedValue;
    s32 lastDelta;
    s32 useLargeCounter;
    s32 animState;
    Tween tween;
    Point basePos;
    void *iconSprite;
} CounterHud;

extern u32 func_ov001_02063b68(s32 index);
extern s32 DigitCount_0207b7a4(s32 value);
extern s32 IntPow_0207b788(s32 base, s32 exponent);
extern void SampleTweenValue_0205258c(Tween *tween, s32 *outValue);
extern void func_02052514(Tween *tween, s32 mode, s32 from, s32 to, s32 duration);
extern void func_0205255c(Tween *tween);
extern int FixedPointMultiply12(int left, int right);
extern void func_ov001_0207ca04(Point *pos, s32 scale, void *sprite, s32 color);
extern u64 func_02023fc8(u32 dividend, u32 divisor);

void func_ov001_0207becc(CounterHud *hud)
{
    s32 t;
    s32 speed;
    Point pos;
    s32 delta;
    s32 digitCount;
    s32 step;
    s32 deltaDigits;
    u32 value;
    u32 divisor;
    s32 i;

    speed = 0;
    if (hud->useLargeCounter == 0) {
        value = func_ov001_02063b68(0);
        if ((s32)value > 999999) {
            value = 999999;
        }
    } else {
        value = func_ov001_02063b68(1);
        if ((s32)value > 9999999) {
            value = 9999999;
        }
    }

    delta = value - hud->displayedValue;
    digitCount = DigitCount_0207b7a4(hud->displayedValue);
    if (delta != 0) {
        if (hud->animState == 0) {
            speed = 0x14cd;
            hud->animState = 1;
        } else if (hud->lastDelta != delta) {
            SampleTweenValue_0205258c(&hud->tween, &speed);
            speed += 0x100;
            if (speed < 0xc00) {
                speed = 0xc00;
            } else if (speed > 0x14cd) {
                speed = 0x14cd;
            }
            hud->animState = 1;
        }
    }
    hud->lastDelta = delta;
    if (delta > 9999) {
        delta = 9999;
    } else if (delta < -9999) {
        delta = -9999;
    }

    switch (hud->animState) {
    case 1:
        func_02052514(&hud->tween, 1, speed, 0x400, 1500);
        func_0205255c(&hud->tween);
        hud->animState++;
    case 2:
        SampleTweenValue_0205258c(&hud->tween, &t);
        if (hud->tween.flags.finished) {
            hud->animState = 0;
            hud->displayedValue = value;
            digitCount = DigitCount_0207b7a4(value);
        }
        break;
    }

    pos = hud->basePos;
    value = hud->displayedValue;
    divisor = IntPow_0207b788(10, digitCount - 1);
    for (i = 0; i < digitCount; i++) {
        func_ov001_0207ca04(&pos, 0x1000, &hud->digits[(u32)func_02023fc8(value, divisor)], 0x7fff);
        value = (u32)(func_02023fc8(value, divisor) >> 32);
        divisor = (u32)func_02023fc8(divisor, 10);
        pos.x += 0xd000;
    }

    if (hud->useLargeCounter == 1) {
        hud->iconPos.x = pos.x + 0xd000;
    }
    func_ov001_0207ca04(&hud->iconPos, 0x1000, hud->iconSprite, 0x7fff);

    if (hud->state != 2 && hud->animState != 0) {
        s16 magnitude;

        magnitude = (delta < 0) ? -delta : delta;
        step = FixedPointMultiply12(0xd000, t);
        pos = hud->basePos;
        deltaDigits = DigitCount_0207b7a4(magnitude);
        pos.y = hud->basePos.y + 0xd000 - FixedPointMultiply12(0xd000, 0x1000 - t);
        func_ov001_0207ca04(&pos, t, &hud->signs[delta > 0], 0x7fff);
        pos.x += step - FixedPointMultiply12(0x1000, t);
        divisor = IntPow_0207b788(10, deltaDigits - 1);
        for (i = 0; i < deltaDigits; i++) {
            func_ov001_0207ca04(&pos, t, &hud->digits[(u32)func_02023fc8(magnitude, divisor)], 0x7fff);
            magnitude = (u32)(func_02023fc8(magnitude, divisor) >> 32);
            divisor = (u32)func_02023fc8(divisor, 10);
            pos.x += step;
        }
    }
}

#include "src/overlays/ov001/CounterHud.h"

#pragma opt_propagation off

extern CounterHud *data_ov001_020a04ec;
extern void DrawCounterDigits(CounterHud *hud);
extern void DrawScaledTextureQuad(const FieldScreenPoint *position, fx32 scale,
                                  HudDigit *digit, u32 color);
extern void SetFadeOrthoCamera(void);
extern void SceneNode_Draw(HudModel *model);

static inline void DrawCounterHud(CounterHud *hud)
{
    u32 flags;
    if (!(hud->drawFlags & 0x80)) {
        if (hud->drawFlags & 2) {
            FieldScreenPoint position = gCounterHudDigitPosition;
            u32 value = 0;
            if (hud->animatedValue >= 0) {
                value = hud->animatedValue >> FX32_SHIFT;
            }
            if (value < 10) {
                DrawScaledTextureQuad(&position, FX32_ONE, &hud->digits[value % 10], 0x7fff);
            } else {
                position.x += 7 * FX32_ONE;
                DrawScaledTextureQuad(&position, FX32_ONE, &hud->digits[value % 10], 0x7fff);
                position.x -= 14 * FX32_ONE;
                DrawScaledTextureQuad(&position, FX32_ONE, &hud->digits[value / 10], 0x7fff);
            }
        }
        if (hud->drawFlags & 1) {
            SetFadeOrthoCamera();
            SceneNode_Draw(&hud->panel);
        }
        {
            flags = hud->drawFlags;
            if (flags & 0xc) {
                int variant;
                SetFadeOrthoCamera();
                variant = (flags & 8) ? 1 : 0;
                SceneNode_Draw(&hud->variants[variant]);
            }
        }
    }
    hud->drawFlags = 0;
}

int UpdateAndDrawCounterHud(void)
{
    CounterHandlers handlers = gCounterHudStateHandlers;
    FadeHandlers fades = gFadeSequenceHandlers;
    CounterHud *hud = data_ov001_020a04ec;
    if (hud->enabled && hud->counter.enabled) {
        DrawCounterDigits(hud);
    }
    if (hud->enabled && handlers.entries[hud->state] != NULL) {
        handlers.entries[hud->state](hud);
    }
    if (hud->fadeEnabled && fades.entries[hud->fadeState] != NULL) {
        fades.entries[hud->fadeState](hud);
        hud->drawFlags |= 0x80;
    }
    DrawCounterHud(hud);
    /* A zero task result keeps this callback installed for the next frame. */
    return 0;
}

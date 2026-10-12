#ifndef EFFECT_TEXTURE_PRESETS_H
#define EFFECT_TEXTURE_PRESETS_H

#include "nitro/types.h"

typedef struct EffectTexturePreset {
    s8 textureSlot;
    /* Copied to Effect's signed-byte fields at 0x1e and 0x1f. */
    s8 param1e;
    s8 param1f;
    u8 reserved;
} EffectTexturePreset;

extern const EffectTexturePreset gEffectTexturePresets[7];

#endif

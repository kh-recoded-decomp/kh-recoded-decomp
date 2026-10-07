#include "nitro/types.h"

typedef struct ArrowPrompt {
    u8 state;
    u8 stepCount;
    u8 pad_02[2];
    BOOL visible;
} ArrowPrompt;

extern ArrowPrompt *data_ov001_020a04f0;

BOOL IsArrowPromptVisible(void)
{
    return data_ov001_020a04f0->visible;
}

#include "nitro/types.h"

typedef struct ArrowPrompt {
    u8 state;
    u8 stepCount;
} ArrowPrompt;

extern ArrowPrompt *data_ov001_020a04f0;

u8 GetArrowPromptState(void)
{
    return data_ov001_020a04f0->state;
}

#include "nitro/types.h"

typedef struct ArrowPrompt {
    u8 state;
    u8 stepCount;
} ArrowPrompt;

extern ArrowPrompt *gArrowPromptWork;

u8 GetArrowPromptState(void)
{
    return gArrowPromptWork->state;
}

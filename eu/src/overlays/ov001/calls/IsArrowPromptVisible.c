#include "nitro/types.h"

typedef struct ArrowPrompt {
    u8 state;
    u8 stepCount;
    u8 pad_02[2];
    BOOL visible;
} ArrowPrompt;

extern ArrowPrompt *gArrowPromptWork;

BOOL IsArrowPromptVisible(void)
{
    return gArrowPromptWork->visible;
}

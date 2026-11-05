#include "nitro/types.h"

typedef struct {
    u8 pad_00[24];
    void *messages[3];
} StoryReportMessageWorkView;

extern const char *gStoryReportResourcePaths[];
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);

void LoadStoryReportMessageContainers(StoryReportMessageWorkView *state)
{
    int i;

    for (i = 0; i < 3; i++) {
        state->messages[i] = Msg_OpenContainerAndReadHeader(gStoryReportResourcePaths[i], 0xE, FALSE);
    }
}

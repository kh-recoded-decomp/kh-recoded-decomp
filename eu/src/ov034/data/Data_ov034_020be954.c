#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitResultsScene(void);
extern void CloseResultsSession(void);

void *gResultsScreenTaskClass[5] = {
    (void *)0x0002000E,
    (void *)InitResultsScene,
    (void *)CloseResultsSession,
    (void *)0x00006D98,
    NULL,
};

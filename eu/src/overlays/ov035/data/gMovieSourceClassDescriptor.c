#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitMovieSceneWork(void);
extern void TeardownMovieContext(void);

void *gMovieSourceClassDescriptor[5] = {
    (void *)0x0002000E,
    (void *)InitMovieSceneWork,
    (void *)TeardownMovieContext,
    (void *)0x000000CC,
    NULL,
};

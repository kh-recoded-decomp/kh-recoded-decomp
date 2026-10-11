#ifndef EU_ACTOR_CHANNEL_DATA_H
#define EU_ACTOR_CHANNEL_DATA_H

#include "nitro/types.h"

typedef struct ActorChannelContext ActorChannelContext;

/* Nitro resource dictionary names occupy four aligned words. */
typedef union ActorResourceName {
    char text[16];
    u32 words[4];
} ActorResourceName;

extern ActorChannelContext *gActorChannelContext;
extern ActorResourceName gActorResourceNameBuffer;

#endif

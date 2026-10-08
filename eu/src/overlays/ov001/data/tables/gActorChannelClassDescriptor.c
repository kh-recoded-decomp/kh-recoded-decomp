#include "nitro/types.h"

#pragma explicit_zero_data on

extern void CreateActorChannel(void);
extern void ActorChannel_Destroy(void);

void *gActorChannelClassDescriptor[5] = {
    (void *)0x000D0001,
    (void *)CreateActorChannel,
    (void *)ActorChannel_Destroy,
    (void *)0x000001F0,
    NULL,
};

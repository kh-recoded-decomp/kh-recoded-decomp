#include "nitro/types.h"

extern void RegisterOverlay053ActorFactory(void);
extern void RegisterOverlay055EntityFactory(void);
extern void RegisterOverlay057EntityFactory(void);

void *const data_ov051_020c73f0[12] = {
    (void *)RegisterOverlay053ActorFactory,
    NULL,
    NULL,
    NULL,
    (void *)RegisterOverlay055EntityFactory,
    NULL,
    NULL,
    NULL,
    (void *)RegisterOverlay057EntityFactory,
    NULL,
    NULL,
    NULL,
};

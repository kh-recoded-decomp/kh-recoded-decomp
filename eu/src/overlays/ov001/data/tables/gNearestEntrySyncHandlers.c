#include "nitro/types.h"

extern void StageActor_DefaultInitNoop(void); /* _fp_init */
extern void SyncNearestEntryPosition(void); /* SyncNearestEntryPosition */
extern void StageActor_DefaultUpdateNoop(void); /* _fp_init */
extern void StageActor_DefaultDrawNoop(void); /* _fp_init */

void (*gNearestEntrySyncHandlers[13])(void) = {
    NULL,
    NULL,
    NULL,
    NULL,
    StageActor_DefaultInitNoop, /* _fp_init */
    SyncNearestEntryPosition, /* SyncNearestEntryPosition */
    StageActor_DefaultUpdateNoop, /* _fp_init */
    StageActor_DefaultDrawNoop, /* _fp_init */
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

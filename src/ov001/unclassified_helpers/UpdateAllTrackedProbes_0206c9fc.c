#include "nitro/types.h"

typedef struct {
    u8 data[0x28];
} Track;

typedef struct {
    u32 flags;
    Track main;
    Track extra[3];
} TrackSet;

extern TrackSet *data_ov001_020a0498;
extern void func_ov001_0206c880(Track *track, int arg);

void UpdateAllTrackedProbes_0206c9fc(int arg) {
    TrackSet *set = data_ov001_020a0498;
    int i;
    if (set == NULL || (set->flags & 1)) {
        return;
    }
    func_ov001_0206c880(&set->main, arg);
    for (i = 0; i < 3; i++) {
        func_ov001_0206c880(&set->extra[i], arg);
    }
}

#include "nitro/types.h"

extern void ConfigureFieldTracks_0206317c(int mainId, int subId, u8 param, int mode);

void PlayFieldTrackSet_02064810(int index) {
    ConfigureFieldTracks_0206317c(index * 100 + 0x65, 0, 1, 2);
}

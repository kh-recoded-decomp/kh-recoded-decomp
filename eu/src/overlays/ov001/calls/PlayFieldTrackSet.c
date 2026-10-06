#include "nitro/types.h"

extern void ConfigureFieldTracks(int mainId, int subId, u8 param, int mode);

void PlayFieldTrackSet(int index) {
    ConfigureFieldTracks(index * 100 + 0x65, 0, 1, 2);
}

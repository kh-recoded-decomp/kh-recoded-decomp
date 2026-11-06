#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x52c];
    u32 unk_52c;
} Manager;

extern u32 gMovieContextState;

void StopStageBrightnessFade(void) {
    Manager *manager = *(Manager **)(gMovieContextState + 0xb8);
    manager->unk_52c = 0;
}

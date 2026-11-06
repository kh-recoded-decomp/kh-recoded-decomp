#include "nitro/types.h"

typedef struct Ov024Context {
    u8 pad_00[8];
    void *handle;
} Ov024Context;

extern Ov024Context *gBoardScreenGlobals;
extern void ClearWidgetTileArea(void *handle, int value);

void ClearBoardWidgetTileArea(int value) {
    ClearWidgetTileArea(gBoardScreenGlobals->handle, value);
}

#include "nitro/types.h"

extern u32 gGroupSceneGlobals;

s32 GetCurrentBoardNodeCode(void) {
    s8 index = *(s8 *)(gGroupSceneGlobals + 0x55);
    return (s32)*(s8 *)(gGroupSceneGlobals + index + 0x56);
}

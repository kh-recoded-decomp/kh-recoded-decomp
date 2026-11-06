#include "nitro/types.h"

extern u8 ***gAreaRewardResourceGlobalsStorage;

u8 *GetAreaRewardAnimationTable(int index) {
    return *gAreaRewardResourceGlobalsStorage[index] + 8;
}

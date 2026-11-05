#include "nitro/types.h"

extern void DestroyEntryGroup(int channel);
extern void ReleaseModelAnimationResources(int *resourceState);

void ReleaseKind6ObjectChannelAndResources(int object)
{
    DestroyEntryGroup((int)*(s16 *)(object + 0x470));
    if (*(int *)(object + 0xd4) != 0) {
        ReleaseModelAnimationResources((int *)(object + 0x138));
    }
    if (*(int *)(object + 0x1d8) != 0) {
        ReleaseModelAnimationResources((int *)(object + 0x23c));
    }
    if (*(int *)(object + 0x2dc) != 0) {
        ReleaseModelAnimationResources((int *)(object + 0x340));
    }
    if (*(int *)(object + 0x3e0) != 0) {
        ReleaseModelAnimationResources((int *)(object + 0x444));
    }
}

#include "nitro/types.h"

typedef struct AnimationRequest {
    u32 unk_00;
    s16 blendIndex;
    u16 pad_06;
    int frameCount;
    char name[0x20];
} AnimationRequest;

typedef struct Actor {
    u8 pad_000[0xd0];
    AnimationRequest requests[6][5];
} Actor;

extern void ApplyActorAnimationRequest_02088d14(Actor *actor, int track);
extern char *strcpy_02021e60(char *dst, const char *src);

void AdvanceAnimationRequestQueue_02088fe4(Actor *actor, int track)
{
    AnimationRequest *request = &actor->requests[0][track];
    int i;

    ApplyActorAnimationRequest_02088d14(actor, track);
    request->blendIndex = -1;
    request->name[0] = 0;
    for (i = 1; i < 6; i++) {
        if (actor->requests[i][track].blendIndex == -1) {
            return;
        }
        actor->requests[i - 1][track].blendIndex = actor->requests[i][track].blendIndex;
        actor->requests[i - 1][track].frameCount = actor->requests[i][track].frameCount;
        strcpy_02021e60(actor->requests[i - 1][track].name, actor->requests[i][track].name);
        actor->requests[i][track].blendIndex = -1;
        actor->requests[i][track].name[0] = 0;
    }
}

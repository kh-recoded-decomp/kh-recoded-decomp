#include "nitro/types.h"

typedef struct ResourceState {
    u32 unk_00[3];
    u32 active;
    u32 unk_10[5];
} ResourceState;

typedef struct AnimationState {
    u8 pad_00[0xd8];
    u8 blendTable[4];
} AnimationState;

typedef struct ActorModel {
    u32 unk_00;
    AnimationState animation;
} ActorModel;

typedef struct AnimationRequest {
    u32 unk_00;
    s16 blendIndex;
    u16 pad_06;
    int frameCount;
    char name[0x20];
} AnimationRequest;

typedef void (*PartyAnimationCallback)(void *party, int blendIndex, int frameCount);

typedef struct PartyMember {
    u8 pad_000[0x1f8];
    PartyAnimationCallback playAnimation;
} PartyMember;

typedef struct Actor {
    u8 pad_000[0xd0];
    AnimationRequest requests[4];
    u8 pad_180[0xd18 - 0x180];
    ActorModel **model;
    ResourceState *resourceStates;
    u8 *archive;
    u8 pad_d24[0xef4 - 0xd24];
    u32 flags;
    u8 pad_ef8[8];
    s32 partyIndex;
    u8 pad_f04[4];
    int currentBlendIndex;
    char currentName[0x20];
} Actor;

extern char data_ov001_0209f2f0[];
extern char data_ov001_0209f2f4[];
extern char data_ov001_0209f2f8[];

extern PartyMember *GetBoundedEntryField_0206db5c(int index);
extern s32 func_ov001_02063a38(void);
extern void *func_ov001_02088c1c(PartyMember *party);
extern void func_ov059_020cd184(PartyMember *party, int track, int blendIndex, int frameCount);
extern void func_ov052_020cfb88(PartyMember *party, int track, int blendIndex, int frameCount);
extern void func_ov059_020cc9f4(PartyMember *party, void *blendTable, int track, int blendIndex, int frameCount);
extern void func_ov052_020ce168(PartyMember *party, void *blendTable, int track, int blendIndex, int frameCount);
extern void func_ov021_020a9cb4(void *party, void *blendTable, int track, int blendIndex, int frameCount);
extern void selectJointAnimationBlend_0202f2cc(AnimationState *state, u16 trackIndex, void *blendTable, s16 blendIndex);
extern void BlendToAnimationTrack_0202f374(AnimationState *state, u16 trackIndex, void *blendTable, s16 blendIndex, int frameCount);
extern int Strlen_02021e44(const char *str);
extern int strcmp_02021fa8(const char *a, const char *b);
extern char *strcpy_02021e60(char *dst, const char *src);
extern void *OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern void func_0202eaf4(ResourceState *state);
extern BOOL func_0202e9ec(void *dst, void *src, int source, int mode);
extern void Actor_ReleaseHeldResource_02088bc4(Actor *actor);

static inline void PlayPartyAnimation(PartyMember *party, int blendIndex, int frameCount)
{
    if (party->playAnimation != NULL) {
        party->playAnimation(party, blendIndex, frameCount);
    }
}

#define ARCHIVE_FILE_ID(base) (((((u32)(base) + 0x8000) & 0xfffffc) << 7) | 0x80000000)

void ApplyActorAnimationRequest_02088d14(Actor *actor, int track)
{
    AnimationRequest *request = &actor->requests[track];

    if (request->name[0] == 0) {
        if (actor->partyIndex < 3 && track == 0) {
            PartyMember *party = GetBoundedEntryField_0206db5c(actor->partyIndex);

            if (actor->flags & 0x4000) {
                if (func_ov001_02063a38() == 7) {
                    func_ov059_020cd184(party, 0, request->blendIndex, request->frameCount);
                } else {
                    func_ov052_020cfb88(party, 0, request->blendIndex, request->frameCount);
                }
            } else {
                PlayPartyAnimation(party, request->blendIndex, request->frameCount);
            }
        } else if (request->frameCount == 0) {
            selectJointAnimationBlend_0202f2cc(&(*actor->model)->animation, track, ((AnimationState *)&(*actor->model)->animation)->blendTable,
                                               request->blendIndex);
        } else {
            BlendToAnimationTrack_0202f374(&(*actor->model)->animation, track, ((AnimationState *)&(*actor->model)->animation)->blendTable,
                                           request->blendIndex, request->frameCount);
        }
    } else {
        int length = Strlen_02021e44(request->name);
        int blendIndex = 0;
        int i;
        char path[0x100];

        for (i = 4; i >= 0; i--) {
            if (actor->resourceStates[i].active != 0) {
                if (i == 4) {
                    func_0202eaf4(&actor->resourceStates[i]);
                    actor->resourceStates[i].active = 0;
                } else {
                    actor->resourceStates[i + 1] = actor->resourceStates[i];
                    actor->resourceStates[i].active = 0;
                }
            }
        }
        if (strcmp_02021fa8(&request->name[length - 3], data_ov001_0209f2f0) == 0) {
            if (actor->flags & 0x4000) {
                func_0202e9ec(actor->resourceStates,
                              (u8 *)func_ov001_02088c1c(GetBoundedEntryField_0206db5c(actor->partyIndex)) + 8,
                              ARCHIVE_FILE_ID(actor->archive) | (request->blendIndex & 0x1ff), 0xd);
            } else {
                func_0202e9ec(actor->resourceStates, &(*actor->model)->animation,
                              ARCHIVE_FILE_ID(actor->archive) | (request->blendIndex & 0x1ff), 0xd);
            }
        } else {
            if (strcmp_02021fa8(&request->name[length - 2], data_ov001_0209f2f4) == 0) {
                strcpy_02021e60(path, request->name);
            } else {
                OS_SPrintf_02002428(path, data_ov001_0209f2f8, request->name);
            }
            func_0202e9ec(actor->resourceStates, &(*actor->model)->animation, (int)path, 0xd);
            if (request->blendIndex >= 0) {
                blendIndex = request->blendIndex;
            }
        }
        if (actor->partyIndex < 3) {
            PartyMember *party = GetBoundedEntryField_0206db5c(actor->partyIndex);

            if (actor->flags & 0x4000) {
                func_ov021_020a9cb4(func_ov001_02088c1c(party), actor->resourceStates, 0, blendIndex, request->frameCount);
            } else if (func_ov001_02063a38() == 7) {
                func_ov059_020cc9f4(party, actor->resourceStates, 0, blendIndex, request->frameCount);
            } else {
                func_ov052_020ce168(party, actor->resourceStates, 0, blendIndex, request->frameCount);
            }
        } else if (request->frameCount == 0) {
            selectJointAnimationBlend_0202f2cc(&(*actor->model)->animation, track, actor->resourceStates, blendIndex);
        } else {
            BlendToAnimationTrack_0202f374(&(*actor->model)->animation, track, actor->resourceStates, blendIndex,
                                           request->frameCount);
        }
    }
    if (track == 0) {
        actor->currentBlendIndex = request->blendIndex;
        strcpy_02021e60(actor->currentName, request->name);
    }
    if (actor->flags & 0x800) {
        Actor_ReleaseHeldResource_02088bc4(actor);
    }
}

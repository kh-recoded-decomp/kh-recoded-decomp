#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FileSection {
    u32 unk_00;
    u32 count;
    u32 stride;
    u8 *data;
} FileSection;

typedef struct StageFile {
    u8 pad_00[8];
    FileSection *sections;
} StageFile;

typedef struct StageEntry {
    u16 id;
    u8 pad_02[2];
    StageFile *file;
} StageEntry;

typedef struct EventSetup {
    u8 pad_00[8];
    u8 solid;
} EventSetup;

typedef struct CueGroup {
    u32 first;
    u32 count;
} CueGroup;

typedef struct Cue {
    u8 pad_00[4];
    s32 frame;
    s32 type;
    u16 arg0;
    u16 arg1;
    u16 arg2;
    u16 arg3;
} Cue;

typedef struct ActorBody {
    u8 pad_00[4];
    u16 flags;
    s16 group;
    u8 pad_08[8];
    s32 *frameCounter;
} ActorBody;

typedef struct StageActor {
    u8 pad_000[8];
    u16 drawFlags;
    u8 pad_00a[6];
    ActorBody body;
    u8 pad_024[0x11c - 0x24];
    u8 surface[0xc];
    u8 surfaceFlags;
    u8 pad_129[0x1d0 - 0x129];
    u8 sequencer[0x26c - 0x1d0];
    u32 behaviorFlags : 31;
    u32 unk_26c_31 : 1;
    u8 pad_270[0x288 - 0x270];
    u16 unk_288_0 : 2;
    u16 pushMode : 2;
    u16 pushable : 1;
    u16 unk_288_5 : 2;
    u16 pushed : 1;
    u16 unk_288_8 : 8;
    u8 pad_28a[2];
    u16 unk_28c_0 : 7;
    u16 crouchLevel : 4;
    u16 unk_28c_11 : 5;
    u8 pad_28e[0x2c0 - 0x28e];
    VecFx32 position;
    u8 pad_2cc[0x2f4 - 0x2cc];
    s32 health;
    u8 pad_2f8[0x320 - 0x2f8];
    u8 fade;
    u8 fadeFrom;
    u8 fadeTo;
    u8 pad_323;
    fx32 fadeSpeed;
    fx32 fadeTimer;
    u8 pad_32c[0x368 - 0x32c];
    VecFx32 velocity;
    VecFx32 push;
    u8 pad_380[0x398 - 0x380];
    fx32 mass;
} StageActor;

typedef struct StageEvent {
    s32 kind;
    u16 unk_04_0 : 2;
    u16 fadeRequest : 1;
    u16 unk_04_3 : 13;
    u16 unk_06_0 : 2;
    u16 handled : 1;
    u16 unk_06_3 : 3;
    u16 fadeActive : 1;
    u16 unk_06_7 : 1;
    u16 fadeEnabled : 1;
    u16 unk_06_9 : 3;
    u16 aborted : 1;
    u16 unk_06_13 : 2;
    u16 updated : 1;
    u8 pad_08;
    u8 ownerKind;
    u8 fadeKind;
    u8 pad_0b[5];
    u16 actorId;
    u8 pad_12[2];
    s16 entryId;
    u8 pad_16[0x64 - 0x16];
    s32 moveA;
    s32 moveB;
    u8 pad_6c[0x1a0 - 0x6c];
    s32 idleTimer;
    u8 pad_1a4[0x1b0 - 0x1a4];
    s32 waitTimer;
    u8 cueGroup;
    u8 cueStep;
    u8 pad_1b6[2];
    u16 links[2];
} StageEvent;

typedef struct StageController {
    u8 pad_00[0xc];
    s16 actorId;
} StageController;

typedef u32 (*StageEventHandler)(StageEvent *event);

extern VecFx32 data_0205344c;
extern StageEventHandler gStageScriptStateHandlers[];

extern StageActor *GetStageActor(int id);
extern fx32 ApplyActorScaleFactors(StageActor *actor);
extern StageEntry *GetStageEntry(int id);
extern void func_ov001_02092e60(StageEvent *event);
extern StageActor *GetLinkedStageActor(StageActor *actor);
extern u32 func_ov001_0209c5ac(u32 mask);
extern StageActor *FindRecordById_0209c304(int id);
extern void func_ov001_02091ae8(StageActor *actor, u32 firstId, u32 secondId, u32 flags);
extern void CopySourceWords(void *cache);
extern void func_ov001_020925e4(StageEvent *event, u32 state);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern int func_ov001_02063a24(void);
extern s32 func_ov001_02063a38(void);
extern u8 *func_ov001_0209c3e8(void);
extern s32 func_ov001_0208f2a4(void *pool);
extern u32 FindFirstActiveStageEvent(void);
extern StageEvent *GetStageEventRecord(u32 handle);
extern BOOL IsCommandType8(StageEvent *event);
extern fx32 Surface_GetKindValue(void *surface);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern fx32 VEC_NormalizeLength(const VecFx32 *source, VecFx32 *dest);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern u32 func_ov001_0209c9c4(u32 handle);
extern void ResolveStageEntryPushOut(StageEvent *event);
extern StageController *GetStageController(u32 id);
extern void PlayActorSound(StageActor *actor, u16 bank, u16 soundId, u32 flags, u16 volume);
extern void SetActorGridCell(StageActor *actor, u16 column, u16 row);
extern void ClearWalkerStepState(StageActor *actor);
extern void UpdateFieldActorMovement(StageActor *actor);
extern void func_ov001_02090a0c(StageActor *actor, int mode);

static inline u32 GetEntrySectionCount(StageEntry *entry, int type)
{
    if (entry == NULL) {
        return 0;
    }
    if (entry->file == NULL) {
        return 0;
    }
    if (type < 0) {
        return 0;
    }
    if (type >= 0x13) {
        return 0;
    }
    return entry->file->sections[type].count;
}

static inline u8 *GetEntrySectionItem(StageEntry *entry, int type, u32 index)
{
    u32 count;
    FileSection *sections;
    u8 *data;

    if (entry == NULL) {
        return NULL;
    }
    if (entry->file == NULL) {
        return NULL;
    }
    if (type < 0) {
        return NULL;
    }
    if (type >= 0x13) {
        return NULL;
    }
    count = GetEntrySectionCount(entry, type);
    sections = entry->file->sections;
    data = sections[type].data;
    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return data + index * sections[type].stride;
}

static inline int GetSessionMode(void)
{
    if (func_ov001_02063a24()) {
        return func_ov001_02063a38();
    }
    return 0;
}

static inline void SetVec(VecFx32 *v, fx32 x, fx32 y, fx32 z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void UpdateStageEvent(StageEvent *event)
{
    VecFx32 dir;
    VecFx32 normal;
    VecFx32 delta;
    fx32 speed;
    BOOL fadeIn;
    fx32 overlap;
    fx32 ratio;
    fx32 dist;
    StageEntry *entry;
    ActorBody *body;
    fx32 scale;
    StageActor *link;
    fx32 peerPush;
    fx32 selfPush;
    fx32 peerRadius;
    fx32 selfRadius;
    u32 handle;
    fx32 reach;
    StageActor *actor;
    EventSetup *setup;
    StageActor *rec;
    u32 result;
    int i;
    StageActor *peer;
    StageEvent *other;
    StageActor *self;
    u32 positionalFlag;
    u32 soundFlags;

    actor = GetStageActor((s16)event->actorId);
    body = &actor->body;
    scale = ApplyActorScaleFactors(actor);
    event->updated = 0;
    entry = GetStageEntry(event->entryId);
    if (entry == NULL) {
        return;
    }
    setup = (EventSetup *)GetEntrySectionItem(entry, 0, 0);
    if (setup == NULL) {
        return;
    }
    actor->push = data_0205344c;
    func_ov001_02092e60(event);
    if (setup->solid) {
        actor->behaviorFlags |= 0x100;
    }
    if (event->waitTimer != 0) {
        event->waitTimer -= scale;
        if (event->waitTimer <= 0) {
            event->waitTimer = 0;
        }
    }
    if (event->moveA != 0 || event->moveB != 0) {
        event->idleTimer -= scale;
        if (event->idleTimer <= 0) {
            event->idleTimer = 0;
        }
    } else {
        event->idleTimer = 0x7fffffff;
    }
    if (event->fadeEnabled && event->fadeKind == 4) {
        for (link = actor; link != NULL; link = GetLinkedStageActor(link)) {
            if (link == actor) {
                fadeIn = FALSE;
                speed = 0;
                if (func_ov001_0209c5ac(1)) {
                    actor->fade = 0x1f;
                    actor->fadeFrom = actor->fade;
                    actor->fadeTo = 0x1f;
                    actor->fadeSpeed = 0;
                    actor->fadeTimer = 0x1e000;
                } else {
                    if (event->fadeRequest) {
                        if (actor->fade == 0 && actor->fadeTimer == 0) {
                            fadeIn = TRUE;
                        } else if (actor->fade == 0x1f && actor->fadeTimer == 0) {
                            fadeIn = FALSE;
                            speed = 0;
                        }
                    } else {
                        speed = -0x1e000;
                        if (actor->crouchLevel != 0) {
                            fadeIn = TRUE;
                            speed = 0;
                        } else if (event->kind == 5) {
                            fadeIn = TRUE;
                            speed = 0;
                        }
                    }
                    if (fadeIn && actor->fade == 0 && actor->fadeTimer == 0) {
                        actor->fadeFrom = actor->fade;
                        actor->fadeTo = 0x1f;
                        actor->fadeSpeed = speed;
                        actor->fadeTimer = 0x1e000;
                    } else if (!fadeIn && actor->fade == 0x1f && actor->fadeTimer == 0) {
                        actor->fadeFrom = actor->fade;
                        actor->fadeTo = 0;
                        actor->fadeSpeed = speed;
                        actor->fadeTimer = 0x1e000;
                    }
                }
            } else {
                link->fade = actor->fade;
            }
        }
        event->fadeActive = event->fadeRequest;
        event->fadeRequest = 0;
    }
    if (event->aborted) {
        event->aborted = 0;
        event->cueGroup = 0;
        event->cueStep = 0;
        rec = FindRecordById_0209c304(event->actorId);
        if (rec != NULL) {
            func_ov001_02091ae8(rec, 0xffff, 0xffff, 0);
            CopySourceWords(rec->sequencer);
        }
        func_ov001_020925e4(event, 0xb);
        return;
    }
    result = gStageScriptStateHandlers[event->kind](event);
    event->handled = 0;
    if (event->actorId == 0) {
        return;
    }
    if (result != 0) {
        if (event->kind != 9) {
            CopySourceWords(actor->sequencer);
        }
        func_ov001_020925e4(event, (u16)result);
    }
    if (event->kind == 1) {
        actor->behaviorFlags &= ~1;
    }
    if (event->kind == 8) {
        actor->behaviorFlags &= ~1;
    }
    if (event->kind == 0) {
        actor->behaviorFlags &= ~1;
    }
    if (actor->behaviorFlags & 1) {
        func_ov001_020925e4(event, 7);
        return;
    }
    VEC_Add(&actor->velocity, &actor->push, &actor->push);
    SetVec(&actor->velocity, FX_Mul(actor->velocity.x, 0x666), FX_Mul(actor->velocity.y, 0x666), FX_Mul(actor->velocity.z, 0x666));
    actor->pushed = 0;
    if (actor->pushMode == 1 && GetSessionMode() != 7) {
        func_ov001_0208f2a4(*(void **)(func_ov001_0209c3e8() + 0x18d7c));
        for (handle = FindFirstActiveStageEvent(); handle != 0; handle = func_ov001_0209c9c4(handle)) {
            other = GetStageEventRecord(handle);
            if (other == NULL) {
                break;
            }
            if (IsCommandType8(other) || other == event || other->actorId == 0 || event->actorId == 0) {
                continue;
            }
            self = GetStageActor((s16)event->actorId);
            peer = GetStageActor((s16)other->actorId);
            selfRadius = Surface_GetKindValue(self->surface);
            peerRadius = Surface_GetKindValue(peer->surface);
            if ((self->surfaceFlags & 2) || (peer->surfaceFlags & 2) || !self->pushable || !peer->pushable) {
                continue;
            }
            VEC_Subtract(&self->position, &peer->position, &delta);
            if (GetSessionMode() == 4) {
                delta.y = 0;
            }
            dist = VEC_Mag(&delta);
            reach = selfRadius + peerRadius;
            if (dist < reach) {
                normal = delta;
                ratio = FX_Div(self->mass, self->mass + peer->mass);
                overlap = FX_Mul(reach - dist, 0xccd);
                selfPush = FX_Mul(overlap, 0x1000 - ratio);
                peerPush = FX_Mul(overlap, ratio);
                VEC_NormalizeLength(&normal, &dir);
                if (GetSessionMode() == 4) {
                    dir.y = 0;
                }
                VEC_MultAdd(selfPush, &dir, &self->push, &self->push);
                VEC_MultAdd(-peerPush, &dir, &peer->push, &peer->push);
            }
        }
        ResolveStageEntryPushOut(event);
    }
    if (event->actorId != 0) {
        self = GetStageActor((s16)event->actorId);

        i = 0;
        do {
            StageController *controller;
            StageActor *target;

            if (event->links[i] == 0) {
                continue;
            }
            controller = GetStageController(event->links[i]);
            if (controller == NULL) {
                continue;
            }
            target = GetStageActor(controller->actorId);
            if (target == NULL) {
                continue;
            }
            target->pushable = 1;
            if (self->health <= 0x19a) {
                target->pushable = 0;
            } else if (i == 0 && self->fade < 1) {
                target->pushable = 0;
            } else if (i == 1 && self->fade < 0x14) {
                target->pushable = 0;
            }
        } while (++i < 2);
    }
    if (body->group >= 0 && scale != 0 && !(body->flags & 4) && event->cueGroup != 0) {
        CueGroup *group = (CueGroup *)GetEntrySectionItem(entry, 16, (u16)(event->cueGroup - 1));

        if (group != NULL && event->cueStep < group->count) {
            Cue *cue = (Cue *)GetEntrySectionItem(entry, 10, (u16)(group->first + event->cueStep));

            if (cue != NULL && *body->frameCounter >= cue->frame) {
                positionalFlag = 4;
                switch (cue->type) {
                case 1:
                    soundFlags = positionalFlag | cue->arg3;
                    PlayActorSound(actor, cue->arg0, cue->arg1, soundFlags, cue->arg2);
                    break;
                case 2:
                    SetActorGridCell(actor, cue->arg0, cue->arg1);
                    actor->behaviorFlags |= 0x200;
                    break;
                case 3:
                    ClearWalkerStepState(actor);
                    actor->behaviorFlags &= ~0x200;
                    break;
                }
                event->cueStep++;
            }
        }
    }
    for (rec = FindRecordById_0209c304(event->actorId); rec != NULL; rec = GetLinkedStageActor(rec)) {
        UpdateFieldActorMovement(rec);
        if (event->ownerKind != 4 && !(rec->drawFlags & 0x1000)) {
            func_ov001_02090a0c(rec, 1);
        }
    }
}

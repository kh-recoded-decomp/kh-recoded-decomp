#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[4];
    s32 isStatic;
} ContactOwner;

typedef struct {
    ContactOwner *owner;
    s32 type;
} Contact;

typedef struct {
    u8 pad_00[0xc];
    s32 strength;
} HitInfo;

typedef struct {
    u8 pad_00[0x38];
    VecFx32 position;
} FieldObject;

typedef struct PushRequest {
    s32 type;
    VecFx32 velocity;
    VecFx32 origin;
    s32 power;
    s32 unk_20;
    u32 resultFlags;
    u8 pad_28[8];
    s32 unk_30;
    s32 unk_34;
} PushRequest;

typedef BOOL (*PushHandler)(void *system, PushRequest *request);

typedef struct PushSystem {
    u8 pad_000[0x208];
    PushHandler push;
} PushSystem;

extern const VecFx32 data_02053438;
extern const s16 data_0205396c;

extern BOOL TestFlagBit10_020a380c(FieldObject *object);
extern PushSystem *GetBoundedEntryField_0206db5c(int index);
extern void PlaySoundChecked_0204d8d0(int bank, int soundId);

BOOL FieldObject_HandleStrongHit_020a28d4(void *arg0, Contact *contact, HitInfo *hit, FieldObject *object)
{
    PushRequest request;
    PushSystem *system;

    if (TestFlagBit10_020a380c(object)) {
        if (contact != NULL && contact->type == 2) {
            return FALSE;
        }
    } else if (contact != NULL && contact->type == 2 && contact->owner->isStatic == 0 && hit->strength > data_0205396c) {
        request.power = 0x2000;
        request.type = 4;
        request.velocity = data_02053438;
        request.origin = object->position;
        request.unk_20 = 0;
        request.unk_30 = 0;
        request.unk_34 = 0;
        system = GetBoundedEntryField_0206db5c(0);
        if (system->push != NULL) {
            system->push(system, &request);
        }
        PlaySoundChecked_0204d8d0(0, 0x36);
    }
    return TRUE;
}

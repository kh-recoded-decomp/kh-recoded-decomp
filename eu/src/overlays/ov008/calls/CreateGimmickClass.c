#include "nitro/types.h"

typedef void (*FieldObjectHook)(void);

typedef struct GimmickClass {
    FieldObjectHook hooks[15];
    u8 pad_3c[0x10];
    int linkId;
    int unk_50;
    u8 pad_54[0x10];
    s16 actorKind;
    u8 pad_66[0xa];
    int unk_70;
    int unk_74;
    int unk_78;
    s8 shapeKind;
    u8 classType;
    u8 pad_7e[0x4];
    u8 unk_82;
} GimmickClass;

extern GimmickClass *CreateByteGrid(u32 classSize, u32 objectSize, int count);
extern void AcquireEffectRecordPair(void);
extern void FieldObject_EnsureModelsLoaded(void);
extern void RespawnDelayedGimmick(void);
extern void func_ov001_0207f210(void);
extern void ReleaseOwnerResource(void);
extern void func_ov001_0207f26c(void);
extern void func_ov008_020a0d70(void);
extern void func_ov008_020a0d74(void);
extern void SetFieldObjectPosition_020a0d78(void);
extern void func_ov008_020a0da0(void);
extern void func_ov008_020a0da8(void);

GimmickClass *CreateGimmickClass(int count)
{
    GimmickClass *objectClass = CreateByteGrid(0x84, 0x78, count);

    objectClass->unk_50 = 0;
    objectClass->shapeKind = -1;
    objectClass->unk_70 = 0;
    objectClass->unk_74 = 0;
    objectClass->unk_78 = 0;
    objectClass->actorKind = 0x7e;
    objectClass->unk_82 = 0xff;
    objectClass->linkId = -1;
    objectClass->hooks[0] = AcquireEffectRecordPair;
    objectClass->hooks[1] = FieldObject_EnsureModelsLoaded;
    objectClass->hooks[2] = RespawnDelayedGimmick;
    objectClass->hooks[3] = func_ov001_0207f210;
    objectClass->hooks[4] = ReleaseOwnerResource;
    objectClass->hooks[6] = func_ov001_0207f26c;
    objectClass->hooks[7] = NULL;
    objectClass->hooks[8] = func_ov008_020a0d70;
    objectClass->hooks[10] = func_ov008_020a0d74;
    objectClass->hooks[9] = SetFieldObjectPosition_020a0d78;
    objectClass->hooks[11] = func_ov008_020a0da0;
    objectClass->hooks[14] = NULL;
    objectClass->hooks[12] = func_ov008_020a0da8;
    objectClass->hooks[13] = NULL;
    objectClass->classType = 8;
    return objectClass;
}

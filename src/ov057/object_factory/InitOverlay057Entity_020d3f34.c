#include "nitro/types.h"

typedef void (*EntityCallback)(void);

typedef struct Entity {
    u8 pad_000[0x1ec];
    EntityCallback drawCallback;
    u8 pad_1f0[0x1f8 - 0x1f0];
    EntityCallback eventCallback;
    u8 pad_1fc[0x200 - 0x1fc];
    EntityCallback resetCallback;
    u8 pad_204[0x20c - 0x204];
    EntityCallback modeCallback;
    u8 pad_210[0x218 - 0x210];
    EntityCallback stepCallback;
    EntityCallback flagsCallback;
    u8 pad_220[0x6bc - 0x220];
    s32 targets[4];
    u8 pad_6cc[0x9ac - 0x6cc];
    u64 stateFlags;
    u8 kind;
    u8 pad_9b5[3];
    s32 unk_9b8;
    u8 pad_9bc[0x10e8 - 0x9bc];
    EntityCallback actionCallback;
    EntityCallback stateCallback;
    EntityCallback thinkCallback;
    u8 pad_10f4[0x1258 - 0x10f4];
    u8 work[4];
} Entity;

extern void func_ov058_020d5ee8(void *work);
extern void func_ov052_020cce6c(Entity *entity);
extern void func_ov058_020d68ec(void);
extern void func_ov058_020d6958(void);
extern void LoadSceneSoundArchives_020d4218(void);
extern void func_ov058_020d6b34(void);
extern void func_ov058_020d6d44(void);
extern void func_ov058_020d6df4(void);
extern void ChangeEnemyState_020d65c4(void);
extern void func_ov057_020d40a0(void);
extern void func_ov058_020d6f58(void);

void InitOverlay057Entity_020d3f34(Entity *entity, u8 kind)
{
    int i;

    func_ov058_020d5ee8(entity->work);
    entity->kind = kind;
    entity->unk_9b8 = 2;
    entity->stateFlags = 0;
    entity->stateFlags |= 0x400;
    for (i = 0; i < 4; i++) {
        entity->targets[i] = -1;
    }
    entity->targets[1] = -2;
    func_ov052_020cce6c(entity);
    entity->eventCallback = func_ov058_020d68ec;
    entity->modeCallback = func_ov058_020d6958;
    entity->stepCallback = LoadSceneSoundArchives_020d4218;
    entity->drawCallback = func_ov058_020d6b34;
    entity->flagsCallback = func_ov058_020d6d44;
    entity->resetCallback = func_ov058_020d6df4;
    entity->stateCallback = ChangeEnemyState_020d65c4;
    entity->actionCallback = func_ov057_020d40a0;
    entity->thinkCallback = func_ov058_020d6f58;
}

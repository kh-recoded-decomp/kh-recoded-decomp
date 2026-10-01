#include "nitro/types.h"

typedef struct Entity Entity;

typedef int (*EntityStateFunc)(Entity *entity);
typedef void (*EntityModeFunc)(Entity *entity, int mode);

typedef struct LinkedModel {
    u8 pad_00[0x3B];
    u8 subKind : 4;
    u8 kind : 4;
} LinkedModel;

typedef struct LinkTarget {
    u8 type;
    u8 pad_01[3];
    LinkedModel *model;
} LinkTarget;

typedef struct LinkRequest {
    u8 slot;
    u8 flag;
} LinkRequest;

struct Entity {
    u8 pad_000[0x1DC];
    int state;
    u8 pad_1E0[0x22C - 0x1E0];
    EntityStateFunc getState;
    u8 pad_230[4];
    u32 attributes;
    u8 pad_238[0x9AC - 0x238];
    u64 stateFlags;
    u8 slot;
    u8 pad_9B5[0xFC8 - 0x9B5];
    u8 unk_FC8[0x1034 - 0xFC8];
    s8 unk_1034;
    u8 pad_1035;
    s8 unk_1036;
    u8 pad_1037[0x1048 - 0x1037];
    LinkTarget link;
    u8 pad_1050[0x1070 - 0x1050];
    u8 unk_1070[0x10EC - 0x1070];
    EntityModeFunc modeCallback;
};

static inline int GetEntityState(Entity *entity)
{
    if (entity->getState != NULL) {
        return entity->getState(entity);
    }
    return entity->state;
}

extern void *func_ov001_0206db78(u8 slot);
extern u16 GetId10_020a755c(void *self);
extern s32 GetFieldAt0x12_020a7560(void *obj);
extern BOOL func_ov001_020645c8(u32 value);
extern void func_ov021_020aa498(void *obj, BOOL flag);
extern void func_ov001_0207e07c(void);
extern BOOL func_ov001_0206c3a4(LinkTarget *link);
extern void func_ov001_0207f884(LinkedModel *model, LinkRequest *request);
extern void func_ov052_020cfd84(Entity *entity);
extern int func_ov052_020ceb54(Entity *entity);
extern BOOL func_ov001_02064e2c(int obj);
extern void func_ov001_020641d4(int value);
extern BOOL func_ov052_020d0524(Entity *entity);
extern BOOL func_ov052_020cc274(Entity *entity);
extern s32 func_ov021_020ad8c4(void *obj);
extern BOOL func_ov052_020d0600(Entity *entity, s32 index);

BOOL DispatchSlotAction_020ced20(Entity *entity)
{
    BOOL result;
    int mode;
    u32 hasAttribute;
    void *self;

    self = func_ov001_0206db78(entity->slot);
    result = FALSE;
    hasAttribute = entity->attributes & 4;

    switch (GetId10_020a755c(self)) {
    case 1:
        if (!func_ov001_020645c8(0x3520) && (entity->stateFlags & 0x100) == 0) {
            entity->modeCallback(entity, 12);
            result = TRUE;
        }
        break;
    case 5:
        mode = GetFieldAt0x12_020a7560(self);
        switch (mode) {
        case 1:
        case 3: {
            BOOL isAlternate = FALSE;
            if (mode == 3) {
                isAlternate = TRUE;
            }
            func_ov021_020aa498(entity->unk_FC8, isAlternate);
            func_ov001_0207e07c();
            entity->modeCallback(entity, 12);
            result = TRUE;
            break;
        }
        case 2:
            break;
        }
        break;
    case 2:
    case 3: {
        LinkTarget *link = &entity->link;
        if (GetEntityState(entity) != 3 && GetEntityState(entity) != 2 && func_ov001_0206c3a4(&entity->link) && link->type == 2) {
            BOOL send = TRUE;
            if (link->model->kind == 1 && hasAttribute == 0) {
                send = FALSE;
            }
            if (send) {
                LinkRequest request;
                request.slot = entity->slot;
                request.flag = 0;
                func_ov001_0207f884(link->model, &request);
            }
        }
        func_ov052_020cfd84(entity);
        break;
    }
    case 4:
        if (GetEntityState(entity) != 2 && hasAttribute != 0) {
            if (func_ov001_02064e2c(func_ov052_020ceb54(entity))) {
                entity->stateFlags |= 0x20;
                func_ov001_020641d4(1);
            }
        }
        break;
    case 0:
        if (func_ov052_020d0524(entity)) {
            mode = 0;
            if (entity->unk_1034 >= 0) {
                mode = 0x15;
            } else if (entity->unk_1036 >= 0) {
                mode = 0x17;
            }
            if (mode != 0) {
                entity->modeCallback(entity, mode);
                if (func_ov052_020cc274(entity)) {
                    result = TRUE;
                }
            }
        }
        break;
    case 7: {
        s32 index = func_ov021_020ad8c4(entity->unk_1070);
        if (func_ov052_020d0600(entity, index)) {
            entity->unk_1034 = index;
            entity->unk_1036 = -1;
            entity->modeCallback(entity, 0x18);
            result = TRUE;
        }
        break;
    }
    }
    return result;
}

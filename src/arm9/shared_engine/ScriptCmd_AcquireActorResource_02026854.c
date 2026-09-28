#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    void *sharedRecord;
    u8 pad_0c[0x40];
    u8 **actorWork;
} ScriptWorld;

typedef struct {
    u8 pad_000[0x1c8];
    ScriptWorld *world;
} ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *ctx, void *cmd);
extern char *func_02025dac(ScriptContext *ctx, void *operand);
extern s32 ScriptCmd_ReturnValue_02025960(ScriptContext *ctx, s32 value);
extern u32 func_02036810(u16 actorIndex);
extern void AllocateSlotIfNull_02025964(ScriptContext *ctx, int index);
extern void func_02036850(void *work, u16 actorIndex);
extern u32 ParseSlotQuantityId_020256ac(ScriptWorld *world, char *name);
extern int AcquireSharedRecord_0202c764(u32 fileId, void **out, int kind);
extern void func_02035898(u16 actorIndex, void *record, int a2, int kind);
extern void ScriptCmd_SetElemField_02025e18(ScriptContext *ctx, s32 value);

int ScriptCmd_AcquireActorResource_02026854(ScriptContext *ctx, u8 *cmd)
{
    int actorOperand = ScriptVm_ReadOperandInt_02025de4(ctx, cmd);
    char *path = func_02025dac(ctx, cmd + 8);
    s32 actorIndex = ScriptCmd_ReturnValue_02025960(ctx, actorOperand);
    ScriptWorld *world;

    if (func_02036810(actorIndex) == 0) {
        AllocateSlotIfNull_02025964(ctx, actorIndex);
        func_02036850(ctx->world->actorWork[actorIndex] + 0xd24, actorIndex);
    }
    world = ctx->world;
    if (AcquireSharedRecord_0202c764(ParseSlotQuantityId_020256ac(world, path), &world->sharedRecord, 0xd) != 0) {
        func_02035898(actorIndex, ctx->world->sharedRecord, 0, 0xd);
        if (actorIndex == 0) {
            ScriptCmd_SetElemField_02025e18(ctx, -99);
        } else {
            ScriptCmd_SetElemField_02025e18(ctx, -actorIndex);
        }
    } else {
        ScriptCmd_SetElemField_02025e18(ctx, actorIndex);
    }
    return 0;
}

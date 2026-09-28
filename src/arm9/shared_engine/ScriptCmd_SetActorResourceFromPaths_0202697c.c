#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x4c];
    u8 **actorWork;
} ScriptWorld;

typedef struct {
    u8 pad_000[0x1c8];
    ScriptWorld *world;
} ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *ctx, void *cmd);
extern char *func_02025dac(ScriptContext *ctx, void *operand);
extern u32 ParseSlotQuantityId_020256ac(ScriptWorld *world, char *name);
extern s32 ScriptCmd_ReturnValue_02025960(ScriptContext *ctx, s32 value);
extern u32 func_02036810(u16 actorIndex);
extern void AllocateSlotIfNull_02025964(ScriptContext *ctx, int index);
extern void func_02036850(void *work, u16 actorIndex);
extern void func_02026a00(int actorIndex, u32 resourceFileId, u32 dataFileId);

int ScriptCmd_SetActorResourceFromPaths_0202697c(ScriptContext *ctx, u8 *cmd)
{
    int actorOperand = ScriptVm_ReadOperandInt_02025de4(ctx, cmd);
    u32 resourceFileId = ParseSlotQuantityId_020256ac(ctx->world, func_02025dac(ctx, cmd + 8));
    u32 dataFileId = ParseSlotQuantityId_020256ac(ctx->world, func_02025dac(ctx, cmd + 0x10));
    int actorIndex = ScriptCmd_ReturnValue_02025960(ctx, actorOperand);

    if (func_02036810(actorIndex) == 0) {
        AllocateSlotIfNull_02025964(ctx, actorIndex);
        func_02036850(ctx->world->actorWork[actorIndex] + 0xd24, actorIndex);
    }
    func_02026a00(actorIndex, resourceFileId, dataFileId);
    return 1;
}

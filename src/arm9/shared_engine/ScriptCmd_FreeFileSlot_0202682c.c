#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x58];
    void *loadedFiles[1];
} ScriptFileSlots;

typedef struct {
    u8 pad_000[0x1c8];
    ScriptFileSlots *fileSlots;
} ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *ctx, void *cmd);
extern void ZeroHalfThenFree_0202cd78(void *file);

int ScriptCmd_FreeFileSlot_0202682c(ScriptContext *ctx, void *cmd)
{
    int slot = ScriptVm_ReadOperandInt_02025de4(ctx, cmd);

    if (ctx->fileSlots->loadedFiles[slot] != NULL) {
        ZeroHalfThenFree_0202cd78(ctx->fileSlots->loadedFiles[slot]);
        ctx->fileSlots->loadedFiles[slot] = NULL;
    }
    return 1;
}

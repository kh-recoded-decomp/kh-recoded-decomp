#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MoviePlayerCtx {
    u8 pad_00[6];
    u16 flags;
} MoviePlayerCtx;

typedef void (*EntryCallback)(void *entry, s32 arg);

typedef struct SceneEntry {
    u8 pad_000[0x200];
    EntryCallback onReset;
} SceneEntry;

extern MoviePlayerCtx *g_moviePlayerCtx_020bd000;
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern void func_ov001_0206a8c8(fx32 rate);
extern void func_ov001_0206a7c0(s32 mode);
extern void func_ov001_0206e444(s32 enable);
extern SceneEntry *GetBoundedEntryField_0206db5c(s32 index);
extern void func_0204d980(void);

void SuspendSceneAtQuarterRate_020bb220(void)
{
    SceneEntry *entry;

    func_ov001_0206a8c8(FX_Div_01ff9c84(0x10000, 0x40000));
    func_ov001_0206a7c0(2);
    func_ov001_0206e444(1);
    entry = GetBoundedEntryField_0206db5c(0);
    if (entry->onReset != NULL) {
        entry->onReset(entry, 0);
    }
    func_0204d980();
    g_moviePlayerCtx_020bd000->flags |= 0x40;
}

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SceneEntry SceneEntry;
typedef void (*SceneResetCallback)(SceneEntry *entry, int arg);

struct SceneEntry {
    u8 pad_000[0x200];
    SceneResetCallback onReset;
};

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern void func_ov001_0206a8c8(fx32 value);
extern void func_ov001_0206a7c0(int mode);
extern void func_ov001_0206e444(int enable);
extern SceneEntry *GetBoundedEntryField_0206db5c(int index);
extern void func_0204d980(void);

void ResetSceneState_020bbf34(void)
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
    g_activeState_020bc800->flags = g_activeState_020bc800->flags | 0x40;
}

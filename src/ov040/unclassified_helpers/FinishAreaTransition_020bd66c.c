#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct AreaContext {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0x1c];
    u16 cursor;
} AreaContext;

typedef struct MenuMachine {
    u8 pad_000[0x13c];
    u16 flags;
} MenuMachine;

extern AreaContext *data_ov035_020bc4e0;
extern MenuMachine *data_ov040_020be260;
extern u8 *data_ov001_020a046c;
extern u32 func_ov001_0206685c(void);
extern void ReleaseResourceAndDetach_0202eee8(MenuMachine *object);
extern void func_ov001_020788b8(s32 id, u16 value);
extern void SetOverlayLayerVisible_0207ef40(BOOL visible);
extern void SuspendTaskAndSetFlag_020667b4(void);
extern void SetMenuHighlight_0206c2f8(BOOL enable);
extern int func_ov001_0206dc38(void);
extern void func_ov001_0206de40(int index);
extern const VecFx32 *func_ov001_0206dc4c(int index);
extern u16 GetBiasAdjustedField_0206dc80(int index);
extern void StoreSessionSpawnPoint_02063524(int index, const VecFx32 *position, u16 angle);
extern void func_ov001_02067a6c(void);
extern void func_ov035_020bb64c(void);
extern void func_ov001_0207d658(void);

int FinishAreaTransition_020bd66c(void)
{
    AreaContext *context = data_ov035_020bc4e0;
    int i;

    if (func_ov001_0206685c() != 0) {
        return -1;
    }
    ReleaseResourceAndDetach_0202eee8(data_ov040_020be260);
    context->cursor = 0xff;
    context->flags &= 0xfff7;
    func_ov001_020788b8(-1, 0);
    data_ov035_020bc4e0->flags &= 0xfff3;
    SetOverlayLayerVisible_0207ef40(TRUE);
    SuspendTaskAndSetFlag_020667b4();
    SetMenuHighlight_0206c2f8(TRUE);
    for (i = 0; i < func_ov001_0206dc38(); i++) {
        const VecFx32 *position;

        func_ov001_0206de40(i);
        position = func_ov001_0206dc4c(i);
        StoreSessionSpawnPoint_02063524(i, position, GetBiasAdjustedField_0206dc80(i));
    }
    func_ov001_02067a6c();
    data_ov001_020a046c[0x10b8] = 0;
    func_ov035_020bb64c();
    func_ov001_0207d658();
    data_ov040_020be260->flags |= 2;
    return 0x12;
}


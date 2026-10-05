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
extern MenuMachine *data_ov040_020be280;
extern u8 *data_ov001_020a048c;
extern u32 func_ov001_0206685c(void);
extern void ReleaseResourceAndDetach(MenuMachine *object);
extern void func_ov001_020788b8(s32 id, u16 value);
extern void func_ov001_0207ef68(BOOL visible);
extern void SuspendTaskAndSetFlag(void);
extern void SetMenuHighlight(BOOL enable);
extern int func_ov001_0206dc38(void);
extern void func_ov001_0206de40(int index);
extern const VecFx32 *func_ov001_0206dc4c(int index);
extern u16 GetBiasAdjustedField(int index);
extern void StoreSessionSpawnPoint(int index, const VecFx32 *position, u16 angle);
extern void func_ov001_02067a6c(void);
extern void func_ov035_020bb66c(void);
extern void func_ov001_0207d680(void);

int FinishAreaTransition(void)
{
    AreaContext *context = data_ov035_020bc4e0;
    int i;

    if (func_ov001_0206685c() != 0) {
        return -1;
    }
    ReleaseResourceAndDetach(data_ov040_020be280);
    context->cursor = 0xff;
    context->flags &= 0xfff7;
    func_ov001_020788b8(-1, 0);
    data_ov035_020bc4e0->flags &= 0xfff3;
    func_ov001_0207ef68(TRUE);
    SuspendTaskAndSetFlag();
    SetMenuHighlight(TRUE);
    for (i = 0; i < func_ov001_0206dc38(); i++) {
        const VecFx32 *position;

        func_ov001_0206de40(i);
        position = func_ov001_0206dc4c(i);
        StoreSessionSpawnPoint(i, position, GetBiasAdjustedField(i));
    }
    func_ov001_02067a6c();
    data_ov001_020a048c[0x10b8] = 0;
    func_ov035_020bb66c();
    func_ov001_0207d680();
    data_ov040_020be280->flags |= 2;
    return 0x12;
}

#include "nitro/types.h"

extern int CanAdvancePastIntro_02063cac(void);
extern BOOL func_ov001_020645c8(u32 flag);
extern int func_ov001_02063a38(void);
extern BOOL ArePartyActorsSettled_0206e5b8(void);
extern BOOL func_ov059_020cd734(void);
extern void func_ov001_020645e8(u32 flag);
extern u32 func_ov021_020af3e8(void);
extern void func_ov001_0208bd38(void);
extern void SetSubModeFrozen_020af434(BOOL frozen);
extern void func_ov001_0206e444(int mode);
extern void RefreshMenuEntries_0206e378(void);
extern void func_ov021_020af7e4(int mode);
extern void *func_ov001_020882b0(void);

void *TryFinishIntroSequence_02088384(void)
{
    if (!CanAdvancePastIntro_02063cac()) {
        if (func_ov001_020645c8(0x3527)
            || (func_ov001_02063a38() != 7 && ArePartyActorsSettled_0206e5b8())
            || (func_ov001_02063a38() == 7 && func_ov059_020cd734())) {
            func_ov001_020645e8(0x3309);
            func_ov001_020645e8(0x3527);
            if (!func_ov021_020af3e8()) {
                func_ov001_0208bd38();
                SetSubModeFrozen_020af434(TRUE);
            }
            func_ov001_0206e444(0);
            RefreshMenuEntries_0206e378();
            func_ov021_020af7e4(0);
            return func_ov001_020882b0;
        }
    }
    return NULL;
}

#include "nitro/types.h"

typedef struct FieldFlags {
    u32 active : 1;
    u32 unk_1 : 3;
    u32 paused : 1;
    u32 reserved : 27;
} FieldFlags;

typedef struct Field {
    u8 pad_000[0x47c];
    s32 state;
    FieldFlags flags;
    u8 pad_484[0x158];
    u8 tween[0x28];
    s32 offset;
} Field;

typedef struct FieldHandle {
    u32 unk_00;
    Field *field;
} FieldHandle;

extern FieldHandle data_ov001_020a04a4;
extern s32 data_0205fde4;

extern BOOL ResumeFieldAfterPause_020704fc(void *panel);
extern void func_ov001_0207a880(int value);
extern void SetupFieldBgLayers_0206ec80(void);
extern void FlushAndFreeBgScreen_0206fdac(Field *field);
extern void SetFieldMenuSuspended_02077b90(s32 suspend, s32 checkPanel);
extern void SetMenuHiddenAndReloadChars_0207525c(int hidden);
extern void func_02052514(void *tween, int mode, int duration, int from, int to);
extern void func_0205255c(void *tween);
extern void SetFieldVisiblePlanes_0206ec3c(void);

#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_BG1OFS (*(vu32 *)0x04000014)
#define REG_WIN0H (*(vu16 *)0x04000040)
#define REG_WIN0V (*(vu16 *)0x04000044)
#define REG_WININ0 (*(vu16 *)0x04000048)
#define REG_WININ1 (*(vu16 *)0x0400004a)

static inline void SetWnd0InsidePlane(int plane, BOOL effect)
{
    u32 value = (REG_WININ0 & ~0x3f) | plane;
    if (effect) {
        value |= 0x20;
    }
    REG_WININ0 = (u16)value;
}

static inline void SetWndOutsidePlane(int plane, BOOL effect)
{
    u32 value = (REG_WININ1 & ~0x3f) | plane;
    if (effect) {
        value |= 0x20;
    }
    REG_WININ1 = (u16)value;
}

static inline void SetVisibleWnd(int mask)
{
    REG_DISPCNT = (REG_DISPCNT & ~0xe000) | (mask << 13);
}

BOOL StartFieldSlideIn_02071898(void)
{
    Field *field = data_ov001_020a04a4.field;

    if (field->state != 2) {
        return FALSE;
    }
    if (data_0205fde4 != 0) {
        return FALSE;
    }
    if (field->flags.paused == 1) {
        ResumeFieldAfterPause_020704fc(NULL);
    }
    func_ov001_0207a880(1);
    SetupFieldBgLayers_0206ec80();
    FlushAndFreeBgScreen_0206fdac(field);
    SetFieldMenuSuspended_02077b90(0, 1);
    SetMenuHiddenAndReloadChars_0207525c(0);
    func_02052514(field->tween, 2, 0x60000, 0, 100);
    func_0205255c(field->tween);
    field->flags.active = 1;
    field->offset = 0x60;
    SetWnd0InsidePlane(1, TRUE);
    SetWndOutsidePlane(0xf, TRUE);
    SetVisibleWnd(1);
    REG_WIN0H = 0xff;
    REG_WIN0V = 0xc0;
    SetFieldVisiblePlanes_0206ec3c();
    REG_BG1OFS = 0x280000;
    field->state = 3;
    return TRUE;
}

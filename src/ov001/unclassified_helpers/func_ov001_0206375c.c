#include "nitro/types.h"

typedef struct Session {
    u8 pad_000[0x20];
    u32 flags;
    u8 pad_024[0x214 - 0x24];
    u32 modeFlags;
} Session;

extern Session *data_ov001_020a0460;
extern void DeactivateManagerEntries_0206e3d8(void);
extern void func_ov001_0206e444(s32 enable);
extern void func_ov021_020af434(s32 value);
extern void func_ov001_0207ef1c(void);
extern int func_ov001_0206dc38(void);
extern int func_ov001_0206dc4c(int index);
extern u16 GetBiasAdjustedField_0206dc80(int index);
extern void func_ov001_02063524(int index, int value, u16 field);
extern void ResumeTaskAndClearFlags_02066780(void);
extern BOOL func_ov001_020645c8(u32 eventId);
extern void func_ov001_020645e8(u32 eventId);
extern void func_ov001_020877dc(void);
extern void func_ov001_020877f4(void);
extern void ReleaseSeqArcHeapLevel_0204e040(int index);
extern int CacheSeqArcStatus_0204e00c(int index);
extern s32 func_ov001_02063a38(void);
extern void func_ov001_02067870(void);
extern void func_ov001_0206daf8(void);
extern void func_ov001_0208804c(void);
extern void func_ov035_020bb334(int stopSeq);
extern int func_02029f48(void);

void func_ov001_0206375c(void) {
    int index;

    data_ov001_020a0460->flags &= ~0x20;
    DeactivateManagerEntries_0206e3d8();
    func_ov001_0206e444(1);
    func_ov021_020af434(0);
    func_ov001_0207ef1c();
    for (index = 0; index < func_ov001_0206dc38(); index++) {
        func_ov001_02063524(index, func_ov001_0206dc4c(index), GetBiasAdjustedField_0206dc80(index));
    }
    ResumeTaskAndClearFlags_02066780();
    if (!func_ov001_020645c8(0x3528)) {
        func_ov001_020877dc();
        func_ov001_020877f4();
    }
    if (func_ov001_020645c8(0x360c)) {
        ReleaseSeqArcHeapLevel_0204e040(1);
        func_ov001_020645e8(0x360c);
        if (func_ov001_02063a38() == 6) {
            func_ov035_020bb334(1);
        } else {
            func_ov001_02067870();
            func_ov001_0206daf8();
            func_ov001_0208804c();
            CacheSeqArcStatus_0204e00c(2);
        }
    } else {
        ReleaseSeqArcHeapLevel_0204e040(2);
        if (func_ov001_02063a38() == 6) {
            func_ov035_020bb334(0);
        }
    }
    if (func_02029f48() == 0) {
        data_ov001_020a0460->modeFlags &= ~0x40000;
    }
}

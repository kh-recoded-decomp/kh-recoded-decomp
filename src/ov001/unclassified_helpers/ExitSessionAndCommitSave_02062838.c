#include "nitro/types.h"

typedef struct RequestFlags {
    u32 mode : 2;
    u32 bit2 : 1;
    u32 unk_3 : 2;
    u32 bit5 : 1;
    u32 unk_6 : 5;
    u32 saveExtra : 1;
    u32 unk_12 : 2;
    u32 bit14 : 1;
    u32 unk_15 : 17;
} RequestFlags;

typedef struct SessionRequest {
    s16 resultId;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 exitKind;
    s16 unk_0A;
    RequestFlags flags;
    u32 unk_10;
} SessionRequest;

typedef struct SaveStaging {
    u8 pad_00[0xcc];
    u32 unk_CC;
    u32 unk_D0;
    u32 unk_D4;
    u16 unk_D8;
    s16 unk_DA;
    s16 unk_DC;
    s8 unk_DE;
    s8 unk_DF;
    s16 unk_E0;
    u8 pad_E2[2];
    void *extraBlock;
} SaveStaging;

typedef struct Session {
    u8 pad_0000[0x208];
    SessionRequest request;
    u8 pad_021c[0x279c];
    SaveStaging *staging;
} Session;

typedef struct SceneArgs {
    s16 unk_00;
    s16 unk_02;
    u8 kind;
    u8 pad_05[2];
    u8 mode : 2;
    u8 bit2 : 1;
    u8 bit3 : 1;
    u8 unk_4 : 1;
    u8 bit5 : 1;
    u8 unk_6 : 2;
    u32 unk_08;
} SceneArgs;

extern Session *data_ov001_020a0460;
extern SceneArgs data_02060850;
extern u8 data_0206085c[];
extern u8 *g_saveBits_0205fe0c;

extern void SetPendingScene_02025644(s32 pendId, s32 pendArg);
extern BOOL func_ov001_020645c8(u32 value);
extern void StoreSessionDifficultyPreset_0206452c(void);
extern u32 ReadGlobalPackedBits_02027348(u32 bitOffset, u32 bitCount);
extern void WriteGlobalPackedBits_02027360(u32 bitOffset, u32 bitCount, u32 value);
extern void func_01ff89a8(const void *src, void *dst, u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

s32 ExitSessionAndCommitSave_02062838(void) {
    Session *session = data_ov001_020a0460;
    SessionRequest *request = &session->request;
    s32 slotBase;

    switch (request->exitKind) {
    case 0:
        SetPendingScene_02025644(1, 0);
        break;
    case 1:
        data_02060850.unk_00 = request->unk_04;
        data_02060850.unk_02 = request->unk_06;
        data_02060850.kind = 2;
        data_02060850.mode = request->flags.mode;
        data_02060850.bit2 = request->flags.bit2;
        data_02060850.bit3 = request->flags.bit5;
        data_02060850.bit5 = request->flags.bit14;
        data_02060850.unk_08 = request->unk_10;
        SetPendingScene_02025644(2, 0);
        break;
    case 2:
        SetPendingScene_02025644(3, (s32)data_0206085c);
        break;
    case 3:
        SetPendingScene_02025644(4, 0);
        break;
    }

    if (!func_ov001_020645c8(0x1a05)) {
        StoreSessionDifficultyPreset_0206452c();
        if (request->resultId == 900) {
            slotBase = ReadGlobalPackedBits_02027348(0x1a00, 2) * 0xf00;
            func_01ff89a8(session->staging, g_saveBits_0205fe0c + ((slotBase + 0x3880) / 32) * 4, 0xcc);
            WriteGlobalPackedBits_02027360(slotBase + 0x3537, 0x20, session->staging->unk_CC);
            WriteGlobalPackedBits_02027360(slotBase + 0x3557, 0x20, session->staging->unk_D0);
            WriteGlobalPackedBits_02027360(slotBase + 0x3577, 0x20, session->staging->unk_D4);
            WriteGlobalPackedBits_02027360(slotBase + 0x3597, 0x10, session->staging->unk_D8);
            if (data_ov001_020a0460->request.flags.saveExtra) {
                g_saveBits_0205fe0c[0x28d4] = session->staging->unk_DE;
                g_saveBits_0205fe0c[0x28d5] = session->staging->unk_E0;
                WriteGlobalPackedBits_02027360(slotBase + 0x330b, 10, session->staging->unk_DA);
                WriteGlobalPackedBits_02027360(slotBase + 0x3315, 10, session->staging->unk_DC);
                func_01ff89a8(session->staging->extraBlock, g_saveBits_0205fe0c + ((slotBase + 0x3300) / 32) * 4, 0x1e0);
                NNSi_FndFreeFromDefaultHeap_0202a1c4(session->staging->extraBlock);
                session->staging->extraBlock = NULL;
            }
            WriteGlobalPackedBits_02027360(slotBase + 0x360d, 7, session->staging->unk_DF);
        }
    }

    if (session->staging != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(session->staging);
        session->staging = NULL;
    }
    return 13;
}

#include "nitro/types.h"

typedef struct UnlockRecord {
    u8 pad_00[0x70];
    u32 unlockedBits;
} UnlockRecord;

typedef struct UnlockList {
    u16 unk_00;
    u16 count;
    UnlockRecord **records;
} UnlockList;

typedef struct SoundContext {
    u8 pad_000[0xc];
    s8 mode;
    s8 subMode;
    u8 pad_00e[0x10b3];
    u8 variantMask;
    u8 pad_10c2[0x6];
    int queuedArcBits[1];
} SoundContext;

extern SoundContext *data_ov001_020a046c;
extern const u8 data_ov001_0209d9ba[][3];
extern const s16 data_ov001_0209d9a8[];
extern const u32 data_ov001_0209d9f0[];
extern UnlockList *func_02036230(void);
extern BOOL func_02036288(u32 value);
extern BOOL func_ov001_020645c8(u32 flagId);
extern BOOL ObjectManager_IsFlagBitSet_0207f068(int bitIndex);
extern s32 func_ov001_02063a38(void);
extern void QueueSoundCommandForArc_0204d670(u32 seqArcNo);
extern void SetPackedBit(int *bitWords, int bitIndex);
extern int GetPackedBitMask(int *bitWords, int bitIndex);

void QueueAreaSoundArchives_02067870(void)
{
    int listIndex;
    int bitIndex;
    UnlockList *list;
    SoundContext *ctx = data_ov001_020a046c;
    int variant;
    s32 seqArcNo;

    list = func_02036230();

    ctx->variantMask = 1;
    if (func_ov001_020645c8(0x3609)) {
        ctx->variantMask |= 2;
    }
    if (func_ov001_020645c8(0x360a)) {
        ctx->variantMask |= 4;
    }
    for (listIndex = 0; listIndex < list->count; listIndex++) {
        UnlockRecord *record = list->records[listIndex];
        for (bitIndex = 0; bitIndex < 17; bitIndex++) {
            if (record->unlockedBits & (1 << bitIndex)) {
                const u8 *arcIds = data_ov001_0209d9ba[bitIndex];
                for (variant = 0; variant < 3; variant++) {
                    if ((ctx->variantMask & (1 << variant)) && arcIds[0] != -1) {
                        QueueSoundCommandForArc_0204d670(arcIds[variant]);
                    }
                }
                SetPackedBit(ctx->queuedArcBits, bitIndex);
            }
        }
        if (func_02036288(data_ov001_0209d9f0[14]) && !GetPackedBitMask(ctx->queuedArcBits, 8)) {
            QueueSoundCommandForArc_0204d670(8);
            SetPackedBit(ctx->queuedArcBits, 8);
        }
    }
    for (bitIndex = 0; bitIndex < 17; bitIndex++) {
        if (!GetPackedBitMask(ctx->queuedArcBits, bitIndex) && ObjectManager_IsFlagBitSet_0207f068(bitIndex)) {
            const u8 *arcIds = data_ov001_0209d9ba[bitIndex];
            for (variant = 0; variant < 3; variant++) {
                if ((ctx->variantMask & (1 << variant)) && arcIds[0] != -1) {
                    QueueSoundCommandForArc_0204d670(arcIds[variant]);
                }
            }
            SetPackedBit(ctx->queuedArcBits, bitIndex);
        }
    }
    if (func_ov001_020645c8(0x360c)) {
        return;
    }
    seqArcNo = data_ov001_0209d9a8[ctx->mode];
    if (seqArcNo >= 0) {
        if (ctx->mode == 6) {
            if (func_ov001_02063a38() == 7) {
                seqArcNo = 0x19d;
            } else if (ctx->subMode == 7) {
                seqArcNo = 0x1a1;
            }
        }
        QueueSoundCommandForArc_0204d670(seqArcNo);
    }
    if (ctx->mode == 8) {
        if (func_ov001_020645c8(0x3609) || func_ov001_020645c8(0x360a)) {
            QueueSoundCommandForArc_0204d670(0x1a2);
        }
    } else if (ctx->mode == 7 && ctx->subMode == 4) {
        QueueSoundCommandForArc_0204d670(0x1a7);
    }
}

#include "nitro/types.h"

typedef struct CardBackupSpec {
    u32 totalSize;
    u32 sectorSize;
    u32 subsectorSize;
} CardBackupSpec;

typedef struct CardCommand {
    s32 result;
    s32 type;
    u32 id;
    u32 src;
    u32 dst;
    u32 length;
    CardBackupSpec spec;
} CardCommand;

typedef struct CardCommon {
    CardCommand *command;
    volatile u32 flags;
    u8 pad_08[0x4fc - 0x08];
    u32 src;
    u32 dst;
    u32 length;
    u8 pad_508[0x510 - 0x508];
    s32 requestType;
    s32 requestRetry;
    s32 requestMode;
    u8 pad_51c[0x540 - 0x51c];
    u8 pageBuffer[0x100];
} CardCommon;

extern CardCommon data_02056fe0;
extern u8 data_02000bac[];
extern void OSi_ReferSymbol_02000b64(void *symbol);
extern u32 CARD_GetBackupSectorSize_02009a7c(void);
extern BOOL func_0200950c(CardCommon *common, s32 requestType, s32 retryCount);
extern void MI_CpuCopy8_01ff89a8(const void *src, void *dst, u32 length);
extern void DC_InvalidateRange_02003414(void *address, u32 length);
extern void DC_FlushRange_0200344c(void *address, u32 length);
extern void DC_WaitWriteBufferEmpty_02003470(void);

void CARDi_RequestStreamCommandCore_020095e0(CardCommon *common)
{
    s32 requestType;
    s32 requestMode;
    s32 retryCount;
    u32 chunkSize;

    requestType = common->requestType;
    requestMode = common->requestMode;
    retryCount = common->requestRetry;
    chunkSize = sizeof(common->pageBuffer);

    OSi_ReferSymbol_02000b64(data_02000bac);
    if (requestType == 0xb) {
        chunkSize = CARD_GetBackupSectorSize_02009a7c();
    } else if (requestType == 0xf) {
        chunkSize = data_02056fe0.command->spec.subsectorSize;
    }
    do {
        const u32 length = (chunkSize < common->length) ? chunkSize : common->length;

        common->command->length = length;
        if ((common->flags & 0x40) != 0) {
            common->flags &= ~0x40;
            common->command->result = 7;
            break;
        }
        switch (requestMode) {
        case 0:
            DC_InvalidateRange_02003414(data_02056fe0.pageBuffer, length);
            common->command->src = common->src;
            common->command->dst = (u32)data_02056fe0.pageBuffer;
            break;
        case 1:
        case 2:
            MI_CpuCopy8_01ff89a8((const void *)common->src, data_02056fe0.pageBuffer, length);
            DC_FlushRange_0200344c(data_02056fe0.pageBuffer, length);
            DC_WaitWriteBufferEmpty_02003470();
            common->command->src = (u32)data_02056fe0.pageBuffer;
            common->command->dst = common->dst;
            break;
        case 3:
            common->command->src = common->src;
            common->command->dst = common->dst;
            break;
        }
        if (!func_0200950c(common, requestType, retryCount)) {
            break;
        }
        if (requestMode == 2) {
            if (!func_0200950c(common, 9, 1)) {
                break;
            }
        } else if (requestMode == 0) {
            MI_CpuCopy8_01ff89a8(data_02056fe0.pageBuffer, (void *)common->dst, length);
        }
        common->src += length;
        common->dst += length;
        common->length -= length;
    } while (common->length > 0);
}

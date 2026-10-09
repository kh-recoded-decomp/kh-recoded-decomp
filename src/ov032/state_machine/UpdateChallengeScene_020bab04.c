#pragma opt_propagation off
#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u16 goal;
    u8 pad_0e[2];
    s16 bestCount;
    s16 currentCount;
    u8 pad_14[0xe];
    u8 category;
    s8 progress;
    u8 stage;
    u8 targetStage;
    s8 conditionType;
    u8 pad_27[0x2e];
    s8 slotIndex;
    s8 slotPending[10];
    u8 rewardFlags;
    u8 pad_61[0xe];
    u8 result;
    u8 pad_70[0x18];
    BOOL succeeded;
    BOOL showSummary;
} ChallengeContext;

typedef struct {
    u8 pad_00[4];
    s16 eventFilter;
    u16 flags;
    s8 mode;
    u8 pad_09[0x1b];
    int messageList[5];
    int totalCount;
    int eventTimer;
    int popupTimer;
    u8 pad_44[4];
    u16 menuId;
} ChallengeScene;

typedef struct {
    ChallengeContext *context;
    ChallengeScene *scene;
} Ov032Globals;

extern Ov032Globals data_ov032_020c0060;
extern u8 *data_ov001_020a0460;

extern void SetFieldEntriesPaused_0206e444(BOOL paused);
extern void SetMenuHighlight_0206c2f8(BOOL enable);
extern BOOL IsEntryFlag2Active_020642d0(int index);
extern void func_0204d7f4(int value);
extern u32 func_ov001_0206e644(void);
extern u32 func_ov001_02063b68(s32 index);
extern BOOL StageEvents_CheckAllEvents_02087844(s16 filterId);
extern u32 SubScene9_Request_02066e50(u8 value);
extern int func_ov001_02067ed4(void);
extern u32 func_ov001_020680cc(int slot, int value);
extern u32 func_ov001_020680e4(int slot, int value);
extern void *func_ov027_020ba2a8(int *list, int index);
extern unsigned short *func_ov027_020ba2e0(int *list, unsigned index, unsigned short *buffer, unsigned size, ...);
extern BOOL ShowFieldPopupText_02071e44(u16 *text, u32 frames);
extern void func_ov032_020ba604(void);
extern BOOL func_ov001_020645c8(u32 value);
extern u32 func_0202b788(u32 index);
extern void UpdateChallengeProgress_020bb57c(ChallengeContext *entry);
extern void SetGroupMenuPercent_020bbb7c(int percent);
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void WriteSessionPackedBits_0206459c(int bitOffset, u32 bitCount, u32 value);
extern int func_ov001_0207d384(int value);

#define sContext (data_ov032_020c0060.context)
#define sScene (data_ov032_020c0060.scene)

int UpdateChallengeScene_020bab04(void)
{
    u16 numberText[0x40];
    u16 summaryText[0x40];
    u16 *text;
    int count;
    s8 offset;
    int current;

    if (sScene->flags & 0x4000) {
        SetFieldEntriesPaused_0206e444(TRUE);
        SetMenuHighlight_0206c2f8(TRUE);
        sScene->flags |= 0x8000;
        return 0xd;
    }
    if (sScene->flags & 0x12) {
        return -1;
    }
    if (sScene->mode >= 0) {
        return 9;
    }
    if (IsEntryFlag2Active_020642d0(0)) {
        sScene->flags |= 0x10;
        func_0204d7f4(0x20);
        return 0xb;
    }
    if (func_ov001_0206e644()) {
        data_ov001_020a0460[0x27b6] |= 0x10;
        SetFieldEntriesPaused_0206e444(TRUE);
        SetMenuHighlight_0206c2f8(TRUE);
        sScene->flags |= 0x8000;
        return 8;
    }
    sScene->totalCount = func_ov001_02063b68(0xe) + func_ov001_02063b68(0xf);
    current = sContext->currentCount;
    if (current > sContext->bestCount) {
        if ((int)func_ov001_02063b68(0x1b) <= current) {
            current = func_ov001_02063b68(0x1b);
        }
        sContext->bestCount = current;
    }
    if (sContext->slotPending[sContext->slotIndex] != 0) {
        if (StageEvents_CheckAllEvents_02087844(sScene->eventFilter)) {
            if (sScene->eventTimer == 10) {
                SubScene9_Request_02066e50(0);
            }
            if (sScene->eventTimer == 1) {
                sContext->slotPending[sContext->slotIndex] = 0;
                func_ov001_020680cc(func_ov001_02067ed4(), 0x16);
                func_ov001_020680e4(func_ov001_02067ed4(), 0x17);
                if (sContext->currentCount == sContext->bestCount) {
                    sContext->succeeded = TRUE;
                    ShowFieldPopupText_02071e44(func_ov027_020ba2a8(sScene->messageList, sContext->stage == sContext->targetStage ? 0x30 : 0x2f), 2000);
                    if (sContext->showSummary) {
                        sScene->popupTimer = 150;
                    }
                }
                func_ov032_020ba604();
            }
            sScene->eventTimer--;
        } else {
            sScene->eventTimer = 10;
        }
    }
    if (sScene->menuId == 0x3f && !(sContext->rewardFlags & 0x80) && func_ov001_02063b68(0x1a) == 0 && func_ov001_020645c8(0x380b)) {
        sContext->rewardFlags |= 0x80;
        ShowFieldPopupText_02071e44(func_ov027_020ba2a8(sScene->messageList, 0x35), 2000);
    }
    if (sScene->popupTimer > 0) {
        sScene->popupTimer--;
        if (sScene->popupTimer == 150) {
            ChallengeContext *ctx = sContext;
            int type = ctx->conditionType;
            if (type >= 0) {
                if (type == 0x16 && ctx->goal == 1) {
                    text = func_ov027_020ba2a8(sScene->messageList, 0x3e);
                } else if (type == 0x18 && ctx->goal == 1) {
                    text = func_ov027_020ba2a8(sScene->messageList, 0x3f);
                } else if (type == 0x19 && ctx->goal == 1) {
                    text = func_ov027_020ba2a8(sScene->messageList, 0x40);
                } else if (type == 0x1d && ctx->goal == 1) {
                    text = func_ov027_020ba2a8(sScene->messageList, 0x41);
                } else if (type == 0x1e && ctx->goal == 1) {
                    text = func_ov027_020ba2a8(sScene->messageList, 0x42);
                } else {
                    count = ctx->goal;
                    if (count != 0) {
                        offset = type - 3;
                        if ((u8)offset <= 4 && func_0202b788((u8)offset)) {
                            count--;
                        }
                        text = func_ov027_020ba2e0(sScene->messageList, sContext->conditionType + 3, numberText, 0x40, count);
                    } else {
                        text = func_ov027_020ba2a8(sScene->messageList, type + 3);
                    }
                }
                text = func_ov027_020ba2e0(sScene->messageList, 0x2a, summaryText, 0x40, text);
                ShowFieldPopupText_02071e44(text, 2000);
            }
        } else if (sScene->popupTimer == 0 && sContext->showSummary) {
            ShowFieldPopupText_02071e44(func_ov027_020ba2a8(sScene->messageList, sContext->succeeded ? 0x32 : 0x31), 2000);
        }
    }
    if (sContext->conditionType >= 0) {
        UpdateChallengeProgress_020bb57c(sContext);
        count = sContext->progress;
        if (count == -1) {
            SetGroupMenuPercent_020bbb7c(100);
        } else {
            SetGroupMenuPercent_020bbb7c(count);
        }
    }
    if (sContext->result) {
        if (sContext->slotPending[sContext->slotIndex] > 0) {
            func_ov001_020680cc(func_ov001_02067ed4(), 0x18);
            func_ov001_020680e4(func_ov001_02067ed4(), 0x19);
        } else {
            func_ov001_020680cc(func_ov001_02067ed4(), 0x16);
            func_ov001_020680e4(func_ov001_02067ed4(), 0x17);
        }
    }
    if (sContext->category == 1 && sContext->stage == 1 && !IsGlobalPackedBitSet_02027304(0xf8c) && (int)func_ov001_02063b68(2) > 0) {
        WriteSessionPackedBits_0206459c(0x3806, 1, 1);
    }
    if (sContext->category == 1 && sContext->stage == 2 && !IsGlobalPackedBitSet_02027304(0xf8d) && sContext->succeeded) {
        WriteSessionPackedBits_0206459c(0x3807, 1, 1);
    }
    if (sContext->category == 1 && sContext->stage == 1 && !IsGlobalPackedBitSet_02027304(0xfa4) && sContext->succeeded) {
        WriteSessionPackedBits_0206459c(0x3808, 1, 1);
    }
    if (sContext->result == 1) {
        sScene->popupTimer = 300;
        func_ov001_0207d384(1);
        ChallengeContext *ctx = sContext;
        u8 category = ctx->category;
        if ((category == 1 && ctx->stage == 1) || (category == 1 && ctx->stage == 2) ||
            (category == 5 && ctx->stage == 1) || (category == 5 && ctx->stage == 2) ||
            (category == 7 && ctx->stage == 1) || (category == 7 && ctx->stage == 2) ||
            (category == 12 && ctx->stage == 1) || (category == 16 && ctx->stage == 1)) {
            WriteSessionPackedBits_0206459c(0x3809, 1, 1);
        } else {
            WriteSessionPackedBits_0206459c(0x3809, 1, 0);
        }
    } else if (sContext->result == 2) {
        if (sScene->menuId == 0x3e && !(sContext->rewardFlags & (1 << sContext->slotIndex))) {
            sContext->rewardFlags |= (u8)(1 << sContext->slotIndex);
            ShowFieldPopupText_02071e44(func_ov027_020ba2a8(sScene->messageList, 0x33), 2000);
        }
        if (sScene->menuId == 0x3f) {
            ShowFieldPopupText_02071e44(func_ov027_020ba2a8(sScene->messageList, 0x34), 2000);
        }
        func_ov001_0207d384(1);
        *(u16 *)(data_ov001_020a0460 + 0x27fa) = 0x55;
    }
    sContext->result = 0;
    return -1;
}

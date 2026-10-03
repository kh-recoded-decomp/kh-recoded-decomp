#include "nitro/types.h"

typedef struct {
    u8 kind;
    u8 timer;
    u8 flags;
    u8 pad_03;
    int args[3];
} HudMessage;

typedef struct {
    u8 pad_000[0x338];
    HudMessage message;
} StageWork;

extern u8 *data_ov035_020bc4e0;
extern void ShowFieldMessageLine_02072ad0(int kind, ...);
extern void HideHudCaption_02072c40(void);
extern s32 GetHudLabelId_02072d44(int labelIndex);
extern const u16 *GetModePrimaryMessage_02072d5c(int mode);
extern const u16 *GetModeSecondaryMessage_02072d98(int mode);

void UpdateStageHudMessage_020be078(void) {
    HudMessage *message = &(*(StageWork **)(data_ov035_020bc4e0 + 0xb8))->message;

    if (message->flags & 1) {
        if (message->timer != 0) {
            switch (message->kind) {
            case 2:
                ShowFieldMessageLine_02072ad0(message->kind, message->args[0]);
                break;
            case 3:
                ShowFieldMessageLine_02072ad0(message->kind, message->args[0]);
                break;
            case 5:
                ShowFieldMessageLine_02072ad0(message->kind, message->args[0]);
                break;
            case 6:
                ShowFieldMessageLine_02072ad0(message->kind, message->args);
                break;
            case 11:
                ShowFieldMessageLine_02072ad0(message->kind, GetHudLabelId_02072d44(message->args[0]),
                                              GetModePrimaryMessage_02072d5c(message->args[1]));
                break;
            case 12:
                ShowFieldMessageLine_02072ad0(message->kind, GetHudLabelId_02072d44(message->kind),
                                              GetModePrimaryMessage_02072d5c(message->args[1]),
                                              GetModeSecondaryMessage_02072d98(message->args[2]));
                break;
            default:
                ShowFieldMessageLine_02072ad0(message->kind);
                break;
            }
            message->timer--;
        } else {
            message->flags &= ~1;
            HideHudCaption_02072c40();
        }
    }
}

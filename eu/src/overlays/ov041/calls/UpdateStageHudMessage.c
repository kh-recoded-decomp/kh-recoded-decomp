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

extern u8 *data_ov035_020bc500;
extern void ShowFieldMessageLine_02072ad0(int kind, ...);
extern void HideHudCaption(void);
extern s32 GetHudLabelId(int labelIndex);
extern const u16 *GetModePrimaryMessage(int mode);
extern const u16 *GetModeSecondaryMessage(int mode);

void UpdateStageHudMessage(void)
{
    HudMessage *message = &(*(StageWork **)(data_ov035_020bc500 + 0xb8))->message;

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
                ShowFieldMessageLine_02072ad0(message->kind, GetHudLabelId(message->args[0]),
                                              GetModePrimaryMessage(message->args[1]));
                break;
            case 12:
                ShowFieldMessageLine_02072ad0(message->kind, GetHudLabelId(message->kind),
                                              GetModePrimaryMessage(message->args[1]),
                                              GetModeSecondaryMessage(message->args[2]));
                break;
            default:
                ShowFieldMessageLine_02072ad0(message->kind);
                break;
            }
            message->timer--;
        } else {
            message->flags &= 0xfe;
            HideHudCaption();
        }
    }
}

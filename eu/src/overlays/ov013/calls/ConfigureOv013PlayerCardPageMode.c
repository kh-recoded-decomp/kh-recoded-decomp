#include "nitro/types.h"

typedef struct {
    u8 blockA : 1;
    u8 blockB : 1;
    u8 pad_2to7 : 6;
} StatusFlagsD259;

extern s8 data_0206085c[];
extern int IsPanelBusy(void);
extern void InitMenuScreenGraphics(void);
extern void ResetOv013PlayerCardPageDisplay(void);
extern void SetOv013MainLayerMask1e(void);
extern void SetPanelPhase(int mode);
extern int data_ov013_02074ce0;

/* Selects the player-card page path from the current position and every-tenth-entry rule. */
void ConfigureOv013PlayerCardPageMode(void) {
    int position = *(s8 *)(data_ov013_02074ce0 + 0x2f0);
    if (IsPanelBusy() == 0) {
        position = data_0206085c[0x11] + data_0206085c[0x10];
    }
    if ((position + 1) % 10 != 0) {
        u8 status99 = *(u8 *)(data_ov013_02074ce0 + 0x99);
        if ((((u32)status99 << 0x1d) >> 0x1f) == 0) {
            int flags = status99;
            flags = flags & ~8;
            *(u8 *)(data_ov013_02074ce0 + 0x99) = (u8)flags;
            *(int *)(data_ov013_02074ce0 + 0x2e8) = position;
            InitMenuScreenGraphics();
            SetOv013MainLayerMask1e();
            return;
        }
        if (((StatusFlagsD259 *)(data_ov013_02074ce0 + 0xd259))->blockA) {
            return;
        }
        if (((StatusFlagsD259 *)(data_ov013_02074ce0 + 0xd259))->blockB) {
            return;
        }
        {
            int flags = status99;
            flags = flags & ~8;
            *(u8 *)(data_ov013_02074ce0 + 0x99) = (u8)flags;
        }
        SetPanelPhase(1);
        return;
    }
    *(int *)(data_ov013_02074ce0 + 0x2e8) = position;
    InitMenuScreenGraphics();
    ResetOv013PlayerCardPageDisplay();
}

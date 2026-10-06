#include "nitro/types.h"

typedef struct {
    u8 blockA : 1;
    u8 blockB : 1;
    u8 pad_2to7 : 6;
} StatusFlagsD259;

extern s8 data_0206085c[];
extern int IsPanelBusy(void);
extern void InitMenuScreenGraphics(void);
extern void func_ov013_0206cff0(void);
extern void func_ov013_0206cfd8(void);
extern void func_ov013_0207174c(int mode);
extern int data_ov013_02074ce0;

/* Advances the day counter and runs the matching panel transition. */
void func_ov013_0206caa4(void) {
    int day = *(s8 *)(data_ov013_02074ce0 + 0x2f0);
    if (IsPanelBusy() == 0) {
        day = data_0206085c[0x11] + data_0206085c[0x10];
    }
    if ((day + 1) % 10 != 0) {
        u8 status99 = *(u8 *)(data_ov013_02074ce0 + 0x99);
        if ((((u32)status99 << 0x1d) >> 0x1f) == 0) {
            int flags = status99;
            flags = flags & ~8;
            *(u8 *)(data_ov013_02074ce0 + 0x99) = (u8)flags;
            *(int *)(data_ov013_02074ce0 + 0x2e8) = day;
            InitMenuScreenGraphics();
            func_ov013_0206cfd8();
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
        func_ov013_0207174c(1);
        return;
    }
    *(int *)(data_ov013_02074ce0 + 0x2e8) = day;
    InitMenuScreenGraphics();
    func_ov013_0206cff0();
}

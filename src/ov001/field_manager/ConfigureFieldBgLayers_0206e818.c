#include "nitro/types.h"
#include "nitro/hw.h"

typedef struct FieldManager {
    u8 pad_000[0x42c];
    void *overlayScreen;
    u8 pad_430[0x480 - 0x430];
    u32 unk_480_0 : 6;
    u32 use256ColorBg : 1;
    u32 unk_480_7 : 25;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04a4;

#define BG0CNT (*(volatile u16 *)REG_BG0CNT_ADDR)
#define BG1CNT (*(volatile u16 *)REG_BG1CNT_ADDR)
#define BG2CNT (*(volatile u16 *)REG_BG2CNT_ADDR)
#define BG3CNT (*(volatile u16 *)REG_BG3CNT_ADDR)

void ConfigureFieldBgLayers_0206e818(void)
{
    FieldManager *manager = data_ov001_020a04a4.manager;

    if (manager->overlayScreen != NULL && manager->use256ColorBg == 1) {
        BG3CNT = (u16)((BG3CNT & 0x43) | 0x1d80);
        BG2CNT = (u16)((BG2CNT & 0x43) | 0x1e80);
    } else {
        BG2CNT = (u16)((BG2CNT & 0x43) | 0x1e08);
        BG3CNT = (u16)((BG3CNT & 0x43) | 0x1d00);
    }
    BG1CNT = (u16)((BG1CNT & 0x43) | 0x1f00);
    BG0CNT = (u16)((BG0CNT & ~3) | 3);
    BG3CNT = (u16)((BG3CNT & ~3) | 2);
    BG2CNT = (u16)((BG2CNT & ~3) | 0);
    BG1CNT = (u16)((BG1CNT & ~3) | 1);
}

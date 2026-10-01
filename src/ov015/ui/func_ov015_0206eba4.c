#include "nitro/types.h"

typedef struct PanelItem {
    u8 pad_00[0x94];
    u32 flag0 : 1;
    u32 isLinked : 1;
} PanelItem;

extern void func_ov002_020620fc(int selector);
extern int func_ov002_02066c78(int a, int b, int c, int d);
extern int func_ov002_020621c4(int a, int b);
extern void func_ov002_02061964(int mode, int x, int y, int size, int textId);
extern int func_ov002_02061930(void);
extern int func_ov002_0206193c(void);
extern int func_ov002_02066484(void *buf, int bufLen, int value, int digits);
extern void func_ov002_02062890(int size[2], int mode, int textId);
extern int OS_SNPrintf_0202e080(void *buf, int bufLen, int format, ...);
extern PanelItem *func_ov027_020b90a4(void *container, int itemId);
extern s8 *data_ov015_0207e960;
extern int data_ov015_0207a19c[];

void func_ov015_0206eba4(void) {
    u16 buf[64] = {0};
    int size[2];
    int textId;
    int format;

    func_ov002_020620fc(-1);
    textId = func_ov002_02066c78(6, 0, 0, 0);
    textId = func_ov002_020621c4(textId, 0);
    func_ov002_02061964(1, 0x1c, 0x14, 10, textId);

    textId = func_ov002_02061930();
    func_ov002_02061964(1, 0x1c, 0x20, 2, textId);

    textId = func_ov002_0206193c();
    textId = func_ov002_02066484(buf, 0x80, textId, 0xd);
    func_ov002_02061964(1, 0x16, 0x51, 0xc, textId);

    textId = func_ov002_020621c4(data_ov015_0207e960[3] + 0x40, 0);
    func_ov002_02062890(size, 0, textId);

    textId = func_ov002_020621c4(data_ov015_0207e960[3] + 0x40, 0);
    func_ov002_02061964(1, 0x52, 0x9c - size[1] / 2, 2, textId);

    format = func_ov002_020621c4(0x72, 0);
    OS_SNPrintf_0202e080(buf, 0x40, format,
        data_ov015_0207e960[3] + 1, data_ov015_0207a19c[func_ov002_02066c78(6, 0, 0, 0)]);
    func_ov002_02061964(1, 0x55, 0xac, 2, (int)buf);

    if (!(func_ov027_020b90a4((u8 *)data_ov015_0207e960 + 0x6ac0, 0x13)->isLinked)) {
        return;
    }
    textId = func_ov002_020621c4(0x20, 0);
    func_ov002_02062890(size, 0, textId);
    textId = func_ov002_020621c4(data_ov015_0207e960[2] + 0x18, 0);
    func_ov002_02061964(1, 0x20 - size[0] / 2, 0xb0, 0xc, textId);
}

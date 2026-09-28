#include "nitro/types.h"

extern void func_ov002_0206203c(int value);
extern int func_ov002_02066c78(int a, int b, int c, int d);
extern int func_ov002_020621c4(int a, int b);
extern void func_ov002_020619e8(int mode, int x, int y, int size, int textId);
extern int func_ov002_02061930(void);
extern int func_ov002_0206193c(void);
extern int func_ov002_02066484(void *buf, int bufLen, int value, int digits);
extern void func_ov002_020627e8(int size[2], int mode, int textId);
extern s8 *data_ov015_0207e960;

void func_ov015_0206edc8(void) {
    u16 buf[64] = {0};
    int size[2];
    int textId;

    func_ov002_0206203c(-1);
    textId = func_ov002_02066c78(6, 0, 0, 0);
    textId = func_ov002_020621c4(textId, 0);
    func_ov002_020619e8(1, 0x1c, 0x14, 10, textId);

    textId = func_ov002_02061930();
    func_ov002_020619e8(1, 0x1c, 0x20, 2, textId);

    textId = func_ov002_0206193c();
    textId = func_ov002_02066484(buf, 0x80, textId, 0xd);
    func_ov002_020619e8(1, 0x16, 0x51, 0xc, textId);

    textId = func_ov002_020621c4(data_ov015_0207e960[3] + 0x40, 0);
    func_ov002_020627e8(size, 1, textId);

    textId = func_ov002_020621c4(data_ov015_0207e960[3] + 0x40, 0);
    func_ov002_020619e8(1, 0x52, 0x9c - size[1] / 2, 2, textId);
}

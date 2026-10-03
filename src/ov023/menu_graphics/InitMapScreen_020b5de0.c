#include "nitro/types.h"

typedef struct ManagerDesc {
    u32 key;
    u32 word1;
    u32 word2;
    u32 word3;
} ManagerDesc;

typedef struct PointPair {
    int x;
    int y;
} PointPair;

typedef struct MarkerSlot {
    int handle;
    int value;
} MarkerSlot;

typedef struct MapScreen {
    char pad00[0xc];
    int vramBase;
    char pad10[0x40 - 0x10];
    int state;
    char pad44[0x58 - 0x44];
    char manager[0x648c - 0x58];
    int handles[6];
    MarkerSlot markers[121];
} MapScreen;

extern ManagerDesc data_ov023_020b6e94;
extern PointPair data_ov023_020b6e84;
extern char data_ov023_020b5b51[];

extern void func_0204efd0(void *manager, ManagerDesc *desc);
extern void func_0204f00c(void *manager, u32 key);
extern int func_0204f0b4(void *manager, int type, int flag);
extern void func_0204f13c(void *manager, int handle, PointPair *pos);
extern void func_0204f178(void *manager, int handle, int value);
extern void func_0204f378(void *manager, int handle, int value);
extern void func_0204f3c8(void *manager, int handle, int value);
extern void func_0204f400(void *manager, int alpha);
extern void func_0204f480(void *manager, int handle, int mode);
extern void func_0204f498(void *manager, int value);
extern void func_0204f4a4(void *manager, int handle, void *callback, int arg, int mode);
extern void func_01ff86fc(int value, void *dest, int size);
extern u32 func_ov001_02071214(int slot);
extern BOOL func_ov001_020728e4(void);
extern BOOL func_ov001_020645c8(int flag);
extern int func_ov001_02064574(int offset, int bits);
extern void func_ov023_020b5db4(MapScreen *screen, int palette);

void InitMapScreen_020b5de0(MapScreen *screen)
{
    ManagerDesc desc = data_ov023_020b6e94;
    PointPair pos = data_ov023_020b6e84;
    int i;

    desc.key = ((screen->vramBase + 0x8000) & 0xfffffc) << 7 | 0x80000000;
    func_0204efd0(screen->manager, &desc);
    func_0204f00c(screen->manager, func_ov001_02071214(10));
    screen->handles[0] = func_0204f0b4(screen->manager, 0, 0);
    screen->handles[1] = func_0204f0b4(screen->manager, 2, 0);
    screen->handles[2] = func_0204f0b4(screen->manager, 4, 0);
    screen->handles[3] = func_0204f0b4(screen->manager, 4, 0);
    screen->handles[4] = func_0204f0b4(screen->manager, 0x1c, 0);
    screen->handles[5] = func_0204f0b4(screen->manager, 1, 1);
    func_0204f13c(screen->manager, screen->handles[0], &pos);
    func_0204f13c(screen->manager, screen->handles[1], &pos);
    func_0204f13c(screen->manager, screen->handles[4], &pos);
    pos.x = 0xc0000;
    pos.y = 0x96000;
    func_0204f13c(screen->manager, screen->handles[5], &pos);
    func_0204f480(screen->manager, screen->handles[0], 3);
    func_0204f480(screen->manager, screen->handles[1], 3);
    func_0204f480(screen->manager, screen->handles[2], 3);
    func_0204f480(screen->manager, screen->handles[3], 3);
    func_0204f480(screen->manager, screen->handles[4], 3);
    func_0204f480(screen->manager, screen->handles[5], 0);
    func_0204f178(screen->manager, screen->handles[0], 1);
    func_0204f178(screen->manager, screen->handles[1], 1);
    func_0204f178(screen->manager, screen->handles[2], 1);
    func_0204f178(screen->manager, screen->handles[3], 1);
    func_0204f178(screen->manager, screen->handles[4], 0);
    func_0204f178(screen->manager, screen->handles[5], 0);
    func_0204f378(screen->manager, screen->handles[4], 0);
    func_0204f378(screen->manager, screen->handles[5], 0);
    if (func_ov001_020728e4()) {
        if (!func_ov001_020645c8(0x360a)) {
            func_0204f378(screen->manager, screen->handles[3], 0);
        }
        if (!func_ov001_020645c8(0x3609)) {
            func_0204f378(screen->manager, screen->handles[2], 0);
        }
    } else {
        func_0204f378(screen->manager, screen->handles[2], 0);
        func_0204f378(screen->manager, screen->handles[3], 0);
    }
    func_0204f3c8(screen->manager, screen->handles[4], 1);
    func_0204f498(screen->manager, 1);
    screen->state = 0;
    func_0204f4a4(screen->manager, screen->handles[4], data_ov023_020b5b51, 0, 2);
    func_01ff86fc(-1, screen->markers, sizeof(screen->markers));
    func_ov023_020b5db4(screen, func_ov001_02064574(0x1a0f, 3));
    for (i = 0; i < 121; i++) {
        screen->markers[i].handle = func_0204f0b4(screen->manager, 0, 0);
        screen->markers[i].value = 0;
        func_0204f480(screen->manager, screen->markers[i].handle, 3);
    }
    func_0204f400(screen->manager, 8);
}

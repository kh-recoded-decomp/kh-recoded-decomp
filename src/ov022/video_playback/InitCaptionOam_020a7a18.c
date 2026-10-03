#include "nitro/types.h"

typedef struct {
    u32 attr01;
    u16 attr2;
    u16 affine;
} OamEntry;

extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern void func_0200344c(void *buffer, u32 size);
extern void func_020073c8(const void *src, u32 offset, u32 size);
extern void GXS_LoadOAM_0200742c(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);

#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_DISPCNT_SUB (*(vu32 *)0x04001000)

void InitCaptionOam_020a7a18(BOOL mainScreen) {
    int count = 0;
    OamEntry *oam = NNSi_FndAllocFromDefaultHeapEx_0202a19c(0x400, 0x20);
    int i;
    int x;
    int y;

    if (mainScreen) {
        REG_DISPCNT = (REG_DISPCNT & 0xffbfff9f) | 0x20;
    } else {
        REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x60) | 0x20;
    }
    for (i = 0; i < 0x80; i++) {
        oam[i].attr01 = 0xc0;
        *(u32 *)&oam[i].attr2 = 0;
    }
    for (y = 0; y < 0xc0; y += 0x40) {
        for (x = 0; x < 0x100; x += 0x40) {
            oam[count].attr01 = ((y + 0x10) & 0xff) | 0xc0000c00 | ((u32)(x << 23) >> 7);
            oam[count].attr2 = (x / 8 + ((y / 8) << 5)) | 0xfc00;
            count++;
        }
    }
    func_0200344c(oam, 0x400);
    if (mainScreen) {
        func_020073c8(oam, 0, 0x400);
    } else {
        GXS_LoadOAM_0200742c(oam, 0, 0x400);
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(oam);
}

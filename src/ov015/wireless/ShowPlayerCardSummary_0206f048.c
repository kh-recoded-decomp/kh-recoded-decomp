#include "nitro/types.h"

typedef struct {
    u8 slotIds[0x10];
    u16 name[0xb];
    u16 title[0x21];
    u8 rank;
    u8 pad_69[7];
} PlayerRecord;

typedef struct {
    u8 pad_0000[0xec];
    int current;
    u8 pad_00f0[0xcf58 - 0xf0];
    PlayerRecord records[1];
} CardWork;

extern CardWork *data_ov015_0207e960;
extern void func_ov002_0206203c(int selector);
extern u16 *CopyWideStringWithNewline_02066484(u16 *dst, int size, const u16 *src, int breakIndex);
extern void func_ov002_020619e8(int screen, int x, int y, int color, const void *text);
extern void func_ov002_02061af0(int screen, int x, int y, int color, int width, const void *text);
extern const u16 *func_ov002_020621c4(int index, int bank);
extern void *OS_SNPrintf_0202e080(u16 *dst, unsigned int len, const u16 *fmt, ...);
extern s32 CountMatchingSlotIds_02069f9c(const u8 *slotIds);
extern unsigned int func_0202a9d0(unsigned int range);

void ShowPlayerCardSummary_0206f048(int skillIndex) {
    u16 buf[0x40] = {0};
    CardWork *work;
    const u16 *fmt;
    const u16 *rankText;
    int count;

    func_ov002_0206203c(-1);
    func_ov002_020619e8(1, 0x10, 0xc, 0xc, CopyWideStringWithNewline_02066484(buf, 0x80, data_ov015_0207e960->records[data_ov015_0207e960->current].title, 0xd));
    work = data_ov015_0207e960;
    OS_SNPrintf_0202e080(buf, 0x40, func_ov002_020621c4(0x27, 0), work->records[work->current].name);
    func_ov002_02061af0(1, 0x1c, 0x8f, 2, 6, buf);
    count = CountMatchingSlotIds_02069f9c(data_ov015_0207e960->records[data_ov015_0207e960->current].slotIds);
    if (count >= 10) {
        func_ov002_020619e8(1, 0x1c, 0x9b, 2, func_ov002_020621c4(func_0202a9d0(5) + 0x28, 0));
    } else if (count >= 5) {
        func_ov002_020619e8(1, 0x1c, 0x9b, 2, func_ov002_020621c4(func_0202a9d0(5) + 0x2d, 0));
    } else {
        func_ov002_020619e8(1, 0x1c, 0x9b, 2, func_ov002_020621c4(func_0202a9d0(5) + 0x32, 0));
    }
    work = data_ov015_0207e960;
    fmt = func_ov002_020621c4(0x37, 0);
    rankText = func_ov002_020621c4(work->records[work->current].rank + 0x18, 0);
    OS_SNPrintf_0202e080(buf, 0x40, fmt, rankText, func_ov002_020621c4(skillIndex + 0x38, 0));
    func_ov002_020619e8(1, 0x1c, 0xa7, 2, buf);
}

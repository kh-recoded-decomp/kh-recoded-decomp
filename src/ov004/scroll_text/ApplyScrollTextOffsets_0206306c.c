#include "nitro/types.h"
#include "nitro/fx_types.h"

#define REG_BG1OFS (*(vu32 *)0x04000014)
#define REG_BG2OFS (*(vu32 *)0x04000018)
#define REG_BG3OFS (*(vu32 *)0x0400001c)
#define REG_DB_BG1OFS (*(vu32 *)0x04001014)
#define REG_DB_BG2OFS (*(vu32 *)0x04001018)
#define REG_DB_BG3OFS (*(vu32 *)0x0400101c)

typedef struct {
    s16 x;
    s16 y;
} ScrollOffset;

typedef struct {
    u8 pad_00[0x10944];
    ScrollOffset mainScroll;
    ScrollOffset mainPrevScroll;
    u8 pad_1094c[0x21284 - 0x1094c];
    ScrollOffset subScroll;
    ScrollOffset subPrevScroll;
    u8 pad_2128c[0x23aac - 0x2128c];
    fx32 rollPosition;
    fx32 lastRollPosition;
    fx32 prevRollPosition;
    u8 pad_23ab8[0x30350 - 0x23ab8];
    u32 offsetsSaved : 1;
    u32 oddFrame : 1;
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals g_scrollText_020645a0;

extern void SaveScrollOffsets_02062ff4(void);
extern int RoundFx32ToInt_020614a4(fx32 value);

void ApplyScrollTextOffsets_0206306c(void)
{
    int mainX = g_scrollText_020645a0.work->mainScroll.x;
    int mainY = g_scrollText_020645a0.work->mainScroll.y;
    int subX = g_scrollText_020645a0.work->subScroll.x;
    int subY = g_scrollText_020645a0.work->subScroll.y;
    fx32 roll = g_scrollText_020645a0.work->rollPosition;
    u32 mainOffset;
    u32 subOffset;

    if (!g_scrollText_020645a0.work->offsetsSaved) {
        SaveScrollOffsets_02062ff4();
        g_scrollText_020645a0.work->offsetsSaved = 1;
    }
    if (!g_scrollText_020645a0.work->oddFrame) {
        ScrollTextWork *work = g_scrollText_020645a0.work;

        mainX = work->mainPrevScroll.x + (mainX - work->mainPrevScroll.x) / 2;
        mainY = work->mainPrevScroll.y + (mainY - work->mainPrevScroll.y) / 2;
        subX = work->subPrevScroll.x + (subX - work->subPrevScroll.x) / 2;
        subY = work->subPrevScroll.y + (subY - work->subPrevScroll.y) / 2;
        roll = work->prevRollPosition + (roll - work->prevRollPosition) / 2;
    } else {
        SaveScrollOffsets_02062ff4();
    }
    REG_BG1OFS = ((u32)(RoundFx32ToInt_020614a4(roll) << 24) >> 8) & 0x1ff0000;
    REG_DB_BG1OFS = ((u32)(RoundFx32ToInt_020614a4(roll) << 24) >> 8) & 0x1ff0000;
    mainOffset = (mainX & 0x1ff) | ((mainY << 16) & 0x1ff0000);
    REG_BG2OFS = mainOffset;
    REG_BG3OFS = mainOffset;
    subOffset = (subX & 0x1ff) | ((subY << 16) & 0x1ff0000);
    REG_DB_BG2OFS = subOffset;
    REG_DB_BG3OFS = subOffset;
    g_scrollText_020645a0.work->oddFrame = !g_scrollText_020645a0.work->oddFrame;
}

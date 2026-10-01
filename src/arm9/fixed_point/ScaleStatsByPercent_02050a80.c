#include "nitro/types.h"

typedef struct {
    u8 pad_00;
    u8 level;
    u16 pad_02;
    u16 hp;
    u16 stats[4];
} UnitStats;

extern u8 *data_0205fe0c;
extern int ReadGlobalPackedBits_02027348(int bitOffset, int bitCount);
extern int func_ov001_02064574(int bitOffset, int bitCount);
extern s32 func_02023dbc(s32 numerator, s32 denominator);

void ScaleStatsByPercent_02050a80(UnitStats *stats, BOOL useOverlay)
{
    int percent = 100;

    if (*(s8 *)(data_0205fe0c + 0x28d4) == 6 && ReadGlobalPackedBits_02027348(0x1a00, 2) != 3) {
        if (useOverlay) {
            percent = func_ov001_02064574(0x3700, 0x10);
        } else {
            percent = ReadGlobalPackedBits_02027348(ReadGlobalPackedBits_02027348(0x1a00, 2) * 0xf00 + 0x3700, 0x10);
        }
    }
    stats->level = func_02023dbc(stats->level * percent, 100);
    stats->hp = func_02023dbc(stats->hp * percent, 100);
    stats->stats[0] = func_02023dbc(stats->stats[0] * percent, 100);
    stats->stats[1] = func_02023dbc(stats->stats[1] * percent, 100);
    stats->stats[2] = func_02023dbc(stats->stats[2] * percent, 100);
    stats->stats[3] = func_02023dbc(stats->stats[3] * percent, 100);
}

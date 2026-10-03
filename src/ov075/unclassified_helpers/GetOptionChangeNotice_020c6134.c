#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct OptionMenu {
    u8 pad_00000[0x13e7d];
    u8 choice;
    u8 pad_13e7e[0x13ea0 - 0x13e7e];
    int page;
} OptionMenu;

typedef struct SaveData {
    u8 pad_0000[0x28d4];
    s8 worldId;
    s8 areaId;
    u8 pad_28d6[0x2c62 - 0x28d6];
    u8 difficulty;
    u8 option2c63;
    u8 pad_2c64;
    u8 option2c65;
} SaveData;

typedef struct PlayerStats {
    u8 pad_00[4];
    u16 level;
} PlayerStats;

extern SaveData *data_0205fe0c;

extern int func_ov075_020c4988(void);
extern int ReadGlobalPackedBits_02027348(int index, int width);
extern int func_ov001_020644b0(void);
extern void WriteSessionPackedBits_0206459c(int index, int width, int value);
extern int ReadSessionPackedBits_02064574(int index, int width);
extern BOOL IsGlobalPackedBitSet_02027304(int index);
extern PlayerStats *func_0205125c(void);
extern fx32 func_02006450(fx32 a, fx32 b);
extern BOOL func_ov001_020645c8(int index);
extern int func_ov075_020c60e8(int value, int level);
extern int ArmObject_0205115c(void);

static inline fx32 ComputeRate(int penalty, int bonus)
{
    fx32 inverse = ((100 - penalty) << 12) / 100;
    fx32 direct = (bonus << 12) / 100;

    return func_02006450(inverse, direct);
}

int GetOptionChangeNotice_020c6134(OptionMenu *menu)
{
    int notice = 0;
    int bitBase = func_ov075_020c4988();
    int state = ReadGlobalPackedBits_02027348(0x1a00, 2);
    int stored;
    u16 level;
    int bonus;
    int penalty;
    fx32 rate;

    if (state != 2 && state != 3) {
        switch (menu->page) {
        case 1:
            if (data_0205fe0c->worldId == 3 && func_ov001_020644b0() == 400 && (u8)(s8)(data_0205fe0c->areaId - 0x1d) <= 1) {
                WriteSessionPackedBits_0206459c(0x3633, 2, data_0205fe0c->difficulty);
            }
            stored = ReadSessionPackedBits_02064574(0x35c7, 2);
            if (stored > data_0205fe0c->difficulty) {
                if (stored == 2 && !IsGlobalPackedBitSet_02027304(bitBase + 0xa1b)) {
                    notice = 1;
                } else if (stored == 3 && !IsGlobalPackedBitSet_02027304(bitBase + 0xa13)) {
                    notice = 2;
                }
            }
            break;
        case 2:
        case 5:
            level = func_0205125c()->level;
            if (menu->page == 2) {
                bonus = data_0205fe0c->option2c63;
                penalty = menu->choice;
            } else {
                bonus = menu->choice;
                penalty = data_0205fe0c->option2c65;
            }
            rate = ComputeRate(penalty, bonus);
            notice = 0;
            if (func_ov001_020645c8(0x35c9) && !func_ov001_020645c8(0xf2e) && func_ov075_020c60e8(rate, level) <= 1
                && func_ov075_020c60e8(ArmObject_0205115c(), level) > 1) {
                notice = 3;
            }
            break;
        }
    }
    return notice;
}

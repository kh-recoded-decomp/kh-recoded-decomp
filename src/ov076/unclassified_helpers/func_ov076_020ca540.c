#include "nitro/types.h"

typedef struct {
    int threshold;
    int value;
} ThresholdEntry;

typedef struct {
    ThresholdEntry entries[5];
} ThresholdTable;

typedef struct {
    u8 pad_00[0xa];
    u16 level;
} PlayerParams;

typedef struct {
    u8 pad_00[0x28d5];
    s8 worldId;
} GameState;

extern const ThresholdTable data_ov075_020cd168;
extern GameState *data_0205fe0c;

extern int func_ov001_02064574(int id, int mode);
extern BOOL func_ov001_020645c8(u32 value);
extern s8 GetCtxModeByte_02068084(void);
extern PlayerParams *func_020505a8(void);
extern void SetParamHalf18_02050630(u16 value);
extern void func_ov073_020c2ac8(void);

void func_ov076_020ca540(int bonus) {
    ThresholdTable table = data_ov075_020cd168;
    int state = func_ov001_02064574(0x1a00, 2);
    if (GetCtxModeByte_02068084() == 5 && state != 2) {
        if (func_ov001_020645c8(0x3609) && func_ov001_020645c8(0x360a) && bonus > 0) {
            SetParamHalf18_02050630(0xce4);
        }
    } else {
        BOOL skip = FALSE;
        if (GetCtxModeByte_02068084() == 3) {
            BOOL outside = FALSE;
            if (data_0205fe0c->worldId != 0x1d && data_0205fe0c->worldId != 0x1e) {
                outside = TRUE;
            }
            if (outside) {
                skip = TRUE;
            }
        }
        if (!skip) {
            PlayerParams *params = func_020505a8();
            int index;
            int rank;
            for (index = 0; index < 5; index++) {
                if (params->level <= table.entries[index].threshold) {
                    break;
                }
            }
            if (index > 4) {
                index = 4;
            }
            rank = index + bonus;
            if (rank >= 4) {
                rank = 4;
            }
            SetParamHalf18_02050630((u16)table.entries[rank].value);
            func_ov073_020c2ac8();
        }
    }
}

#include "nitro/types.h"

typedef struct MenuState {
    u8 unknown_00[0x2e];
    s16 level;
} MenuState;

extern MenuState *data_ov035_020bc4e0;

int GetScaledMenuLevel_020bb0a0(int mode) {
    switch (mode) {
    case 0:
        return data_ov035_020bc4e0->level;
    case 1:
        return (data_ov035_020bc4e0->level * 130 + 50) / 100;
    case 2:
        return (data_ov035_020bc4e0->level * 115 + 50) / 100;
    }
    return -1;
}

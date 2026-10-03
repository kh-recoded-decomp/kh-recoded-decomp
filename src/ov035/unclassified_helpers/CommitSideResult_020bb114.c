#include "nitro/types.h"

extern int func_ov035_020baf88(void);
extern int SNDi_LockMutex_020baf94(void);
extern void func_ov001_020645dc(int flagId);
extern int func_ov035_020bafc4(int kind);
extern void WriteSessionPackedBits_0206459c(int id, int bits, int value);
extern int func_ov035_020bb054(int mode);
extern void SetFieldSlotValue_020715d4(int index, int value, u16 param, u16 extra);

void CommitSideResult_020bb114(int side) {
    switch (side) {
    case 0:
        if (func_ov035_020baf88() == 0) {
            func_ov001_020645dc(0x3700);
            WriteSessionPackedBits_0206459c(0x3703, 0x10, func_ov035_020bafc4(1));
            SetFieldSlotValue_020715d4(0, 1, func_ov035_020bb054(0), func_ov035_020bb054(0));
        }
        break;
    case 1:
        if (SNDi_LockMutex_020baf94() == 0) {
            func_ov001_020645dc(0x3701);
            WriteSessionPackedBits_0206459c(0x3713, 0x10, func_ov035_020bafc4(2));
            SetFieldSlotValue_020715d4(1, 0, func_ov035_020bb054(0), func_ov035_020bb054(0));
        }
        break;
    }
}

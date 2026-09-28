#include "nitro/types.h"

extern u32 func_02009b7c(void);
extern void func_02009c14(void);
extern u16 IsAlarmSystemActive(void);
extern void OS_Sleep_02002c78(u32 arg0);
extern u32 data_02056b5c;

void func_02009bd0(u32 mask) {
    if (func_02009b7c() & mask) {
        func_02009c14();
        while (!(func_02009b7c() & 0x20)) {
            if (data_02056b5c != 0 && IsAlarmSystemActive() != 0) {
                OS_Sleep_02002c78(1);
            }
        }
    }
}

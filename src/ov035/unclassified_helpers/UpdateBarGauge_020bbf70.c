#include "nitro/types.h"

typedef struct BarGauge {
    const void *source;
    void *buffer;
    u8 unknown_08[0x128];
    int target;
    int current;
} BarGauge;

extern void func_01ff878c(const void *src, void *dest, u32 size);
extern void func_ov035_020bb8c4(void *buffer, u16 index, int style);
extern int GFXi_EnqueueCommand_02014090(void *a, int b, int c, int d);

void UpdateBarGauge_020bbf70(BarGauge *gauge) {
    int current = gauge->current;
    int target = gauge->target;
    int i;

    if (target < current) {
        current -= 2;
        gauge->current = current;
        if (target < current) {
            target = current;
        }
        gauge->current = target;
    } else if (target > current) {
        current += 2;
        gauge->current = current;
        if (target > current) {
            target = current;
        }
        gauge->current = target;
    }
    func_01ff878c(gauge->source, gauge->buffer, 0x160);
    for (i = 0; i < gauge->current; i++) {
        func_ov035_020bb8c4(gauge->buffer, i, 0);
    }
    for (; i < 0x57; i++) {
        func_ov035_020bb8c4(gauge->buffer, i, 1);
    }
    func_ov035_020bb8c4(gauge->buffer, 0x22, 2);
    GFXi_EnqueueCommand_02014090((void *)7, 0x50a0, (int)gauge->buffer, 0x160);
}

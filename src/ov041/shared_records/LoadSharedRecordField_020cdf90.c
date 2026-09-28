#include "nitro/types.h"

extern u32 data_ov041_020cfaa0;
extern int RetainOrInitializeSharedRecord_0202c80c(void *table, int id);
extern void func_0202c690(int enable);
extern int func_0202c940(int record, int index, int type);
extern void func_0202d3c8(int value, int key);
extern int func_0202d3e0(int value, int key, int flags);
extern void func_0202fd00(void *dest, int value, int flags);
extern void func_0202c8a8(int record);

void LoadSharedRecordField_020cdf90(int owner) {
    int record;
    int value;

    record = RetainOrInitializeSharedRecord_0202c80c(&data_ov041_020cfaa0, 0x12);
    func_0202c690(0);
    value = func_0202c940(record, 0, 1);
    func_0202c690(1);
    func_0202d3c8(value, 7);
    value = func_0202d3e0(value, 7, 0);
    func_0202fd00((void *)(owner + 0x1dd0), value, 0);
    func_0202c8a8(record);
}

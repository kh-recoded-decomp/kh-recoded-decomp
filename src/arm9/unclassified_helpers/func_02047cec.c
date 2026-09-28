#include "nitro/types.h"

typedef struct {
    u32 field0;
    s32 field1;
    u32 field2;
    s32 field3;
    u32 field4;
    u32 field5;
    u32 field6;
    s32 field7;
    u32 field8;
    u32 field9;
    u32 field10;
    u32 field11;
    u32 field12;
} Record13_02047cec;

extern void func_0203ac24(Record13_02047cec *out);

void func_02047cec(Record13_02047cec *out) {
    Record13_02047cec tmp;
    func_0203ac24(&tmp);
    *out = tmp;
}

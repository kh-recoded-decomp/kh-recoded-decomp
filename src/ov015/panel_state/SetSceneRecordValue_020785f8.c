#include "nitro/types.h"

typedef struct {
    s32 first;
    s32 second;
} TwoWordValue;

typedef struct {
    u8 pad_0000[0x65dc];
    void *records;
} Ov015Scene;

extern Ov015Scene *data_ov015_020812e0;

extern void func_0204f13c(void *records, int recordIndex, TwoWordValue *value);
extern void func_0204f2c0(void *records, int recordIndex);

void SetSceneRecordValue_020785f8(int recordIndex, TwoWordValue *value) {
    func_0204f13c(data_ov015_020812e0->records, recordIndex, value);
    func_0204f2c0(data_ov015_020812e0->records, recordIndex);
}

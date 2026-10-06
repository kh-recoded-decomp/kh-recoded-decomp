#include "nitro/types.h"

typedef struct {
    s16 kind;
    s16 id;
    s16 count;
} PanelDescriptor;

extern void SPrintfUnbounded(int dst, u32 value, int count);
extern void AcquireRecordSlot(int a, int b);
extern void ReleaseRecordSlot(int a);
extern int GetRecordSlotPair0Entry(int id);
extern int GetWideStringLength(int param);
extern void CopyWideStringBounded(int param1, u32 value, int mode);
extern void CopyRecordTableBField(int id, int param);
extern u32 func_ov027_020ba2c8(void *ptr, int mode);
extern u8 *data_ov015_020812e0;

int func_ov015_02078554(int param1, PanelDescriptor *desc) {
    int offset;
    u32 value;
    int base;

    if (desc->kind == 0) {
        AcquireRecordSlot(0, 1);
        base = GetRecordSlotPair0Entry(desc->id);
        CopyWideStringBounded(param1, *(u32 *)(base + 0x40), 0x3f);
        ReleaseRecordSlot(0);
        if (desc->count > 0) {
            offset = GetWideStringLength(param1);
            value = func_ov027_020ba2c8(data_ov015_020812e0 + 0x65e0, 0x37);
            SPrintfUnbounded(param1 + offset * 2, value, desc->count);
        }
    } else {
        CopyRecordTableBField(desc->id, param1);
    }
    return param1;
}

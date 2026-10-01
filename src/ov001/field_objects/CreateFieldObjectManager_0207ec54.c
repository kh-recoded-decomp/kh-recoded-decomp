#include "nitro/types.h"

typedef struct {
    void **objects;
    s8 count;
    u8 pad_05[7];
    u8 *resource;
    void *buffer;
    u8 pad_14[0x110];
} FieldObjectManager;

extern FieldObjectManager *data_ov001_020a04d8;
extern char data_ov001_0209f018[];
extern char data_ov001_0209f028[];
extern void StoreGlobalArrayEntry_02025668(int index, void *value);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8740(u32 value, void *dest, u32 size);
extern u8 *Msg_OpenContainerAndReadHeader_0202cc6c(const char *path, int mode, int flags);
extern void func_ov001_02063560(int slot, u8 *resource);
extern void *func_0202c478(u32 fileId, u32 flags);
extern void func_ov001_02086c10(void);

void CreateFieldObjectManager_0207ec54(void)
{
    StoreGlobalArrayEntry_02025668(4, data_ov001_0209f028);
    data_ov001_020a04d8 = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(FieldObjectManager));
    func_01ff8740(0, data_ov001_020a04d8, sizeof(FieldObjectManager));
    data_ov001_020a04d8->resource = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov001_0209f018, 3, 0);
    func_ov001_02063560(1, data_ov001_020a04d8->resource);
    data_ov001_020a04d8->buffer = func_0202c478(0x80000000 | (((u32)data_ov001_020a04d8->resource + 0x8000) & 0xfffffc) << 7, 3);
    func_ov001_02086c10();
}

#include "nitro/types.h"

typedef struct StageSource {
    u16 unk00;
    u16 entryCount;
} StageSource;

typedef struct StageState {
    u8 pad_0000[4];
    void *loader;
    u8 pad_0008[0x200];
    void *entries;
    void *entryRefs;
    u8 pad_0210[0x18de6 - 0x210];
    u16 entryCount;
    u16 cursor;
    u16 selection;
    u16 pad_18dec;
    u16 scroll;
    u8 pad_18df0[8];
    StageSource *source;
    u8 pad_18dfc[0x18f4c - 0x18dfc];
    void *handlers[5];
} StageState;

extern StageState *data_ov001_020a0508;
extern void func_ov001_0209c3c0(void);
extern void CacheStageEntrySlot_02098f64(int slot);
extern BOOL Session_Exists_02063a24(void);
extern int func_ov001_02064784(void);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff88c4(void *dst, u32 value, u32 size);
extern void func_0202a5ac(void *loader, void *callback);
extern void func_ov006_020a14c8(void);
extern void func_ov006_020a1510(void);
extern void func_ov006_020a1570(void);
extern void func_ov006_020a1694(void);
extern void func_ov006_020a154c(void);
extern void func_ov010_020a1aa8(void);
extern void func_ov010_020a1af0(void);
extern void func_ov010_020a1b50(void);
extern void func_ov010_020a1c74(void);
extern void func_ov010_020a1b2c(void);
extern void func_ov001_02099c28(void);

void BeginStageEntries_02099aec(StageSource *source)
{
    func_ov001_0209c3c0();
    if (source == NULL) {
        return;
    }
    data_ov001_020a0508->cursor = 0;
    data_ov001_020a0508->selection = 0;
    data_ov001_020a0508->scroll = 0;
    data_ov001_020a0508->source = source;
    CacheStageEntrySlot_02098f64(0);
    CacheStageEntrySlot_02098f64(1);
    CacheStageEntrySlot_02098f64(2);
    if (Session_Exists_02063a24()) {
        if (func_ov001_02064784() == 2) {
            data_ov001_020a0508->handlers[0] = func_ov006_020a14c8;
            data_ov001_020a0508->handlers[1] = func_ov006_020a1510;
            data_ov001_020a0508->handlers[2] = func_ov006_020a1570;
            data_ov001_020a0508->handlers[3] = func_ov006_020a1694;
            data_ov001_020a0508->handlers[4] = func_ov006_020a154c;
        } else if (func_ov001_02064784() == 6) {
            data_ov001_020a0508->handlers[0] = func_ov010_020a1aa8;
            data_ov001_020a0508->handlers[1] = func_ov010_020a1af0;
            data_ov001_020a0508->handlers[2] = func_ov010_020a1b50;
            data_ov001_020a0508->handlers[3] = func_ov010_020a1c74;
            data_ov001_020a0508->handlers[4] = func_ov010_020a1b2c;
        }
    }
    data_ov001_020a0508->entryCount = source->entryCount;
    data_ov001_020a0508->entries = NNSi_FndAllocFromDefaultHeap_0202a178(data_ov001_020a0508->entryCount * 0x28);
    data_ov001_020a0508->entryRefs = NNSi_FndAllocFromDefaultHeap_0202a178(data_ov001_020a0508->entryCount * 4);
    func_01ff88c4(data_ov001_020a0508->entries, 0, data_ov001_020a0508->entryCount * 0x28);
    func_01ff88c4(data_ov001_020a0508->entryRefs, 0, data_ov001_020a0508->entryCount * 4);
    func_0202a5ac(data_ov001_020a0508->loader, func_ov001_02099c28);
}

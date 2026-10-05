#include "nitro/types.h"

typedef struct SaveOptions {
    u32 difficulty : 2;
    u32 opt2 : 1;
    u32 opt3 : 2;
    u32 opt5 : 1;
    u32 opt6 : 1;
    u32 opt7 : 1;
    u32 opt8 : 1;
    u32 opt9 : 1;
    u32 opt10 : 1;
    u32 opt11 : 1;
    u32 opt12 : 2;
    u32 opt14 : 2;
    u32 opt16 : 1;
    u32 opt17 : 1;
    u32 opt18 : 2;
    u32 opt20 : 1;
    u32 opt21 : 1;
    u32 reserved : 10;
} SaveOptions;

typedef struct SaveNibbles {
    u8 low : 4;
    u8 high : 4;
} SaveNibbles;

typedef struct SaveContext {
    u8 pad_00[8];
    u8 *buffer;
    u8 *save;
} SaveContext;

extern SaveContext data_0205fe00;

extern void func_01ff8830(void *dest, u32 value, u32 size);
extern void func_01ff8740(u32 value, void *dest, u32 size);
extern void func_01ff86fc(u32 value, void *dest, u32 size);
extern void SetGlobalPackedBit_02027320(int bit);
extern void AcquireRecordManager_02051c80(void);
extern void GrantStartingRecords_02027670(void);
extern void ReleaseRecordManager_02051cdc(void);

static inline void ResetOptions(SaveOptions *options, u32 difficulty)
{
    options->difficulty = difficulty;
    options->opt8 = 0;
    options->opt14 = 0;
    options->opt5 = 0;
    options->opt6 = 0;
    options->opt3 = 1;
    options->opt2 = 1;
    options->opt7 = 0;
    options->opt10 = 0;
    options->opt9 = 0;
    options->opt16 = 0;
    options->opt18 = 0;
    options->opt17 = 0;
    options->opt20 = 0;
    options->opt12 = 1;
    options->opt21 = 0;
    options->opt11 = 0;
}

void InitSaveData_02026ee0(u32 difficulty)
{
    u8 *save = data_0205fe00.buffer + 0x18;

    data_0205fe00.save = save;
    func_01ff8830(save, 0, 0x3760);
    ResetOptions((SaveOptions *)(save + 0x2878), difficulty);
    func_01ff8740(0xffffffff, save + 0x2d84, 0x30);
    func_01ff86fc(0xffffffff, save + 0x2db8, 8);
    *(u16 *)(save + 0x2db4) = 0xd0;
    save[0x29a8] = 1;
    SetGlobalPackedBit_02027320(0xd0);
    *(u16 *)(save + 0x2db6) = 0x110;
    save[0x29e8] = 1;
    SetGlobalPackedBit_02027320(0x110);
    func_01ff8830(save + 0x2c6d, 0xff, 200);
    save[0x2c62] = difficulty;
    save[0x2c63] = 100;
    save[0x2c66] = 1;
    *(u16 *)(save + 0x2d36) = 0xffff;
    ((SaveNibbles *)(save + 0x28d7))->low = 0xf;
    ((SaveNibbles *)(save + 0x28d7))->high = 0xf;
    AcquireRecordManager_02051c80();
    GrantStartingRecords_02027670();
    ReleaseRecordManager_02051cdc();
}

#include "nitro/types.h"

extern void func_0200903c(void);
extern u32 func_020023a0(void);
extern void func_0200af10(void *arc);
extern void func_0200af34(void *arc, void *name, u32 nameLen);
extern u16 GetU16Field_020049f0(void);
extern u32 func_0200913c(void);
extern void FS_SetArchiveProcedure_0200d09c(void *arc, void *proc, u32 flags);
extern u32 SelectAndDispatchRomOp_0200d320(void *unused, int mode);
extern u32 SelectModeCode_0200d390(void *unused, int mode);
extern int FSi_ReadRomCallback_0200d2d8(void *arc, u32 src, u32 dst, u32 length);
extern u32 func_0200d3a4(u32 a, u32 b, u32 c, u32 d);
extern u32 func_0200d3ac(u32 a, u32 b, u32 c, u32 d);
extern u32 func_0200d3b4(void *arc);
extern void func_0200cfb0(void *arc, u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, void *pRead, void *pWrite);
extern void SubmitSaveRequest_0200aaf4(void *context);

typedef struct {
    void *target;
    u32 value;
} RomState;

typedef struct {
    u8 pad_00[0x14];
    u32 flags;
} Arc;

typedef struct {
    u8 pad_00[0x40];
    u32 field_40;
    u32 field_44;
    u32 field_48;
    u32 field_4c;
} RomHeader;

extern RomState data_02057b1c;
extern Arc data_02057b24;
extern u8 data_02055c34;
extern u8 data_02055c38;

void InitRomArchive_0200d3bc(void *param1)
{
    RomHeader *header;
    RomHeader *header2;
    u32 status;

    func_0200903c();
    data_02057b1c.target = param1;
    data_02057b1c.value = func_020023a0();

    func_0200af10(&data_02057b24);
    func_0200af34(&data_02057b24, &data_02055c34, 3);

    if (GetU16Field_020049f0() == 1) {
        header = (RomHeader *)func_0200913c();
        header2 = (RomHeader *)func_0200913c();
        FS_SetArchiveProcedure_0200d09c(&data_02057b24, (void *)SelectAndDispatchRomOp_0200d320, 0x682);
        if (header->field_40 != -1 && header->field_40 != 0) {
            status = header2->field_48;
            if (status != -1 && status != 0) {
                func_0200cfb0(&data_02057b24, 0, header2->field_48, header2->field_4c, header->field_40,
                              header->field_44, (void *)FSi_ReadRomCallback_0200d2d8, 0);
            }
        }
    } else {
        func_0200d3b4(&data_02057b24);
    }

    u32 flagSet = (data_02057b24.flags & 2) ? 1 : 0;
    if (flagSet == 0) {
        FS_SetArchiveProcedure_0200d09c(&data_02057b24, (void *)SelectModeCode_0200d390, 0xffffffff);
        func_0200cfb0(&data_02057b24, 0, 0, 0, 0, 0, (void *)func_0200d3a4, (void *)func_0200d3ac);
    }

    SubmitSaveRequest_0200aaf4(&data_02055c38);
}

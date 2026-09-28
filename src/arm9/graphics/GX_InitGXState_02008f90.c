typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u16 bankA;
    u16 bankB;
    u16 bankC;
    u16 bankD;
    u16 bankE;
    u16 bankF;
    u16 bankG;
    u16 bankH;
    u16 bankI;
    u16 reserved12;
    u16 reserved14;
    u16 reserved16;
    u16 reserved18;
} VramBankState;

extern VramBankState data_02056f48;

void GX_InitGXState_02008f90(void) {
    VramBankState *bankState = &data_02056f48;
    bankState->bankA = 0;
    bankState->bankB = 0;
    bankState->bankC = 0;
    bankState->bankD = 0;
    bankState->bankE = 0;
    bankState->bankF = 0;
    bankState->bankG = 0;
    bankState->bankH = 0;
    bankState->bankI = 0;
    bankState->reserved12 = 0;
    bankState->reserved14 = 0;
    bankState->reserved16 = 0;
    bankState->reserved18 = 0;

    *(volatile u32 *)0x04000240 = 0;

    *(volatile u8 *)0x04000244 = 0;

    *(volatile u8 *)0x04000245 = 0;

    *(volatile u8 *)0x04000246 = 0;

    *(volatile u16 *)0x04000248 = 0;
}

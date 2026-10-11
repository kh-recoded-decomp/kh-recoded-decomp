typedef unsigned long u32;

extern unsigned char DSProt_BSS_020d3720[];
extern const u32 Garbage_020d36e0[];
extern u32 Encryptor_DecryptionWrapperFragment_020d28e8(void);
extern void Encryptor_DecodeFunctionTable_020d2620(void *functions);

extern u32 RC4_Init_020d3228(void);
extern u32 RC4_InitSBox_020d330c(void);
extern u32 RC4_EncryptInstructions_020d3344(void);
extern u32 RC4_DecryptInstructions_020d345c(void);
extern u32 RC4_InitAndEncryptInstructions_020d35e4(void);
extern u32 RC4_InitAndDecryptInstructions_020d363c(void);
extern u32 RC4_Byte_020d32b4(void);

asm void __sinit_ov104_020d36b4_020d3694(void)
{
    orr   r0, pc, #0
    adds  r0, r0, #4
    bne   Encryptor_DecodeFunctionTable_020d2620
    DCD   RC4_Init_020d3228 + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1084
    DCD   RC4_InitSBox_020d330c + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1030
    DCD   RC4_EncryptInstructions_020d3344 + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1118
    DCD   RC4_DecryptInstructions_020d345c + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1184
    DCD   RC4_InitAndEncryptInstructions_020d35e4 + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1058
    DCD   RC4_InitAndDecryptInstructions_020d363c + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1058
    DCD   RC4_Byte_020d32b4 + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1058
    DCD   0
    DCD   0
}

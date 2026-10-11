typedef unsigned long u32;

extern unsigned char DSProt_BSS_020d3720[];
extern const u32 Garbage_020d36e0[];
extern u32 Encryptor_DecryptionWrapperFragment_020d28e8(void);
extern void Encryptor_DecodeFunctionTable_020d2620(void *functions);

extern u32 Encryptor_EncryptFunction_020d2810(void);
extern u32 Encryptor_DecryptFunction_020d2750(void);
extern u32 Encryptor_DecryptionWrapperFragment_020d28e8(void);

asm void __sinit_ov104_020d2958_020d2938(void)
{
    orr   r0, pc, #0
    adds  r0, r0, #4
    bne   Encryptor_DecodeFunctionTable_020d2620
    DCD   Encryptor_EncryptFunction_020d2810 + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x10d0
    DCD   Encryptor_DecryptFunction_020d2750 + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x10bc
    DCD   Encryptor_DecryptionWrapperFragment_020d28e8 + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1050
    DCD   0
    DCD   0
}

typedef unsigned long u32;

extern unsigned char DSProt_BSS_020d3720[];
extern const u32 Garbage_020d36e0[];
extern u32 Encryptor_DecryptionWrapperFragment_020d28e8(void);
extern void Encryptor_DecodeFunctionTable_020d2620(void *functions);

extern u32 RunEncrypted_ROMTest_IsBad_020d30d4(void);
extern u32 RunEncrypted_ROMTest_IsGood_020d3110(void);
extern u32 RunEncrypted_MACOwner_IsBad_020d2ac4(void);
extern u32 RunEncrypted_MACOwner_IsGood_020d2b00(void);
extern u32 RunEncrypted_ROMUtil_CRC32_020d2bd0(void);
extern u32 RunEncrypted_Dummy_IsBad_020d3164(void);
extern u32 RunEncrypted_Dummy_IsGood_020d31a0(void);

asm void __sinit_ov104_020d31fc_020d31dc(void)
{
    orr   r0, pc, #0
    adds  r0, r0, #4
    bne   Encryptor_DecodeFunctionTable_020d2620
    DCD   RunEncrypted_ROMTest_IsBad_020d30d4 + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1024
    DCD   RunEncrypted_ROMTest_IsGood_020d3110 + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1024
    DCD   RunEncrypted_MACOwner_IsBad_020d2ac4 + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1024
    DCD   RunEncrypted_MACOwner_IsGood_020d2b00 + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1024
    DCD   RunEncrypted_ROMUtil_CRC32_020d2bd0 + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1024
    DCD   RunEncrypted_Dummy_IsBad_020d3164 + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1024
    DCD   RunEncrypted_Dummy_IsGood_020d31a0 + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1024
    DCD   0
    DCD   0
}

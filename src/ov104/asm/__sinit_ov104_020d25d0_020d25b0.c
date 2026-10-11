typedef unsigned long u32;

extern unsigned char DSProt_BSS_020d3720[];
extern const u32 Garbage_020d36e0[];
extern u32 Encryptor_DecryptionWrapperFragment_020d28e8(void);
extern void Encryptor_DecodeFunctionTable_020d2620(void *functions);

extern u32 RunEncrypted_Integrity_MACOwner_IsBad_020d24c0(void);
extern u32 RunEncrypted_Integrity_MACOwner_IsGood_020d24fc(void);
extern u32 RunEncrypted_Integrity_ROMTest_IsBad_020d2538(void);
extern u32 RunEncrypted_Integrity_ROMTest_IsGood_020d2574(void);

asm void __sinit_ov104_020d25d0_020d25b0(void)
{
    orr   r0, pc, #0
    adds  r0, r0, #4
    bne   Encryptor_DecodeFunctionTable_020d2620
    DCD   RunEncrypted_Integrity_MACOwner_IsBad_020d24c0 + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1024
    DCD   RunEncrypted_Integrity_MACOwner_IsGood_020d24fc + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1024
    DCD   RunEncrypted_Integrity_ROMTest_IsBad_020d2538 + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1024
    DCD   RunEncrypted_Integrity_ROMTest_IsGood_020d2574 + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1024
    DCD   0
    DCD   0
}

typedef unsigned long u32;

extern unsigned char DSProt_BSS_020d3720[];
extern const u32 Garbage_020d36e0[];
extern u32 Encryptor_DecryptionWrapperFragment_020d28e8(void);
extern void Encryptor_DecodeFunctionTable_020d2620(void *functions);

extern u32 __DSProt_DetectFlashcart_020d1ea0(void);
extern u32 __DSProt_DetectNotFlashcart_020d1edc(void);
extern u32 __DSProt_DetectEmulator_020d1f18(void);
extern u32 __DSProt_DetectNotEmulator_020d1f54(void);
extern u32 __DSProt_DetectDummy_020d1f90(void);
extern u32 __DSProt_DetectNotDummy_020d1fcc(void);

asm void __sinit_ov104_020d2028_020d2008(void)
{
    orr   r0, pc, #0
    adds  r0, r0, #4
    bne   Encryptor_DecodeFunctionTable_020d2620
    DCD   __DSProt_DetectFlashcart_020d1ea0 + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1024
    DCD   __DSProt_DetectNotFlashcart_020d1edc + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1024
    DCD   __DSProt_DetectEmulator_020d1f18 + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1024
    DCD   __DSProt_DetectNotEmulator_020d1f54 + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1024
    DCD   __DSProt_DetectDummy_020d1f90 + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1024
    DCD   __DSProt_DetectNotDummy_020d1fcc + 0x1000
    DCD   DSProt_BSS_020d3720 + 0x1024
    DCD   0
    DCD   0
    DCD   Garbage_020d36e0 + 0x1000
}

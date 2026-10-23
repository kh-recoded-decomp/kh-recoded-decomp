#include "src/overlays/ov104/DSProtWrapperContext.h"

extern unsigned long ROMTest_IsGood(void);

#pragma define_section dsprotWrapperContext ".text" RW

__declspec(dsprotWrapperContext) DSProtWrapperContext gDSProtROMTestIsGoodContext = {
    (unsigned long)(DSProt_BSS + 1),
    (unsigned long)(DSProt_BSS + 0x1000 + 0x83e5),
    DSPROT_FUNCTION_ENTRY(ROMTest_IsGood, 0x23c),
    0,
    (unsigned long)((unsigned char *)Encryptor_DecryptionWrapperFragment + 0x1000)
};

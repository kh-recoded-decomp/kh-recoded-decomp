#include "src/overlays/ov104/DSProtWrapperContext.h"

extern unsigned long ROMTest_IsBad(void);

#pragma define_section dsprotWrapperContext ".text" RW

__declspec(dsprotWrapperContext) DSProtWrapperContext gDSProtROMTestIsBadContext = {
    (unsigned long)(DSProt_BSS + 1),
    (unsigned long)(DSProt_BSS + 0x1000 + 0x8145),
    DSPROT_FUNCTION_ENTRY(ROMTest_IsBad, 0x23c),
    0,
    (unsigned long)((unsigned char *)Encryptor_DecryptionWrapperFragment + 0x1000)
};

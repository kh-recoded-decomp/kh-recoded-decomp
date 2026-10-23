#include "src/overlays/ov104/DSProtWrapperContext.h"

extern unsigned long Integrity_ROMTest_IsGood(void);

#pragma define_section dsprotWrapperContext ".text" RW

__declspec(dsprotWrapperContext) DSProtWrapperContext gDSProtIntegrityROMTestIsGoodContext = {
    (unsigned long)(DSProt_BSS + 1),
    (unsigned long)(DSProt_BSS + 0x1000 + 0x1843c),
    DSPROT_FUNCTION_ENTRY(Integrity_ROMTest_IsGood, 0x110),
    0,
    (unsigned long)((unsigned char *)Encryptor_DecryptionWrapperFragment + 0x1000)
};

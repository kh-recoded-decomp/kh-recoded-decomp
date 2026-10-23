#include "src/overlays/ov104/DSProtWrapperContext.h"

extern unsigned long Dummy_IsBad(void);

#pragma define_section dsprotWrapperContext ".text" RW

__declspec(dsprotWrapperContext) DSProtWrapperContext gDSProtDummyIsBadContext = {
    (unsigned long)(DSProt_BSS + 1),
    (unsigned long)(DSProt_BSS + 0x1000 + 0x8785),
    DSPROT_FUNCTION_ENTRY(Dummy_IsBad, 0x8),
    0,
    (unsigned long)((unsigned char *)Encryptor_DecryptionWrapperFragment + 0x1000)
};

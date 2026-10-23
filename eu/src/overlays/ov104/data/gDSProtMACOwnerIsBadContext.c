#include "src/overlays/ov104/DSProtWrapperContext.h"

extern unsigned long MACOwner_IsBad(void);

#pragma define_section dsprotWrapperContext ".text" RW

__declspec(dsprotWrapperContext) DSProtWrapperContext gDSProtMACOwnerIsBadContext = {
    (unsigned long)(DSProt_BSS + 1),
    (unsigned long)(DSProt_BSS + 0x1000 + 0x7d65),
    DSPROT_FUNCTION_ENTRY(MACOwner_IsBad, 0xac),
    0,
    (unsigned long)((unsigned char *)Encryptor_DecryptionWrapperFragment + 0x1000)
};

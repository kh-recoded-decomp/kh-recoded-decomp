#include "src/overlays/ov104/DSProtWrapperContext.h"

extern unsigned long Integrity_MACOwner_IsGood(void);

#pragma define_section dsprotWrapperContext ".text" RW

__declspec(dsprotWrapperContext) DSProtWrapperContext gDSProtIntegrityMACOwnerIsGoodContext = {
    (unsigned long)(DSProt_BSS + 1),
    (unsigned long)(DSProt_BSS + 0x1000 + 0x181dc),
    DSPROT_FUNCTION_ENTRY(Integrity_MACOwner_IsGood, 0x110),
    0,
    (unsigned long)((unsigned char *)Encryptor_DecryptionWrapperFragment + 0x1000)
};

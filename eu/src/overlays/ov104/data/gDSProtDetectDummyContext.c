#include "src/overlays/ov104/DSProtWrapperContext.h"

extern unsigned long DetectDummy(void *callback, void *param, unsigned long unused);

#pragma define_section dsprotWrapperContext ".text" RW

__declspec(dsprotWrapperContext) DSProtWrapperContext gDSProtDetectDummyContext = {
    (unsigned long)(DSProt_BSS + 1),
    (unsigned long)(DSProt_BSS + 0x1000 + 0x17d82),
    DSPROT_FUNCTION_ENTRY(DetectDummy, 0x80),
    0,
    (unsigned long)((unsigned char *)Encryptor_DecryptionWrapperFragment + 0x1000)
};

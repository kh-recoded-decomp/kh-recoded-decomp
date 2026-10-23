#include "src/overlays/ov104/DSProtWrapperContext.h"

extern unsigned long DetectNotFlashcart(void *callback, void *param, unsigned long unused);

#pragma define_section dsprotWrapperContext ".text" RW

__declspec(dsprotWrapperContext) DSProtWrapperContext gDSProtDetectNotFlashcartContext = {
    (unsigned long)(DSProt_BSS + 1),
    (unsigned long)(DSProt_BSS + 0x1000 + 0x17b42),
    DSPROT_FUNCTION_ENTRY(DetectNotFlashcart, 0x8c),
    0,
    (unsigned long)((unsigned char *)Encryptor_DecryptionWrapperFragment + 0x1000)
};

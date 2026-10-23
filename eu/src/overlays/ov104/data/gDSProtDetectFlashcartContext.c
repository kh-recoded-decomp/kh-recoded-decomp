#include "src/overlays/ov104/DSProtWrapperContext.h"

extern unsigned long DetectFlashcart(void *callback, void *param, unsigned long unused);

#pragma define_section dsprotWrapperContext ".text" RW

__declspec(dsprotWrapperContext) DSProtWrapperContext gDSProtDetectFlashcartContext = {
    (unsigned long)(DSProt_BSS + 1),
    (unsigned long)(DSProt_BSS + 0x1000 + 0x17a82),
    DSPROT_FUNCTION_ENTRY(DetectFlashcart, 0x8c),
    0,
    (unsigned long)((unsigned char *)Encryptor_DecryptionWrapperFragment + 0x1000)
};

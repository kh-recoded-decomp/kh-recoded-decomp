#include "src/overlays/ov104/DSProtWrapperContext.h"

extern unsigned long DetectNotEmulator(void *callback, void *param, unsigned long unused);

#pragma define_section dsprotWrapperContext ".text" RW

__declspec(dsprotWrapperContext) DSProtWrapperContext gDSProtDetectNotEmulatorContext = {
    (unsigned long)(DSProt_BSS + 1),
    (unsigned long)(DSProt_BSS + 0x1000 + 0x17cc2),
    DSPROT_FUNCTION_ENTRY(DetectNotEmulator, 0x8c),
    0,
    (unsigned long)((unsigned char *)Encryptor_DecryptionWrapperFragment + 0x1000)
};

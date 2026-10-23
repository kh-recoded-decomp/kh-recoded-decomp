#include "src/overlays/ov104/DSProtWrapperContext.h"

extern unsigned long ROMUtil_CRC32(void *buffer, unsigned long size);

#pragma define_section dsprotWrapperContext ".text" RW

__declspec(dsprotWrapperContext) DSProtWrapperContext gDSProtROMUtilCRC32Context = {
    (unsigned long)(DSProt_BSS + 1),
    (unsigned long)(DSProt_BSS + 0x1000 + 0x8025),
    DSPROT_FUNCTION_ENTRY(ROMUtil_CRC32, 0x90),
    0,
    (unsigned long)((unsigned char *)Encryptor_DecryptionWrapperFragment + 0x1000)
};

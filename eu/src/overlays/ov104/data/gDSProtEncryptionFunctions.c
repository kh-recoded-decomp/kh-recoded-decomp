#include "src/overlays/ov104/DSProtFunctionInfo.h"

extern unsigned long Encryptor_EncryptFunction(unsigned long key, unsigned long address, unsigned long size);
extern void *Encryptor_DecryptFunction(unsigned long key, unsigned long address, unsigned long size);
extern unsigned long Encryptor_DecryptionWrapperFragment(void);

#pragma define_section dsprotFunctionTable ".text" RW

/* The initializer passes this table to the decoder, which clears it after use. */
__declspec(dsprotFunctionTable) DSProtFunctionInfo gDSProtEncryptionFunctions[] = {
    DSPROT_FUNCTION_ENTRY(Encryptor_EncryptFunction, 0xd0),
    DSPROT_FUNCTION_ENTRY(Encryptor_DecryptFunction, 0xbc),
    DSPROT_FUNCTION_ENTRY(Encryptor_DecryptionWrapperFragment, 0x50),
    {0, 0}
};

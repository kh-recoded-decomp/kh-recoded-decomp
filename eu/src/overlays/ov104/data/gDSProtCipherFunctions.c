#include "src/overlays/ov104/DSProtFunctionInfo.h"

typedef struct RC4Context RC4Context;

extern void RC4_Init(RC4Context *context, const void *key, unsigned long keyLength);
extern unsigned long RC4_InitSBox(unsigned char *state);
extern unsigned long RC4_EncryptInstructions(RC4Context *context, void *source, void *destination, unsigned long size);
extern unsigned long RC4_DecryptInstructions(RC4Context *context, void *source, void *destination, unsigned long size);
extern unsigned long RC4_InitAndEncryptInstructions(void *key, void *destination, void *source, unsigned long size);
extern unsigned long RC4_InitAndDecryptInstructions(void *key, void *destination, void *source, unsigned long size);
extern unsigned char RC4_Byte(RC4Context *context);

#pragma define_section dsprotFunctionTable ".text" RW

/* The initializer passes this table to the decoder, which clears it after use. */
__declspec(dsprotFunctionTable) DSProtFunctionInfo gDSProtCipherFunctions[] = {
    DSPROT_FUNCTION_ENTRY(RC4_Init, 0x84),
    DSPROT_FUNCTION_ENTRY(RC4_InitSBox, 0x30),
    DSPROT_FUNCTION_ENTRY(RC4_EncryptInstructions, 0x118),
    DSPROT_FUNCTION_ENTRY(RC4_DecryptInstructions, 0x184),
    DSPROT_FUNCTION_ENTRY(RC4_InitAndEncryptInstructions, 0x58),
    DSPROT_FUNCTION_ENTRY(RC4_InitAndDecryptInstructions, 0x58),
    DSPROT_FUNCTION_ENTRY(RC4_Byte, 0x58),
    {0, 0}
};

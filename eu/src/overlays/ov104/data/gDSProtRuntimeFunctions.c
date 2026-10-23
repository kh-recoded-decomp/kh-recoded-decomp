#include "src/overlays/ov104/DSProtFunctionInfo.h"

extern unsigned long RunEncrypted_ROMTest_IsBad(void);
extern unsigned long RunEncrypted_ROMTest_IsGood(void);
extern unsigned long RunEncrypted_MACOwner_IsBad(void);
extern unsigned long RunEncrypted_MACOwner_IsGood(void);
extern unsigned long RunEncrypted_ROMUtil_CRC32(void);
extern unsigned long RunEncrypted_Dummy_IsBad(void);
extern unsigned long RunEncrypted_Dummy_IsGood(void);

#pragma define_section dsprotFunctionTable ".text" RW

/* The initializer passes this table to the decoder, which clears it after use. */
__declspec(dsprotFunctionTable) DSProtFunctionInfo gDSProtRuntimeFunctions[] = {
    DSPROT_FUNCTION_ENTRY(RunEncrypted_ROMTest_IsBad, 0x24),
    DSPROT_FUNCTION_ENTRY(RunEncrypted_ROMTest_IsGood, 0x24),
    DSPROT_FUNCTION_ENTRY(RunEncrypted_MACOwner_IsBad, 0x24),
    DSPROT_FUNCTION_ENTRY(RunEncrypted_MACOwner_IsGood, 0x24),
    DSPROT_FUNCTION_ENTRY(RunEncrypted_ROMUtil_CRC32, 0x24),
    DSPROT_FUNCTION_ENTRY(RunEncrypted_Dummy_IsBad, 0x24),
    DSPROT_FUNCTION_ENTRY(RunEncrypted_Dummy_IsGood, 0x24),
    {0, 0}
};

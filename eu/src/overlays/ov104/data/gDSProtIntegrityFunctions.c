#include "src/overlays/ov104/DSProtFunctionInfo.h"

extern unsigned long RunEncrypted_Integrity_MACOwner_IsBad(void);
extern unsigned long RunEncrypted_Integrity_MACOwner_IsGood(void);
extern unsigned long RunEncrypted_Integrity_ROMTest_IsBad(void);
extern unsigned long RunEncrypted_Integrity_ROMTest_IsGood(void);

#pragma define_section dsprotFunctionTable ".text" RW

/* The initializer passes this table to the decoder, which clears it after use. */
__declspec(dsprotFunctionTable) DSProtFunctionInfo gDSProtIntegrityFunctions[] = {
    DSPROT_FUNCTION_ENTRY(RunEncrypted_Integrity_MACOwner_IsBad, 0x24),
    DSPROT_FUNCTION_ENTRY(RunEncrypted_Integrity_MACOwner_IsGood, 0x24),
    DSPROT_FUNCTION_ENTRY(RunEncrypted_Integrity_ROMTest_IsBad, 0x24),
    DSPROT_FUNCTION_ENTRY(RunEncrypted_Integrity_ROMTest_IsGood, 0x24),
    {0, 0}
};

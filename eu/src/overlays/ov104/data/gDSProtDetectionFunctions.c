#include "src/overlays/ov104/DSProtFunctionInfo.h"

extern unsigned long __DSProt_DetectFlashcart(void);
extern unsigned long __DSProt_DetectNotFlashcart(void);
extern unsigned long __DSProt_DetectEmulator(void);
extern unsigned long __DSProt_DetectNotEmulator(void);
extern unsigned long __DSProt_DetectDummy(void);
extern unsigned long __DSProt_DetectNotDummy(void);

#pragma define_section dsprotFunctionTable ".text" RW

typedef struct DSProtDetectionTable {
    DSProtFunctionInfo functions[7];
    unsigned long encodedTrailer;
} DSProtDetectionTable;

extern const unsigned long Garbage[];

/* The encoded trailer follows the table terminator and is not decoded. */
__declspec(dsprotFunctionTable) DSProtDetectionTable gDSProtDetectionFunctions = {
    {
        DSPROT_FUNCTION_ENTRY(__DSProt_DetectFlashcart, 0x24),
        DSPROT_FUNCTION_ENTRY(__DSProt_DetectNotFlashcart, 0x24),
        DSPROT_FUNCTION_ENTRY(__DSProt_DetectEmulator, 0x24),
        DSPROT_FUNCTION_ENTRY(__DSProt_DetectNotEmulator, 0x24),
        DSPROT_FUNCTION_ENTRY(__DSProt_DetectDummy, 0x24),
        DSPROT_FUNCTION_ENTRY(__DSProt_DetectNotDummy, 0x24),
        {0, 0}
    },
    (unsigned long)((const unsigned char *)Garbage + 0x1000)
};

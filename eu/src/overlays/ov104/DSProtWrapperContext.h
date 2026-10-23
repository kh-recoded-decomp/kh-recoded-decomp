#ifndef DSPROT_WRAPPER_CONTEXT_H
#define DSPROT_WRAPPER_CONTEXT_H

#include "src/overlays/ov104/DSProtFunctionInfo.h"

/* The dispatcher saves LR and R10 here while the encrypted function runs. */
typedef struct DSProtWrapperContext {
    unsigned long returnAddress;
    unsigned long encodedKey;
    DSProtFunctionInfo function;
    unsigned long savedR10;
    unsigned long encodedDispatcher;
} DSProtWrapperContext;

extern unsigned long Encryptor_DecryptionWrapperFragment(void);

#endif

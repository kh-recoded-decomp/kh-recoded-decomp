#ifndef DSPROT_FUNCTION_INFO_H
#define DSPROT_FUNCTION_INFO_H

typedef struct DSProtFunctionInfo {
    unsigned long encodedAddress;
    unsigned long encodedSize;
} DSProtFunctionInfo;

extern unsigned char DSProt_BSS[];

/* The decoder subtracts 0x1000 from addresses and DSProt_BSS + 0x1000 from sizes. */
#define DSPROT_FUNCTION_ENTRY(function, byteSize) \
    {(unsigned long)((unsigned char *)(function) + 0x1000), \
     (unsigned long)(DSProt_BSS + 0x1000 + (byteSize))}

#endif

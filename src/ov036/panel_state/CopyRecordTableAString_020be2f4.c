#include "nitro/types.h"

extern void func_02051c80(void);
extern void func_02051cdc(void);
extern void func_02051d3c(s32 id, s32 value);
extern void func_02051dfc(s32 id);
extern int func_02051ec8(s32 id);
extern unsigned short *CopyTerminatedHalfwords(unsigned short *destination, unsigned short *source);

void CopyRecordTableAString_020be2f4(s32 id, unsigned short *destination)
{
    int entry;

    func_02051c80();
    func_02051d3c(0, 1);
    entry = func_02051ec8(id);
    CopyTerminatedHalfwords(destination, *(unsigned short **)(entry + 0x40));
    func_02051dfc(0);
    func_02051cdc();
}

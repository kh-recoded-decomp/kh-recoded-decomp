#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nnsys/snd.h"

void SND_InvalidateBankData(const void *start, const void *end);
void SND_DestroyBank(struct SNDBankData * bank);
extern void DisposeCallback(void * mem, NNSSndArc * arc, u32 fileId);
extern void DisposeCallback (void * mem, NNSSndArc * arc, u32 fileId);

void BankDisposeCallback_0201fa4c (void * mem, u32 size, u32 data1, u32 data2)
{
    SNDBankData * bank = (SNDBankData *)mem;
    NNSSndArc * arc = (NNSSndArc *)data1;
    u32 fileId = data2;

    DisposeCallback(mem, arc, fileId);
    SND_InvalidateBankData(mem, (u8 *)mem + size);

    SND_DestroyBank(bank);
}

#include "nitro/types.h"
#include "nnsys/gfd.h"

typedef void (*PlttVramDumpCallback)(u32 loAddr, u32 hiAddr, u32 szFree, u32 szTotal);

extern NNSGfdFrmPlttVramManager data_0205a8c4;

void NNS_GfdDumpFrmPlttVramManagerEx_02013bac(PlttVramDumpCallback callback)
{
    callback(data_0205a8c4.loAddr, data_0205a8c4.hiAddr, data_0205a8c4.hiAddr - data_0205a8c4.loAddr,
             data_0205a8c4.szTotal);
}

#include "nitro/types.h"
#include "nitro/os.h"
#include "nitro/pxi.h"
#include "nitro/ctrdg.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

void OS_Terminate();
extern void OS_Terminate(void);
void CTRDGi_SendtoPxi(u32 data);
extern void CTRDGi_SendtoPxi(u32 data);

void CTRDG_TerminateForPulledOut_02012768 (void)
{
	CTRDGi_SendtoPxi(CTRDG_PXI_COMMAND_TERMINATE);
	OS_Terminate();
}

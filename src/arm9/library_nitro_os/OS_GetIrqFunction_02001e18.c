#include "nitro/types.h"
#include "nitro/os.h"

extern OSiIrqSlot data_02056ae8[];
extern unsigned int data_027e0000;

#define OSi_IrqTable ((OSIrqFunction *)&data_027e0000)

OSIrqFunction OS_GetIrqFunction_02001e18(unsigned int intrBits)
{
    int i;
    OSIrqFunction *entry = OSi_IrqTable;

    for (i = 0; i < OS_IRQ_TABLE_MAX; i++, intrBits >>= 1, entry++) {
        if (intrBits & 1) {
            if (i >= 8 && i <= 11) {
                return data_02056ae8[i - 8].pfnHandler;
            }
            if (i >= 3 && i <= 6) {
                return data_02056ae8[i + 1].pfnHandler;
            }
            return *entry;
        }
    }
    return 0;
}

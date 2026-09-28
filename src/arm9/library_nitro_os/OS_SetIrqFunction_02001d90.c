#include "nitro/types.h"
#include "nitro/os.h"

extern OSiIrqSlot data_02056ae8[];
extern unsigned int data_027e0000;

#define OSi_IrqTable ((OSIrqFunction *)&data_027e0000)

void OS_SetIrqFunction_02001d90(unsigned int intrBits, OSIrqFunction function)
{
    int i;

    for (i = 0; i < OS_IRQ_TABLE_MAX; i++, intrBits >>= 1) {
        if (intrBits & 1) {
            OSiIrqSlot *slot = 0;

            if (i >= 8 && i <= 11) {
                slot = &data_02056ae8[i - 8];
            } else if (i >= 3 && i <= 6) {
                slot = &data_02056ae8[i + 1];
            } else {
                OSi_IrqTable[i] = function;
            }

            if (slot != 0) {
                slot->pfnHandler = function;
                slot->pArg = 0;
                slot->bKeepEnabled = 1;
            }
        }
    }
}

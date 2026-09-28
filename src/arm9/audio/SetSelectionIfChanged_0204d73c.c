#include "nitro/types.h"

extern u8 *g_soundWork_0206084c;
extern u8 *func_0204cf58(int value);
extern void func_0204ce84(int kind, int arg1, int arg2);

int SetSelectionIfChanged_0204d73c(int selection)
{
    u8 *record;

    if (*(s16 *)(g_soundWork_0206084c + 0xb472a) != selection ||
        *(u8 *)(g_soundWork_0206084c + 0xb47be) == 1) {
        record = func_0204cf58(0);
        if (record == NULL || record[0] != 2) {
            func_0204ce84(2, selection, 0);
        } else {
            record[1] = (u8)selection;
        }
    }
    return 1;
}

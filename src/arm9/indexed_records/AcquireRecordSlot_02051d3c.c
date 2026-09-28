#include "nitro/types.h"

extern int g_recordManager_020613d0;

extern void func_020513b4(int param);
extern void func_0205144c(int param);
extern void func_020514e8(int param);
extern void func_02051618(int param);
extern void func_02051710(int param);
extern void func_0205175c(int param);
extern void func_020517a8(int param);
extern void func_02051818(int param);
extern void func_02051864(int param);
extern void func_020518b0(int param);
extern void func_02051948(int param);
extern void func_020519d8(int param);
extern void func_02051aa4(int param);
extern void func_02051580(int param);

/* Bumps a record slot's reference count. */
int AcquireRecordSlot_02051d3c(int slot, int param)
{
    int manager;

    manager = g_recordManager_020613d0;
    *(u8 *)(g_recordManager_020613d0 + 0x44 + slot) = *(u8 *)(g_recordManager_020613d0 + 0x44 + slot) + 1;
    if (*(u8 *)(manager + slot + 0x44) > 1) {
        return 1;
    }
    switch (slot) {
        case 0:
            func_020513b4(param);
            break;
        case 1:
            func_0205144c(param);
            break;
        case 2:
            func_020514e8(param);
            break;
        case 3:
            func_02051618(param);
            break;
        case 4:
            func_02051710(param);
            break;
        case 5:
            func_0205175c(param);
            break;
        case 6:
            func_020517a8(param);
            break;
        case 7:
            func_02051818(param);
            break;
        case 8:
            func_02051864(param);
            break;
        case 9:
            func_020518b0(param);
            break;
        case 10:
            func_02051948(param);
            break;
        case 11:
            func_020519d8(param);
            break;
        case 12:
            func_02051aa4(param);
            break;
        case 13:
            func_02051580(param);
            break;
        }
    return 1;
}

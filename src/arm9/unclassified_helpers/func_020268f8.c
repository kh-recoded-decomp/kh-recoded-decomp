#include "nitro/types.h"

extern void func_020359d4(u16 value);
extern int IsRecordIdFree_0202c38c(int id);
extern void func_02035898(u16 value, int obj, int a, int b);
extern void ScriptCmd_SetElemField_02025e18(int scriptCtx, int value);

int func_020268f8(int scriptCtx, int angle)
{
    if (angle < 0) {
        if (angle == -0x63) {
            angle = 0;
        }
        func_020359d4(-angle & 0xffff);
        *(int *)(*(int *)(scriptCtx + 0x1c8) + 8) = 0;
        return 1;
    }
    if (IsRecordIdFree_0202c38c(*(int *)(*(int *)(*(int *)(scriptCtx + 0x1c8) + 8) + 0xc)) != 0) {
        func_02035898(angle & 0xffff, *(int *)(*(int *)(scriptCtx + 0x1c8) + 8), 0, 0xd);
        if (angle == 0) {
            ScriptCmd_SetElemField_02025e18(scriptCtx, -0x63);
        } else {
            ScriptCmd_SetElemField_02025e18(scriptCtx, -angle);
        }
    }
    return 0;
}

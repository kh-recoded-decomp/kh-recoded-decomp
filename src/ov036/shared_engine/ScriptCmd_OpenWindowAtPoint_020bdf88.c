#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptContext {
    u8 pad_000[0x628];
    s32 isSkipping;
} ScriptContext;

typedef struct ScreenPoint {
    s32 x;
    s32 y;
} ScreenPoint;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern void func_ov036_020bdda8(ScreenPoint *out, int actorId);
extern int func_ov036_020bdde8(ScreenPoint *point);
extern void func_ov036_020c2f4c(int balloonId, int direction, ScreenPoint *point, int style);

int ScriptCmd_OpenWindowAtPoint_020bdf88(ScriptContext *context, ScriptOperand *operands)
{
    int actorId = ScriptVm_ReadOperandInt_02025de4(context, &operands[0]);
    int balloonId = ScriptVm_ReadOperandInt_02025de4(context, &operands[1]);
    int direction = ScriptVm_ReadOperandInt_02025de4(context, &operands[2]);
    int style = ScriptVm_ReadOperandInt_02025de4(context, &operands[3]);
    ScreenPoint point;

    if (context->isSkipping != 0) {
        return 1;
    }
    if (operands[4].type == 0) {
        func_ov036_020bdda8(&point, actorId);
        if (direction == -1) {
            direction = func_ov036_020bdde8(&point);
        }
        point.x = 0x80;
        point.y = 0x60;
    } else {
        point.x = ScriptVm_ReadOperandInt_02025de4(context, &operands[4]);
        point.y = ScriptVm_ReadOperandInt_02025de4(context, &operands[5]);
        if (direction == -1) {
            direction = func_ov036_020bdde8(&point);
        }
    }
    func_ov036_020c2f4c(balloonId, direction, &point, style);
    return 1;
}

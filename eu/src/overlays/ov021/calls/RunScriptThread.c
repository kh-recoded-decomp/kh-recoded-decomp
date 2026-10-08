#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    u16 actorId;
} StageEvent;

typedef struct {
    u8 pad_00[0xc];
    u16 actorId;
} StageLink;

typedef struct {
    StageEvent *eventRecord;
    StageLink *link;
    void *player;
} FieldContext;

typedef struct {
    s8 handler;
    u8 pad_01;
    u16 length;
} ScriptOpcode;

typedef struct {
    u16 ownerKind;
    u16 ownerId;
    u8 pad_04[0x10];
    s32 registerIndex;
    u8 pad_18[4];
    s32 pc;
    s32 depth;
    s32 jumpTarget;
    u8 pad_28[0x38];
    s32 callStack[4];
    s32 registers[1];
} ScriptThread;

typedef s32 (*ScriptHandler)(ScriptThread *thread, u32 operand);

extern FieldContext data_ov021_020b56c4;
extern FieldContext gActiveFieldContext;
extern FieldContext data_ov021_020b56d0;
extern ScriptHandler data_ov021_020b56dc[];

extern void *func_ov001_0209c3e8(void);
extern void MI_CpuFill8(void *dest, u32 value, u32 size);
extern StageEvent *GetStageEventRecord(u32 id);
extern StageLink *GetStageController(u32 id);
extern void *GetStageActor(int id);
extern u32 func_ov001_0209c5ac(u32 mask);
extern int ApplyActorScaleFactors(void *actor);
extern ScriptOpcode *func_ov021_020b0370(ScriptThread *thread);
extern u32 func_ov021_020b037c(ScriptThread *thread);

s32 RunScriptThread(ScriptThread *thread)
{
    BOOL running;
    u16 actorId;
    s32 result;

    func_ov001_0209c3e8();
    running = TRUE;
    data_ov021_020b56d0 = data_ov021_020b56c4;
    MI_CpuFill8(&data_ov021_020b56c4, 0, sizeof(FieldContext));
    if (thread->ownerKind == 1) {
        gActiveFieldContext.eventRecord = GetStageEventRecord(thread->ownerId);
        actorId = gActiveFieldContext.eventRecord->actorId;
    } else if (thread->ownerKind == 2) {
        gActiveFieldContext.link = GetStageController(thread->ownerId);
        actorId = gActiveFieldContext.link->actorId;
    } else {
        actorId = thread->ownerId;
    }
    gActiveFieldContext.player = GetStageActor((s16)actorId);
    if (func_ov001_0209c5ac(0x40) && gActiveFieldContext.player != NULL && ApplyActorScaleFactors(gActiveFieldContext.player) <= 0) {
        return 0;
    }
    do {
        ScriptOpcode *op = func_ov021_020b0370(thread);
        u32 operand = 0;
        ScriptHandler handler;
        if (op->length >= 4) {
            operand = func_ov021_020b037c(thread);
        }
        handler = data_ov021_020b56dc[op->handler];
        if (handler == NULL) {
            return 0;
        }
        result = handler(thread, operand);
        switch (result) {
        case 0:
        case 8:
            if (op->length == 0) {
                return 4;
            }
            thread->pc += op->length;
            break;
        case 7:
            thread->registers[thread->registerIndex] = thread->jumpTarget;
            thread->registerIndex = 0;
            running = FALSE;
            break;
        case 1:
            thread->pc = thread->jumpTarget;
            running = FALSE;
            break;
        case 2:
            thread->pc = thread->jumpTarget;
            break;
        case 6:
            thread->pc += op->length;
            thread->callStack[++thread->depth] = thread->pc;
            thread->pc = thread->jumpTarget;
            break;
        case 3:
            running = FALSE;
            break;
        case 5:
            thread->pc += op->length;
            if (thread->depth != 0) {
                thread->pc = thread->callStack[thread->depth--];
                running = FALSE;
                break;
            }
            result = 4;
            /* fall through */
        case 4:
            thread->registerIndex = 0;
            running = FALSE;
            break;
        }
    } while (running);
    data_ov021_020b56c4 = data_ov021_020b56d0;
    return result;
}

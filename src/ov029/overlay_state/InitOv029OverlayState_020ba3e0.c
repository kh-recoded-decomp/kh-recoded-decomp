#include "nitro/types.h"

typedef struct {
    s16 areaId;
    s16 posX;
    s16 posY;
    u16 flags;
    u8 pad_08[4];
    void *mainTask;
    void *subTask;
    int counter;
} Ov029State;

typedef struct {
    s8 fadeMode;
    s8 areaId;
    s16 posX;
    s16 posY;
} Ov029EntryParams;

typedef struct {
    int unk_00;
    int heapHandle;
    int unk_08;
} TaskDescriptorArgs;

typedef int (*StateHandler)(void);

extern Ov029State *data_ov029_020baba0;
extern u8 data_020b52a0[];
extern u8 data_0209eb18[];

extern Ov029State *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void CreateSessionNameMenu_02063ba4(void);
extern void func_ov029_020ba8b8(void);
extern void QueueFieldUpdate_020633a0(int mode);
extern int func_0202a158(void);
extern void *func_0202a448(void *descriptor, void *userData);
extern int RunSceneStateMachine_020ba4a4(void);

StateHandler InitOv029OverlayState_020ba3e0(Ov029EntryParams *params)
{
    TaskDescriptorArgs argsCopy;
    TaskDescriptorArgs args;

    data_ov029_020baba0 = NNSi_FndGetCurrentRootHeap_0202a764();
    data_ov029_020baba0->areaId = params->areaId;
    data_ov029_020baba0->posX = params->posX;
    data_ov029_020baba0->posY = params->posY;
    data_ov029_020baba0->flags = 3;
    CreateSessionNameMenu_02063ba4();
    func_ov029_020ba8b8();
    QueueFieldUpdate_020633a0(0);
    args.heapHandle = func_0202a158();
    args.unk_00 = 0;
    args.unk_08 = 0;
    argsCopy = args;
    data_ov029_020baba0->mainTask = func_0202a448(data_020b52a0, &argsCopy);
    data_ov029_020baba0->subTask = func_0202a448(data_0209eb18, NULL);
    data_ov029_020baba0->counter = 0;
    return RunSceneStateMachine_020ba4a4;
}

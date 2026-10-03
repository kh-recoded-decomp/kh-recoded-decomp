#include "nitro/types.h"

typedef void (*ModeHandler)(void);

typedef struct ModeHandlers {
    ModeHandler handlers[10];
} ModeHandlers;

extern void func_ov033_020ba8d4(void);
extern void func_ov033_020ba8f8(void);
extern void func_ov033_020ba924(void);
extern void func_ov033_020ba948(void);
extern void func_ov033_020ba96c(void);
extern void func_ov033_020ba990(void);
extern void func_ov033_020ba9b0(void);
extern void func_ov033_020ba9b8(void);

void InstallResumeModeHandlers_020ba9cc(ModeHandlers *table)
{
    table->handlers[0] = func_ov033_020ba8d4;
    table->handlers[1] = func_ov033_020ba8f8;
    table->handlers[2] = func_ov033_020ba924;
    table->handlers[3] = func_ov033_020ba948;
    table->handlers[4] = func_ov033_020ba96c;
    table->handlers[5] = func_ov033_020ba990;
    table->handlers[6] = NULL;
    table->handlers[7] = func_ov033_020ba9b0;
    table->handlers[8] = NULL;
    table->handlers[9] = func_ov033_020ba9b8;
}

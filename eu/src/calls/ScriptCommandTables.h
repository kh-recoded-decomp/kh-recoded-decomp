#ifndef EU_SCRIPT_COMMAND_TABLES_H
#define EU_SCRIPT_COMMAND_TABLES_H

#include "nitro/types.h"

typedef struct ScriptVm ScriptVm;

/* run consumes operands; resume polls a suspended command's saved argument. */
typedef struct ScriptCommandHandler {
    int (*run)(ScriptVm *vm, u8 *operands);
    int (*resume)(ScriptVm *vm, s32 argument);
} ScriptCommandHandler;

extern ScriptCommandHandler gCoreScriptCommandHandlers[33];
extern ScriptCommandHandler *gScriptHandlerTables[9];

#endif

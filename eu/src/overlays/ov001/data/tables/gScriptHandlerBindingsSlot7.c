#include "src/overlays/ov001/ScriptHandlerBindings.h"

extern const u8 gOv005HandlerTable[];
extern const u8 gOv006Handlers[];
extern const u8 gFieldActorScriptCommandHandlers[];
extern const u8 gOv008ScriptObjectCreationHandlers[];
extern const u8 gOv009ScriptObjectHandlers[];
extern const u8 gOv010ScriptObjectCreationHandlers[];
extern const u8 gCrawlScriptCommandHandlers[];
extern const u8 gDefaultStepHandler[];

const ScriptHandlerBindingsSlot7Table gScriptHandlerBindingsSlot7 = {{
    { 0, -1 },
    { gOv005HandlerTable, 5 },
    { gOv006Handlers, 6 },
    { gFieldActorScriptCommandHandlers, 7 },
    { gOv008ScriptObjectCreationHandlers, 8 },
    { gOv009ScriptObjectHandlers, 9 },
    { gOv010ScriptObjectCreationHandlers, 10 },
    { gCrawlScriptCommandHandlers, 11 },
    { gDefaultStepHandler, 12 },
}};

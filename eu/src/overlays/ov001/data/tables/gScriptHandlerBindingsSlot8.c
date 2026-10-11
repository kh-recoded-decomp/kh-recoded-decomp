#include "src/overlays/ov001/ScriptHandlerBindings.h"

extern const u8 data_ov016_020a6e60[];
extern const u8 gPoolScriptCommandHandlers[];
extern const u8 gScriptObjectCreationHandlers[];
extern const u8 gLinkedObjectCreationHandlers[];
extern const u8 gPanelObjectScriptCommandHandlers[];

const ScriptHandlerBindingsSlot8Table gScriptHandlerBindingsSlot8 = {{
    { data_ov016_020a6e60, 16 },
    { gPoolScriptCommandHandlers, 17 },
    { gScriptObjectCreationHandlers, 18 },
    { gLinkedObjectCreationHandlers, 19 },
    { gPanelObjectScriptCommandHandlers, 20 },
}};

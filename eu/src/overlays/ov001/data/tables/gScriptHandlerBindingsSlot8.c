#include "src/overlays/ov001/ScriptHandlerBindings.h"

extern const u8 gOverlay016ScriptCommandHandlers[];
extern const u8 gPoolScriptCommandHandlers[];
extern const u8 gScriptObjectCreationHandlers[];
extern const u8 gLinkedObjectCreationHandlers[];
extern const u8 gPanelObjectScriptCommandHandlers[];

const ScriptHandlerBindingsSlot8Table gScriptHandlerBindingsSlot8 = {{
    { gOverlay016ScriptCommandHandlers, 16 },
    { gPoolScriptCommandHandlers, 17 },
    { gScriptObjectCreationHandlers, 18 },
    { gLinkedObjectCreationHandlers, 19 },
    { gPanelObjectScriptCommandHandlers, 20 },
}};

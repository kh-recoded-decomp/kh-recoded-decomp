#ifndef RECODED_SCRIPT_HANDLER_BINDINGS_H
#define RECODED_SCRIPT_HANDLER_BINDINGS_H

#include "nitro/types.h"

typedef struct ScriptHandlerOverlayBinding {
    const void *handlers;
    int overlayId;
} ScriptHandlerOverlayBinding;

typedef struct ScriptHandlerBindingsSlot7Table {
    ScriptHandlerOverlayBinding entries[9];
} ScriptHandlerBindingsSlot7Table;

typedef struct ScriptHandlerBindingsSlot8Table {
    ScriptHandlerOverlayBinding entries[5];
} ScriptHandlerBindingsSlot8Table;

typedef struct FieldScriptHandlerState {
    u8 unknown00[0x10];
    int slot7OverlayId;
    int slot8OverlayId;
    u8 slot7Index;
    u8 slot8Index;
} FieldScriptHandlerState;

/* Stored in engine table slots 7 and 8 before loading the owning overlay. */
extern const ScriptHandlerBindingsSlot7Table gScriptHandlerBindingsSlot7;
extern const ScriptHandlerBindingsSlot8Table gScriptHandlerBindingsSlot8;

void BindScriptHandlersSlot7(int index);
void BindScriptHandlersSlot8(int index);

#endif

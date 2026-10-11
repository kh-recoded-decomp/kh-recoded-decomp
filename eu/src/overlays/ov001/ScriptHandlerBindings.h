#ifndef RECODED_SCRIPT_HANDLER_BINDINGS_H
#define RECODED_SCRIPT_HANDLER_BINDINGS_H

#include "nitro/types.h"

typedef struct ScriptHandlerOverlayBinding {
    const void *handlers;
    int overlayId;
} ScriptHandlerOverlayBinding;

/* Stored in engine table slots 7 and 8 before loading the owning overlay. */
extern const ScriptHandlerOverlayBinding gScriptHandlerBindingsSlot7[9];
extern const ScriptHandlerOverlayBinding gScriptHandlerBindingsSlot8[5];

#endif

#include "src/overlays/ov001/ScriptHandlerBindings.h"

extern FieldScriptHandlerState *data_ov001_020a0480;
extern void StoreGlobalArrayEntry(int index, int value);
extern void LoadOverlayAfterGeometryTransfer(int processor, int overlayId);

void BindScriptHandlersSlot7(int index)
{
    ScriptHandlerBindingsSlot7Table bindings = gScriptHandlerBindingsSlot7;
    if (bindings.entries[index].handlers != NULL)
        StoreGlobalArrayEntry(7, (int)bindings.entries[index].handlers);
    if (bindings.entries[index].overlayId != -1) {
        data_ov001_020a0480->slot7OverlayId = bindings.entries[index].overlayId;
        LoadOverlayAfterGeometryTransfer(0, data_ov001_020a0480->slot7OverlayId);
    }
    data_ov001_020a0480->slot7Index = index;
}

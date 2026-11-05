#include "src/overlays/ov001/ScriptHandlerBindings.h"

extern FieldScriptHandlerState *data_ov001_020a0480;
extern void StoreGlobalArrayEntry(int index, int value);
extern void LoadOverlayAfterGeometryTransfer(int processor, int overlayId);

void BindScriptHandlersSlot8(int index)
{
    ScriptHandlerBindingsSlot8Table bindings = gScriptHandlerBindingsSlot8;
    if (bindings.entries[index].handlers != NULL)
        StoreGlobalArrayEntry(8, (int)bindings.entries[index].handlers);
    if (bindings.entries[index].overlayId != -1) {
        data_ov001_020a0480->slot8OverlayId = bindings.entries[index].overlayId;
        LoadOverlayAfterGeometryTransfer(0, data_ov001_020a0480->slot8OverlayId);
        data_ov001_020a0480->slot8Index = index;
    }
}

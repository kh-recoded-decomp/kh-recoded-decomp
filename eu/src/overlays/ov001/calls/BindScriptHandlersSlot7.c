#include "src/overlays/ov001/ScriptHandlerBindings.h"

extern FieldScriptHandlerState *gFieldSessionWork;
extern void StoreGlobalArrayEntry(int index, int value);
extern void LoadOverlayAfterGeometryTransfer(int processor, int overlayId);

void BindScriptHandlersSlot7(int index)
{
    ScriptHandlerBindingsSlot7Table bindings = gScriptHandlerBindingsSlot7;
    if (bindings.entries[index].handlers != NULL)
        StoreGlobalArrayEntry(7, (int)bindings.entries[index].handlers);
    if (bindings.entries[index].overlayId != -1) {
        gFieldSessionWork->slot7OverlayId = bindings.entries[index].overlayId;
        LoadOverlayAfterGeometryTransfer(0, gFieldSessionWork->slot7OverlayId);
    }
    gFieldSessionWork->slot7Index = index;
}

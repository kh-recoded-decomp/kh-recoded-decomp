#include "nitro/types.h"

extern void RefreshAreaEvents();
extern void SwitchAreaObjects();
extern void SwitchAreaLayers();
extern void UpdateAreaProgressLevel();

void RefreshAreaEventObjectAndLayerState(u32 handle)
{
    RefreshAreaEvents();
    SwitchAreaObjects(handle);
    UpdateAreaProgressLevel(handle);
    SwitchAreaLayers(handle);
}

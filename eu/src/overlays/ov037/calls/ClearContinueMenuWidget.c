#include "src/overlays/ov037/ContinueMenu.h"

extern void ClearWidgetTileArea(ContinueMenuTileTable *, ContinueMenuWidget *);

void ClearContinueMenuWidget(ContinueMenuWidget *widget)
{
    ClearWidgetTileArea(&gContinueScreenContext->tileTable, widget);
}

#include "src/overlays/ov037/ContinueMenu.h"

extern void BlitWidgetToTileTable(ContinueMenuTileTable *, ContinueMenuWidget *);

void BlitContinueMenuWidget(ContinueMenuWidget *widget)
{
    BlitWidgetToTileTable(&gContinueScreenContext->tileTable, widget);
}

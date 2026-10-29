#include "src/overlays/ov027/WidgetPosition.h"

WidgetPoint *GetWidgetPosition(void *context, WidgetPositionRecord *widget)
{
    return &widget->position;
}

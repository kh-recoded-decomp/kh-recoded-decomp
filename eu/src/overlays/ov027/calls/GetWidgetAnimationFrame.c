#include "src/overlays/ov027/WidgetPosition.h"
#include "src/overlays/ov027/WidgetRecordOps.h"
#include "src/indexed_records/IndexedRecordState.h"

int GetWidgetAnimationFrame(void *records, const WidgetPositionRecord *widget)
{
    int i;
    int result;
    int absent;
    int id;

    result = 0;
    i = result;
    absent = -1;
    do {
        id = widget->recordIds[i];
        if (id != absent) {
            result = GetIndexedRecordAnimationFrame(records, id);
            break;
        }
        i++;
    } while (i < 2);
    return result;
}

#include "src/overlays/ov027/WidgetPosition.h"
#include "src/overlays/ov027/WidgetRecordOps.h"
#include "src/indexed_records/IndexedRecordState.h"

void SetWidgetRecordMode(void *records, const WidgetPositionRecord *widget, int mode)
{
    int i;
    for (i = 0; i < 2; i++) {
        int id = widget->recordIds[i];
        if (id != -1) {
            SetIndexedRecordMode(records, id, mode);
        }
    }
}

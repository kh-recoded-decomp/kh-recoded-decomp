#include "src/overlays/ov027/WidgetPosition.h"
#include "src/overlays/ov027/WidgetRecordOps.h"
#include "src/indexed_records/IndexedRecordState.h"

void SetWidgetRecordActiveBits(void *records, const WidgetPositionRecord *widget)
{
    int i;
    int id;
    for (i = 0; i < 2; i++) {
        id = widget->recordIds[i];
        if (id != -1) {
            IndexedRecord_SetActive(records, id);
        }
    }
}

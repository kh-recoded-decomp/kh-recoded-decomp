#ifndef EU_WIDGET_RECORD_OPS_H
#define EU_WIDGET_RECORD_OPS_H

/* The existing prefix is defined in WidgetPosition.h. Keep this public API
 * independent of that header's separate position-function declarations.
 */
struct WidgetPositionRecord;

void ClearWidgetRecordActiveBits(void *records, const struct WidgetPositionRecord *widget);
void SetWidgetRecordActiveBits(void *records, const struct WidgetPositionRecord *widget);
/* Query the first ID other than -1; zero if both are absent. Other negative
 * IDs still select a slot, then the indexed getter returns zero.
 */
int GetWidgetAnimationFrame(void *records, const struct WidgetPositionRecord *widget);
void SetWidgetAnimationFrame(void *records, const struct WidgetPositionRecord *widget, int frame);
/* Writes mode & 3 to each configured indexed record. */
void SetWidgetRecordMode(void *records, const struct WidgetPositionRecord *widget, int mode);

#endif

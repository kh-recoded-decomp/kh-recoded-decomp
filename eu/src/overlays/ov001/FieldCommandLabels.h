#ifndef FIELD_COMMAND_LABELS_H
#define FIELD_COMMAND_LABELS_H

#include "nitro/types.h"

/* UTF-16 labels, including their terminator and original alignment padding. */
extern u16 gFieldEmptyCommandLabel[12];
extern u16 gFieldFinishCommandLabel[8];

struct PackedResourceView;
/* Copies the frame tile template to the indexed cell and draws its packed
 * entry using the existing field text helper. menuBase is a DS menu view.
 */
void DrawPackedFieldMenuEntry(void *menuBase, const struct PackedResourceView *view, u32 index);

#endif

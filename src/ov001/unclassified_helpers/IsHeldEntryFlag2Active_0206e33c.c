#include "nitro/types.h"

typedef struct Entry Entry;

struct Entry {
    u8 pad[0x21c];
    u32 (*getFlags)(Entry *entry);
};

typedef struct {
    u8 pad[8];
    Entry *entry;
} Holder;

extern Holder *data_ov001_020a049c;
extern u32 GetBoundedEntryField_0206db5c(int index);

static inline u32 GetEntryFlags(Entry *entry) {
    if (entry->getFlags != NULL) {
        return entry->getFlags(entry);
    }
    return 0;
}

BOOL IsHeldEntryFlag2Active_0206e33c(void) {
    Holder *holder = data_ov001_020a049c;
    BOOL result = FALSE;
    if (holder == NULL) {
        return result;
    }
    if (GetBoundedEntryField_0206db5c(0) != 0 && (GetEntryFlags(holder->entry) & 2)) {
        result = TRUE;
    }
    return result;
}

#include "nitro/types.h"

typedef struct FadeEntry {
    s8 material;
    s8 target;
    s8 value;
    u8 unknown_03;
} FadeEntry;

typedef struct FadeWork {
    u8 unknown_000[0x109];
    s8 current;
    s8 count;
    u8 active;
    FadeEntry *entries;
} FadeWork;

extern FadeWork *data_ov035_020bc4e4;
extern const s8 data_ov035_020bc3ec[4];
extern int func_ov035_020bae74(void);
extern void func_ov035_020bb40c(int index, int mode);
extern int func_ov035_020badf0(int index);
extern void func_ov035_020bb448(int index);
extern void AdvanceAnimationTracks_0202ef24(FadeWork *work, int frames);

void UpdateMaterialFades_020bb670(int selection, int frames) {
    FadeWork *work = data_ov035_020bc4e4;
    int i;

    if (work->active == 0) {
        return;
    }
    if (func_ov035_020bae74() == 0) {
        int previous = work->current;
        if (previous != selection) {
            if (previous >= 0) {
                func_ov035_020bb40c(previous, 0);
            }
            work->current = selection;
        }
        if (selection >= 0) {
            u8 kind = func_ov035_020badf0(work->current);
            if (kind <= 3) {
                func_ov035_020bb40c(selection, data_ov035_020bc3ec[kind]);
            }
        }
        for (i = 0; i < work->count; i++) {
            FadeEntry *entry = &work->entries[i];
            if (entry->value > entry->target) {
                entry->value -= 4;
                if (entry->value < entry->target) {
                    entry->value = entry->target;
                }
                func_ov035_020bb448(i);
            } else if (entry->value < entry->target) {
                entry->value += 4;
                if (entry->value > entry->target) {
                    entry->value = entry->target;
                }
                func_ov035_020bb448(i);
            }
        }
    }
    AdvanceAnimationTracks_0202ef24(work, frames);
}

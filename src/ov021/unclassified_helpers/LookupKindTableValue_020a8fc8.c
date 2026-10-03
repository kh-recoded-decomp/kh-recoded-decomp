#include "nitro/types.h"

typedef struct {
    s16 values[17];
} KindTable;

extern const KindTable data_ov021_020b4e3c;
extern const KindTable data_ov021_020b4e60;
extern const KindTable data_ov021_020b4e84;

int LookupKindTableValue_020a8fc8(u32 kind, int index)
{
    KindTable primary;
    KindTable secondary;
    KindTable tertiary;
    int result = -1;

    switch (kind) {
    case 0:
    case 3:
        primary = data_ov021_020b4e3c;
        if (index <= 17) {
            result = primary.values[index];
        }
        break;
    case 2:
        secondary = data_ov021_020b4e60;
        if (index <= 17) {
            result = secondary.values[index];
        }
        break;
    case 1:
        tertiary = data_ov021_020b4e84;
        if (index <= 17) {
            result = tertiary.values[index];
        }
        break;
    }
    return result;
}

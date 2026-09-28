#include "nitro/types.h"

typedef struct {
    int linked;
    int kind;
} KindObj;

BOOL IsKind4WithState0Or3_020a0a74(KindObj *obj) {
    if ((obj->kind == 4) &&
        ((*(int *)(obj->linked + 0x40) == 0) || (*(int *)(obj->linked + 0x40) == 3))) {
        return 0;
    }
    return 1;
}

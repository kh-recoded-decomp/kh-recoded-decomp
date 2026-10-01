#include "nitro/types.h"

typedef struct CollModel CollModel;

typedef struct CollModelSet {
    u16 pad_00;
    u16 modelCount;
    CollModel **models;
} CollModelSet;

typedef void (*CollFaceCallback)(CollModel *model, void *face, void *arg);

extern CollModelSet *func_02036230(void);
extern char *FindNextNamedEntry_020670b4(CollModel *model, const char *name, int nameLength, int *searchIndex);
extern void ForEachFaceOnPoint_02033918(CollModel *model, u8 kindMask, char *point, CollFaceCallback callback, void *arg);
extern void func_ov001_02068180(CollModel *model, void *face, void *arg);

void ApplyToNamedCollisionFaces_020680fc(const char *name, int nameLength, void *arg)
{
    int i;
    CollModelSet *set = func_02036230();

    for (i = 0; i < set->modelCount; i++) {
        CollModel *model = set->models[i];
        char *entry;
        int cursor;

        for (cursor = 0;; cursor++) {
            entry = FindNextNamedEntry_020670b4(model, name, nameLength, &cursor);
            if (entry == NULL) {
                break;
            }
            ForEachFaceOnPoint_02033918(model, 2, entry, func_ov001_02068180, arg);
            ForEachFaceOnPoint_02033918(model, 1, entry, func_ov001_02068180, arg);
            ForEachFaceOnPoint_02033918(model, 4, entry, func_ov001_02068180, arg);
        }
    }
}

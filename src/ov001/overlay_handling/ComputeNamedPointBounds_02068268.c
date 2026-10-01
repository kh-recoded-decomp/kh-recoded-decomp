#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 nameId;
    u8 pad_01[7];
} PointRecord;

typedef struct {
    u8 pad_00[0x20];
    PointRecord *records;
} PointSet;

typedef struct {
    u8 pad_00[8];
    PointSet *sets[1];
} PointTable;

typedef struct {
    u16 pad_00;
    u16 count;
    void **models;
} ModelGroup;

typedef struct {
    VecFx32 min;
    VecFx32 max;
} Bounds;

extern PointTable **data_ov001_020a046c;
extern char data_ov001_0209ea70[];
extern char data_ov001_0209ea78[];
extern ModelGroup *func_02036230(void);
extern int OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern int Strlen_02021e44(const char *str);
extern char *FindNextNamedEntry_020670b4(void *owner, const char *name, int length, int *index);
extern void ForEachFaceOnPoint_02033918(void *model, u8 kindMask, char *point, void *callback, void *arg);
extern void func_ov001_02067184(void);
extern void func_01ff8710(const void *src, void *dst, u32 size);

BOOL ComputeNamedPointBounds_02068268(int setIndex, int recordIndex, VecFx32 *outMin, VecFx32 *outMax)
{
    int i;
    ModelGroup *group;
    char name[8];
    int index;
    Bounds bounds;

    group = func_02036230();
    OS_SPrintf_02002428(name, data_ov001_0209ea70, data_ov001_0209ea78,
                        (*data_ov001_020a046c)->sets[setIndex]->records[recordIndex].nameId);
    bounds.min.z = 0x7fffffff;
    bounds.min.y = 0x7fffffff;
    bounds.min.x = 0x7fffffff;
    bounds.max.z = 0x80000000;
    bounds.max.y = 0x80000000;
    bounds.max.x = 0x80000000;
    for (i = 0; i < group->count; i++) {
        void *model = group->models[i];
        char *entry;
        index = 0;
        for (;;) {
            entry = FindNextNamedEntry_020670b4(model, name, Strlen_02021e44(name), &index);
            if (entry == 0) {
                break;
            }
            ForEachFaceOnPoint_02033918(model, 2, entry, func_ov001_02067184, &bounds);
            index++;
        }
    }
    if (bounds.min.x != 0x7fffffff && bounds.max.x != 0x80000000) {
        func_01ff8710(&bounds.min, outMin, sizeof(VecFx32));
        func_01ff8710(&bounds.max, outMax, sizeof(VecFx32));
        return TRUE;
    }
    return FALSE;
}



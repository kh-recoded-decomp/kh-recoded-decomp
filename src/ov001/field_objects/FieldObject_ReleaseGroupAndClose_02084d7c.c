#include "nitro/types.h"

typedef struct FieldWork {
    u8 pad_00[0x86];
    s16 groupId;
} FieldWork;

typedef struct FieldObject {
    u8 pad_00[8];
    FieldWork *work;
} FieldObject;

extern void func_ov021_020a8a68(int groupId);
extern void func_ov001_0207f20c(FieldObject *object, void *arg);

void FieldObject_ReleaseGroupAndClose_02084d7c(FieldObject *object, void *arg)
{
    FieldWork *work = object->work;

    if (work->groupId != -1) {
        func_ov021_020a8a68(work->groupId);
        work->groupId = -1;
    }
    func_ov001_0207f20c(object, arg);
}

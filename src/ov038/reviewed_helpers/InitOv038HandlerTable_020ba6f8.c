#include "nitro/types.h"

typedef struct Ov038HandlerTable {
    void *start;
    void *isIdle;
    void *update;
    void *setMode;
    void *hasObject;
    void *release;
    void *reserved0;
    void *pause;
    void *reserved1[2];
    void *resume;
} Ov038HandlerTable;

extern void func_ov038_020ba5fc(void);
extern void IsOv038SoundCtxFlag0Clear_020ba620(void);
extern void func_ov038_020ba64c(void);
extern void SetSoundCtxMode_020ba670(void);
extern void HasOv038ObjectField28_020ba694(void);
extern void ReleaseOv038Object_020ba6b8(void);
extern void func_ov038_020ba6d8(void);
extern void func_ov038_020ba6e0(void);

void InitOv038HandlerTable_020ba6f8(Ov038HandlerTable *table)
{
    table->start = func_ov038_020ba5fc;
    table->isIdle = IsOv038SoundCtxFlag0Clear_020ba620;
    table->update = func_ov038_020ba64c;
    table->setMode = SetSoundCtxMode_020ba670;
    table->hasObject = HasOv038ObjectField28_020ba694;
    table->release = ReleaseOv038Object_020ba6b8;
    table->pause = func_ov038_020ba6d8;
    table->resume = func_ov038_020ba6e0;
}

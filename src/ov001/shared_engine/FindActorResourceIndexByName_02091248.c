#include "nitro/types.h"

typedef struct ActorModel {
    u8 pad_00[0x28];
    u8 *modelResource;
} ActorModel;

typedef struct ModelActor {
    u8 pad_00[0x10];
    ActorModel model;
} ModelActor;

extern char g_resourceNameBuffer_020a04f8[];
extern void func_01ff86fc(u32 data, void *dst, u32 size);
extern u32 Strlen_02021e44(const char *str);
extern char *strncpy_02021f28(char *dst, const char *src, u32 count);
extern int FindResourceIndexByName_0201aafc(const void *dict, const void *name);

u16 FindActorResourceIndexByName_02091248(ModelActor *actor, const char *name)
{
    ActorModel *model = &actor->model;
    void *dict = NULL;
    u32 length;

    if (name == NULL) {
        return 0xffff;
    }
    length = Strlen_02021e44(name);
    if (length >= 0x10) {
        return 0xffff;
    }
    func_01ff86fc(0, g_resourceNameBuffer_020a04f8, 0x10);
    strncpy_02021f28(g_resourceNameBuffer_020a04f8, name, length);
    if (model->modelResource != NULL) {
        dict = model->modelResource + 0x40;
    }
    return dict != NULL ? FindResourceIndexByName_0201aafc(dict, g_resourceNameBuffer_020a04f8) : -1;
}

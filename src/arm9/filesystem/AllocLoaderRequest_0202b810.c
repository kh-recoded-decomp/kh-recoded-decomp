#include "nitro/types.h"

typedef struct LoaderRequest {
    struct LoaderRequest *next;
} LoaderRequest;

typedef struct FileLoader {
    u8 pad_00[0x18];
    LoaderRequest *volatile freeList;
} FileLoader;

extern FileLoader data_02060564;

extern int func_02004938(void);
extern void func_0200494c(int state);
extern int func_0202c438(void);

LoaderRequest *AllocLoaderRequest_0202b810(void)
{
    int state = func_02004938();
    LoaderRequest *request;

    while (data_02060564.freeList == NULL) {
        func_0202c438();
    }
    request = data_02060564.freeList;
    if (request != NULL) {
        data_02060564.freeList = request->next;
        request->next = NULL;
    }
    func_0200494c(state);
    return request;
}

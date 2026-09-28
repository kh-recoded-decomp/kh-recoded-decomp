#include "nitro/types.h"

typedef struct ListView {
    u8 pad_00[0xc];
    void *workBuffer;
} ListView;

extern void *func_ov027_020ba1d8(void *request);
extern void func_ov073_020c3530(ListView *list, void *data, void *workBuffer);
extern void func_ov027_020ba1e0(void *request, BOOL freeData);

void OnListDataLoaded_020c3684(void *request, ListView *list)
{
    func_ov073_020c3530(list, func_ov027_020ba1d8(request), list->workBuffer);
    func_ov027_020ba1e0(request, TRUE);
}

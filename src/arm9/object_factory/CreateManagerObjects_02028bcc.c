#include "nitro/types.h"

typedef struct ManagerObjects
{
    u8 pad_00[0x14];
    void *firstObject;
    void *secondObject;
} ManagerObjects;

extern u8 data_02055fc0[];
extern u8 data_02055fac[];
extern ManagerObjects data_0205fea8;
extern void *func_0202a448(void *descriptor, void *userData);

void CreateManagerObjects_02028bcc(void)
{
    data_0205fea8.firstObject = func_0202a448(data_02055fc0, NULL);
    data_0205fea8.secondObject = func_0202a448(data_02055fac, NULL);
}

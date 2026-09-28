#include "nitro/types.h"

extern u8 data_ov001_0209ea00[];
extern void *data_ov001_0209e9fc;
extern void *func_0202a448(void *descriptor, void *userData);

void CreateSubScene9Task_02066e00(void)
{
    data_ov001_0209e9fc = func_0202a448(data_ov001_0209ea00, NULL);
}

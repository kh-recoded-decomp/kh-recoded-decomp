#include "nitro/types.h"

extern int func_ov036_020c2870(void);

int GetTextWindowStatus_020c3080(void)
{
    int status;

    switch (func_ov036_020c2870()) {
    case 0:
        status = 0;
        break;
    case 1:
    case 4:
        status = 1;
        break;
    case 6:
        status = 2;
        break;
    case 7:
        status = 3;
        break;
    }
    return status;
}

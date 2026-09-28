#include "nitro/types.h"

/* Raises a field to a new floor value */
void ExtendIfGreater_020cc1ec(int entity, int minValue)
{
    if (*(int *)(entity + 0x9f8) < minValue) {
        *(int *)(entity + 0x9f8) = minValue;
    }
}

#include "nitro/types.h"

typedef struct FlagValues {
    int values[6];
} FlagValues;

extern const FlagValues data_02055ae4;
extern u8 *data_0205fe0c;

int GetFlagTableValue_020511c4(void)
{
    FlagValues table = data_02055ae4;

    return table.values[(u16)(data_0205fe0c[0x2c66] & 7)];
}

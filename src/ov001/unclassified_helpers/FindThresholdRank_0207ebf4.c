#include "nitro/types.h"

extern u32 data_ov001_0209e114[][3];

int FindThresholdRank_0207ebf4(int row, u32 value)
{
    int result = 3;
    int rank;

    for (rank = 0; rank < 3; rank++) {
        if (value >= data_ov001_0209e114[row][rank]) {
            result = rank;
            break;
        }
    }
    return result;
}

#include "nitro/types.h"

typedef struct LayoutCell {
    u32 unk_00;
    u32 unk_04;
} LayoutCell;

extern LayoutCell data_ov001_0209e0c4;
extern LayoutCell data_ov001_0209e180[][6];

LayoutCell *GetLayoutCell_0207ec2c(int row, int column, int offset)
{
    if (offset == 3) {
        return &data_ov001_0209e0c4;
    }
    return &data_ov001_0209e180[row][column + offset];
}

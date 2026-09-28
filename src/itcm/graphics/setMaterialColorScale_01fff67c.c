typedef unsigned short u16;

typedef struct MaterialColorScale {
    u16 red;
    u16 green;
    u16 blue;
} MaterialColorScale;

extern MaterialColorScale data_027e01f0;
extern u16 data_027e01ec;

void setMaterialColorScale_01fff67c(int packedRgb)
{
    data_027e01ec = 1;
    data_027e01f0.red = (packedRgb & 0x1f) + 1;
    data_027e01f0.green = ((packedRgb >> 5) & 0x1f) + 1;
    data_027e01f0.blue = ((packedRgb >> 10) & 0x1f) + 1;
}

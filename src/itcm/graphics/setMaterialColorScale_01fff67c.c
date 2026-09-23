/* Behavior: Unpacks a 15-bit RGB value into three material color scale channels.
 * Inputs/outputs and evidence: Sets an enable word and extracts three five-bit channels, storing each plus one.
 * Uncertainty: Meaning of the enable word is inferred from adjacent material state, not present here.
 * Source: khdays-decomp/src/calls/func_01ffcec0.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
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

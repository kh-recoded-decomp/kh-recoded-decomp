/* Emits uniform scale from normal or alternate value when explicit scale is absent.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/func_01ffcbac.c.
 * Original routine: func_01ffcbac. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef unsigned int u32;
typedef unsigned char u8;

typedef struct RenderCommandState {
    u8 *stream00;
    u8 pad04[4];
    u32 flags08;
    u8 pad0c[0xe0 - 0x0c];
    u32 scaleE0;
    u32 alternateScaleE4;
} RenderCommandState;

extern void func_01ffa37c(u32 command, const void *words, u32 count);

void EmitJointScaleCommand_01fff374(RenderCommandState *state, int useAlternate)
{
    u32 values[3];

    if ((state->flags08 & 0x100) == 0 &&
        (state->flags08 & 0x200) == 0) {
        if (useAlternate == 0) {
            values[0] = values[1] = values[2] = state->scaleE0;
        } else {
            values[0] = values[1] = values[2] = state->alternateScaleE4;
        }
        func_01ffa37c(0x1b, values, 3);
    }
    state->stream00++;
}

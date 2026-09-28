/* Clamps a frame coordinate, selects a frame-table record, and forwards its payload.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/func_01ffb234.c.
 * Original routine: func_01ffb234. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef void (*JointScaleCallback)(u32 *result, u32 *scratch,
                                   void *render_context, u32 flags);

typedef struct NNSG3dRenderState {
    void *render_context;
    u8 unknown_004[0xe4];
    JointScaleCallback joint_scale_callback;
} NNSG3dRenderState;

extern NNSG3dRenderState *data_0205ab60;

extern void func_02039a54(void *model, void *record, u32 packed,
                          u32 coordinate, u32 *result, u32 *scratch);
extern void func_01ffd6ac(void *model, void *record, u32 packed,
                          u32 coordinate, u32 *result, u32 *scratch);

void HandleJointAnimationStreamCommand_01ffd934(u32 *result, u32 *input, s32 index)
{
    u32 scratch[6];
    u8 *model = (u8 *)input[2];
    s32 coordinate = (s32)input[0];
    s32 limit = *(u16 *)(model + 4);
    u32 offset;
    u32 packed;
    u32 callback_flags;
    NNSG3dRenderState *state;

    if (coordinate >= limit << 12) {
        coordinate = (limit << 12) - 1;
    } else if (coordinate < 0) {
        coordinate = 0;
    }

    offset = *(u16 *)(model + index * 2 + 0x14);
    packed = *(u32 *)(model + offset);
    if (packed & 1) {
        *result = 7;
        return;
    }

    *result = 0;
    if ((coordinate & 0xfff) != 0 && (*(u32 *)(model + 8) & 1) != 0) {
        func_02039a54(model, model + offset, packed, coordinate,
                      result, scratch);
    } else {
        func_01ffd6ac(model, model + offset, packed, coordinate,
                      result, scratch);
    }

    callback_flags = (*result & 1) ? 4 : 0;
    state = data_0205ab60;
    state->joint_scale_callback(result, scratch, state->render_context,
                                callback_flags);
}

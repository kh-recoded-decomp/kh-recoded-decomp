/* Resolves a frame-table entry, submits its payload, and advances render stream.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/func_01ffc0d0.c.
 * Original routine: func_01ffc0d0. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct FrameTable {
    u8 unknown00;
    u8 frameCount01;
    u8 pad02[4];
    u16 entryTableOffset06;
} FrameTable;

typedef struct FrameData {
    u8 pad00[8];
    u32 payloadOffset08;
    u32 payloadSize0c;
} FrameData;

typedef struct RenderCommandState {
    u8 *stream00;
    u8 pad04[4];
    u32 flags08;
    u8 pad0c[0xdc - 0x0c];
    FrameTable *frameTableDc;
} RenderCommandState;

extern void func_01ffa204(const void *source, u32 size);

static inline s32 *GetFrameEntry(FrameTable *table, u32 frame)
{
    u8 *entries;
    u16 stride;
    s32 *entry;

    if (table != 0 && frame < table->frameCount01) {
        entries = (u8 *)table + table->entryTableOffset06;
        stride = *(u16 *)entries;
        entry = (s32 *)(entries + 4 + stride * frame);
    } else {
        entry = 0;
    }
    return entry;
}

void EmitJointAnimationFramePayload_01ffe8a0(RenderCommandState *state)
{
    FrameTable *table;
    FrameData *data;
    s32 *entry;
    u32 frame;

    if ((state->flags08 & 0x303) == 1) {
        frame = state->stream00[1];
        table = state->frameTableDc;
        if (table == 0) {
            goto no_data;
        }
        entry = GetFrameEntry(table, frame);
        if (entry != 0) {
            data = (FrameData *)((u8 *)table + *entry);
            goto have_data;
        }
no_data:
        data = 0;
have_data:
        func_01ffa204((u8 *)data + data->payloadOffset08, data->payloadSize0c);
    }
    state->stream00 += 2;
}

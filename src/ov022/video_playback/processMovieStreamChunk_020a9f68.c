/* Processes one pending movie-stream chunk and advances its stream and frame-slot cursors.
 * Evidence: Checks the pending/read counts at +0xcc/+0xc8, dispatches on the 16-bit type at +0x1c, records the current stream address and output buffer in the 0x14f8-byte slot table at +0x58, and advances the stream cursor by a type-specific size. When the slot index reaches the header count at +0x1e it resets the slot index and state word at +0xa4.
 * Uncertainty: Type meanings, helper internals, and the output buffer's eventual display path are not established here.
 * Source: Reconstructed from the BK9E Ghidra decompilation at build/ghidra/decompiled/ov022_func_ov022_020a9f68.c. No upstream C body was copied.
 */
typedef unsigned int u32;
typedef unsigned short u16;
enum MovieContextByteOffset {
    MOVIE_CONTEXT_CHUNK_TYPE = 0x1c,
    MOVIE_CONTEXT_STREAM_CURSOR_POINTER = 0x34,
    MOVIE_CONTEXT_CHUNK_SLOT_TABLE = 0x58,
    MOVIE_CONTEXT_READ_LIMIT = 0xc8,
    MOVIE_CONTEXT_PENDING_CHUNK_COUNT = 0xcc,
    MOVIE_CONTEXT_ACTIVE_SLOT_INDEX = 0xd0,
    MOVIE_CONTEXT_CHUNK_STATE = 0xa4,
    MOVIE_CONTEXT_SLOT_COUNT = 0x1e
};
struct MovieChunkRecord {
    int chunkStreamAddress;
    int outputBuffer;
    unsigned char unknown_008[0x14f0];
};
extern int func_ov022_020aac34(int chunkRecord);
extern void func_ov022_020ab5f4(int chunkRecord);
extern void func_ov022_020aaac8(int chunkRecord, int chunkAddress);
extern void func_ov022_020aaadc(int chunkRecord, int chunkAddress, int size, int outputBuffer);
extern void func_01ff869c(int source, int outputBuffer, int size, int option);
int processMovieStreamChunk_020a9f68(int movieContext, int outputBuffer, int unusedArgument, int copyOption)
{
    u16 chunkType;
    u32 frameSlot;
    if (*(int *)(movieContext + MOVIE_CONTEXT_PENDING_CHUNK_COUNT) == *(int *)(movieContext + MOVIE_CONTEXT_READ_LIMIT)) {
        return 0;
    }
    chunkType = *(short *)(movieContext + MOVIE_CONTEXT_CHUNK_TYPE);
    if (chunkType == 0) {
        return 0;
    }
    if (chunkType == 1) {
        ((struct MovieChunkRecord *)*(int *)(movieContext + MOVIE_CONTEXT_CHUNK_SLOT_TABLE))[*(int *)(movieContext + MOVIE_CONTEXT_ACTIVE_SLOT_INDEX)].chunkStreamAddress =
            **(int **)(movieContext + MOVIE_CONTEXT_STREAM_CURSOR_POINTER);
        ((struct MovieChunkRecord *)*(int *)(movieContext + MOVIE_CONTEXT_CHUNK_SLOT_TABLE))[*(int *)(movieContext + MOVIE_CONTEXT_ACTIVE_SLOT_INDEX)].outputBuffer = outputBuffer;
        **(int **)(movieContext + MOVIE_CONTEXT_STREAM_CURSOR_POINTER) += func_ov022_020aac34(*(int *)(movieContext + MOVIE_CONTEXT_ACTIVE_SLOT_INDEX) * 0x14f8 + *(int *)(movieContext + MOVIE_CONTEXT_CHUNK_SLOT_TABLE));
    } else if (chunkType == 2) {
        ((struct MovieChunkRecord *)*(int *)(movieContext + MOVIE_CONTEXT_CHUNK_SLOT_TABLE))[*(int *)(movieContext + MOVIE_CONTEXT_ACTIVE_SLOT_INDEX)].chunkStreamAddress =
            **(int **)(movieContext + MOVIE_CONTEXT_STREAM_CURSOR_POINTER);
        ((struct MovieChunkRecord *)*(int *)(movieContext + MOVIE_CONTEXT_CHUNK_SLOT_TABLE))[*(int *)(movieContext + MOVIE_CONTEXT_ACTIVE_SLOT_INDEX)].outputBuffer = outputBuffer;
        func_ov022_020ab5f4(*(int *)(movieContext + MOVIE_CONTEXT_ACTIVE_SLOT_INDEX) * 0x14f8 + *(int *)(movieContext + MOVIE_CONTEXT_CHUNK_SLOT_TABLE));
        **(int **)(movieContext + MOVIE_CONTEXT_STREAM_CURSOR_POINTER) += 0x28;
    } else if (chunkType == 3) {
        if (*(int *)(movieContext + MOVIE_CONTEXT_CHUNK_STATE) == 1) {
            func_ov022_020aaac8(*(int *)(movieContext + MOVIE_CONTEXT_ACTIVE_SLOT_INDEX) * 0x14f8 + *(int *)(movieContext + MOVIE_CONTEXT_CHUNK_SLOT_TABLE),
                                **(int **)(movieContext + MOVIE_CONTEXT_STREAM_CURSOR_POINTER));
            **(int **)(movieContext + MOVIE_CONTEXT_STREAM_CURSOR_POINTER) += 4;
        }
        func_ov022_020aaadc(*(int *)(movieContext + MOVIE_CONTEXT_ACTIVE_SLOT_INDEX) * 0x14f8 + *(int *)(movieContext + MOVIE_CONTEXT_CHUNK_SLOT_TABLE),
                            **(int **)(movieContext + MOVIE_CONTEXT_STREAM_CURSOR_POINTER), 0x80, outputBuffer);
        **(int **)(movieContext + MOVIE_CONTEXT_STREAM_CURSOR_POINTER) += 0x80;
    } else {
        func_01ff869c(**(int **)(movieContext + MOVIE_CONTEXT_STREAM_CURSOR_POINTER), outputBuffer, 0x200, copyOption);
        **(int **)(movieContext + MOVIE_CONTEXT_STREAM_CURSOR_POINTER) += 0x200;
    }
    frameSlot = *(u32 *)(movieContext + MOVIE_CONTEXT_ACTIVE_SLOT_INDEX) + 1;
    *(u32 *)(movieContext + MOVIE_CONTEXT_ACTIVE_SLOT_INDEX) = frameSlot;
    if (frameSlot == *(u16 *)(movieContext + MOVIE_CONTEXT_SLOT_COUNT)) {
        *(u32 *)(movieContext + MOVIE_CONTEXT_ACTIVE_SLOT_INDEX) = 0;
        *(u32 *)(movieContext + MOVIE_CONTEXT_CHUNK_STATE) = 0;
    }
    *(int *)(movieContext + MOVIE_CONTEXT_PENDING_CHUNK_COUNT) = *(int *)(movieContext + MOVIE_CONTEXT_PENDING_CHUNK_COUNT) + 1;
    return 1;
}

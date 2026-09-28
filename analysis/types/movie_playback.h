/* BK9E ARM9, 32-bit pointers. Partial layouts contain only fields observed in
 * the movie overlay decompilations. Reserved bytes and unknown fields are not
 * claims about their original semantic types. Evidence lives in
 * analysis/movie_playback.json.
 */
typedef unsigned char MovieU8;
typedef unsigned short MovieU16;
typedef unsigned int MovieU32;
typedef signed int MovieS32;

typedef struct MoviePixelConvertContext {
    MovieU32 lumaSource_000;             /* +0x00 from conversion-context base */
    MovieU32 chromaSource_004;           /* +0x04 */
    MovieU32 outputBuffer_008;           /* +0x08 */
    MovieU32 doubledSourceLine_00c;      /* +0x0c; caller supplies sourceLine * 2 */
    MovieU32 unknown_010[5];             /* +0x10 through +0x20 */
} MoviePixelConvertContext;

typedef struct MovieChunkRecordObserved {
    MovieU32 chunkStreamAddress_000;
    MovieU32 outputBuffer_004;
    MovieU8 unknown_008[0x14f0];
} MovieChunkRecordObserved; /* slot stride is 0x14f8 bytes */

typedef struct MoviePlaneSetupRequest {
    MovieU32 firstPlaneAddress;
    MovieU32 secondPlaneAddress;
    MovieU32 firstWorkingBufferAddress;
    MovieU32 secondWorkingBufferAddress;
    MovieU32 frameWidth;
    MovieU32 frameHeight;
    MovieU32 auxiliaryPlaneAddress;
    MovieU32 pixelClampTableAddress;
    MovieU32 modeIsNotTwo;
} MoviePlaneSetupRequest; /* Nine words passed to ov022:0x020b713c. */

/* The stream reader object assembled by ov022:0x020a91a0 and populated by
 * BindMovieReaderToFileContext_020aa130. Only the listed offsets are used in
 * the observed routines; other object state is omitted. */
typedef struct MovieReaderObserved {
    MovieU32 vtableAddress_000;
    MovieU32 fileSize_004;
    MovieU32 filePosition_008;
    MovieU32 fileContextAddress_00c;
    MovieU8 state_010;
    MovieU8 reserved_011[3];
} MovieReaderObserved;

typedef struct MovieAdpcmStateObserved {
    MovieS32 predictor_000;
    MovieS32 stepIndex_004;
} MovieAdpcmStateObserved;

typedef struct MovieDecoderInitializationView {
    MovieU32 unknown_03c[4];
    MovieU32 planeWidth_04c;
    MovieU32 planeHeight_050;
    MovieU32 saturationTableAddress_054;
    MovieU32 audioTrackRingAddress_058;
    MovieU32 lumaSlotTableAddress_05c;
} MovieDecoderInitializationView;

/* Ghidra and exact C recovery observe two uses of the +0x3c region: pixel
 * conversion request words and decoder-init resource fields. */
typedef union MovieDecoderOverlay_03c {
    MoviePixelConvertContext conversionRequest;
    MovieDecoderInitializationView initialization;
} MovieDecoderOverlay_03c;

typedef struct MovieDecodeContextObserved {
    MovieU32 readerAddress_000;
    MovieU8 signature_004[5];
    MovieU8 version_009;
    MovieU16 headerWordCount_00a;
    MovieU32 frameCount_00c;
    MovieU32 frameWidth_010;
    MovieU32 frameHeight_014;
    MovieU8 unknown_018[4];
    MovieU16 audioKind_01c;
    MovieU16 audioTrackCount_01e;
    MovieU32 unknown_020;
    MovieU32 scratchBufferBytes_024;
    MovieU32 audioDataOffset_028;
    MovieU32 frameIndexOffset_02c;
    MovieU32 frameIndexEntryCount_030;
    MovieU32 frameStateAddress_034;
    MovieU32 quantTableAddress_038;
    MovieDecoderOverlay_03c overlay_03c;
    MovieU32 chromaSlotTableAddress_060;
    MovieU32 auxiliaryPlaneTableAddress_064;
    MovieU32 scaleLumaAddress_068;
    MovieU32 scaleChromaAddress_06c;
    MovieU32 scratchBufferAAddress_070;
    MovieU32 scratchBufferBAddress_074;
    MovieU32 chunkByteCount_078[2];
    MovieU32 chunkReadOffset_080[2];
    MovieU32 chunkDataOffset_088[2];
    MovieU32 readParity_090;
    MovieU32 frameIndexTableAddress_094;
    MovieU32 movieFrameIndex_098;
    MovieU32 consumedFrameCount_09c;
    MovieU32 decodedFrameCount_0a0;
    MovieU32 unknown_0a4;
    MovieU32 frameRingCapacity_0a8;
    MovieU32 frameLeadOffsets_0ac[6];
    MovieU32 frameRingCursor_0c4;
    MovieU32 chunkReadLimit_0c8;
    MovieU32 completedChunkCount_0cc;
    MovieU32 activeFrameSlot_0d0;
    MovieU32 streamBaseOffset_0d4;
} MovieDecodeContextObserved;

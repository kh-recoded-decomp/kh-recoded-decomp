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

typedef struct MovieDecodeContextObserved {
    MovieU8 unknown_000[0x10];
    MovieU32 frameWidth_010;
    MovieU32 frameHeight_014;
    MovieU8 unknown_018[0x04];
    MovieU16 chunkType_01c;
    MovieU16 chunkSlotCount_01e;
    MovieU8 unknown_020[0x14];
    MovieU32 streamCursorPointer_034;
    MovieU8 unknown_038[0x04];
    MovieU32 conversion_lumaSource_03c;
    MovieU32 conversion_chromaSource_040;
    MovieU32 conversion_outputBuffer_044;
    MovieU32 conversion_doubledSourceLine_048;
    MovieU8 unknown_04c[0x10];
    MovieU32 planeAddressTableA_05c;
    MovieU32 planeAddressTableB_060;
    MovieU32 planeAddressTableC_064;
    MovieU32 firstWorkingPlaneBuffer_068;
    MovieU32 secondWorkingPlaneBuffer_06c;
    MovieU8 unknown_070[0x28];
    MovieU32 unknown_098;
    MovieU32 consumedFrameCount_09c;
    MovieU32 decodedFrameCount_0a0;
    MovieU32 hasExtendedHeader_0a4;
    MovieU32 frameRingCapacity_0a8;
    MovieU32 unknown_0ac;
    MovieU8 unknown_0b0[0x14];
    MovieU32 frameRingCursor_0c4;
    MovieU32 chunkReadLimit_0c8;
    MovieU32 completedChunkCount_0cc;
    MovieU32 activeFrameSlot_0d0;
} MovieDecodeContextObserved;

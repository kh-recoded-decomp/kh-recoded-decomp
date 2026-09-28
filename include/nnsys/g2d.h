/* NitroSystem 2D graphics, as the library sources declare them (the NitroSDK / NitroSystem names). */
#ifndef NNSYS_G2D_H
#define NNSYS_G2D_H

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"
#include "nitro/gx.h"

struct NNSG2dAffineParamProxy;
struct NNSG2dAnimBankData;
struct NNSG2dAnimBankDataBlock;
struct NNSG2dAnimController;
struct NNSG2dAnimDataSRT;
struct NNSG2dAnimDataT;
struct NNSG2dAnimFrameData;
struct NNSG2dAnimSequenceData;
struct NNSG2dBinaryBlockHeader;
struct NNSG2dBinaryFileHeader;
struct NNSG2dCMapInfoScan;
struct NNSG2dCMapScanEntry;
struct NNSG2dCallBackFunctor;
struct NNSG2dCellAnimation;
struct NNSG2dCellBoundingRectS16;
struct NNSG2dCellData;
struct NNSG2dCellDataBank;
struct NNSG2dCellDataBankBlock;
struct NNSG2dCellDataWithBR;
struct NNSG2dCellOAMAttrData;
struct NNSG2dCellTransferState;
struct NNSG2dCellVramTransferData;
struct NNSG2dCharCanvas;
struct NNSG2dCharWidths;
struct NNSG2dCharacterData;
struct NNSG2dCharacterPosInfo;
struct NNSG2dFVec2;
struct NNSG2dFont;
struct NNSG2dFontCodeMap;
struct NNSG2dFontGlyph;
struct NNSG2dFontInformation;
struct NNSG2dFontWidth;
struct NNSG2dGlyph;
struct NNSG2dImageAttr;
struct NNSG2dImagePaletteProxy;
struct NNSG2dImageProxy;
struct NNSG2dOamChunk;
struct NNSG2dOamChunkList;
struct NNSG2dOamExEntryFunctions;
struct NNSG2dOamManagerInstanceEx;
struct NNSG2dPaletteCompressInfo;
struct NNSG2dPaletteData;
struct NNSG2dPaletteDataBlock;
struct NNSG2dSVec2;
struct NNSG2dScreenData;
struct NNSG2dScreenDataBlock;
struct NNSG2dTagCallbackInfo;
struct NNSG2dTextCanvas;
struct NNSG2dTextRect;
struct NNSG2dUserExAnimAttrBank;
struct NNSG2dUserExAnimFrameAttr;
struct NNSG2dUserExAnimSequenceAttr;
struct NNSG2dUserExCellAttr;
struct NNSG2dUserExCellAttrBank;
struct NNSG2dUserExDataBlock;
struct NNSG2dVRamLocation;
struct NNSG2dVramTransferData;
struct NNSiG2dBitReader;
struct NNSiG2dCharCanvasVTable;
struct NNSiG2dTextDirection;

typedef struct NNSG2dScreenData {
    u16 screenWidth;
    u16 screenHeight;
    u16 colorMode;
    u16 screenFormat;
    u32 szByte;
    u32 rawData[1];
} NNSG2dScreenData;

typedef enum NNSG2dBGExtPlttSlot {
    NNS_G2D_BGEXTPLTTSLOT_MAIN0,
    NNS_G2D_BGEXTPLTTSLOT_MAIN1,
    NNS_G2D_BGEXTPLTTSLOT_MAIN2,
    NNS_G2D_BGEXTPLTTSLOT_MAIN3,
    NNS_G2D_BGEXTPLTTSLOT_SUB0,
    NNS_G2D_BGEXTPLTTSLOT_SUB1,
    NNS_G2D_BGEXTPLTTSLOT_SUB2,
    NNS_G2D_BGEXTPLTTSLOT_SUB3
} NNSG2dBGExtPlttSlot;

typedef struct NNSG2dPaletteCompressInfo {
    u16 numPalette;
    u16 pad16;
    void *pPlttIdxTbl;
} NNSG2dPaletteCompressInfo;

typedef struct NNSG2dPaletteData {
    GXTexFmt fmt;
    BOOL bExtendedPlt;
    u32 szByte;
    void *pRawData;
} NNSG2dPaletteData;

typedef void (*NNSG2dAnmCallBackPtr)(u32 data, fx32 currentFrame);

#define NNS_G2D_INVALID_CELL_TRANSFER_STATE_HANDLE 0xffffffff

typedef enum NNSG2dAnimationElement {
    NNS_G2D_ANIMELEMENT_INDEX = 0,
    NNS_G2D_ANIMELEMENT_INDEX_SRT = 1,
    NNS_G2D_ANIMELEMENT_INDEX_T = 2
} NNSG2dAnimationElement;

typedef struct NNSG2dAnimDataSRT {
    u16 index;
    u16 rotZ;
    fx32 sx;
    fx32 sy;
    s16 px;
    s16 py;
} NNSG2dAnimDataSRT;

typedef struct NNSG2dAnimDataT {
    u16 index;
    u16 pad_;
    s16 px;
    s16 py;
} NNSG2dAnimDataT;

typedef struct NNSG2dCellVramTransferData {
    u32 srcDataOffset;
    u32 szByte;
} NNSG2dCellVramTransferData;

typedef struct NNSG2dVramTransferData {
    u32 szByteMax;
    NNSG2dCellVramTransferData *pCellTransferDataArray;
} NNSG2dVramTransferData;

typedef enum NNSG2dAnmCallbackType {
    NNS_G2D_ANMCALLBACKTYPE_NONE = 0,
    NNS_G2D_ANMCALLBACKTYPE_LAST_FRM,
    NNS_G2D_ANMCALLBACKTYPE_SPEC_FRM,
    NNS_G2D_ANMCALLBACKTYPE_EVER_FRM,
    AnmCallbackType_MAX
} NNSG2dAnmCallbackType;

typedef struct NNSG2dCallBackFunctor {
    NNSG2dAnmCallbackType type;
    u32 param;
    NNSG2dAnmCallBackPtr pFunc;
    u16 frameIdx;
    u16 pad16_;
} NNSG2dCallBackFunctor, NNSG2dAnimCallBackFunctor;

typedef struct NNSG2dAnimFrameData {
    void * pContent;
    u16 frames;
    u16 pad16;
} NNSG2dAnimFrameData;

typedef NNSG2dAnimFrameData NNSG2dAnimFrame;

typedef enum NNSG2dAnimationPlayMode {
    NNS_G2D_ANIMATIONPLAYMODE_INVALID = 0x0,
    NNS_G2D_ANIMATIONPLAYMODE_FORWARD,
    NNS_G2D_ANIMATIONPLAYMODE_FORWARD_LOOP,
    NNS_G2D_ANIMATIONPLAYMODE_REVERSE,
    NNS_G2D_ANIMATIONPLAYMODE_REVERSE_LOOP,
    NNS_G2D_ANIMATIONPLAYMODE_MAX
} NNSG2dAnimationPlayMode;

typedef struct NNSG2dAnimSequenceData {
    u16 numFrames;
    u16 loopStartFrameIdx;
    u32 animType;
    NNSG2dAnimationPlayMode playMode;
    NNSG2dAnimFrameData * pAnmFrameArray;
} NNSG2dAnimSequenceData;

typedef NNSG2dAnimSequenceData NNSG2dAnimSequence;

typedef struct NNSG2dAnimController {
    const NNSG2dAnimFrame * pCurrent;
    const NNSG2dAnimFrame * pActiveCurrent;
    BOOL bReverse;
    BOOL bActive;
    fx32 currentTime;
    fx32 speed;
    NNSG2dAnimationPlayMode overriddenPlayMode;
    const NNSG2dAnimSequence * pAnimSequence;
    NNSG2dAnimCallBackFunctor callbackFunctor;
} NNSG2dAnimController;

typedef struct NNSG2dCellOAMAttrData {
    u16 attr0;
    u16 attr1;
    u16 attr2;
} NNSG2dCellOAMAttrData;

typedef struct NNSG2dCellData {
    u16 numOAMAttrs;
    u16 cellAttr;
    NNSG2dCellOAMAttrData *pOamAttrArray;
} NNSG2dCellData;

typedef enum NNSG2dCharacterDataMappingType {
    NNS_G2D_CHARACTERMAPPING_1D_32,
    NNS_G2D_CHARACTERMAPPING_1D_64,
    NNS_G2D_CHARACTERMAPPING_1D_128,
    NNS_G2D_CHARACTERMAPPING_1D_256,
    NNS_G2D_CHARACTERMAPPING_2D,
    NNS_G2D_CHARACTERMAPPING_MAX
} NNSG2dCharacterDataMappingType;

typedef struct NNSG2dCellDataBank {
    u16 numCells;
    u16 cellBankAttr;
    NNSG2dCellData * pCellDataArrayHead;
    NNSG2dCharacterDataMappingType mappingMode;
    NNSG2dVramTransferData * pVramTransferData;
    void * pStringBank;
    void * pExtendedData;
} NNSG2dCellDataBank;

typedef enum {
    NNS_G2D_SRTCONTROLTYPE_INVALID,
    NNS_G2D_SRTCONTROLTYPE_SRT,
    NNS_G2D_SRTCONTROLTYPE_MTX2D,
    NNS_G2D_SRTCONTROLTYPE_MTX3D,
    NNS_G2D_SRTCONTROLTYPE_MAX
} NNSG2dSRTControlType;

typedef struct NNSG2dFVec2 {
    fx32 x;
    fx32 y;
} NNSG2dFVec2;

typedef struct NNSG2dSVec2 {
    s16 x;
    s16 y;
} NNSG2dSVec2;

typedef union {
    struct {
        NNSG2dFVec2 scale;
        NNSG2dSVec2 trans;
        u16 rotZ;
        u16 SRT_EnableFlag;
    };
    MtxFx32 mtx;
} NNSG2dSRTData;

typedef struct {
    NNSG2dSRTControlType type;
    NNSG2dSRTData srtData;
} NNSG2dSRTControl;

typedef struct NNSG2dCellAnimation {
    NNSG2dAnimController animCtrl;
    const NNSG2dCellData *pCurrentCell;
    const NNSG2dCellDataBank *pCellDataBank;
    u32 cellTransferStateHandle;
    NNSG2dSRTControl srtCtrl;
} NNSG2dCellAnimation;

typedef enum NNSG2dScreenFormat {
    NNS_G2D_SCREENFORMAT_TEXT,
    NNS_G2D_SCREENFORMAT_AFFINE,
    NNS_G2D_SCREENFORMAT_AFFINEEXT
} NNSG2dScreenFormat;

typedef enum NNSG2dScreenColorMode {
    NNS_G2D_SCREENCOLORMODE_16x16,
    NNS_G2D_SCREENCOLORMODE_256x1
} NNSG2dScreenColorMode;

typedef struct NNSG2dCharacterData NNSG2dCharacterData;

typedef struct NNSG2dPaletteData NNSG2dPaletteData;

typedef struct NNSG2dCharacterPosInfo NNSG2dCharacterPosInfo;

typedef struct NNSG2dPaletteCompressInfo NNSG2dPaletteCompressInfo;

typedef struct NNSG2dCharCanvas NNSG2dCharCanvas;

typedef struct NNSG2dCharWidths {
    s8 left;
    u8 glyphWidth;
    s8 charWidth;
} NNSG2dCharWidths;

typedef struct NNSG2dFontCodeMap {
    u16 ccodeBegin;
    u16 ccodeEnd;
    u16 mappingMethod;
    u16 reserved;
    struct NNSG2dFontCodeMap * pNext;
    u16 mapInfo[];
} NNSG2dFontCodeMap;

typedef struct NNSG2dFontGlyph {
    u8 cellWidth;
    u8 cellHeight;
    u16 cellSize;
    s8 baselinePos;
    u8 maxCharWidth;
    u8 bpp;
    u8 flags;
    u8 glyphTable[];
} NNSG2dFontGlyph;

typedef struct NNSG2dFontWidth {
    u16 indexBegin;
    u16 indexEnd;
    struct NNSG2dFontWidth * pNext;
    NNSG2dCharWidths widthTable[];
} NNSG2dFontWidth;

typedef struct NNSG2dFontInformation {
    u8 fontType;
    s8 linefeed;
    u16 alterCharIndex;
    NNSG2dCharWidths defaultWidth;
    u8 encoding;
    NNSG2dFontGlyph * pGlyph;
    NNSG2dFontWidth * pWidth;
    NNSG2dFontCodeMap * pMap;
} NNSG2dFontInformation;

typedef u16 (*NNSiG2dSplitCharCallback)(const void ** ppChar);

typedef struct NNSG2dFont {
    NNSG2dFontInformation *pRes;
    NNSiG2dSplitCharCallback cbCharSpliter;
} NNSG2dFont;

typedef struct NNSG2dTextCanvas {
    NNSG2dCharCanvas *pCanvas;
    NNSG2dFont *pFont;
    int hSpace;
    int vSpace;
} NNSG2dTextCanvas;

typedef struct NNSG2dTagCallbackInfo {
    NNSG2dTextCanvas txn;
    const void *str;
    int x;
    int y;
    int clr;
    void *cbParam;
} NNSG2dTagCallbackInfo;

typedef void (*NNSG2dTagCallback)(u16 c, NNSG2dTagCallbackInfo *cbInfo);

typedef struct NNSiG2dTextDirection {
    s8 x;
    s8 y;
} NNSiG2dTextDirection;

#define NNS_G2D_BINFILE_SIG_FONTDATA 0x4e465452

#define NNS_G2D_NFTR_VER 0x0101

#define NNS_G2D_NFTR_PREV_VER 0x0100

#define NNS_G2D_BINBLK_SIG_FINFDATA 0x46494e46

typedef struct NNSG2dBinaryFileHeader {
    u32 signature;
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 dataBlocks;
} NNSG2dBinaryFileHeader;

typedef struct NNSG2dBinaryBlockHeader {
    u32 kind;
    u32 size;
} NNSG2dBinaryBlockHeader;

#define NNS_G2D_GLYPH_INDEX_NOT_FOUND 0xFFFF

typedef enum NNSG2dFontMappingMethod {
    NNS_G2D_MAPMETHOD_DIRECT,
    NNS_G2D_MAPMETHOD_TABLE,
    NNS_G2D_MAPMETHOD_SCAN,
    NNS_G2D_NUM_OF_MAPMETHOD
} NNSG2dFontMappingMethod;

typedef struct NNSG2dCMapScanEntry {
    u16 ccode;
    u16 index;
} NNSG2dCMapScanEntry;

typedef struct NNSG2dCMapInfoScan {
    u16 num;
    NNSG2dCMapScanEntry entries[];
} NNSG2dCMapInfoScan;

typedef struct NNSG2dCellBoundingRectS16 {
    s16 maxX;
    s16 maxY;
    s16 minX;
    s16 minY;
} NNSG2dCellBoundingRectS16;

typedef struct NNSG2dCellDataWithBR {
    NNSG2dCellData cellData;
    NNSG2dCellBoundingRectS16 boundingRect;
} NNSG2dCellDataWithBR;

typedef struct NNSG2dGlyph {
    const NNSG2dCharWidths * pWidths;
    const u8 * image;
} NNSG2dGlyph;

typedef enum NNSG2dCharaColorMode {
    NNS_G2D_CHARA_COLORMODE_16  = 4,
    NNS_G2D_CHARA_COLORMODE_256 = 8
} NNSG2dCharaColorMode;

typedef void (*NNSiG2dDrawGlyphFunc)(const struct NNSG2dCharCanvas * pCC, const NNSG2dFont * pFont, int x, int y, int cl, const NNSG2dGlyph * pGlyph);

typedef void (*NNSiG2dClearFunc)(const struct NNSG2dCharCanvas * pCC, int cl);

typedef void (*NNSiG2dClearAreaFunc)(const struct NNSG2dCharCanvas * pCC, int cl, int x, int y, int w, int h);

typedef struct NNSiG2dCharCanvasVTable {
    NNSiG2dDrawGlyphFunc pDrawGlyph;
    NNSiG2dClearFunc pClear;
    NNSiG2dClearAreaFunc pClearArea;
} NNSiG2dCharCanvasVTable;

typedef struct NNSG2dCharCanvas {
    u8 * charBase;
    int areaWidth;
    int areaHeight;
    u8 dstBpp;
    u8 reserved[3];
    u32 param;
    const NNSiG2dCharCanvasVTable * vtable;
} NNSG2dCharCanvas;

typedef enum NNSG2dOamExDrawOrder {
    NNSG2D_OAMEX_DRAWORDER_BACKWARD = 0x0,
    NNSG2D_OAMEX_DRAWORDER_FORWARD  = 0x1
} NNSG2dOamExDrawOrder;

typedef u16 (*NNSG2dGetOamCpacityFuncPtr)();

typedef BOOL (*NNSG2dEntryNewOamFuncPtr)(const GXOamAttr * pOam, u16 index);

typedef u16 (*NNSG2dEntryNewOamAffineFuncPtr)(const MtxFx22 * mtx, u16 index);

typedef struct NNSG2dOamExEntryFunctions {
    NNSG2dGetOamCpacityFuncPtr getOamCapacity;
    NNSG2dGetOamCpacityFuncPtr getAffineCapacity;
    NNSG2dEntryNewOamFuncPtr entryNewOam;
    NNSG2dEntryNewOamAffineFuncPtr entryNewAffine;
} NNSG2dOamExEntryFunctions;

typedef struct NNSG2dOamChunk {
    GXOamAttr oam;
    u16 affineProxyIdx;
    u16 pad16_;
    struct NNSG2dOamChunk * pNext;
} NNSG2dOamChunk;

typedef struct NNSG2dOamChunkList {
    u16 numChunks;
    u16 numLastFrameDrawn;
    u16 numDrawn;
    u16 bDrawn;
    NNSG2dOamChunk * pChunks;
    NNSG2dOamChunk * pAffinedChunks;
    NNSG2dOamChunk * pLastChunk;
    NNSG2dOamChunk * pLastAffinedChunk;
} NNSG2dOamChunkList;

typedef struct NNSG2dAffineParamProxy {
    MtxFx22 mtxAffine;
    u16 affineHWIndex;
    u16 pad16_;
} NNSG2dAffineParamProxy;

typedef struct NNSG2dOamManagerInstanceEx {
    NNSG2dOamChunkList * pOamOrderingTbl;
    u16 numPooledOam;
    u16 numUsedOam;
    NNSG2dOamChunk * pPoolOamChunks;
    u16 lengthOfOrderingTbl;
    u16 lengthAffineBuffer;
    u16 numAffineBufferUsed;
    u16 lastFrameAffineIdx;
    NNSG2dAffineParamProxy * pAffineBuffer;
    NNSG2dOamExEntryFunctions oamEntryFuncs;
    u16 lastRenderedOrderingTblIdx;
    u16 lastRenderedChunkIdx;
    NNSG2dOamExDrawOrder drawOrderType;
} NNSG2dOamManagerInstanceEx;

typedef struct NNSG2dAnimBankData {
    u16 numSequences;
    u16 numTotalFrames;
    NNSG2dAnimSequenceData * pSequenceArrayHead;
    NNSG2dAnimFrameData * pFrameArrayHead;
    void * pAnimContents;
    void * pStringBank;
    void * pExtendedData;
} NNSG2dAnimBankData;

typedef enum NNS_G2D_VRAM_TYPE {
    NNS_G2D_VRAM_TYPE_3DMAIN = 0,
    NNS_G2D_VRAM_TYPE_2DMAIN = 1,
    NNS_G2D_VRAM_TYPE_2DSUB  = 2,
    NNS_G2D_VRAM_TYPE_2DBOTH = 3,
    NNS_G2D_VRAM_TYPE_MAX    = 3
} NNS_G2D_VRAM_TYPE;

typedef struct NNSG2dVRamLocation {
    u32 baseAddrOfVram[NNS_G2D_VRAM_TYPE_MAX];
} NNSG2dVRamLocation;

typedef struct NNSG2dImagePaletteProxy {
    GXTexFmt fmt;
    BOOL bExtendedPlt;
    NNSG2dVRamLocation vramLocation;
} NNSG2dImagePaletteProxy;

typedef struct NNSG2dImageAttr {
    GXTexSizeS sizeS;
    GXTexSizeT sizeT;
    GXTexFmt fmt;
    BOOL bExtendedPlt;
    GXTexPlttColor0 plttUse;
    GXOBJVRamModeChar mappingType;
} NNSG2dImageAttr;

typedef struct NNSG2dImageProxy {
    NNSG2dVRamLocation vramLocation;
    NNSG2dImageAttr attr;
} NNSG2dImageProxy;

typedef enum NNSG2d256x16PlttBGWidth {
    NNS_G2D_256x16PLTT_BG_WIDTH_128  = 16,
    NNS_G2D_256x16PLTT_BG_WIDTH_256  = 32,
    NNS_G2D_256x16PLTT_BG_WIDTH_512  = 64,
    NNS_G2D_256x16PLTT_BG_WIDTH_1024 = 128
} NNSG2d256x16PlttBGWidth;

#define NNS_G2D_UNPACK_OFFSET_PTR(ptr, baseOffs) (ptr) = (void *)((u32)(ptr) + (u32)baseOffs)

typedef struct NNSG2dUserExDataBlock {
    u32 blkTypeID;
    u32 blkSize;
} NNSG2dUserExDataBlock;

typedef struct NNSG2dUserExAnimFrameAttr {
    u32 * pAttr;
} NNSG2dUserExAnimFrameAttr;

typedef struct NNSG2dUserExAnimSequenceAttr {
    u16 numFrames;
    u16 pad16;
    u32 * pAttr;
    NNSG2dUserExAnimFrameAttr * pAnmFrmAttrArray;
} NNSG2dUserExAnimSequenceAttr;

typedef struct NNSG2dUserExAnimAttrBank {
    u16 numSequences;
    u16 numAttribute;
    NNSG2dUserExAnimSequenceAttr * pAnmSeqAttrArray;
} NNSG2dUserExAnimAttrBank;

typedef enum NNSG2dAffineEnable {
    NNS_G2D_AFFINEENABLE_NONE   = 0x00,
    NNS_G2D_AFFINEENABLE_SCALE  = 0x02,
    NNS_G2D_AFFINEENABLE_ROTATE = 0x04,
    NNS_G2D_AFFINEENABLE_TRANS  = 0x08,
    NNS_G2D_AFFINEENABLE_MAX    = 0x10
} NNSG2dAffineEnable;

typedef struct NNSG2dUserExCellAttr {
    u32 * pAttr;
} NNSG2dUserExCellAttr;

typedef struct NNSG2dUserExCellAttrBank {
    u16 numCells;
    u16 numAttribute;
    NNSG2dUserExCellAttr * pCellAttrArray;
} NNSG2dUserExCellAttrBank;

typedef enum NNSG2dBGSelect {
    NNS_G2D_BGSELECT_MAIN0,
    NNS_G2D_BGSELECT_MAIN1,
    NNS_G2D_BGSELECT_MAIN2,
    NNS_G2D_BGSELECT_MAIN3,
    NNS_G2D_BGSELECT_SUB0,
    NNS_G2D_BGSELECT_SUB1,
    NNS_G2D_BGSELECT_SUB2,
    NNS_G2D_BGSELECT_SUB3,
    NNS_G2D_BGSELECT_NUM
} NNSG2dBGSelect;

#define NNS_G2D_BLKSIG_ANIMBANK (u32)'ABNK'

typedef struct NNSG2dAnimBankDataBlock {
    NNSG2dBinaryBlockHeader blockHeader;
    NNSG2dAnimBankData animBankData;
} NNSG2dAnimBankDataBlock;

typedef struct NNSiG2dBitReader {
    const u8 * src;
    s8 availableBits;
    u8 bits;
    u8 padding_[2];
} NNSiG2dBitReader;

typedef struct NNSG2dCharacterData {
    u16 H;
    u16 W;
    GXTexFmt pixelFmt;
    GXOBJVRamModeChar mappingType;
    u32 characterFmt;
    u32 szByte;
    void * pRawData;
} NNSG2dCharacterData;

typedef struct NNSG2dCharacterPosInfo {
    u16 srcPosX;
    u16 srcPosY;
    u16 srcW;
    u16 srcH;
} NNSG2dCharacterPosInfo;

#define NNS_G2D_BLKSIG_CELLBANK (u32)'CEBK'

typedef struct NNSG2dCellDataBankBlock {
    NNSG2dBinaryBlockHeader blockHeader;
    NNSG2dCellDataBank cellDataBank;
} NNSG2dCellDataBankBlock;

#define NNS_G2D_BINBLK_SIG_PALETTEDATA (u32)'PLTT'

typedef struct NNSG2dPaletteDataBlock {
    NNSG2dBinaryBlockHeader blockHeader;
    NNSG2dPaletteData paletteData;
} NNSG2dPaletteDataBlock;

#define NNS_G2D_BINBLK_SIG_SCRDATA (u32)'SCRN'

typedef struct NNSG2dScreenDataBlock {
    NNSG2dBinaryBlockHeader blockHeader;
    NNSG2dScreenData screenData;
} NNSG2dScreenDataBlock;

typedef enum NNSG2dCharacterFmt {
    NNS_G2D_CHARACTER_FMT_CHAR,
    NNS_G2D_CHARACTER_FMT_BMP,
    NNS_G2D_CHARACTER_FMT_MAX
} NNSG2dCharacterFmt;

typedef struct NNSG2dCellTransferState {
    NNSG2dVRamLocation dstVramLocation;
    u32 szDst;
    const void * pSrcNCGR;
    const void * pSrcNCBR;
    u32 szSrcData;
    BOOL bActive;
    u32 bDrawn;
    u32 bTransferRequested;
    u32 srcOffset;
    u32 szByte;
} NNSG2dCellTransferState;

typedef struct NNSG2dTextRect {
    int width;
    int height;
} NNSG2dTextRect;

#endif

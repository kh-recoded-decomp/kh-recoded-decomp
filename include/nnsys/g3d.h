/* NitroSystem 3D graphics, as the library sources declare them (the NitroSDK / NitroSystem names). */
#ifndef NNSYS_G3D_H
#define NNSYS_G3D_H

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"
#include "nnsys/gfd.h"

struct NNSG3dAnmObj;
struct NNSG3dAnmObjInitFunc;
struct NNSG3dAnmObj_;
struct NNSG3dGeBuffer;
struct NNSG3dGeCommandBuffer;
struct NNSG3dGlb;
struct NNSG3dGlbMaterial;
struct NNSG3dJntAnmResult_;
struct NNSG3dJointScale;
struct NNSG3dMatAnmResult_;
struct NNSG3dNodeMixCacheEntry;
struct NNSG3dNodeMixResult;
struct NNSG3dProjectionBuilderTable;
struct NNSG3dProjectionPacket;
struct NNSG3dProjectionState;
struct NNSG3dRSOnGlobal;
struct NNSG3dRS_;
struct NNSG3dRenderObj_;
struct NNSG3dRenderState;
struct NNSG3dResAnmHeader_;
struct NNSG3dResDataBlockHeader_;
struct NNSG3dResDictEntryHeader_;
struct NNSG3dResDictMatCAnmData_;
struct NNSG3dResDictMatData_;
struct NNSG3dResDictMdlSetData_;
struct NNSG3dResDictNodeData;
struct NNSG3dResDictPlttData_;
struct NNSG3dResDictPlttToMatIdxData_;
struct NNSG3dResDictShpData;
struct NNSG3dResDictTexData_;
struct NNSG3dResDictTexPatAnmData_;
struct NNSG3dResDictTexSRTAnmData_;
struct NNSG3dResDictTexToMatIdxData_;
struct NNSG3dResDictTreeNode_;
struct NNSG3dResDict_;
struct NNSG3dResEvpMtx;
struct NNSG3dResFileHeader_;
struct NNSG3dResJntAnm;
struct NNSG3dResJntAnmSRTTag_;
struct NNSG3dResMatCAnm_;
struct NNSG3dResMatData_;
struct NNSG3dResMat_;
struct NNSG3dResMdlInfo_;
struct NNSG3dResMdlSet_;
struct NNSG3dResMdl_;
union NNSG3dResName_;
struct NNSG3dResNodeData;
struct NNSG3dResNodeInfo_;
struct NNSG3dResPlttInfo_;
struct NNSG3dResShpData;
struct NNSG3dResShp_;
struct NNSG3dResTex4x4Info_;
struct NNSG3dResTexInfo_;
struct NNSG3dResTexPatAnmFV_;
struct NNSG3dResTexPatAnm_;
struct NNSG3dResTexSRTAnm_;
struct NNSG3dResTex_;
struct NNSG3dResVisAnm_;
struct NNSG3dSbcNodeDesc;
struct NNSG3dSbcNodeMix;
struct NNSG3dSbcNodeMixEntry;
struct NNSG3dVisAnmResult_;

typedef struct NNSG3dResJntAnm NNSG3dResJntAnm;

typedef struct NNSG3dGeBuffer {
    u32 idx;
    u32 data[192];
} NNSG3dGeBuffer;

typedef struct NNSG3dResDictShpData { u32 offset; } NNSG3dResDictShpData;

typedef struct NNSG3dResShpData {
    u16 itemTag, size;
    u8 pad04[4];
    u32 ofsDL, sizeDL;
} NNSG3dResShpData;

typedef enum {
    NNS_G3D_MATANM_RESULTFLAG_TEXMTX_SCALEONE  = 0x00000001,
    NNS_G3D_MATANM_RESULTFLAG_TEXMTX_ROTZERO   = 0x00000002,
    NNS_G3D_MATANM_RESULTFLAG_TEXMTX_TRANSZERO = 0x00000004,
    NNS_G3D_MATANM_RESULTFLAG_TEXMTX_SET       = 0x00000008,
    NNS_G3D_MATANM_RESULTFLAG_TEXMTX_MULT      = 0x00000010,
    NNS_G3D_MATANM_RESULTFLAG_WIREFRAME        = 0x00000020}
NNSG3dMatAnmResultFlag;

typedef struct NNSG3dMatAnmResult_ {
    NNSG3dMatAnmResultFlag flag;
    u32 prmMatColor0;
    u32 prmMatColor1;
    u32 prmPolygonAttr;
    u32 prmTexImage;
    u32 prmTexPltt;
    fx32 scaleS, scaleT;
    fx16 sinR, cosR;
    fx32 transS, transT;
    u16 origWidth, origHeight;
    fx32 magW, magH;
} NNSG3dMatAnmResult;

typedef void (*NNSG3dFuncMatSend)(NNSG3dMatAnmResult *result);

typedef struct NNSG3dResDataBlockHeader_ {
    union {
        u32 kind;
        char chr[4];
    };
    u32 size;
} NNSG3dResDataBlockHeader;

typedef struct NNSG3dResDictTreeNode_ {
    u8 refBit;
    u8 idxLeft;
    u8 idxRight;
    u8 idxEntry;
} NNSG3dResDictTreeNode;

typedef struct NNSG3dResDict_ {
    u8 revision;
    u8 numEntry;
    u16 sizeDictBlk;
    u16 dummy_;
    u16 ofsEntry;
    NNSG3dResDictTreeNode node[1];
} NNSG3dResDict;

typedef struct NNSG3dResPlttInfo_ {
    NNSGfdTexKey vramKey;
    u16 sizePltt;
    u16 flag;
    u16 ofsDict;
    u16 dummy_;
    u32 ofsPlttData;
} NNSG3dResPlttInfo;

typedef struct NNSG3dResTex4x4Info_ {
    NNSGfdTexKey vramKey;
    u16 sizeTex;
    u16 ofsDict;
    u16 flag;
    u16 dummy_;
    u32 ofsTex;
    u32 ofsTexPlttIdx;
} NNSG3dResTex4x4Info;

typedef struct NNSG3dResTexInfo_ {
    NNSGfdTexKey vramKey;
    u16 sizeTex;
    u16 ofsDict;
    u16 flag;
    u16 dummy_;
    u32 ofsTex;
} NNSG3dResTexInfo;

typedef struct NNSG3dResTex_ {
    NNSG3dResDataBlockHeader header;
    NNSG3dResTexInfo texInfo;
    NNSG3dResTex4x4Info tex4x4Info;
    NNSG3dResPlttInfo plttInfo;
    NNSG3dResDict dict;
} NNSG3dResTex;

typedef struct NNSG3dAnmObj_ {
    fx32 frame;
    fx32 ratio;
    void * resAnm;
    void * funcAnm;
    struct NNSG3dAnmObj_ * next;
    const NNSG3dResTex * resTex;
    u8 priority;
    u8 numMapData;
    u16 mapData[1];
} NNSG3dAnmObj;

typedef BOOL (*NNSG3dFuncAnmBlendJnt)(struct NNSG3dJntAnmResult_ *, const NNSG3dAnmObj *, u32);

typedef BOOL (*NNSG3dFuncAnmBlendMat)(struct NNSG3dMatAnmResult_ *, const NNSG3dAnmObj *, u32);

typedef BOOL (*NNSG3dFuncAnmBlendVis)(struct NNSG3dVisAnmResult_ *, const NNSG3dAnmObj *, u32);

typedef struct NNSG3dResMdlInfo_ {
    u8 sbcType;
    u8 scalingRule;
    u8 texMtxMode;
    u8 numNode;
    u8 numMat;
    u8 numShp;
    u8 firstUnusedMtxStackID;
    u8 dummy_;
    fx32 posScale;
    fx32 invPosScale;
    u16 numVertex;
    u16 numPolygon;
    u16 numTriangle;
    u16 numQuad;
    fx16 boxX, boxY, boxZ;
    fx16 boxW, boxH, boxD;
    fx32 boxPosScale;
    fx32 boxInvPosScale;
} NNSG3dResMdlInfo;

typedef struct NNSG3dResNodeInfo_ {
    NNSG3dResDict dict;
} NNSG3dResNodeInfo;

typedef struct NNSG3dResMdl_ {
    u32 size;
    u32 ofsSbc;
    u32 ofsMat;
    u32 ofsShp;
    u32 ofsEvpMtx;
    NNSG3dResMdlInfo info;
    NNSG3dResNodeInfo nodeInfo;
} NNSG3dResMdl;

typedef void (*NNSG3dSbcCallBackFunc)(struct NNSG3dRS_ *);

typedef struct NNSG3dRenderObj_ {
    u32 flag;
    NNSG3dResMdl * resMdl;
    NNSG3dAnmObj * anmMat;
    NNSG3dFuncAnmBlendMat funcBlendMat;
    NNSG3dAnmObj * anmJnt;
    NNSG3dFuncAnmBlendJnt funcBlendJnt;
    NNSG3dAnmObj * anmVis;
    NNSG3dFuncAnmBlendVis funcBlendVis;
    NNSG3dSbcCallBackFunc cbFunc;
    u8 cbCmd;
    u8 cbTiming;
    u16 dummy_;
    NNSG3dSbcCallBackFunc cbInitFunc;
    void * ptrUser;
    u8 * ptrUserSbc;
    struct NNSG3dJntAnmResult_ * recJntAnm;
    struct NNSG3dMatAnmResult_ * recMatAnm;
    u32 hintMatAnmExist[64 / 32];
    u32 hintJntAnmExist[64 / 32];
    u32 hintVisAnmExist[64 / 32];
} NNSG3dRenderObj;

typedef struct NNSG3dResMat_ {
    u16 ofsDictTexToMatList;
    u16 ofsDictPlttToMatList;
    NNSG3dResDict dict;
} NNSG3dResMat;

typedef struct NNSG3dRenderState {
    u8 *pSbc;
    NNSG3dRenderObj *pRenderObj;
    u32 flags;
    u8 pad00c_0ac[0xa0];
    u8 commandAc;
    u8 materialAd;
    u8 pad0ae_0b0[2];
    NNSG3dMatAnmResult *currentMat;
    u8 pad0b4_0bc[8];
    u32 matDone[4];
    u8 pad0cc_0d8[0x0c];
    NNSG3dResMat *pResMat;
    u8 pad0dc_0f0[0x14];
    NNSG3dFuncMatSend sendMat;
    NNSG3dMatAnmResult matBuffer;
} NNSG3dRenderState;

typedef struct NNSG3dGlbMaterial {
    u8 pad00_80[0x80];
    u32 prmMatColor0;
    u32 prmMatColor1;
    u32 prmPolygonAttr;
} NNSG3dGlbMaterial;

typedef struct NNSG3dRSOnGlobal {
    NNSG3dMatAnmResult matCache[1];
} NNSG3dRSOnGlobal;

typedef struct NNSG3dResDictNodeData { u32 offset; } NNSG3dResDictNodeData;

typedef struct NNSG3dResNodeData { u16 flag; s16 rot00; } NNSG3dResNodeData;

typedef void (*NNSG3dSbcCallback)(struct NNSG3dRenderState *);

typedef enum {
    NNS_G3D_JNTANM_RESULTFLAG_SCALE_ONE    = 0x00000001,
    NNS_G3D_JNTANM_RESULTFLAG_ROT_ZERO     = 0x00000002,
    NNS_G3D_JNTANM_RESULTFLAG_TRANS_ZERO   = 0x00000004,
    NNS_G3D_JNTANM_RESULTFLAG_SCALEEX0_ONE = 0x00000008,
    NNS_G3D_JNTANM_RESULTFLAG_SCALEEX1_ONE = 0x00000010,
    NNS_G3D_JNTANM_RESULTFLAG_MAYA_SSC     = 0x00000020
} NNSG3dJntAnmResultFlag;

typedef struct NNSG3dJntAnmResult_ {
    NNSG3dJntAnmResultFlag flag;
    VecFx32 scale;
    VecFx32 scaleEx0;
    VecFx32 scaleEx1;
    MtxFx33 rot;
    VecFx32 trans;
} NNSG3dJntAnmResult;

typedef void (*NNSG3dFuncJntScale)(NNSG3dJntAnmResult *, const fx32 *, const u8 *, u32);

typedef void (*NNSG3dFuncJntSend)(NNSG3dJntAnmResult *);

typedef struct NNSG3dResEvpMtx {
    MtxFx43 invPosition;
    MtxFx33 invVector;
} NNSG3dResEvpMtx;

typedef struct NNSG3dNodeMixCacheEntry {
    MtxFx44 clip;
    MtxFx33 vector;
} NNSG3dNodeMixCacheEntry;

typedef struct NNSG3dNodeMixResult {
    MtxFx43 position;
    MtxFx33 vector;
} NNSG3dNodeMixResult;

typedef struct NNSG3dSbcNodeMixEntry {
    u8 matrixIndex, nodeId, weight;
} NNSG3dSbcNodeMixEntry;

typedef struct NNSG3dSbcNodeMix {
    u8 opcode, destinationIndex, numEntries;
    NNSG3dSbcNodeMixEntry entries[1];
} NNSG3dSbcNodeMix;

typedef struct NNSG3dGeCommandBuffer {
    u32 count;
    u32 words[0xc0];
} NNSG3dGeCommandBuffer;

typedef struct NNSG3dProjectionState {
    u32 flags;
    unsigned char pad004[0x2c];
    fx32 scaleX;
    fx32 scaleY;
} NNSG3dProjectionState;

typedef struct NNSG3dProjectionPacket {
    u32 command;
    u32 projectionMode;
    MtxFx44 matrix;
    u32 positionVectorMode;
} NNSG3dProjectionPacket;

typedef void (*NNSG3dProjectionBuilder)(MtxFx44 *matrix,
                                        const NNSG3dProjectionState *state);

typedef struct NNSG3dProjectionBuilderTable {
    NNSG3dProjectionBuilder entries[8];
} NNSG3dProjectionBuilderTable;

typedef struct NNSG3dJointScale {
    VecFx32 scale;
    VecFx32 inverseScale;
} NNSG3dJointScale;

typedef struct NNSG3dSbcNodeDesc {
    u8 opcode;
    u8 nodeId;
    u8 parentId;
    u8 flags;
} NNSG3dSbcNodeDesc;

typedef struct NNSG3dResAnmHeader_ {
    u8 category0;
    u8 revision;
    u16 category1;
} NNSG3dResAnmHeader;

typedef struct NNSG3dResJntAnm {
    NNSG3dResAnmHeader anmHeader;
    u16 numFrame;
    u16 numNode;
    u32 flag;
    u32 ofsRot3;
    u32 ofsRot5;
} NNSG3dResJntAnm;

typedef void (*NNSG3dRenderInitCallback)(struct NNSG3dRenderState *);

typedef void (*NNSG3dSbcHandler)(struct NNSG3dRenderState *, u32);

typedef void (*NNSG3dFuncAnmJnt)(NNSG3dJntAnmResult *, const struct NNSG3dAnmObj *, u32);

typedef enum {
    NNS_G3D_MATCANM_ELEM_CONST                 = 0x20000000,
    NNS_G3D_MATCANM_ELEM_STEP_1                = 0x00000000,
    NNS_G3D_MATCANM_ELEM_STEP_2                = 0x40000000,
    NNS_G3D_MATCANM_ELEM_STEP_4                = 0x80000000,
    NNS_G3D_MATCANM_ELEM_STEP_MASK             = 0xc0000000,
    NNS_G3D_MATCANM_ELEM_LAST_INTERP_MASK      = 0x1fff0000,
    NNS_G3D_MATCANM_ELEM_OFFSET_CONSTANT_MASK  = 0x0000ffff,
    NNS_G3D_MATCANM_ELEM_OFFSET_CONSTANT_SHIFT = 0,
    NNS_G3D_MATCANM_ELEM_LAST_INTERP_SHIFT     = 16
} NNSG3dMatCElem;

typedef struct NNSG3dResMatCAnm_ {
    NNSG3dResAnmHeader anmHeader;
    u16 numFrame;
    u16 flag;
    NNSG3dResDict dict;
} NNSG3dResMatCAnm;

typedef enum {
    NNS_G3D_TEXSRTANM_ELEM_FX16              = 0x10000000,
    NNS_G3D_TEXSRTANM_ELEM_CONST             = 0x20000000,
    NNS_G3D_TEXSRTANM_ELEM_STEP_1            = 0x00000000,
    NNS_G3D_TEXSRTANM_ELEM_STEP_2            = 0x40000000,
    NNS_G3D_TEXSRTANM_ELEM_STEP_4            = 0x80000000,
    NNS_G3D_TEXSRTANM_ELEM_STEP_MASK         = 0xc0000000,
    NNS_G3D_TEXSRTANM_ELEM_LAST_INTERP_MASK  = 0x0000ffff,
    NNS_G3D_TEXSRTANM_ELEM_LAST_INTERP_SHIFT = 0
} NNSG3dTexSRTElem;

typedef struct NNSG3dResTexSRTAnm_ {
    NNSG3dResAnmHeader anmHeader;
    u16 numFrame;
    u8 flag;
    u8 texMtxMode;
    NNSG3dResDict dict;
} NNSG3dResTexSRTAnm;

typedef struct NNSG3dResFileHeader_ {
    union {
        char signature[4];
        u32 sigVal;
    };
    u16 byteOrder;
    u16 version;
    u32 fileSize;
    u16 headerSize;
    u16 dataBlocks;
} NNSG3dResFileHeader;

typedef struct NNSG3dResDictEntryHeader_ {
    u16 sizeUnit;
    u16 ofsName;
    u8 data[4];
} NNSG3dResDictEntryHeader;

typedef struct {
    u32 offset;
} NNSG3dResDictAnmSetData;

typedef struct {
    NNSG3dResDataBlockHeader header;
    NNSG3dResDict dict;
} NNSG3dResAnmSet;

typedef struct NNSG3dResMdlSet_ {
    NNSG3dResDataBlockHeader header;
    NNSG3dResDict dict;
} NNSG3dResMdlSet;

typedef union NNSG3dResName_ {
    char name[(16) ];
    u32 val[((16) / sizeof(u32)) ];
} NNSG3dResName;

#define NNS_G3D_SIGNATURE_NSBTX '0XTB'

typedef u16 NNSG3dItemTag;

typedef struct NNSG3dResDictMatData_ {
    u32 offset;
} NNSG3dResDictMatData;

typedef struct NNSG3dResMatData_ {
    NNSG3dItemTag itemTag;
    u16 size;
    u32 diffAmb;
    u32 specEmi;
    u32 polyAttr;
    u32 polyAttrMask;
    u32 texImageParam;
    u32 texImageParamMask;
    u16 texPlttBase;
    u16 flag;
    u16 origWidth, origHeight;
    fx32 magW;
    fx32 magH;
} NNSG3dResMatData;

typedef enum {
    NNS_G3D_RESPLTT_LOADED   = 0x0001,
    NNS_G3D_RESPLTT_USEPLTT4 = 0x8000
} NNSG3dResPlttFlag;

typedef u32 NNSG3dPlttKey;

typedef struct NNSG3dResDictPlttToMatIdxData_ {
    u16 offset;
    u8 numIdx;
    u8 flag;
} NNSG3dResDictPlttToMatIdxData;

typedef struct NNSG3dVisAnmResult_ {
    BOOL isVisible;
} NNSG3dVisAnmResult;

typedef enum {
    NNS_G3D_SBC_CALLBACK_TIMING_NONE = 0x00,
    NNS_G3D_SBC_CALLBACK_TIMING_A    = 0x01,
    NNS_G3D_SBC_CALLBACK_TIMING_B    = 0x02,
    NNS_G3D_SBC_CALLBACK_TIMING_C    = 0x03
} NNSG3dSbcCallBackTiming;

typedef enum {
    NNS_G3D_RESTEX_LOADED = 0x0001
} NNSG3dResTexFlag;

typedef enum {
    NNS_G3D_RESTEX4x4_LOADED = 0x0001
} NNSG3dResTex4x4Flag;

typedef u32 NNSG3dTexKey;

typedef enum {
    NNS_G3D_ANMOBJ_MAPDATA_EXIST     = 0x0100,
    NNS_G3D_ANMOBJ_MAPDATA_DISABLED  = 0x0200,
    NNS_G3D_ANMOBJ_MAPDATA_DATAFIELD = 0x00ff
} NNSG3dAnmObjMapData;

typedef void (*NNSG3dFuncAnmMat)(NNSG3dMatAnmResult *, const NNSG3dAnmObj *, u32);

typedef void (*NNSG3dFuncAnmVis)(NNSG3dVisAnmResult *, const NNSG3dAnmObj *, u32);

typedef struct NNSG3dResVisAnm_ {
    NNSG3dResAnmHeader anmHeader;
    u16 numFrame;
    u16 numNode;
    u16 size;
    u16 dummy_;
    u32 visData[1];
} NNSG3dResVisAnm;

typedef struct NNSG3dResDictTexPatAnmData_ {
    u16 numFV;
    u16 flag;
    fx16 ratioDataFrame;
    u16 offset;
} NNSG3dResDictTexPatAnmData;

typedef struct NNSG3dResTexPatAnm_ {
    NNSG3dResAnmHeader anmHeader;
    u16 numFrame;
    u8 numTex;
    u8 numPltt;
    u16 ofsTexName;
    u16 ofsPlttName;
    NNSG3dResDict dict;
} NNSG3dResTexPatAnm;

#define NNS_G3D_SBC_NOP 0x00

typedef struct NNSG3dResShp_ {
    NNSG3dResDict dict;
} NNSG3dResShp;

typedef void (*NNSG3dGetJointScale)(NNSG3dJntAnmResult * pResult, const fx32 * p, const u8 * cmd, u32 srtflag);

typedef void (*NNSG3dSendJointSRT)(const NNSG3dJntAnmResult *);

typedef void (*NNSG3dSendTexSRT)(const NNSG3dMatAnmResult *);

typedef struct NNSG3dRS_ {
    u8 * c;
    NNSG3dRenderObj * pRenderObj;
    u32 flag;
    NNSG3dSbcCallBackFunc cbVecFunc[0x20 ];
    u8 cbVecTiming[0x20 ];
    u8 currentNode;
    u8 currentMat;
    u8 currentNodeDesc;
    u8 dummy_;
    NNSG3dMatAnmResult * pMatAnmResult;
    NNSG3dJntAnmResult * pJntAnmResult;
    NNSG3dVisAnmResult * pVisAnmResult;
    u32 isMatCached[64 / 32];
    u32 isScaleCacheOne[64 / 32];
    u32 isEvpCached[64 / 32];
    const NNSG3dResNodeInfo * pResNodeInfo;
    const NNSG3dResMat * pResMat;
    const NNSG3dResShp * pResShp;
    fx32 posScale;
    fx32 invPosScale;
    NNSG3dGetJointScale funcJntScale;
    NNSG3dSendJointSRT funcJntMtx;
    NNSG3dSendTexSRT funcTexMtx;
    NNSG3dMatAnmResult tmpMatAnmResult;
    NNSG3dJntAnmResult tmpJntAnmResult;
    NNSG3dVisAnmResult tmpVisAnmResult;
} NNSG3dRS;

#define NNS_G3D_SBC_RET 0x01

typedef enum {
    NNS_G3D_RSFLAG_NODE_VISIBLE           = 0x00000001,
    NNS_G3D_RSFLAG_MAT_TRANSPARENT        = 0x00000002,
    NNS_G3D_RSFLAG_CURRENT_NODE_VALID     = 0x00000004,
    NNS_G3D_RSFLAG_CURRENT_MAT_VALID      = 0x00000008,
    NNS_G3D_RSFLAG_CURRENT_NODEDESC_VALID = 0x00000010,
    NNS_G3D_RSFLAG_RETURN                 = 0x00000020,
    NNS_G3D_RSFLAG_SKIP                   = 0x00000040,
    NNS_G3D_RSFLAG_OPT_RECORD             = 0x00000080,
    NNS_G3D_RSFLAG_OPT_NOGECMD            = 0x00000100,
    NNS_G3D_RSFLAG_OPT_SKIP_SBCDRAW       = 0x00000200,
    NNS_G3D_RSFLAG_OPT_SKIP_SBCMTXCALC    = 0x00000400
} NNSG3dRSFlag;

typedef struct NNSG3dResDictPlttData_ {
    u16 offset;
    u16 flag;
} NNSG3dResDictPlttData;

typedef void (*NNSG3dAnimInitFunc)(void *pAnmObj, void *pResAnm, const void *pResMdl);

typedef struct NNSG3dAnmObjInitFunc {
    u8 category0;
    u8 dummy;
    u16 category1;
    NNSG3dAnimInitFunc func;
} NNSG3dAnmObjInitFunc;

#define NNS_G3D_ANMOBJ_INITFUNC_MAX 10

typedef enum {
    NNS_G3D_JNTANM_TINFO_STEP_1            = 0x00000000,
    NNS_G3D_JNTANM_TINFO_STEP_2            = 0x40000000,
    NNS_G3D_JNTANM_TINFO_STEP_4            = 0x80000000,
    NNS_G3D_JNTANM_TINFO_FX16ARRAY         = 0x20000000,
    NNS_G3D_JNTANM_TINFO_LAST_INTERP_MASK  = 0x1fff0000,
    NNS_G3D_JNTANM_TINFO_STEP_MASK         = 0xc0000000,
    NNS_G3D_JNTANM_TINFO_LAST_INTERP_SHIFT = 16,
    NNS_G3D_JNTANM_TINFO_STEP_SHIFT        = 30
} NNSG3dJntAnmTInfo;

typedef enum {
    NNS_G3D_JNTANM_OPTION_INTERPOLATION = 0x01,
    NNS_G3D_JNTANM_OPTION_END_TO_START_INTERPOLATION = 0x02
} NNSG3dJntAnmOption;

typedef struct NNSG3dResDictTexToMatIdxData_ {
    u16 offset;
    u8 numIdx;
    u8 flag;
} NNSG3dResDictTexToMatIdxData;

typedef struct NNSG3dResDictTexSRTAnmData_ {
    u32 scaleS;
    u32 scaleSEx;
    u32 scaleT;
    u32 scaleTEx;
    u32 rot;
    u32 rotEx;
    u32 transS;
    u32 transSEx;
    u32 transT;
    u32 transTEx;
} NNSG3dResDictTexSRTAnmData;

typedef struct NNSG3dResDictMdlSetData_ {
    u32 offset;
} NNSG3dResDictMdlSetData;

typedef struct NNSG3dResDictTexData_ {
    u32 texImageParam;
    u32 extraParam;
} NNSG3dResDictTexData;

#define NNS_G3D_WARNING SDK_WARNING

typedef enum {
    NNS_G3D_RENDEROBJ_FLAG_RECORD           = 0x00000001,
    NNS_G3D_RENDEROBJ_FLAG_NOGECMD          = 0x00000002,
    NNS_G3D_RENDEROBJ_FLAG_SKIP_SBC_DRAW    = 0x00000004,
    NNS_G3D_RENDEROBJ_FLAG_SKIP_SBC_MTXCALC = 0x00000008,
    NNS_G3D_RENDEROBJ_FLAG_HINT_OBSOLETE    = 0x00000010
} NNSG3dRenderObjFlag;

#define NNS_G3D_SIGNATURE_NSBMD '0DMB'

#define NNS_G3D_SIGNATURE_NSBCA '0ACB'

#define NNS_G3D_SIGNATURE_NSBVA '0AVB'

#define NNS_G3D_SIGNATURE_NSBMA '0AMB'

#define NNS_G3D_SIGNATURE_NSBTP '0PTB'

#define NNS_G3D_SIGNATURE_NSBTA '0ATB'

typedef struct NNSG3dResDictMatCAnmData_ {
    u32 diffuse;
    u32 ambient;
    u32 specular;
    u32 emission;
    u32 polygon_alpha;
} NNSG3dResDictMatCAnmData;

typedef struct NNSG3dResTexPatAnmFV_ {
    u16 idxFrame;
    u8 idTex;
    u8 idPltt;
} NNSG3dResTexPatAnmFV;

typedef enum {
    NNS_G3D_JNTANM_SRTINFO_IDENTITY   = 0x00000001,
    NNS_G3D_JNTANM_SRTINFO_IDENTITY_T = 0x00000002,
    NNS_G3D_JNTANM_SRTINFO_BASE_T     = 0x00000004,
    NNS_G3D_JNTANM_SRTINFO_CONST_TX   = 0x00000008,
    NNS_G3D_JNTANM_SRTINFO_CONST_TY   = 0x00000010,
    NNS_G3D_JNTANM_SRTINFO_CONST_TZ   = 0x00000020,
    NNS_G3D_JNTANM_SRTINFO_IDENTITY_R = 0x00000040,
    NNS_G3D_JNTANM_SRTINFO_BASE_R     = 0x00000080,
    NNS_G3D_JNTANM_SRTINFO_CONST_R    = 0x00000100,
    NNS_G3D_JNTANM_SRTINFO_IDENTITY_S = 0x00000200,
    NNS_G3D_JNTANM_SRTINFO_BASE_S     = 0x00000400,
    NNS_G3D_JNTANM_SRTINFO_CONST_SX   = 0x00000800,
    NNS_G3D_JNTANM_SRTINFO_CONST_SY   = 0x00001000,
    NNS_G3D_JNTANM_SRTINFO_CONST_SZ   = 0x00002000,
    NNS_G3D_JNTANM_SRTINFO_NODE_MASK  = 0xff000000,
    NNS_G3D_JNTANM_SRTINFO_NODE_SHIFT = 24
} NNSG3dJntAnmSRTTag;

typedef struct NNSG3dResJntAnmSRTTag_ {
    u32 tag;
} NNSG3dResJntAnmSRTTag;

typedef struct NNSG3dGlb {
    char pad00[0x4c];
    MtxFx43 cameraMtx;                  /* +0x4c */
    char pad7c[0xd4 - 0x7c];
    u32 flag;                           /* +0xd4 */
} NNSG3dGlb;

#define NNS_G3D_SBCFLG_001 0x20

#define NNS_G3D_SBCFLG_010 0x40

#define NNS_G3D_SBCFLG_011 0x60

#define NNS_G3D_GLB_FLAG_FLUSH_WVP 1

#define NNS_G3D_GLB_FLAG_FLUSH_VP  2

#define NNS_G3D_MATFLAG_TEXMTX_SCALEONE  0x0002

#define NNS_G3D_MATFLAG_TEXMTX_ROTZERO   0x0004

#define NNS_G3D_MATFLAG_TEXMTX_TRANSZERO 0x0008

#define NNS_G3D_MATFLAG_EFFECTMTX        0x2000

#define NNS_G3D_MTXSTACK_SYS 30

typedef enum {
    NNS_G3D_SRTFLAG_TRANS_ZERO        = 0x0001,
    NNS_G3D_SRTFLAG_ROT_ZERO          = 0x0002,
    NNS_G3D_SRTFLAG_SCALE_ONE         = 0x0004,
    NNS_G3D_SRTFLAG_PIVOT_EXIST       = 0x0008,
    NNS_G3D_SRTFLAG_IDXPIVOT_MASK     = 0x00f0,
    NNS_G3D_SRTFLAG_PIVOT_MINUS       = 0x0100,
    NNS_G3D_SRTFLAG_SIGN_REVC         = 0x0200,
    NNS_G3D_SRTFLAG_SIGN_REVD         = 0x0400,
    NNS_G3D_SRTFLAG_IDXMTXSTACK_MASK  = 0xf800,
    NNS_G3D_SRTFLAG_IDENTITY          = NNS_G3D_SRTFLAG_TRANS_ZERO |
                                        NNS_G3D_SRTFLAG_ROT_ZERO |
                                        NNS_G3D_SRTFLAG_SCALE_ONE,
    NNS_G3D_SRTFLAG_IDXPIVOT_SHIFT    = 4,
    NNS_G3D_SRTFLAG_IDXMTXSTACK_SHIFT = 11
} NNSG3dSRTFlag;

typedef enum {
    NNS_G3D_TEXIMAGE_PARAMEX_ORIGW_MASK   = 0x000007ff,
    NNS_G3D_TEXIMAGE_PARAMEX_ORIGH_MASK   = 0x003ff800,
    NNS_G3D_TEXIMAGE_PARAMEX_WHSAME_MASK  = 0x80000000,
    NNS_G3D_TEXIMAGE_PARAMEX_ORIGW_SHIFT  = 0,
    NNS_G3D_TEXIMAGE_PARAMEX_ORIGH_SHIFT  = 11,
    NNS_G3D_TEXIMAGE_PARAMEX_WHSAME_SHIFT = 31
} NNSG3dTexImageParamEx;

typedef enum {
    NNS_G3D_JNTANM_RIDX_PIVOT         = 0x8000,
    NNS_G3D_JNTANM_RIDX_IDXDATA_MASK  = 0x7fff,
    NNS_G3D_JNTANM_RIDX_IDXDATA_SHIFT = 0
} NNSG3dJntAnmRIdx;

typedef enum {
    NNS_G3D_JNTANM_PIVOTINFO_IDXPIVOT_MASK   = 0x000f,
    NNS_G3D_JNTANM_PIVOTINFO_MINUS           = 0x0010,
    NNS_G3D_JNTANM_PIVOTINFO_SIGN_REVC       = 0x0020,
    NNS_G3D_JNTANM_PIVOTINFO_SIGN_REVD       = 0x0040,
    NNS_G3D_JNTANM_PIVOT_INFO_IDXPIVOT_SHIFT = 0
} NNSG3dJntAnmPivotInfo;

typedef enum {
    NNS_G3D_JNTANM_RINFO_STEP_1            = 0x00000000,
    NNS_G3D_JNTANM_RINFO_STEP_2            = 0x40000000,
    NNS_G3D_JNTANM_RINFO_STEP_4            = 0x80000000,
    NNS_G3D_JNTANM_RINFO_LAST_INTERP_MASK  = 0x1fff0000,
    NNS_G3D_JNTANM_RINFO_STEP_MASK         = 0xc0000000,
    NNS_G3D_JNTANM_RINFO_LAST_INTERP_SHIFT = 16,
    NNS_G3D_JNTANM_RINFO_STEP_SHIFT        = 30
} NNSG3dJntAnmRInfo;

#endif

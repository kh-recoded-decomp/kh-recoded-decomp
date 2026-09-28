/* Emits translation, rotation, and scale commands based on joint-result flags.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/func_01ffa218.c.
 * Original routine: func_01ffa218. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef unsigned long u32;
typedef signed long fx32;
typedef int BOOL;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct MtxFx43 {
    fx32 _00, _01, _02;
    fx32 _10, _11, _12;
    fx32 _20, _21, _22;
    fx32 _30, _31, _32;
} MtxFx43;

typedef struct NNSG3dJntAnmResult {
    u32 flag;
    VecFx32 scale;
    VecFx32 scaleEx0;
    VecFx32 scaleEx1;
    MtxFx43 mtx;
} NNSG3dJntAnmResult;

enum {
    JNT_SCALE_ONE = 0x01,
    JNT_ROT_ZERO = 0x02,
    JNT_TRANS_ZERO = 0x04,
    JNT_SCALEEX0_ONE = 0x08,
    JNT_MAYA_SSC = 0x20
};

extern void func_01ffa37c(u32 op, const void *args, u32 numWords);

void EmitJointAnimationResult_01ffa680(const NNSG3dJntAnmResult *result)
{
    BOOL sendTranslation = 0;
    u32 flag = result->flag;

    if (!(flag & JNT_TRANS_ZERO)) {
        sendTranslation = 1;
    }

    if ((flag & JNT_MAYA_SSC) && !(flag & JNT_SCALEEX0_ONE)) {
        if (sendTranslation) {
            func_01ffa37c(0x1c, &result->mtx._30, 3);
            sendTranslation = 0;
        }
        func_01ffa37c(0x1b, &result->scaleEx0, 3);
    }

    if (!(result->flag & JNT_ROT_ZERO)) {
        if (sendTranslation) {
            func_01ffa37c(0x19, &result->mtx, 12);
        } else {
            func_01ffa37c(0x1a, &result->mtx, 9);
        }
    } else if (sendTranslation) {
        func_01ffa37c(0x1c, &result->mtx._30, 3);
    }

    if (result->flag & JNT_SCALE_ONE) {
        return;
    }
    func_01ffa37c(0x1b, &result->scale, 3);
}

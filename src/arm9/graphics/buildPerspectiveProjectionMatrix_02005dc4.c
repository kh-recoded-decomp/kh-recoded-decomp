typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef s32 fx32;
typedef s64 fx64c;

extern fx32 FX_Inv(fx32 numerator, fx32 denominator);
extern fx64c func_01ff9d30(void);
extern fx64c func_02023ba4(fx64c numerator, fx64c denominator);
extern fx32 FX_GetDivResult(void);

typedef struct {
    fx32 _00, _01, _02, _03;
    fx32 _10, _11, _12, _13;
    fx32 _20, _21, _22, _23;
    fx32 _30, _31, _32, _33;
} MtxFx44;

static inline void CP_SetDivImm64_64_NS_(u64 numerator, u64 denominator)
{
    *(u64 *)0x04000290 = numerator;
    *(u64 *)0x04000298 = denominator;
}

static inline fx32 roundFx64ToFx32(u64 wideFixedPointValue)
{
    return (fx32)((wideFixedPointValue + 0x80000000ULL) >> 32);
}

static inline fx32 multiplyFixedPoint(fx32 leftFactor, fx32 rightFactor)
{
    return (fx32)(((fx64c)leftFactor * rightFactor + 0x800) >> 12);
}

void buildPerspectiveProjectionMatrix_02005dc4(fx32 verticalFovSine, fx32 verticalFovCosine, fx32 aspectRatio, fx32 nearPlane, fx32 farPlane,
                   fx32 clipWScale, MtxFx44 *projectionMatrix)
{
    fx64c depthReciprocal;
    fx32 fieldOfViewCotangent;

    fieldOfViewCotangent = FX_Inv(verticalFovCosine, verticalFovSine);
    CP_SetDivImm64_64_NS_((u64)0x1000 << 32, (u64)(u32)(nearPlane - farPlane));
    if (clipWScale != 0x1000)
        fieldOfViewCotangent = (fieldOfViewCotangent * clipWScale) / 0x1000;

    projectionMatrix->_01 = 0;
    projectionMatrix->_02 = 0;
    projectionMatrix->_03 = 0;
    projectionMatrix->_10 = 0;
    projectionMatrix->_11 = fieldOfViewCotangent;
    projectionMatrix->_12 = 0;
    projectionMatrix->_13 = 0;
    projectionMatrix->_20 = 0;
    projectionMatrix->_21 = 0;
    projectionMatrix->_23 = -clipWScale;
    projectionMatrix->_30 = 0;
    projectionMatrix->_31 = 0;
    projectionMatrix->_33 = 0;

    depthReciprocal = func_01ff9d30();
    CP_SetDivImm64_64_NS_((u64)fieldOfViewCotangent << 32, (u64)(u32)aspectRatio);
    if (clipWScale != 0x1000)
        depthReciprocal = func_02023ba4(depthReciprocal * clipWScale, 0x1000);

    projectionMatrix->_22 = roundFx64ToFx32((u64)(depthReciprocal * (farPlane + nearPlane)));
    projectionMatrix->_32 = roundFx64ToFx32((u64)(depthReciprocal * multiplyFixedPoint(nearPlane * 2, farPlane)));
    projectionMatrix->_00 = FX_GetDivResult();
}

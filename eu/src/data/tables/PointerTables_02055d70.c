#include "nitro/types.h"

extern void NNSi_G3dSendTexMtxMode2(void);
extern void SendTexMtxAltBuilders(void);
extern void DecodeBasicJointScale(void); /* func */
extern void NNSi_G3dGetJointScaleMaya(void); /* func */

void (*gMaterialAnimationDispatch[4])(void) = {
    NNSi_G3dSendTexMtxMode2,
    NULL,
    SendTexMtxAltBuilders,
    NULL,
};

void (*gJointAnimationNodeDispatch[3])(void) = {
    DecodeBasicJointScale, /* func */
    NNSi_G3dGetJointScaleMaya, /* func */
    NULL,
};

#ifndef STAGE_MODEL_RENDER_H
#define STAGE_MODEL_RENDER_H

#include "src/overlays/ov041/StageWork.h"

extern void NNS_G3dGeBufferOP_N(u32 command, const void *data, u32 words);
extern void NNS_G3dGlbFlushP(void);
extern void setMaterialColorScale(int colorScale);
extern void NNS_G3dDraw(StageModelRenderObject *renderObject);

void DrawTrackedStageShadow(StageFollowerActor *actor);
void DrawStagePrimaryModel(StageFollowerActor *actor);

#endif

extern void ModelRenderCallbackKindC(void *renderState);
extern void CaptureTrackedNodeMatrixThunk(void *renderState);

void ModelRenderCallbackKind12(void *renderState)
{
    ModelRenderCallbackKindC(renderState);
    CaptureTrackedNodeMatrixThunk(renderState);
}

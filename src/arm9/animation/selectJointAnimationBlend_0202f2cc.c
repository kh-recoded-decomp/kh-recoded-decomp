/* Behavior: Switches a model to the selected animation and restarts it at the beginning at normal speed.
 * Inputs/outputs and evidence: Skips empty or unchanged selections, unbinds the old object, binds the indexed target, and writes frame zero and speed one.
 * Uncertainty: Render object and animation object layouts are inferred from offsets; selectedAnimationIndices semantics beyond selecting a track entry are unknown.
 * Source: khdays-decomp/src/calls/func_0202accc.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
extern void func_02018850(int *ptr, int arg);
extern void func_0201875c(void *pRenderObj, void *pAnmObj);


typedef struct {
    short field_00;
    short selectedAnimationIndices[5];      
    void *boundAnimations[5];   
} AnimationBindingState;


typedef struct {
    short animationCounts[5];
    char pad_0a[0x10 - 0xa];
    void **animationChoices[5]; 
} AnimationBlendTable;

void selectJointAnimationBlend_0202f2cc(AnimationBindingState *animationState, unsigned short trackIndex, AnimationBlendTable *blendTable, short blendIndex)
{
    if (blendTable->animationCounts[trackIndex] == 0)
        return;

    void *currentAnimation = animationState->boundAnimations[trackIndex];
    void *targetAnimation = blendTable->animationChoices[trackIndex][blendIndex];
    if (currentAnimation == targetAnimation)
        return;

    if (currentAnimation != 0)
        func_02018850((int *)((char *)animationState + 0x20), (int)currentAnimation);

    animationState->selectedAnimationIndices[trackIndex] = blendIndex;
    if (blendIndex >= 0) {
        targetAnimation = blendTable->animationChoices[trackIndex][blendIndex];
        animationState->boundAnimations[trackIndex] = targetAnimation;
        func_0201875c((char *)animationState + 0x20, targetAnimation);

        *(int *)((char *)animationState->boundAnimations[trackIndex] + 4) = 0x1000; 
        *(int *)animationState->boundAnimations[trackIndex] = 0;                    
        return;
    }
    animationState->boundAnimations[trackIndex] = 0;
}

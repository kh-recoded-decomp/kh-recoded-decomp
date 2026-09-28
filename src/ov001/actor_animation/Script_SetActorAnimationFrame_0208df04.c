extern int func_02025de4(int scriptContext, void *arg);
extern int func_02025df8(int scriptContext, void *arg);
extern int func_02025960(int scriptContext, int arg);
extern void func_020219b4(int scriptContext, int commandOperands);

extern char *func_02036240(int index);
extern void Animation_SetFrameWithSingleWrap(void *p, int animationTrack, int animationFrame);

int Script_SetActorAnimationFrame_0208df04(int scriptContext, int commandOperands) {
    int entityIndex = func_02025de4(scriptContext, (void *)commandOperands);
    int animationTrack = func_02025de4(scriptContext, (void *)(commandOperands + 8));
    int animationFrame = func_02025df8(scriptContext, (void *)(commandOperands + 0x10));
    Animation_SetFrameWithSingleWrap(func_02036240((unsigned short)func_02025960(scriptContext, entityIndex)) + 4,
                  (unsigned short)animationTrack, animationFrame);
    return 1;
}

/* Sets an actor's selected animation track to a requested frame.
 * Inputs: script entity ID, animation track index, and a 20.12 fixed-point frame.
 * Re:coded ITCM helper 0x01ffb2f8 stores that frame and subtracts the clip duration
 * once when the value reaches it. This is a single wrap, not a general modulo.
 * The entity operand passes through 0x02025960 unchanged in Re:coded.
 * Uncertainty: specific actors and meanings of track indices are not established.
 * Adapted from khdays-decomp/src/overlays/ov023/calls/func_ov023_020862e8.c,
 * CC0, revision ab832f38b943c15f461228968a89002e1a99c03e.
 */
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

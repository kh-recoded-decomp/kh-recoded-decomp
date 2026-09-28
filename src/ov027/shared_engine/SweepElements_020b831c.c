extern void Ov000_SweepReleasePendingElements(int arg);
extern void Ov000_FlushFlaggedElements(int a, int b);
extern void Ov000_SweepFreeElementBuffers(int arg);
void SweepElements_020b831c(int param_1) {
    Ov000_SweepReleasePendingElements(param_1);
    Ov000_FlushFlaggedElements(param_1, 0);
    Ov000_SweepFreeElementBuffers(param_1);
}

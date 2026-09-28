extern void NNSi_FndGetCurrentRootHeap(void);
extern void Ov008_CommitSelectedPage(void);

void *ReturnToCommitPage_020c3500(void) {
    NNSi_FndGetCurrentRootHeap();
    return (void *)&Ov008_CommitSelectedPage;
}

extern int Ov002_ScriptIsEntryFree();
extern int Slot48_StoreAtCurrentIndex();

int ScriptCmd_StoreIfFree_0208cd80(int arg0, int arg1) {
    int r = Ov002_ScriptIsEntryFree(arg0, arg1);
    if (r == 0) {
        Slot48_StoreAtCurrentIndex(arg0, arg1);
    }
    return r;
}

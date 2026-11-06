extern void GetPackedFileEntry();
extern int gTutorialMenuGlobalStorage;

void GetTutorialTextEntry(int arg0) {
    GetPackedFileEntry(gTutorialMenuGlobalStorage + 8, arg0);
}

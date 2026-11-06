extern void GetPackedFileEntry();
extern int gTutorialMenuGlobalStorage;

void GetTutorialListTextEntry(int arg0) {
    GetPackedFileEntry(gTutorialMenuGlobalStorage + 20, arg0);
}

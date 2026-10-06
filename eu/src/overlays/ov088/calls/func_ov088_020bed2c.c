typedef struct Overlay088Pair { short first, second; } Overlay088Pair;
typedef struct Overlay088PairSettings { Overlay088Pair entries[4]; } Overlay088PairSettings;
extern const Overlay088PairSettings data_ov088_020bee5c;
extern char sOv088_UiMenuStrLanguageCdSZ_020bef08[];
extern int UpdateScreenWidgetLayer(int id);
extern void LoadPackedFileView(void *state, void *data, int flags);
extern int func_ov039_020bc9b4(void);
extern void InitTextLayerAt(void *context, int kind, int entry, int value, Overlay088PairSettings *pairedSettings);
extern int func_ov027_020ba2c8(void *state, int index);
extern void DrawTextAnchored(void *context, int first, int second, int third, int flags, int value);
extern void Text_UploadTileBuffer(void *context);
extern void SetScreenLayerDirty(int id);
void func_ov088_020bed2c(void *context) {
    Overlay088PairSettings pairedSettings = data_ov088_020bee5c;
    int entry = UpdateScreenWidgetLayer(0x1a);
    LoadPackedFileView((char *)context + 0x34, sOv088_UiMenuStrLanguageCdSZ_020bef08, 0);
    InitTextLayerAt(context, 6, entry, func_ov039_020bc9b4(), &pairedSettings);
    DrawTextAnchored(context, 4, 0, 2, 0x209, func_ov027_020ba2c8((char *)context + 0x34, 0));
    Text_UploadTileBuffer(context);
    SetScreenLayerDirty(0x1a);
}

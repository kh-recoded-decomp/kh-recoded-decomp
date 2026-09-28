typedef struct Overlay088Pair { short first, second; } Overlay088Pair;
typedef struct Overlay088PairSettings { Overlay088Pair entries[4]; } Overlay088PairSettings;
extern const Overlay088PairSettings defaultPairSettings;
extern char callbackData[];
extern int func_ov039_020bc1e4(int id);
extern void func_ov027_020ba25c(void *state, void *data, int flags);
extern int func_ov039_020bc994(void);
extern void func_020014b0(void *context, int kind, int entry, int value, Overlay088PairSettings *pairedSettings);
extern int func_ov027_020ba2a8(void *state, int index);
extern void func_020015a0(void *context, int first, int second, int third, int flags, int value);
extern void func_02001520(void *context);
extern void func_ov039_020bc104(int id);
void func_ov088_020bed0c(void *context) {
    Overlay088PairSettings pairedSettings = defaultPairSettings;
    int entry = func_ov039_020bc1e4(0x1a);
    func_ov027_020ba25c((char *)context + 0x34, callbackData, 0);
    func_020014b0(context, 6, entry, func_ov039_020bc994(), &pairedSettings);
    func_020015a0(context, 4, 0, 2, 0x209, func_ov027_020ba2a8((char *)context + 0x34, 0));
    func_02001520(context);
    func_ov039_020bc104(0x1a);
}

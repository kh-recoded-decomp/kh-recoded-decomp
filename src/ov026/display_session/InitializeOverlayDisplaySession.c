typedef struct OverlayDisplaySession {
    unsigned char sharedState[0x647c];
    int alternateUpdate;
    int firstUpdatePending;
    int restorePositiveBrightness;
    unsigned int savedDisplayLayers;
    int savedBrightness;
    int savedDisplaySetting;
    int updateInProgress;
    void *updateRegistration;
} OverlayDisplaySession;
typedef struct DisplaySessionSettings { int values[6]; } DisplaySessionSettings;
extern const DisplaySessionSettings defaultDisplaySessionSettings;
extern const unsigned short positiveBrightnessPalette;
extern int GetSecondaryBrightness(void);
extern int GetDisplaySetting(void);
extern void SetDisplaySetting(int setting);
extern void func_020072b4(const void *source, unsigned offset, unsigned size);
extern void func_ov027_020b8bd4(OverlayDisplaySession *session, const DisplaySessionSettings *settings);
void InitializeOverlayDisplaySession(OverlayDisplaySession *session, int *alternateUpdate) {
    DisplaySessionSettings settings = defaultDisplaySessionSettings;
    session->savedDisplayLayers = (*(volatile unsigned int *)0x04001000 & 0x1f00) >> 8;
    session->savedBrightness = GetSecondaryBrightness();
    session->alternateUpdate = *alternateUpdate;
    session->savedDisplaySetting = GetDisplaySetting();
    session->firstUpdatePending = 1;
    if (GetSecondaryBrightness() == 0x10) {
        func_020072b4(&positiveBrightnessPalette, 0, 2);
        session->restorePositiveBrightness = 1;
    }
    SetDisplaySetting(0);
    func_ov027_020b8bd4(session, &settings);
}

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
extern OverlayDisplaySession *gOverlayDisplaySessionWorkStorage;
extern OverlayDisplaySession *GetRunningTaskWork(void);
extern void GXS_LoadBGPltt(const void *source, unsigned offset, unsigned size);
extern void InitializeOverlayDisplaySession(OverlayDisplaySession *session, int *alternateUpdate);
extern void SetPanelSessionActive(void);
extern void *AddFieldListener(void (*callback)(void));
extern void RunOverlayDisplayUpdate(void);
extern int ShouldRestorePositiveBrightness(OverlayDisplaySession *session);
extern void RequestPanelBrightnessRestore(void);
extern int OverlayDisplaySessionNoOpCallback(void);
int (*BeginOverlayDisplaySession(void))(void) {
    OverlayDisplaySession *session = GetRunningTaskWork();
    unsigned short paletteValue = 0;
    int alternateUpdate;
    gOverlayDisplaySessionWorkStorage = session;
    alternateUpdate = 1;
    GXS_LoadBGPltt(&paletteValue, 0, 2);
    InitializeOverlayDisplaySession(session, &alternateUpdate);
    SetPanelSessionActive();
    session->updateRegistration = AddFieldListener(RunOverlayDisplayUpdate);
    if (ShouldRestorePositiveBrightness(session)) RequestPanelBrightnessRestore();
    return OverlayDisplaySessionNoOpCallback;
}

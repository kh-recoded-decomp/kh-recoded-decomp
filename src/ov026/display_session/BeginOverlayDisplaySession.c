/* Starts a display session, prepares its initial palette value and installs its update callback.
 * Obtains the current session, publishes it, initializes it with alternate-update mode 1, registers RunOverlayDisplayUpdate, stores the registration at +0x6498, and returns a callback that reports zero.
 * The display-state operations are established. The session's particular menu, scene or gameplay purpose and the shared display-setting meaning remain unknown.
 * Recovered from the persistent Ghidra caller chain and verified disassembly. */
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
extern OverlayDisplaySession *currentDisplaySession;
extern OverlayDisplaySession *func_0202a764(void);
extern void func_020072b4(const void *source, unsigned offset, unsigned size);
extern void InitializeOverlayDisplaySession(OverlayDisplaySession *session, int *alternateUpdate);
extern void func_ov001_0207b4d8(void);
extern void *func_ov001_0207157c(void (*callback)(void));
extern void RunOverlayDisplayUpdate(void);
extern int ShouldRestorePositiveBrightness(OverlayDisplaySession *session);
extern void func_ov001_0207b778(void);
extern int func_ov026_020b58c8(void);
int (*BeginOverlayDisplaySession(void))(void) {
    OverlayDisplaySession *session = func_0202a764();
    unsigned short paletteValue = 0;
    int alternateUpdate;
    currentDisplaySession = session;
    alternateUpdate = 1;
    func_020072b4(&paletteValue, 0, 2);
    InitializeOverlayDisplaySession(session, &alternateUpdate);
    func_ov001_0207b4d8();
    session->updateRegistration = func_ov001_0207157c(RunOverlayDisplayUpdate);
    if (ShouldRestorePositiveBrightness(session)) func_ov001_0207b778();
    return func_ov026_020b58c8;
}

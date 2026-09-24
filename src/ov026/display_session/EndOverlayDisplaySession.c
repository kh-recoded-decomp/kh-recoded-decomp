/* Removes the session update callback and restores its saved display state.
 * Unregisters the handle at +0x6498 through ov001:020715ac, invokes the restore path and clears the global session pointer.
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
extern void func_ov001_020715ac(void *registration);
extern void RestoreOverlayDisplayState(OverlayDisplaySession *session);
void EndOverlayDisplaySession(void) {
    OverlayDisplaySession *session = func_0202a764();
    func_ov001_020715ac(session->updateRegistration);
    RestoreOverlayDisplayState(session);
    currentDisplaySession = 0;
}

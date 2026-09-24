/* Updates the active display session once, preventing recursive updates.
 * Checks the global session pointer and +0x6494 guard, sets the guard around the shared update, then clears it.
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
extern void UpdateOverlayDisplaySession(OverlayDisplaySession *session);
void RunOverlayDisplayUpdate(void) {
    OverlayDisplaySession *session = currentDisplaySession;
    if (session == 0) return;
    if (session->updateInProgress != 0) return;
    session->updateInProgress = 1;
    UpdateOverlayDisplaySession(session);
    session->updateInProgress = 0;
}

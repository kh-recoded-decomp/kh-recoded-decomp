/* Reports whether the display session was marked for positive full-brightness restoration.
 * Returns the word at +0x6484, which initialization sets when the incoming secondary brightness equals +16.
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
int ShouldRestorePositiveBrightness(OverlayDisplaySession *session) {
    return session->restorePositiveBrightness;
}

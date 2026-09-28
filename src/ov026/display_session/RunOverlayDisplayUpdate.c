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

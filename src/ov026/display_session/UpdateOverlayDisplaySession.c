/* Configures the display on the first update and forwards each update to the selected session handler.
 * On the first update it enables only layer bit 0x1000, sets secondary brightness to zero and clears the first-update flag. It then calls ov027:020b8c94 or 020b8c80 according to the stored update mode.
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
extern void SetSecondaryBrightness(int brightness);
extern void func_ov027_020b8c94(OverlayDisplaySession *session, int argument);
extern void func_ov027_020b8c80(OverlayDisplaySession *session, int argument);
void UpdateOverlayDisplaySession(OverlayDisplaySession *session) {
    if (session->firstUpdatePending) {
        *(volatile unsigned int *)0x04001000 = (*(volatile unsigned int *)0x04001000 & ~0x1f00) | 0x1000;
        SetSecondaryBrightness(0);
        session->firstUpdatePending = 0;
    }
    if (session->alternateUpdate) func_ov027_020b8c94(session, 0);
    else func_ov027_020b8c80(session, 0);
}

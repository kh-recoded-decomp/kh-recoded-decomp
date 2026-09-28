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
extern OverlayDisplaySession *func_020b9fac(void);
int func_ov027_020ba104(void) { func_020b9fac(); return 0; }

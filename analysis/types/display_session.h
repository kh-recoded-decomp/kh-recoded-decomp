/* BK9E ARM9 partial display-session layout. Unknown shared prefix is reserved. */
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
typedef int (*DisplaySessionCallback)(void);

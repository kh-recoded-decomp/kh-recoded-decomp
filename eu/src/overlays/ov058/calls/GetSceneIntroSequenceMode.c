extern int gOverlay058SceneControlHead;

int GetSceneIntroSequenceMode(void) {
    return *(signed char *)&gOverlay058SceneControlHead;
}

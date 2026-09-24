/* Unloads an overlay and frees its first matching tracked slot so it can be used again.
 * See analysis/overlay_loading.json for the connected caller evidence. */
extern void UnloadOverlay(int processor, int overlayId);
extern int loadedOverlayIds[3];
void UnloadTrackedOverlay(int overlayId)
{
    int slot;
    UnloadOverlay(0, overlayId);
    for (slot = 0; slot < 3; ++slot) {
        if (loadedOverlayIds[slot] == overlayId) {
            loadedOverlayIds[slot] = -1;
            return;
        }
    }
}

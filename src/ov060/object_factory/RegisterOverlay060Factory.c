/* Loading overlay 60 installs this creation callback in the shared factory
 * slot. The object's particular in-game role is still unknown. */
typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOverlay060Object(void);
extern void SetOverlayObjectFactory(OverlayObjectFactory factory);
void RegisterOverlay060Factory(void)
{
    SetOverlayObjectFactory(CreateOverlay060Object);
}

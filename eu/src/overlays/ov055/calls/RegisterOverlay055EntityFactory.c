typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOverlay055Entity(void);
extern void SetOverlayObjectFactory(OverlayObjectFactory factory);
void RegisterOverlay055EntityFactory(void)
{
    SetOverlayObjectFactory(CreateOverlay055Entity);
}

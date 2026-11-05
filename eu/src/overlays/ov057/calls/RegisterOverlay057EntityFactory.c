typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOverlay057Entity(void);
extern void SetOverlayObjectFactory(OverlayObjectFactory factory);
void RegisterOverlay057EntityFactory(void)
{
    SetOverlayObjectFactory(CreateOverlay057Entity);
}

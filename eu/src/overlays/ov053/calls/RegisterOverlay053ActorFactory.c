typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);
extern OverlayObject *CreateOv053Actor(void);
extern void SetOverlayObjectFactory(OverlayObjectFactory factory);
void RegisterOverlay053ActorFactory(void)
{
    SetOverlayObjectFactory(CreateOv053Actor);
}

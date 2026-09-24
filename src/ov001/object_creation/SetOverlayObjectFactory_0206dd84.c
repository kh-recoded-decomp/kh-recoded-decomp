/* Stores the callback later used by the overlay-object creation path. */
typedef struct OverlayObject OverlayObject;
typedef OverlayObject *(*OverlayObjectFactory)(void);

typedef struct OverlayObjectFactoryStateObserved {
    unsigned int unknown_000;
    OverlayObjectFactory currentFactory_004;
} OverlayObjectFactoryStateObserved;

extern OverlayObjectFactoryStateObserved data_ov001_020a049c;

void SetOverlayObjectFactory_0206dd84(OverlayObjectFactory factory)
{
    data_ov001_020a049c.currentFactory_004 = factory;
}

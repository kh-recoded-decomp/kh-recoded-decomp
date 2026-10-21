#include "nitro/types.h"

extern void func_02042f68(void); /* func */
extern void SweepObbAgainstSphereSwapped(void); /* SweepObbAgainstSphereSwapped */
extern void SweepObbAgainstObb(void); /* SweepObbAgainstObb */
extern void SweepObbAgainstSegment(void); /* SweepObbAgainstSegment */
extern void func_020434e4(void); /* func */
extern void SweepObbAgainstPolygon(void); /* func */
extern void SweepCylinderAgainstSphereSwapped(void); /* SweepCylinderAgainstSphereSwapped */
extern void SweepSegmentAgainstObbSwapped(void); /* SweepSegmentAgainstObbSwapped */
extern void SweepSegmentAgainstSegment(void); /* func */
extern void SweepSegmentAgainstCylinder(void); /* SweepSegmentAgainstCylinder */
extern void SweepSegmentAgainstPolygon(void); /* SweepSegmentAgainstPolygon */
extern void SweepCylinderAgainstInflatedSphereSwapped(void); /* SweepCylinderAgainstInflatedSphereSwapped */
extern void SweepCylinderAgainstBoxSwapped(void); /* SweepCylinderAgainstBoxSwapped */
extern void SweepCylinderAgainstSegmentSwapped(void); /* SweepCylinderAgainstSegmentSwapped */
extern void SweepCapsuleAgainstCapsule(void); /* SweepCapsuleAgainstCapsule */
extern void func_020449c8(void); /* func */
extern void func_020456d4(void); /* func */
extern void SweepCappedCylinderAgainstSphereSwapped(void); /* SweepCappedCylinderAgainstSphereSwapped */
extern void SweepCylinderAgainstCylinderSwapped(void); /* SweepCylinderAgainstCylinderSwapped */
extern void SweepPolygonAgainstSphereSwapped(void); /* SweepPolygonAgainstSphereSwapped */
extern void SweepSwappedShapes(void); /* SweepSwappedShapes */
extern void SweepPolygonAgainstSegmentSwapped(void); /* SweepPolygonAgainstSegmentSwapped */
extern void SweepSwappedShapesAlt(void); /* SweepSwappedShapesAlt */
extern void SweepPolygonAgainstPolygon(void); /* SweepPolygonAgainstPolygon */
extern void SweepSphereAgainstSphere(void); /* SweepSphereAgainstSphere */
extern void SweepSphereAgainstObb(void); /* SweepSphereAgainstObb */
extern void SweepSphereAgainstCylinder(void); /* SweepSphereAgainstCylinder */
extern void SweepInflatedSphereAgainstCylinder(void); /* SweepInflatedSphereAgainstCylinder */
extern void SweepSphereAgainstCappedCylinder(void); /* SweepSphereAgainstCappedCylinder */

void (*const gCollisionSweepPairDispatch[31])(void) = {
    func_02042f68, /* func */
    SweepObbAgainstSphereSwapped, /* SweepObbAgainstSphereSwapped */
    SweepObbAgainstObb, /* SweepObbAgainstObb */
    SweepObbAgainstSegment, /* SweepObbAgainstSegment */
    func_020434e4, /* func */
    func_020434e4, /* func */
    SweepObbAgainstPolygon, /* func */
    SweepCylinderAgainstSphereSwapped, /* SweepCylinderAgainstSphereSwapped */
    SweepSegmentAgainstObbSwapped, /* SweepSegmentAgainstObbSwapped */
    SweepSegmentAgainstSegment, /* func */
    SweepSegmentAgainstCylinder, /* SweepSegmentAgainstCylinder */
    SweepSegmentAgainstCylinder, /* SweepSegmentAgainstCylinder */
    SweepSegmentAgainstPolygon, /* SweepSegmentAgainstPolygon */
    SweepCylinderAgainstInflatedSphereSwapped, /* SweepCylinderAgainstInflatedSphereSwapped */
    SweepCylinderAgainstBoxSwapped, /* SweepCylinderAgainstBoxSwapped */
    SweepCylinderAgainstSegmentSwapped, /* SweepCylinderAgainstSegmentSwapped */
    SweepCapsuleAgainstCapsule, /* SweepCapsuleAgainstCapsule */
    func_020449c8, /* func */
    func_020456d4, /* func */
    SweepCappedCylinderAgainstSphereSwapped, /* SweepCappedCylinderAgainstSphereSwapped */
    SweepCylinderAgainstBoxSwapped, /* SweepCylinderAgainstBoxSwapped */
    SweepCylinderAgainstSegmentSwapped, /* SweepCylinderAgainstSegmentSwapped */
    SweepCylinderAgainstCylinderSwapped, /* SweepCylinderAgainstCylinderSwapped */
    func_020449c8, /* func */
    func_020456d4, /* func */
    SweepPolygonAgainstSphereSwapped, /* SweepPolygonAgainstSphereSwapped */
    SweepSwappedShapes, /* SweepSwappedShapes */
    SweepPolygonAgainstSegmentSwapped, /* SweepPolygonAgainstSegmentSwapped */
    SweepSwappedShapesAlt, /* SweepSwappedShapesAlt */
    SweepSwappedShapesAlt, /* SweepSwappedShapesAlt */
    SweepPolygonAgainstPolygon, /* SweepPolygonAgainstPolygon */
};

void (*const gCollisionSweepDispatch[5])(void) = {
    SweepSphereAgainstSphere, /* SweepSphereAgainstSphere */
    SweepSphereAgainstObb, /* SweepSphereAgainstObb */
    SweepSphereAgainstCylinder, /* SweepSphereAgainstCylinder */
    SweepInflatedSphereAgainstCylinder, /* SweepInflatedSphereAgainstCylinder */
    SweepSphereAgainstCappedCylinder, /* SweepSphereAgainstCappedCylinder */
};

#include "nitro/types.h"

extern void SweepCappedCylinderAgainstSphereSwapped_02041bb4(void);
extern void SweepCylinderAgainstBoxSwapped_02041984(void);
extern void SweepCylinderAgainstCylinderSwapped_02041c24(void);
extern void SweepCylinderAgainstInflatedSphereSwapped_02041b44(void);
extern void SweepCylinderAgainstSegmentSwapped_02041ad4(void);
extern void SweepCylinderAgainstSphereSwapped_020419f4(void);
extern void SweepObbAgainstObb_02047b40(void);
extern void SweepObbAgainstSegment_02047dc4(void);
extern void SweepObbAgainstSphereSwapped_02041914(void);
extern void SweepPolygonAgainstSegmentSwapped_02041d74(void);
extern void SweepPolygonAgainstSphereSwapped_02041c94(void);
extern void SweepSegmentAgainstCylinder_02048468(void);
extern void SweepSegmentAgainstObbSwapped_02041a64(void);
extern void SweepSegmentAgainstPolygon_02048c7c(void);
extern void SweepSphereAgainstCappedCylinder_02042b84(void);
extern void SweepSwappedShapesAlt_02041de4(void);
extern void SweepSwappedShapes_02041d04(void);
extern void func_02041e54(void);
extern void func_02041f2c(void);
extern void func_02042678(void);
extern void func_02042b04(void);
extern void func_02042f54(void);
extern void func_020434d0(void);
extern void func_02044914(void);
extern void func_020449b4(void);
extern void func_020456c0(void);
extern void func_02048020(void);
extern void func_02048214(void);
extern void func_02048e18(void);

void (*const data_02055944[31])(void) = {
    func_02042f54,
    SweepObbAgainstSphereSwapped_02041914,
    SweepObbAgainstObb_02047b40,
    SweepObbAgainstSegment_02047dc4,
    func_020434d0,
    func_020434d0,
    func_02048020,
    SweepCylinderAgainstSphereSwapped_020419f4,
    SweepSegmentAgainstObbSwapped_02041a64,
    func_02048214,
    SweepSegmentAgainstCylinder_02048468,
    SweepSegmentAgainstCylinder_02048468,
    SweepSegmentAgainstPolygon_02048c7c,
    SweepCylinderAgainstInflatedSphereSwapped_02041b44,
    SweepCylinderAgainstBoxSwapped_02041984,
    SweepCylinderAgainstSegmentSwapped_02041ad4,
    func_02044914,
    func_020449b4,
    func_020456c0,
    SweepCappedCylinderAgainstSphereSwapped_02041bb4,
    SweepCylinderAgainstBoxSwapped_02041984,
    SweepCylinderAgainstSegmentSwapped_02041ad4,
    SweepCylinderAgainstCylinderSwapped_02041c24,
    func_020449b4,
    func_020456c0,
    SweepPolygonAgainstSphereSwapped_02041c94,
    SweepSwappedShapes_02041d04,
    SweepPolygonAgainstSegmentSwapped_02041d74,
    SweepSwappedShapesAlt_02041de4,
    SweepSwappedShapesAlt_02041de4,
    func_02048e18,
};

void (*const data_02055930[5])(void) = {
    func_02041e54,
    func_02041f2c,
    func_02042678,
    func_02042b04,
    SweepSphereAgainstCappedCylinder_02042b84,
};

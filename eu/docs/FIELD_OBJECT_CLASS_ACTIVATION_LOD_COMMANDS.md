# Field-object class activation, LOD and command selection

This block follows the registered field-object class from its class-table lookup to activation, resource loading, rendering and the active-target command consumers. These are operational names supported by the EU native code. The existing C ABI views and compiler profiles are retained.

## Function identities

| EU identity | Function | Active source |
| --- | --- | --- |
| ov001:0x0207f9c0 (Thumb, 0xe bytes) | `SetFieldObjectClassActivationFlagBit` | `eu/src/overlays/ov001/calls/SetFieldObjectClassActivationFlagBit.c` |
| ov001:0x0207fb58 (Thumb, 0x22 bytes) | `ScriptCmd_SetFieldObjectClassActivationFlagBit` | `eu/src/overlays/ov001/calls/ScriptCmd_SetFieldObjectClassActivationFlagBit.c` |
| ov001:0x0207fa24 (Thumb, 0x18 bytes) | `ConfigureFieldObjectClassLod` | `eu/src/overlays/ov001/calls/ConfigureFieldObjectClassLod.c` |
| ov001:0x0207f91c (Thumb, 0x8 bytes) | `GetFieldObjectActionCommandKind` | `eu/src/overlays/ov001/auto/GetFieldObjectActionCommandKind.c` |
| ov001:0x02080168 (Thumb, 0x3e bytes) | `ScriptCmd_ConfigureFieldObjectClassLod` | `eu/src/overlays/ov001/calls/ScriptCmd_ConfigureFieldObjectClassLod.c` |

The final row corrects the existing `ScriptCmd_SpawnStateSpot_02080168` label; it does not spawn an object. It is supplied as a separate correction from the four previously numeric functions.

## Activation flag index

`SetFieldObjectClassActivationFlagBit(classIndex, bitIndex)` writes the low byte of the second input to class +0x81. The native setter leaves R0 unchanged before calling `GetFieldObjectClassAtIndex`, whose R0 input indexes the manager's class-pointer table. The matching source's first parameter name `unused` and its no-prototype call do not describe the native input contract.

`FieldObject_Activate` first sets the instance activation mode and invokes the class activation hook. If class flags +0x7e bit 0 was clear, it sets that bit and reads class +0x81 as a signed byte. A nonnegative index calls `ObjectManager_SetFlagBit`, which marks the packed bit at `gFieldObjectClassManager + 0x120`. Values 0x80..0xff disable this operation because the reader is signed. The setter itself neither activates an instance nor writes the manager bit. The flag is manager-owned; persistence and a gameplay label for each bit are not established here.

`ScriptCmd_SetFieldObjectClassActivationFlagBit` is group 4, opcode 0x03. It resolves two integer operands at descriptor offsets 0 and 8, forwards the values to the setter and returns 1. Its resume slot is NULL. The native run word at 0x0209f060 is 0x0207fb59.

Evidence sources:

- `eu/src/overlays/ov001/calls/GetFieldObjectClassAtIndex.c`
- `eu/src/overlays/ov001/calls/FieldObject_Activate.c` and shared `src/ov001/field_objects/FieldObject_Activate_0207f4c0.c`
- `eu/src/overlays/ov001/calls/ObjectManager_SetFlagBit.c`
- `eu/src/overlays/ov001/calls/CreateFieldObjectManager.c`
- `eu/src/overlays/ov001/data/tables/gFieldObjectScriptCommandHandlers.c`

## Secondary LOD resource and hysteresis

`ConfigureFieldObjectClassLod(classIndex, secondaryResourceIndex, enterFarDistance, exitFarDistance)` writes the low halfword of its second input at class +0x66 and the two 32-bit distance values at +0x68/+0x6c. Native R0 reaches the class-table lookup unchanged. Class +0x66 is read as a signed index: negative values disable the secondary-model path. It does not select a track in an already loaded animation.

`AcquireEffectRecordPair` reads the two signed resource indices at class +0x64/+0x66. For the second nonnegative index, it obtains the shared/model resource at class +0x5c and, when class flags +0x7e bit 0 permits loading, the animation buffer at +0x60. `FieldObject_TrySpawn` allocates the secondary instance at object +0x10 using those resources and binds track 0, frame 0. The primary instance is object +0x0c. These instance pointers belong to the field object and are released by the class destruction path; the configuration setter only changes class values.

`DrawLinkedActorPass` gives a custom class draw hook priority. Otherwise, a nonnegative class +0x66 selects `DrawLodSceneObject`; a negative value draws the primary actor node. The LOD draw function computes distance from the active camera culling origin to object position +0x40 and uses instance flags +0x4e bit 0x8000:

- If the bit is clear and `class[+0x68] <= distance`, set it.
- If the bit is set and `distance <= class[+0x6c]`, clear it.
- Draw the secondary instance while the bit is set; draw the primary actor node otherwise.

There are no threshold ordering, range or sign checks. The equality cases above are intentional native behavior. Configuration does not allocate or reload resources, update existing instances, change draw hooks, or provide an ownership transfer. Resource indices refer to the manager resource tables; no original asset names are assigned.

The related script command is group 4, opcode 0x13. It resolves integer class/resource indices and two fx32 distances at descriptor offsets 0, 8, 0x10 and 0x18, calls the configuration setter, and returns 1. It has no resume handler. The native run word at 0x0209f0e0 is 0x02080169.

Evidence sources:

- `eu/src/overlays/ov001/calls/AcquireEffectRecordPair.c` and shared `src/ov001/unclassified_helpers/AcquireEffectRecordPair_0207f0d0.c`
- `eu/src/overlays/ov001/calls/FieldObject_TrySpawn.c`
- `eu/src/overlays/ov001/calls/DrawLinkedActorPass.c`
- `eu/src/overlays/ov001/calls/DrawLodSceneObject.c`
- `eu/src/overlays/ov001/calls/FieldObjectClass_Destroy.c` and shared `src/ov001/field_objects/FieldObjectClass_Destroy_0207f3d0.c`

## Active-target command kind

`GetFieldObjectActionCommandKind(object)` reads the object's class pointer at +8 and returns the unsigned byte at class +0x82. The logical input is the field object in native R0. The four-argument leaf C view is a legacy ABI view; only R0 is read. In particular, 0xff returns 255, not -1.

For active target kind 2, both `RefreshFieldMenuPage` and `UpdateActionCommand` switch on this byte. Values 0, 1 and 2 select the corresponding initial menu page/command family. For other values the initial selection remains -1. Constructors provide matching examples in the same class owner: `CreateProjectionViewClass` writes 0, `CreateWorkSlotObjectClass` writes 1, `CreateFieldObjectClassType9` writes 2 and `CreateFieldObjectClassFromDesc` writes 0xff. Unrelated instance fields at offset +0x82 are excluded.

This accessor returns a selector, not a guarantee that a command will be displayed or accepted. The consumers apply eligibility, class hooks and state gates, can suppress the command, and can substitute special command IDs. This block deliberately leaves the full gameplay/UI enum labels unassigned.

Evidence sources:

- `eu/src/overlays/ov001/calls/RefreshFieldMenuPage.c` and shared `src/ov001/field_manager/RefreshFieldMenuPage_0206d248.c`
- `eu/src/overlays/ov001/calls/UpdateActionCommand.c` and shared `src/ov001/unclassified_helpers/UpdateActionCommand_0206d0ac.c`
- `eu/src/overlays/ov001/calls/CreateProjectionViewClass.c`
- `eu/src/overlays/ov001/calls/CreateWorkSlotObjectClass.c`
- `eu/src/overlays/ov001/calls/CreateFieldObjectClassType9.c`
- `eu/src/overlays/ov001/calls/CreateFieldObjectClassFromDesc.c`

## ABI and port boundaries

The two setters have native class-index inputs even though the existing matching source uses no-prototype class lookups and labels those inputs unused. This naming block does not repair or invent parameters. Preserve that native contract when creating a portable interface, and perform any later prototype cleanup as a separately validated change.

The class stores a byte flag index, signed halfword resource index, two fixed-point distances and an unsigned command selector. Their storage widths and signed reads are distinct. There is no new public class layout in this block, and similarly numbered fields in other object families do not inherit these roles.

## Byte-exact validation

All 14 affected official function checks pass. All 16 complete production objects retain allocated bytes/alignment, symbol layouts and relocation targets/types/addends. A fresh gate passes all 108 modules with identical hashes. Bodies, prototypes, numeric constants and shared ROOT implementations are preserved. From `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/SetFieldObjectClassActivationFlagBit.c SetFieldObjectClassActivationFlagBit --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_SetFieldObjectClassActivationFlagBit.c ScriptCmd_SetFieldObjectClassActivationFlagBit --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ConfigureFieldObjectClassLod.c ConfigureFieldObjectClassLod --thumb
python tools/verify_idx.py src/overlays/ov001/auto/GetFieldObjectActionCommandKind.c GetFieldObjectActionCommandKind --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ScriptCmd_ConfigureFieldObjectClassLod.c ScriptCmd_ConfigureFieldObjectClassLod --thumb
bash tools/gate.sh
```

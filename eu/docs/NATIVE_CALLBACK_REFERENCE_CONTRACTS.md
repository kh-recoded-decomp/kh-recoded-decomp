# Native callback, descriptor and registration-key references

These thirteen EU functions now name their actual referenced code or storage
instead of embedding its ROM address as an integer. Their existing 32-bit task,
registration and descriptor interfaces remain unchanged. No parameter, compiler
flag or callback identity is added to influence code generation.

## Reference map

| Function | Native symbolic reference | Kind |
|---|---|---|
| `InitEventTriggerScene` | `WaitForEventTriggerActivation` | Callback/state word |
| `InitModeHandlerContext` | `RunActiveModeHandler` | Callback/state word |
| `InitOverlayObjectSystem` | `func_ov001_020882d4` | Callback/state word |
| `InitScreenFadeContext` | `SelectScreenFadeHandler` | Callback/state word |
| `SelectScreenFadeHandler` | `ScreenFadeInStep`, `ScreenFadeOutStep`, `StepBrightnessFadeIn`, `StepBrightnessFade` | Callback/state word |
| `ShutdownSceneWork` | `RefreshActiveMenuObjects` | Registered callback identity key |
| `SubScene9_Create_02066c80` | `FinishFadeTween` | Callback/state word |
| `SubScene9_Create_02068c0c` | `StartTimerState` | Callback/state word |
| `TryShutdownActorSystem` | `func_ov001_020882d4` | Callback/state word |
| `RefreshTagCallbacksAndSchedule` | `ApplySubBgScroll`, `UpdateMenuScreen` | Callback/state word |
| `FinishAreaSceneLoad` | `gBarGaugeClassDescriptor` | Resident overlay 035 descriptor |
| `InstallResultPanelCallbacks` | `PlaySoundOnPanelEntryMatch` | Widget input callback |
| `DestroyResultsGraphics` | `sOv034_SYSAREAMENU_020c0f10` | Borrowed 16-byte name key |

## Task continuation words

The task runner calls the callback stored at task+0x14 and replaces it only
when the return word is nonzero. Constructors and transitions therefore return
native callback words; zero keeps the current callback. Preserve the actual
function declarations and transition behavior rather than converting these
words to a Boolean result or inventing an unused task argument.

The fade helpers retain their real current return declarations, including the
pointer-to-function forms. This change does not declare one universal host
callback type. Native function words carry the ARM/Thumb state bit and occupy
32 bits; a host port needs the runner's logical function-pointer representation.

## Registration identities and input arguments

ShutdownSceneWork removes entries using RefreshActiveMenuObjects as an identity
key. It does not invoke that function there. RefreshTagCallbacksAndSchedule
registers ApplySubBgScroll and returns UpdateMenuScreen. Its fourth native word
`0xffffffff` selects both channels; it is not a duration.

InstallResultPanelCallbacks registers PlaySoundOnPanelEntryMatch. The dispatcher
passes the focused widget word in R0 and the key mask in R1. The legacy definition's
`selectedEntry` spelling denotes that native widget word, not a list index. Its
actual integer-width declaration is preserved.

DestroyResultsGraphics unregisters the borrowed `char[16]` key at
sOv034_SYSAREAMENU_020c0f10. Its bytes are `SYS_AREA_MENU` followed by three zeros.
Initialization registers that same padded key; destruction uses IRQ mask 1 and
channel 0. Preserve the full native key identity and channel behavior.

## Resident descriptor and source context

FinishAreaSceneLoad uses the existing 24-byte gBarGaugeClassDescriptor from
resident overlay 035 while its child overlay 040 is loaded. The parent/child loader
proof and narrowed relocation bank establish ownership; the same RAM address in
another overlay does not define an interchangeable descriptor.

Eight former EU wrappers now expose their region-specific bodies directly.
They retain the original ROOT integer declarations through
`../include/nitro/types.h`, resolved by the existing EU project include search.
The original shared ROOT/US bodies and both type headers remain unchanged.
This preserves CodeWarrior's original signed/unsigned-long type context without
changing flags or silently substituting the EU int-based declarations. The
other five bodies keep their existing EU header context.

Per-file compiler and ARM/Thumb selections are unchanged, including the default
3.0_patch4 selection for the two SubScene9 constructors. Their only executable
expression changes replace the seventeen proved address literals with the real
symbol references.

## Native-equivalence validation

All thirteen actual-path official checks pass. At exactly seventeen approved
pool words, each new ABS32 reference plus its addend and Thumb state resolves
to the original ROM value. All other instruction/literal bytes, common relocation
targets/types/addends and allocated DATA bytes/alignment remain unchanged.
No source or header in the shared ROOT implementation is modified.

A fresh gate passes all 108 linked modules with identical hashes. The eight
separate metadata repairs also pass fresh checks in this state, so all 21 cases
from the [historical baseline](DATA_NATIVE_RELOCATION_BASELINE.md) now pass their
strict official standalone comparisons. The comparator itself is unchanged.

Run from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/InitEventTriggerScene.c InitEventTriggerScene --thumb
python tools/verify_idx.py src/overlays/ov001/calls/InitModeHandlerContext.c InitModeHandlerContext --thumb
python tools/verify_idx.py src/overlays/ov001/calls/InitOverlayObjectSystem.c InitOverlayObjectSystem --thumb
python tools/verify_idx.py src/overlays/ov001/calls/InitScreenFadeContext.c InitScreenFadeContext --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SelectScreenFadeHandler.c SelectScreenFadeHandler --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ShutdownSceneWork.c ShutdownSceneWork --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SubScene9_Create_02066c80.c SubScene9_Create_02066c80 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SubScene9_Create_02068c0c.c SubScene9_Create_02068c0c --thumb
python tools/verify_idx.py src/overlays/ov001/calls/TryShutdownActorSystem.c TryShutdownActorSystem --thumb
python tools/verify_idx.py src/overlays/ov025/calls/RefreshTagCallbacksAndSchedule.c RefreshTagCallbacksAndSchedule --thumb
python tools/verify_idx.py src/overlays/ov040/calls/FinishAreaSceneLoad.c FinishAreaSceneLoad --thumb
python tools/verify_idx.py src/overlays/ov015/calls/InstallResultPanelCallbacks.c InstallResultPanelCallbacks
python tools/verify_idx.py src/overlays/ov034/calls/DestroyResultsGraphics.c DestroyResultsGraphics --thumb
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```

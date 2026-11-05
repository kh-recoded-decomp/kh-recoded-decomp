# Camera request and gauge entry hooks

This block resolves five previously held EU functions using the callers, sibling implementations, exact argument registers and owner initialization/consumers. All five native bodies are empty. Their names identify the interface/lifecycle slot that invokes them, not newly invented behavior inside the body. No prototype, algorithm or return-register change is included.

## Camera request branches

`ForwardSubModePairA` dispatches the request to standard-camera tracking, the ov043 camera's mode word, or an empty panel implementation. The standard tracking worker explicitly selects behavior by the first argument; mode 3 interprets the second word as a preset index, while modes 4/9 copy a VecFx32 supplied through that word. The script's vector opcode passes mode 4 plus a stack vector; action/projectile callers pass mode 3 plus a scalar. That concrete request role supports `PanelCamera_SetTrackingModeNoop`. It does not establish one shared enum or one pointer-only second parameter for every bank.

`ForwardSubModePairB` dispatches the first mode/request word to the standard preset-mode request or the ov042 collider-registration mode setter. The latter stores current/previous mode and updates collider registration. Its ov043 branch is empty, supporting the general name `Ov043Camera_RequestModeNoop` without claiming a particular preset enum for that bank.

`FinishEventCameraCut` constructs a temporary state record and passes its address through `ForwardSubModeValue`. The standard branch applies the stored view vectors and angle. Its panel branch is empty, supporting `PanelCamera_ApplyViewStateNoop`. The dispatcher source's integer parameter is an erased native pointer view, not evidence of a scalar gameplay value.

Each of those three empty bodies preserves incoming r0. The native forwarder then returns through its epilogue, so the first request word or state pointer propagates. This block does not claim that all outer callers discard that word, does not normalize it to BOOL, and does not expose an owned/fluent pointer result. The existing bytes and caller ABI must remain exact during naming.

## Ov043 initialization hook

`Ov043Camera_InitializationHookNoop` is called inside the real camera initializer, after flags/offset parameters and before default projection/initial pose. It is not the final initialization step and initializes nothing itself. There is no explicit argument setup; native r0 still holds the preceding parameter value. Immediately after the call at EU ov043:0x020bcc32, the instruction at 0x020bcc36 restores the saved camera pointer into r0. Do not invent a camera argument or resource lifetime for this hook.

## Embedded gauge, not spawned effect

The charge-update callback at EU ov059:0x020c81be receives `(actor+0x1524, actor)`. The literal 0x1524 and argument registers are present in ROM; it does not receive the entry-group spawn result. `Actor_Init` initializes that same embedded region through `GaugePanel_Init`, whose body initializes cell sprites and gauge storage. `GaugePanel_Update` takes the same panel/owner pair and tests the actor's mode at +0x934, including mode 2.

The charge updater sets mode 2 before invoking this empty hook, supporting `GaugePanel_EnterChargeMode2Noop`. It does not clear/initialize gauge fields, free resources or signal that a visual effect has completed. Mode 2 retains its numerical identity. The common actor tail overwrites residual r0 at 0x020c8292 before use. A private `effect` array label in the charge source is misleading about this exact owner.

## Identities and sources

Paths below are relative to `eu/` and use the planned names. Shared evidence suffixes retain reference-region addresses; the original identity and mode identify EU.

| Original EU symbol | Descriptive name | Mode / bytes | Planned EU source | Evidence |
|---|---|---|---|---|
| `Ov043Camera_RequestModeNoop` | `Ov043Camera_RequestModeNoop` | THUMB / 0x2 | `src/overlays/ov043/auto/Ov043Camera_RequestModeNoop.c` | `src/ov021/sub_mode/ForwardSubModePairB_020af57c.c` |
| `Ov043Camera_InitializationHookNoop` | `Ov043Camera_InitializationHookNoop` | ARM / 0x4 | `src/overlays/ov043/auto/Ov043Camera_InitializationHookNoop.c` | `src/ov043/camera/InitCameraState_020bcbcc.c` |
| `PanelCamera_SetTrackingModeNoop` | `PanelCamera_SetTrackingModeNoop` | THUMB / 0x2 | `src/overlays/ov044/auto/PanelCamera_SetTrackingModeNoop.c` | `src/ov047/camera/Camera_SetTrackingMode_020c3558.c` |
| `PanelCamera_ApplyViewStateNoop` | `PanelCamera_ApplyViewStateNoop` | ARM / 0x4 | `src/overlays/ov044/auto/PanelCamera_ApplyViewStateNoop.c` | `src/ov047/camera/Camera_ApplyViewState_020c6ca4.c` |
| `GaugePanel_EnterChargeMode2Noop` | `GaugePanel_EnterChargeMode2Noop` | THUMB / 0x2 | `src/overlays/ov059/auto/GaugePanel_EnterChargeMode2Noop.c` | `src/ov059/unclassified_helpers/GaugePanel_Update_020cfd1c.c` |


## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov043/auto/Ov043Camera_RequestModeNoop.c Ov043Camera_RequestModeNoop --thumb
python tools/verify_idx.py src/overlays/ov043/auto/Ov043Camera_InitializationHookNoop.c Ov043Camera_InitializationHookNoop
python tools/verify_idx.py src/overlays/ov044/auto/PanelCamera_SetTrackingModeNoop.c PanelCamera_SetTrackingModeNoop --thumb
python tools/verify_idx.py src/overlays/ov044/auto/PanelCamera_ApplyViewStateNoop.c PanelCamera_ApplyViewStateNoop
python tools/verify_idx.py src/overlays/ov059/auto/GaugePanel_EnterChargeMode2Noop.c GaugePanel_EnterChargeMode2Noop --thumb
bash tools/gate.sh
```

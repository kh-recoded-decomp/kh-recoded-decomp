# Carried launcher emission

`StartCarriedLauncherEmission` (ov030:020bcec0) belongs to the source-kind 19 factory/event/update chain. The factory installs UpdateCarriedLauncher on the same allocation; its event starts the emission state used by that updater.

The event always places and activates the source and resets animation before comparing its signed active count with its signed limit. Only the below-limit path selects mode 1, clears the interval and duration clocks, copies projectile kind/subkind/power, stores the owner-relative placement offset and increments the active count. Reaching the limit therefore does not suppress placement. The byte cleared at source+0x1a0 remains opaque.

UpdateCarriedLauncher advances the clocks and emits through SpawnTiltedProjectile, which consumes those exact descriptor fields. Preserve store widths, signed comparisons, call order and the hidden composite-return placement operation. Individual kind/subkind values are not assigned guessed gameplay meanings.

The existing overlay(30,38) reference metadata remains unchanged. The same RAM locations in overlay 038 lie inside results DATA with different bytes; equal addresses alone do not establish a code binding. The reviewed ov030 factory, event and updater provide the relevant owner evidence.


## Active EU sources

- [StartCarriedLauncherEmission](../src/overlays/ov030/calls/StartCarriedLauncherEmission.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov030/calls/StartCarriedLauncherEmission.c StartCarriedLauncherEmission --thumb
bash tools/gate.sh
```

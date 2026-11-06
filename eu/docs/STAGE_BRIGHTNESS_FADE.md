# Stopping the stage-local brightness fade

`StopStageBrightnessFade` is ov041:0x020bcd78, Thumb, 24 bytes. It stores zero
only to the current StageWork word at +0x52c. The owner is reached through
`gMovieContextState->stageWork` at context +0xb8.

The field is a mode, not the neighboring orb pool. `UpdateSceneFade` uses a
four-word fade record beginning at StageWork +0x528:

| StageWork offset | Proven use |
|---|---|
| +0x528 | Target brightness. |
| +0x52c | Mode: 0 inactive; 1 brightens to 16 then enters 2; 2 decreases to the target. |
| +0x530 | Duration parameter stored by StartSceneFadeIn; no additional unit is assigned here. |
| +0x534 | fx32 rate; the update uses its signed value shifted right by 12. |

`StartSceneFadeIn` supplies the nonzero writer. It sets target 0; unless stage
flags contain 0x20000000, it sets main brightness 10, computes the rate from its
duration input, and writes mode 2. `UpdateSceneFade`, called by
`UpdateStageFrame`, reads this same record and adjusts the main-brightness
setting through `GetMainBrightnessSetting` and `SetBrightnessAndSyncMain`.
Mode 1 adds the rate, clamps at 16, doubles the rate and moves to mode 2. Mode 2
subtracts the rate, clamps to the target and clears the mode on arrival.

The stop helper clears that mode directly. It leaves the current brightness,
target, duration and rate unchanged. It does not finish the effect by restoring
brightness and does not modify the separate global screen-fade object.
`StartStageFadeOut` starts the global screen fade, stops this stage-local loop,
then enters state 0x15. These two effects have distinct owners.

The matched no-input body and its legacy declarations remain unchanged. The
name follows the exact writer/reader/owner chain; no new actor layout or
guessed gameplay purpose is introduced.

Evidence sources:

- `eu/src/overlays/ov041/calls/StartSceneFadeIn.c`
- `eu/src/overlays/ov041/calls/UpdateSceneFade.c`
- `eu/src/overlays/ov041/calls/UpdateStageFrame.c`
- `eu/src/overlays/ov041/calls/StartStageFadeOut.c`
- `eu/src/overlays/ov041/StageWork.h`
- `eu/src/calls/GetMainBrightnessSetting.c`
- `eu/src/calls/SetBrightnessAndSyncMain.c`

Seven original functions were checked in full against the extracted EU ROM;
Ghidra's bank-qualified decompilation independently exposes the same offsets.
Official configured-path verification of the renamed candidate remains an
integration check.


## Active EU sources

- [StopStageBrightnessFade](../src/overlays/ov041/calls/StopStageBrightnessFade.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov041/calls/StopStageBrightnessFade.c StopStageBrightnessFade --thumb
bash tools/gate.sh
```

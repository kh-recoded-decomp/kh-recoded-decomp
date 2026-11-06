# Results-screen handoff to the field session

`PrepareResultsSessionHandoff` is ov001:020648c8, Thumb, 116 bytes, with the unchanged native declaration void(u32 value). Its EU source is src/overlays/ov001/calls/PrepareResultsSessionHandoff.c; the historical ROOT body remains src/ov001/unclassified_helpers/func_ov001_020648c8.c.

CloseResultsScreen and RefreshResultsScreen are the actual callers. They pass the same results outcome word after their existing activity, script and displayed-counter gates. The input handler produces that word through its results and shop choices. No success, retry or next-scene enum is inferred from its numeric values.

Unless session flags at +0x214 contain mask 0x800, the helper loads the difficulty preset and passes the saved stage/entry code pair at saved record +0xda/+0xdc to ConfigureFieldTracks. That helper writes the pending stage/entry fields and requests exit kind 1 when the stage code is nonzero. The handoff then invokes the optional finish hook at session +0x2818 with the signed byte argument at +0x28a4, sets mask 4 in session +0x214 and stores the supplied outcome word at +0x218. If mask 0x800 is set, it instead requests exit kind 2.

The downstream consumer establishes this as session handoff data. ExitSessionAndCommitSave copies the pending stage/entry pair, flag bit 2 and the exact word at +0x218 into gPendingFieldSessionArgs for exit kind 1 before requesting primary scene 2. Exit kind 2 requests primary scene 3 with gSceneHandoffSharedHeader. SetPendingFieldValue only accepts a request while its field is -1, so an existing pending request is preserved.

Preserve every flag, signed halfword and byte load, callback guard, call order and full u32 outcome. This helper prepares the existing handoff; it does not guarantee successful completion, allocate a new request or replace an earlier request. The private sceneId/subSceneId field labels are not a portable scene enum.

RESULTS_TRANSITION_SCROLL5_REVIEW_V1.json records source paths and hashes, numbered writer/consumer evidence, exact script-table words and complete original BK9P NDS function comparisons. Native declarations and bodies remain unchanged.




## Active EU sources

- [PrepareResultsSessionHandoff](../src/overlays/ov001/calls/PrepareResultsSessionHandoff.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/PrepareResultsSessionHandoff.c PrepareResultsSessionHandoff --thumb
bash tools/gate.sh
```

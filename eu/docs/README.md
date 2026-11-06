# EU source and porting documentation

EU ARM9 reconstruction covers all 108 native modules byte-exact. Semantic
names, layouts and host interfaces have their own evidence boundaries.
Begin with the [source-tree map](SOURCE_LAYOUT.md), then the
[porting guide](PORTING_GUIDE.md) and [progress policy](PROGRESS_POLICY.md).

## Systems

| Area | Native entrypoints | Contracts |
|---|---|---|
| Engine, tasks and resource services | Main/autoloads; EU wrappers in `eu/src/calls/` | [Engine services](ENGINE_SERVICE_HELPERS.md), [display lists](DISPLAY_OBJECT_LIST_UPDATE_CONTRACTS.md), [task DATA owners](SCENE_TASK_DATA_OWNERS.md), [file loader](FILE_LOADER.md), [load queue](FILE_LOAD_QUEUE.md) |
| Collision and geometry | Main/ITCM and their configured callers | [Geometry](COLLISION_GEOMETRY.md), [traversal](COLLISION_TRAVERSAL.md), [contact motion](CONTACT_MOTION.md), [sphere/rim sweep](SPHERE_RIM.md), [scene-group callbacks](SCENE_GROUP_CONTACT_CONTRACT.md) |
| Field session, actors and HUD | Common overlay 001 services and their actual scene callers | [Actor/contact ownership](FIELD_ACTOR_TARGET_PERMISSION_CONTRACTS.md), [HUD/menu/minigame](FIELD_HUD_MENU_MINIGAME_POOL_CONTRACTS.md), [resource/VM callbacks](FIELD_VM_CALLBACK_RESOURCE_CONTRACTS.md), [global storage](FIELD_SESSION_GLOBAL_DATA_CONTRACTS.md), [session buffers](SESSION_BUFFERS.md) |
| Scripts and commands | Main VM, overlay 001 and the separate stage-script interfaces | [Field delegates](FIELD_SCRIPT_DELEGATES.md), [stage services](STAGE_SCRIPT_CAMERA_TASK_SERVICE_CONTRACTS.md), [effect action selectors](SCRIPTED_EFFECT_ACTION_SELECTOR_CONTRACT.md), [scene/member consumers](SCENE_MEMBER_TRACKER_SCRIPT_CONTRACTS.md) |
| Field objects | Class owners in overlays 001/007-011; separate pools in 016-020 | [Class callbacks](FIELD_CLASS_CALLBACK_CONTRACTS.md), [kind/pose](FIELD_OBJECT_KIND_POSE_CONTRACTS.md), [pool requests](FIELD_POOL_REQUEST_CONTRACTS.md), [panel/state callbacks](FIELD_STATE_PANEL_CALLBACK_CONTRACTS.md) |
| Scene lifecycle | Individually identified owners in overlays 028-040 | [Field scenes](GROUP_FIELD_SCENE_CONTRACTS.md), [resume](RESUME_MODE_LIFECYCLE_CONTRACTS.md), [results](RESULTS_SCREEN_NATIVE_HELPER_CONTRACTS.md), [area scenes](AREA_SCENE_DEFINITION_FADE_GAUGE_CONTRACTS.md), [continue](CONTINUE_SCENE_LIFECYCLE_CONTRACTS.md) |
| Menus, panels and text | The descriptor's actual overlay bank and task owner | [Navigation/state](MENU_STATE_NAVIGATION_HELPERS.md), [panel/wireless slots](PANEL_WIRELESS_CALLBACK_CONTRACTS.md), [text windows](EVENT2D_PANEL_TEXT_WINDOW_CONTRACTS.md), [menu phases](MENU_PHASE_SUBOVERLAY_TEXT_CONTRACTS.md), [DATA registries](MENU_DATA_REGISTRIES_DESCRIPTORS.md) |
| Wireless | Overlay 015 helper, menu, board and connection owners | [Wireless helpers](WIRELESS_MENU_HELPER_CONTRACTS.md), [native WM boundary](library/sdk_wh.md), [tables and state storage](WIRELESS_TABLES_STATE_STORAGE.md) |
| Movie and captions | The movie scene and decoder/caption owners have separate lifetimes | [Caption/decoder contracts](MOVIE_CAPTION_DECODER_CONTRACTS.md) |
| Cameras and model animation | The configured scene/camera bank and its callers | [Camera helpers](CAMERA_HELPER_CONTRACTS.md), [request hooks](CAMERA_REQUEST_GAUGE_HOOK_CONTRACTS.md), [saved camera](SAVED_CAMERA.md), [animation tracks](MODEL_ANIMATION_TRACKS.md), [model ownership](MODEL_RESOURCE_OWNERSHIP.md) |
| Libraries and platform adapters | Native library entrypoints and verified models | [Library boundaries](PORTING_GUIDE.md#library-boundaries), [portable references](../portable/README.md) |

Source locations in the table describe entrypoints, not a promise that each
entire overlay implements only one system. Follow the source map for actual
build ownership and regional aliases. [SYMBOL_EVIDENCE.md](SYMBOL_EVIDENCE.md)
links the complete sequence of documented naming blocks.

## Native data maps

- [Early contexts, task classes and constants](EARLY_CONTEXT_CONSTANT_DATA.md).
- [Wireless scan and board storage](WIRELESS_SCAN_BOARD_STORAGE.md).
- [Pool kind-4 trigger callbacks](POOL_KIND4_TRIGGER_CALLBACKS.md).

- [Menu Descriptor Record Tables](MENU_DESCRIPTOR_RECORD_TABLES.md).
- [Late Scene Global Storage](LATE_SCENE_GLOBAL_STORAGE.md).
- [Gauge Actor Effect Data](GAUGE_ACTOR_EFFECT_DATA.md).

- [Menu Layout Template Data](MENU_LAYOUT_TEMPLATE_DATA.md).
- [Stage Camera Native Storage](STAGE_CAMERA_NATIVE_STORAGE.md).
- [Overlay058 Scene Native Storage](OVERLAY058_SCENE_NATIVE_STORAGE.md).

- [Actor Scene Parameter Data](ACTOR_SCENE_PARAMETER_DATA.md).
- [Matrix Draw Refresh Data](MATRIX_DRAW_REFRESH_DATA.md).
- [Slot Item Native Template Data](SLOT_ITEM_NATIVE_TEMPLATE_DATA.md).

## Unresolved function contracts

At the `ad0a8778153f72218e4bdad3a5cec1bd8e2a7470` naming checkpoint,
100 matched C functions retain numeric names. Every one has a mechanical
contract, a specific semantic blocker and a next useful proof:

- [73 common field functions](EU_PENDING_FIELD_FUNCTIONS.md).
- [18 engine, script and scene functions](EU_PENDING_ENGINE_SCENE_FUNCTIONS.md).
- [9 background/camera/other callbacks](EU_PENDING_CALLBACK_FUNCTIONS.md).

These are limits on recovered meaning. Full-module matching and reconstructed
DATA coverage are separate measurements. The
[standalone relocation discrepancies](DATA_NATIVE_RELOCATION_BASELINE.md)
also have their original-versus-renamed controls and exact offsets documented.

## Reading native types for a port

Use field owners, constructor/writer evidence, callback registration and real
consumers together. A native `u32` can carry an encoded DS address; an interior
label can lie inside a larger allocation; an empty callback can preserve a
residual return register. Preserve documented rounding, overflow, raw masks,
borrowed lifetimes and partial clears before selecting host types.

Shared headers should collect layouts proved for this game. Per-function
partial views and the Days reference remain evidence to reconcile, rather
than automatic host declarations. The [porting guide](PORTING_GUIDE.md)
describes the platform adapters and validation expected at handoff.

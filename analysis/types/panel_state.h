/* BK9E: observed overlay88 settings records. Their individual setting meanings
 * remain unconfirmed; no specific menu or collectible type is assigned. */
typedef struct Overlay088Pair { short first, second; } Overlay088Pair;
typedef struct Overlay088PairSettings { Overlay088Pair entries[4]; } Overlay088PairSettings;
typedef struct Overlay088GridSettings { int resource; int unknown[3]; } Overlay088GridSettings;
typedef int Overlay088GridEntryIds[6][3];

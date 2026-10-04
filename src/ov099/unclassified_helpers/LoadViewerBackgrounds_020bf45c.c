#include "nitro/types.h"

typedef struct BgGraphicsData {
  void *screen;
  int *character;
  int *palette;
} BgGraphicsData;

typedef struct BgResource {
  void *file;
  BgGraphicsData data;
} BgResource;

typedef struct ViewerWork {
  u8 pad_000[0x300];
  u32 archiveA;
  u32 archiveB;
  u8 pad_308[0x42c - 0x308];
  BgResource mainBg;
  BgResource subBg;
  BgResource mainExtraChars;
} ViewerWork;

extern void *func_0202c478(u32 fileId, u32 heap);
extern void GetBgDataFromArchive_0202b554(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex, int paletteIndex);
extern void DispatchByPartType_0202b4c0(int bg, void *screen, int *character, int *palette, int priority, int flags);
extern void Bg_LoadPaletteForScreen_0202b3f0(int bg, int *palette, void *screen, int offset, int size);
extern void Gfx_EnqueueTableCmdAt14_0202b448(int bg, int *character, int offset, int size);

#define ARCHIVE_FILE_ID(archive) ((((archive) + 0x8000) & 0xfffffc) << 7)

void LoadViewerBackgrounds_020bf45c(ViewerWork *work) {
  BgResource *res;

  res = &work->mainBg;
  res->file = func_0202c478(ARCHIVE_FILE_ID(work->archiveA) | 0x80000002, 0xe);
  GetBgDataFromArchive_0202b554(&res->data, res->file, 0, 0, 0);
  DispatchByPartType_0202b4c0(2, res->data.screen, res->data.character, res->data.palette, 0x1f, 0);
  Bg_LoadPaletteForScreen_0202b3f0(0, res->data.palette, res->data.screen, 0x200, res->data.palette[2]);
  res = &work->mainExtraChars;
  res->file = func_0202c478(ARCHIVE_FILE_ID(work->archiveB) | 0x80000000, 0xe);
  GetBgDataFromArchive_0202b554(&res->data, res->file, 0, 0, 0);
  Gfx_EnqueueTableCmdAt14_0202b448(2, res->data.character, 0xc00, res->data.character[4]);
  res = &work->subBg;
  res->file = func_0202c478(ARCHIVE_FILE_ID(work->archiveA) | 0x80000000, 0xe);
  GetBgDataFromArchive_0202b554(&res->data, res->file, 0, 0, 0);
  DispatchByPartType_0202b4c0(6, res->data.screen, res->data.character, res->data.palette, 0x1e, 0);
}

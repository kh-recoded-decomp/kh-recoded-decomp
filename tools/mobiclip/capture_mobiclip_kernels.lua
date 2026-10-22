-- One-shot DeSmuME capture of the hand-written MobiClip kernels in ov022 (EU, BK9P).
--
-- The game reaches only some of them on its own: the player always blits in display mode 0 (no
-- deblocking post-filter) and every movie carries IMA ADPCM audio (coding 3), so neither FastAudio
-- (coding 2) nor the coding-1 speech decoder ever runs. This script records one real call of the
-- colour converter and forces the other paths, each once, while a movie plays:
--
--   * deblock: at the blit call (0x020a9368) the display mode r3 is set to 2 for one frame, so
--     renderDecodedMovieFrame allocates its planes and runs the filter at 0x020b715c (both edge
--     directions). Only that frame's picture is the filtered copy.
--   * FastAudio: on one ADPCM entry that does not start a frame, the stream dispatcher
--     (0x020a9f88) is made to take coding 2 for that call.
--   * coding 1: on three later entries the dispatcher takes coding 1. At the decoder's entry
--     (0x020aac54) the channel record (all but its stream and output pointers) and the frame bytes
--     at the stream cursor are replaced by the inputs `mobiclip_audio.py --inputs` wrote: a
--     restart frame, a predicted frame and a silent-start frame.
--   In both audio cases the channel record and the stream bytes are put back afterwards and the
--   cursor is advanced by the 0x80 bytes the ADPCM block would have used, so the stream stays in
--   sync; one 256-sample block of that channel is noise.
--
-- First run, from the repository root:
--     python tools/mobiclip/mobiclip_audio.py --inputs eu/build/mobiclip/kernel_captures
-- Then load this script while the game runs (Tools > Lua Scripting > New Lua Script Window), let a
-- movie play and wait for "all captures saved". Replay with tools/mobiclip/verify_mobiclip.py.

local SCRIPT = debug.getinfo(1, "S").source:gsub("^@", ""):gsub("\\", "/")
local REPO = SCRIPT:gsub("/tools/mobiclip/[^/]*$", "")
local ROOT = REPO .. "/eu/build/mobiclip/kernel_captures"

local SKIP_BLITS = 30            -- frames shown before the deblock and colour captures
local SKIP_AUDIO = 40            -- eligible audio entries before the FastAudio capture

local BLIT_CALL = 0x020a9368     -- bl renderDecodedMovieFrame; r3 = display mode
local COLOUR = 0x020aa300        -- MobiClip_BlitRows
local DEBLOCK = 0x020b715c       -- MobiClip_DeblockFrame
local AUDIO_DISPATCH = 0x020a9f88 -- processMovieStreamChunk
local TRANSFORM = 0x020aac54     -- MobiClip_AudioTransformDecode
local FASTAUDIO = 0x020ab614     -- MobiClip_FastAudioDecode
local CHANNEL_STRIDE = 0x14f8
local FASTAUDIO_BYTES = 0x1d0
local TRANSFORM_FRAMES = 3
local FRAME_BYTES = 20

local blits = 0
local deblock_state = "waiting"  -- waiting -> forced -> done
local colour_state = "waiting"
local audio_entries = 0
local audio_queue = {"fastaudio"}
for i = 0, TRANSFORM_FRAMES - 1 do
    audio_queue[#audio_queue + 1] = i
end
local audio = nil                -- the forced entry in progress
local pending = 2 + 1 + TRANSFORM_FRAMES

local function unsigned(value)
    if value < 0 then
        return value + 4294967296
    end
    return value
end

local function reg(name)
    return unsigned(memory.getregister("arm9." .. name))
end

local function u32(address)
    return unsigned(memory.readdword(address))
end

local function read_bytes(address, length)
    local out = {}
    local bytes = memory.readbyterange(address, length)
    for i = 1, length do
        out[i] = bytes[i] or 0
    end
    return out
end

local function write_bytes(address, bytes, first, last)
    for i = first, last do
        memory.writebyte(address + i - 1, bytes[i])
    end
end

local function write_range(path, address, length)
    local file = assert(io.open(path, "wb"), "cannot write " .. path .. " (create the directory)")
    local offset = 0
    while offset < length do
        local count = math.min(1024, length - offset)
        local bytes = memory.readbyterange(address + offset, count)
        local chars = {}
        for i = 1, count do
            chars[i] = string.char(bytes[i] or 0)
        end
        file:write(table.concat(chars))
        offset = offset + count
    end
    file:close()
end

local function read_file(path)
    local file = assert(io.open(path, "rb"), "missing " .. path .. " (run mobiclip_audio.py --inputs)")
    local data = file:read("*a")
    file:close()
    local out = {}
    for i = 1, #data do
        out[i] = data:byte(i)
    end
    return out
end

local function write_json(path, fields)
    local file = assert(io.open(path, "w"))
    local parts = {}
    for _, pair in ipairs(fields) do
        local value = pair[2]
        if type(value) == "table" then
            value = value.json                                      -- already JSON
        elseif type(value) == "string" then
            value = '"' .. value .. '"'
        end
        parts[#parts + 1] = string.format('  "%s": %s', pair[1], tostring(value))
    end
    file:write("{\n" .. table.concat(parts, ",\n") .. "\n}\n")
    file:close()
end

local function saved(what)
    pending = pending - 1
    print("capture_mobiclip_kernels: saved " .. what .. (pending == 0 and " -- all captures saved" or ""))
end

-- colour converter (a real call) ---------------------------------------------------------------

local colour = nil

local function finish_colour()
    memory.registerexec(colour.return_address, 2, nil)
    write_range(ROOT .. "/colour_rgb555.bin", colour.dest, colour.stride * colour.height)
    write_json(ROOT .. "/colour.json", {
        {"kind", "ycocg_to_rgb555"},
        {"entry", string.format("0x%08x", COLOUR)},
        {"lumaAddress", string.format("0x%08x", colour.luma)},
        {"chromaAddress", string.format("0x%08x", colour.chroma)},
        {"destinationAddress", string.format("0x%08x", colour.dest)},
        {"width", colour.width},
        {"height", colour.height},
        {"lumaStride", 256},
        {"chromaStride", 256},
        {"destinationStrideBytes", colour.stride},
        {"files", {json = '{"luma": "colour_luma.bin", "chroma": "colour_chroma.bin", "rgb555": "colour_rgb555.bin"}'}},
    })
    colour_state = "done"
    saved("colour converter")
end

local function begin_colour()
    if colour_state ~= "waiting" or blits < SKIP_BLITS or deblock_state == "forced" then
        return
    end
    local view = reg("r0")
    colour = {
        luma = u32(view), chroma = u32(view + 4), dest = u32(view + 8), stride = u32(view + 12),
        width = u32(view + 16), height = u32(view + 20), return_address = reg("r14"),
    }
    write_range(ROOT .. "/colour_luma.bin", colour.luma, 0x100 * colour.height)
    write_range(ROOT .. "/colour_chroma.bin", colour.chroma, 0x100 * math.floor(colour.height / 2))
    colour_state = "running"
    memory.registerexec(colour.return_address, 2, finish_colour)
end

-- deblocking post-filter -------------------------------------------------------------------------

local deblock = nil

local function finish_deblock()
    memory.registerexec(deblock.return_address, 2, nil)
    local rows = deblock.height
    write_range(ROOT .. "/deblock_after_luma.bin", deblock.dst_luma, 0x100 * rows)
    write_range(ROOT .. "/deblock_after_chroma.bin", deblock.dst_chroma, 0x100 * math.floor(rows / 2))
    write_json(ROOT .. "/deblock.json", {
        {"kernel", "deblock"},
        {"width", deblock.width},
        {"height", deblock.height},
        {"quantiser", deblock.qp},
        {"vertical_only", deblock.vertical_only},
        {"before_luma", "deblock_before_luma.bin"},
        {"before_chroma", "deblock_before_chroma.bin"},
        {"clip_table", "deblock_clip_table.bin"},
        {"after_luma", "deblock_after_luma.bin"},
        {"after_chroma", "deblock_after_chroma.bin"},
    })
    deblock_state = "done"
    saved("deblock")
end

local function begin_deblock()
    if deblock_state ~= "forced" or deblock then
        return
    end
    local req = reg("r0")
    deblock = {
        src_luma = u32(req + 0x00), src_chroma = u32(req + 0x04),
        dst_luma = u32(req + 0x08), dst_chroma = u32(req + 0x0c),
        width = u32(req + 0x10), height = u32(req + 0x14), qp = u32(req + 0x18),
        table = u32(req + 0x1c), vertical_only = u32(req + 0x20), return_address = reg("r14"),
    }
    local rows = deblock.height
    write_range(ROOT .. "/deblock_before_luma.bin", deblock.src_luma, 0x100 * rows)
    write_range(ROOT .. "/deblock_before_chroma.bin", deblock.src_chroma, 0x100 * math.floor(rows / 2))
    write_range(ROOT .. "/deblock_clip_table.bin", deblock.table, 0x180)
    memory.registerexec(deblock.return_address, 2, finish_deblock)
end

local function on_blit_call()
    blits = blits + 1
    if deblock_state == "waiting" and colour_state == "done" then
        memory.setregister("arm9.r3", 2)
        deblock_state = "forced"
    end
end

-- forced audio entries ---------------------------------------------------------------------------

local function finish_fastaudio()
    memory.registerexec(audio.kernel_return, 2, nil)
    write_range(ROOT .. "/fastaudio_after_channel.bin", audio.chan, FASTAUDIO_BYTES)
    write_range(ROOT .. "/fastaudio_output.bin", audio.output, 0x200)
    write_json(ROOT .. "/fastaudio.json", {
        {"kernel", "fastaudio"},
        {"stride", 2},
        {"block", "fastaudio_block.bin"},
        {"before_channel", "fastaudio_before_channel.bin"},
        {"after_channel", "fastaudio_after_channel.bin"},
        {"output", "fastaudio_output.bin"},
    })
    saved("FastAudio")
end

local function begin_fastaudio()
    if not audio or audio.job ~= "fastaudio" or audio.kernel_return or reg("r0") ~= audio.chan then
        return
    end
    audio.output = u32(audio.chan + 4)
    audio.kernel_return = reg("r14")
    write_range(ROOT .. "/fastaudio_before_channel.bin", audio.chan, FASTAUDIO_BYTES)
    write_range(ROOT .. "/fastaudio_block.bin", u32(audio.chan), 0x28)
    memory.registerexec(audio.kernel_return, 2, finish_fastaudio)
end

local function finish_transform()
    memory.registerexec(audio.kernel_return, 2, nil)
    local stem = ROOT .. "/audio_transform_" .. audio.job
    local name = "audio_transform_" .. audio.job
    write_range(stem .. "_after_channel.bin", audio.chan, CHANNEL_STRIDE)
    write_range(stem .. "_output.bin", audio.output, 128 * 2)
    write_json(stem .. ".json", {
        {"kernel", "audio_transform"},
        {"channel", string.format("0x%08x", audio.chan)},
        {"stride", 2},
        {"consumed", reg("r0")},
        {"before_channel", name .. "_before_channel.bin"},
        {"frame", name .. "_frame.bin"},
        {"after_channel", name .. "_after_channel.bin"},
        {"output", name .. "_output.bin"},
    })
    saved("coding-1 frame " .. audio.job)
end

local function begin_transform()
    if not audio or type(audio.job) ~= "number" or audio.kernel_return or reg("r0") ~= audio.chan then
        return
    end
    local input = read_file(ROOT .. "/audio_transform_input_" .. audio.job .. ".bin")
    local stream = u32(audio.chan)
    audio.output = u32(audio.chan + 4)
    audio.stream = stream
    audio.stream_saved = read_bytes(stream, FRAME_BYTES)
    write_bytes(audio.chan, input, 9, CHANNEL_STRIDE - 4)          -- keep +0 (stream), +4 (output)
    memory.writedword(audio.chan + CHANNEL_STRIDE - 4, 2)           -- output stride: halfwords
    for i = 1, FRAME_BYTES do
        memory.writebyte(stream + i - 1, input[CHANNEL_STRIDE + i])
    end
    local stem = ROOT .. "/audio_transform_" .. audio.job
    write_range(stem .. "_before_channel.bin", audio.chan, CHANNEL_STRIDE)
    write_range(stem .. "_frame.bin", stream, FRAME_BYTES)
    audio.kernel_return = reg("r14")
    memory.registerexec(audio.kernel_return, 2, finish_transform)
end

local function restore_audio()
    memory.registerexec(audio.dispatch_return, 2, nil)
    memory.writeword(audio.ctx + 0x1c, 3)
    write_bytes(audio.chan, audio.saved, 1, #audio.saved)
    if audio.stream_saved then
        write_bytes(audio.stream, audio.stream_saved, 1, FRAME_BYTES)
    end
    memory.writedword(audio.cursor_ptr, audio.cursor + 0x80)
    audio = nil
end

local function on_audio_dispatch()
    if audio or #audio_queue == 0 then
        return
    end
    local ctx = reg("r0")
    if memory.readword(ctx + 0x1c) ~= 3 or u32(ctx + 0xcc) == u32(ctx + 0xc8) or u32(ctx + 0xa4) ~= 0 then
        return
    end
    audio_entries = audio_entries + 1
    if audio_entries < SKIP_AUDIO or audio_entries % 4 ~= 0 then
        return
    end
    local job = table.remove(audio_queue, 1)
    local chan = u32(ctx + 0x58) + u32(ctx + 0xd0) * CHANNEL_STRIDE
    local cursor_ptr = u32(ctx + 0x34)
    audio = {
        job = job, ctx = ctx, chan = chan, saved = read_bytes(chan, CHANNEL_STRIDE),
        cursor_ptr = cursor_ptr, cursor = u32(cursor_ptr), dispatch_return = reg("r14"),
    }
    if job == "fastaudio" then
        memory.writeword(ctx + 0x1c, 2)
        memory.writedword(chan + 0x1cc, 2)
    else
        memory.writeword(ctx + 0x1c, 1)
    end
    memory.registerexec(audio.dispatch_return, 2, restore_audio)
end

memory.registerexec(BLIT_CALL, 2, on_blit_call)
memory.registerexec(COLOUR, 2, begin_colour)
memory.registerexec(DEBLOCK, 2, begin_deblock)
memory.registerexec(AUDIO_DISPATCH, 2, on_audio_dispatch)
memory.registerexec(FASTAUDIO, 2, begin_fastaudio)
memory.registerexec(TRANSFORM, 2, begin_transform)

print("capture_mobiclip_kernels: armed, output " .. ROOT)
print("  play any movie and wait for 'all captures saved'")

while true do
    emu.frameadvance()
end

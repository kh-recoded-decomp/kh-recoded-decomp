// Export decompiler views for a target list. Pseudocode is a starting point, never a match.
// @category KHRecoded
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.*;
import com.google.gson.*;
import java.nio.file.*;

public class DecompileTargetsBK9E extends GhidraScript {
    @Override public void run() throws Exception {
        String[] args=getScriptArgs();
        Path root=Paths.get(args[0]);
        JsonArray targets=JsonParser.parseString(Files.readString(root.resolve("build/ghidra/decompile_targets.json"))).getAsJsonArray();
        Path output=root.resolve(args.length>1?args[1]:"build/ghidra/decomp");
        DecompInterface decompiler=new DecompInterface();
        DecompileOptions options=new DecompileOptions();options.setRespectReadOnly(true);decompiler.setOptions(options);
        decompiler.openProgram(currentProgram);
        Memory memory=currentProgram.getMemory();
        int written=0,failed=0;
        for(JsonElement item:targets) {
            JsonObject target=item.getAsJsonObject();
            String module=target.get("module").getAsString(),symbol=target.get("symbol").getAsString();
            Path file=output.resolve(module).resolve(symbol+".c");
            if(Files.exists(file))continue;
            Files.createDirectories(file.getParent());
            AddressSpace space=currentProgram.getAddressFactory().getDefaultAddressSpace();
            if(module.startsWith("ov")) {
                MemoryBlock block=memory.getBlock(module);
                if(block==null){failed++;continue;}
                space=block.getStart().getAddressSpace();
            }
            Address address=space.getAddress(target.get("address").getAsLong());
            Function function=getFunctionAt(address);
            if(function==null){failed++;continue;}
            DecompileResults result=decompiler.decompileFunction(function,45,monitor);
            if(!result.decompileCompleted()){failed++;Files.writeString(file,"/* decompile failed: "+result.getErrorMessage()+" */\n");continue;}
            Files.writeString(file,result.getDecompiledFunction().getC());
            if(++written%500==0)println("decompiled "+written);
        }
        decompiler.dispose();
        println("Decompiled "+written+" functions; "+failed+" failed");
    }
}

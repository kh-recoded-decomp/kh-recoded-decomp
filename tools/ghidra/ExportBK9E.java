// Export local decompiler views and caller evidence without treating pseudocode as a match.
// @category KHRecoded
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.pcode.*;
import java.util.*;
import com.google.gson.*;
import java.nio.file.*;

public class ExportBK9E extends GhidraScript {
    @Override public void run() throws Exception {
        String[] args=getScriptArgs();if(!args[1].equals("arm9"))return;
        Path root=Paths.get(args[0]),output=root.resolve("build/ghidra/decompiled");Files.createDirectories(output);
        JsonObject knowledge=JsonParser.parseString(Files.readString(root.resolve("analysis/actor_model.json"))).getAsJsonObject();
        JsonArray results=new JsonArray();DecompInterface decompiler=new DecompInterface();
        DecompileOptions options=new DecompileOptions();options.setRespectReadOnly(true);decompiler.setOptions(options);
        decompiler.openProgram(currentProgram);
        for(JsonElement item:knowledge.getAsJsonArray("functions")) {
            JsonObject entry=item.getAsJsonObject();String module=entry.get("module").getAsString();
            AddressSpace space=module.startsWith("ov")?currentProgram.getAddressFactory().getAddressSpace(module):currentProgram.getAddressFactory().getDefaultAddressSpace();
            Address address=space.getAddress(Long.decode(entry.get("address").getAsString()));Function function=getFunctionAt(address);
            DecompileResults result=decompiler.decompileFunction(function,60,monitor);
            if(result.decompileCompleted() && entry.has("local_names")) {
                JsonObject names=entry.getAsJsonObject("local_names");boolean changed=false;
                Iterator<HighSymbol> symbols=result.getHighFunction().getLocalSymbolMap().getSymbols();
                while(symbols.hasNext()) {
                    HighSymbol symbol=symbols.next();
                    if(names.has(symbol.getName())) {
                        HighFunctionDBUtil.updateDBVariable(symbol,names.get(symbol.getName()).getAsString(),null,SourceType.USER_DEFINED);changed=true;
                    }
                }
                if(changed) {decompiler.flushCache();result=decompiler.decompileFunction(function,60,monitor);}
            }
            JsonObject record=new JsonObject();record.addProperty("module",module);record.addProperty("address",address.toString());record.addProperty("name",function.getName());record.addProperty("decompiled",result.decompileCompleted());
            record.addProperty("prototype",function.getSignature().getPrototypeString());
            if(result.decompileCompleted())Files.writeString(output.resolve(module+"_"+function.getName()+".c"),result.getDecompiledFunction().getC());
            else record.addProperty("error",result.getErrorMessage());
            JsonArray callers=new JsonArray();ReferenceIterator references=currentProgram.getReferenceManager().getReferencesTo(address);
            while(references.hasNext()) {Reference reference=references.next();if(reference.getReferenceType().isCall())callers.add(reference.getFromAddress().toString());}
            record.add("call_sites",callers);results.add(record);
        }
        decompiler.dispose();Files.writeString(root.resolve("build/ghidra/actor-model-export.json"),new GsonBuilder().setPrettyPrinting().create().toJson(results));
        println("Exported "+results.size()+" typed decompiler views. These are analysis, not byte-match claims.");
    }
}

// Apply prototypes and names from verified C matches (build/ghidra/prototypes.json).
// @category KHRecoded
import ghidra.app.script.GhidraScript;
import ghidra.app.cmd.function.ApplyFunctionSignatureCmd;
import ghidra.app.util.cparser.C.CParser;
import ghidra.program.model.address.*;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.symbol.*;
import com.google.gson.*;
import java.nio.file.*;

public class ApplyMatchedPrototypesBK9E extends GhidraScript {
    @Override public void run() throws Exception {
        Path root=Paths.get(getScriptArgs()[0]);
        JsonArray rows=JsonParser.parseString(Files.readString(root.resolve("build/ghidra/prototypes.json"))).getAsJsonArray();
        Memory memory=currentProgram.getMemory();
        int applied=0,failed=0;
        for(JsonElement item:rows) {
            JsonObject row=item.getAsJsonObject();
            String module=row.get("module").getAsString();
            AddressSpace space=currentProgram.getAddressFactory().getDefaultAddressSpace();
            if(module.startsWith("ov")) {
                MemoryBlock block=memory.getBlock(module);
                if(block==null){failed++;continue;}
                space=block.getStart().getAddressSpace();
            }
            Function function=getFunctionAt(space.getAddress(row.get("address").getAsLong()));
            if(function==null){failed++;continue;}
            try {
                CParser parser=new CParser(currentProgram.getDataTypeManager(),false,null);
                DataType parsed=parser.parse(row.get("prototype").getAsString()+";");
                if(!(parsed instanceof FunctionDefinition)){failed++;continue;}
                ApplyFunctionSignatureCmd command=new ApplyFunctionSignatureCmd(function.getEntryPoint(),(FunctionDefinition)parsed,SourceType.USER_DEFINED,true,true);
                if(!command.applyTo(currentProgram,monitor)){failed++;continue;}
                function.setName(row.get("name").getAsString(),SourceType.USER_DEFINED);
                applied++;
            } catch(Exception error) {failed++;}
        }
        println("Applied "+applied+" matched prototypes; "+failed+" failed");
    }
}

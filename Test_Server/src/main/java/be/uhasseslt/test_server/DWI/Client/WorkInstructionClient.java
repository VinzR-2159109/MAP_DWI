package be.uhasseslt.test_server.DWI.Client;

import be.uhasseslt.test_server.DWI.Model.Workinstruction.WorkInstruction;
import be.uhasseslt.test_server.Values.Id;

import java.util.List;

public interface WorkInstructionClient<T extends WorkInstruction> {
    List<T> getAllWorkInstructions();
    T getWorkInstructionById(Id id);
}

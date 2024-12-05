package be.uhasseslt.test_server.DWI.Model.Workinstruction;

import lombok.Data;

import java.net.URI;
import java.util.List;

@Data
public class WorkInstructionResponse<T extends WorkInstruction> {
    private String object;
    private URI url;
    private String next;

    private List<T> data;
}
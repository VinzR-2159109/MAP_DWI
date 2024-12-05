package be.uhasseslt.test_server.DWI.Model.Workinstruction;

import be.uhasseslt.test_server.Values.Description;
import be.uhasseslt.test_server.Values.Id;
import be.uhasseslt.test_server.Values.Name;
import lombok.Data;

@Data
public class WorkInstruction {
    private String object;
    private Id id;
    private Name name;
    private Description description;
}
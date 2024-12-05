package be.uhasseslt.test_server;

import be.uhasseslt.test_server.DWI.Client.AzumutaWorkInstructionClient;
import be.uhasseslt.test_server.DWI.Model.Workinstruction.AzumutaWorkInstruction;
import be.uhasseslt.test_server.Values.Description;
import be.uhasseslt.test_server.Values.Id;
import be.uhasseslt.test_server.Values.Name;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.HttpMethod;
import org.springframework.http.MediaType;
import org.springframework.test.web.client.MockRestServiceServer;
import org.springframework.web.client.RestTemplate;

import java.util.List;

import static org.assertj.core.api.Assertions.assertThat;
import static org.springframework.test.web.client.match.MockRestRequestMatchers.*;
import static org.springframework.test.web.client.response.MockRestResponseCreators.*;

@SpringBootTest
public class AzumutaWorkInstructionClientTest {

    @Autowired
    private AzumutaWorkInstructionClient client;

    @Autowired
    private RestTemplate restTemplate;

    private MockRestServiceServer mockServer;

    @BeforeEach
    public void setUp() {
        // Create a mock server to simulate API responses
        mockServer = MockRestServiceServer.createServer(restTemplate);
    }

    @Test
    public void testGetAllWorkInstructions() {
        // Mock API response
        String responseJson = """
            {
                "data": [
                    {
                        "object": "work-instruction",
                        "id": "1",
                        "name": "Instruction 1",
                        "description": {
                            "en": "This is a description"
                        },
                        "thumbnail": {
                            "object": "image",
                            "smallUrl": "http://example.com/small.jpg",
                            "mediumUrl": "http://example.com/medium.jpg",
                            "originalUrl": "http://example.com/original.jpg"
                        },
                        "isAudit": true,
                        "latestOfficialVersion": 1
                    }
                ]
            }
        """;

        mockServer.expect(requestTo("/api/v1/workinstructions"))
                .andExpect(method(HttpMethod.GET))
                .andRespond(withSuccess(responseJson, MediaType.APPLICATION_JSON));

        // Call the client
        List<AzumutaWorkInstruction> instructions = client.getAllWorkInstructions();

        // Verify the result
        assertThat(instructions).isNotEmpty();
        assertThat(instructions.getFirst().getId().getValue()).isEqualTo("1");

        Name name = instructions.getFirst().getName();
        assertThat(name.getNames().get(Name.Language.EN)).isEqualTo("Instruction 1");

        assertThat(instructions.getFirst().getDescription().getDescriptionInLanguage(Description.Language.EN)).isEqualTo("This is a description");
    }

    @Test
    public void testGetWorkInstructionById() {
        // Mock API response
        String responseJson = """
            {
                "object": "work-instruction",
                "id": "1",
                "name": "Instruction 1",
                "description": {
                    "en": "This is a description"
                },
                "thumbnail": {
                    "object": "image",
                    "smallUrl": "http://example.com/small.jpg",
                    "mediumUrl": "http://example.com/medium.jpg",
                    "originalUrl": "http://example.com/original.jpg"
                },
                "isAudit": true,
                "latestOfficialVersion": 1
            }
        """;

        mockServer.expect(requestTo("/api/v1/workinstructions/1"))
                .andExpect(method(HttpMethod.GET))
                .andRespond(withSuccess(responseJson, MediaType.APPLICATION_JSON));

        // Call the client
        AzumutaWorkInstruction instruction = client.getWorkInstructionById(new Id("1"));

        // Verify the result
        assertThat(instruction).isNotNull();
        assertThat(instruction.getId().getValue()).isEqualTo("1");
        Name name = instruction.getName();
        assertThat(name.getNames().get(Name.Language.EN)).isEqualTo("Instruction 1");
    }
}

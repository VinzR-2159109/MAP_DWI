package be.uhasseslt.test_server.DWI.Client;

import be.uhasseslt.test_server.DWI.Model.Workinstruction.AzumutaWorkInstruction;
import be.uhasseslt.test_server.DWI.Model.Workinstruction.WorkInstructionResponse;
import be.uhasseslt.test_server.Values.Id;
import lombok.RequiredArgsConstructor;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.core.ParameterizedTypeReference;
import org.springframework.http.HttpMethod;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;

import java.util.List;

@Service
@RequiredArgsConstructor
public class AzumutaWorkInstructionClient implements WorkInstructionClient<AzumutaWorkInstruction> {

    private final RestTemplate restTemplate;

    @Value("/api/v1")
    private String baseUrl;

    @Override
    public List<AzumutaWorkInstruction> getAllWorkInstructions() {
        String url = baseUrl + "/workinstructions";

        //Java's type system does not handle generics well at runtime:
        ResponseEntity<WorkInstructionResponse<AzumutaWorkInstruction>> responseEntity = restTemplate.exchange(
                url,
                HttpMethod.GET,
                null,
                new ParameterizedTypeReference<>() {}
        );

        WorkInstructionResponse<AzumutaWorkInstruction> response = responseEntity.getBody();

        if (response != null && response.getData() != null) {
            return response.getData();
        } else {
            return List.of();
        }
    }

    @Override
    public AzumutaWorkInstruction getWorkInstructionById(Id id) {
        String url = baseUrl + "/workinstructions/" + id.getValue();

        return restTemplate.getForObject(url, AzumutaWorkInstruction.class);
    }
}

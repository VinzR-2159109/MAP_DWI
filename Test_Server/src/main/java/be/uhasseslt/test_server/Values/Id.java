package be.uhasseslt.test_server.Values;

import com.fasterxml.jackson.annotation.JsonCreator;
import com.fasterxml.jackson.annotation.JsonValue;
import lombok.Value;

@Value
public class Id {
    @JsonValue
    String value;

    @JsonCreator
    public Id(String id) {
        if (id == null || id.isBlank()) {
            throw new IllegalArgumentException("Id cannot be null or blank");
        }
        this.value = id;
    }
}

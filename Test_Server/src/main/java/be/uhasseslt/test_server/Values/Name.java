package be.uhasseslt.test_server.Values;

import com.fasterxml.jackson.core.JsonParser;
import com.fasterxml.jackson.databind.DeserializationContext;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.annotation.JsonDeserialize;
import com.fasterxml.jackson.databind.deser.std.StdDeserializer;
import lombok.Getter;
import lombok.Value;

import java.io.IOException;
import java.util.EnumMap;
import java.util.Map;

@Value
@JsonDeserialize(using = Name.NameDeserializer.class)
public class Name {
    Map<Language, String> names;

    public Name(Map<Language, String> names) {
        if (names == null || names.isEmpty()) {
            throw new IllegalArgumentException("Names map cannot be null or empty");
        }

        this.names = names;
    }

    public String getName(Language language) {
        return names.getOrDefault(language, names.get(Language.EN));
    }

    @Getter
    public enum Language {
        EN("en"),
        NL("nl");

        private final String code;

        Language(String code) {
            this.code = code;
        }

        public static Language fromCode(String code) {
            for (Language language : values()) {
                if (language.code.equalsIgnoreCase(code)) {
                    return language;
                }
            }
            return null; // Return null for unsupported languages
        }
    }

    public static class NameDeserializer extends StdDeserializer<Name> {

        public NameDeserializer() {
            super(Name.class);
        }

        @Override
        public Name deserialize(JsonParser p, DeserializationContext ctxt) throws IOException {
            JsonNode node = p.getCodec().readTree(p);

            // Check if the JSON is a simple string
            if (node.isTextual()) {
                String value = node.asText();
                Map<Name.Language, String> names = new EnumMap<>(Name.Language.class);
                names.put(Name.Language.EN, value); // Assume English for simple strings
                return new Name(names);
            }

            // Otherwise, assume it's a map
            Map<Name.Language, String> names = new EnumMap<>(Name.Language.class);
            node.fields().forEachRemaining(entry -> {
                Name.Language language = Name.Language.fromCode(entry.getKey());
                if (language != null) {
                    names.put(language, entry.getValue().asText());
                }
            });

            return new Name(names);
        }
    }

}

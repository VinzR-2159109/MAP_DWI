package be.uhasseslt.test_server.Values;

import com.fasterxml.jackson.databind.annotation.JsonDeserialize;
import lombok.Getter;

import java.util.EnumMap;
import java.util.Map;
import java.io.IOException;

import com.fasterxml.jackson.core.JsonParser;
import com.fasterxml.jackson.databind.DeserializationContext;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.deser.std.StdDeserializer;

@Getter
@JsonDeserialize(using = Description.DescriptionDeserializer.class)
public class Description {
    private final Map<Language, String> descriptions;

    public Description(Map<Language, String> descriptions) {
        this.descriptions = descriptions == null ? Map.of() : descriptions;
    }

    public String getDescriptionInLanguage(Language language) {
        return descriptions.getOrDefault(language, descriptions.get(Language.EN));
    }

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

    public static class DescriptionDeserializer extends StdDeserializer<Description> {

        public DescriptionDeserializer() {
            super(Description.class);
        }

        @Override
        public Description deserialize(JsonParser p, DeserializationContext ctxt) throws IOException {
            JsonNode node = p.getCodec().readTree(p);

            if (node == null || node.isEmpty()) {
                return new Description(Map.of()); // Default to an empty map
            }

            EnumMap<Description.Language, String> descriptions = new EnumMap<>(Description.Language.class);
            node.fields().forEachRemaining(entry -> {
                Description.Language language = Description.Language.fromCode(entry.getKey());
                if (language != null) {
                    descriptions.put(language, entry.getValue().asText());
                }
            });

            return new Description(descriptions);
        }
    }

}

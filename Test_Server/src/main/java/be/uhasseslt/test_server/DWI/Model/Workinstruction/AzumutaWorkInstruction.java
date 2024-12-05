package be.uhasseslt.test_server.DWI.Model.Workinstruction;

import java.net.URI;
import java.util.List;
import java.util.Map;

import be.uhasseslt.test_server.Values.Id;
import lombok.Data;
import lombok.EqualsAndHashCode;

import be.uhasseslt.test_server.Values.Description;

@Data
@EqualsAndHashCode(callSuper = true)
public class AzumutaWorkInstruction extends WorkInstruction {
    private Description description;
    private boolean isAudit;
    private int latestOfficialVersion;
    private URI url;
    private Thumbnail thumbnail;

    private Boolean archived = false;
    private List<String> treeNodeIds = List.of();
    private List<ArticleCategory> articleCategories = List.of();
    private List<String> tags = List.of();
    private List<Property> properties = List.of();
    private List<String> linkedVariants = List.of();
}

@Data
class Thumbnail {
    private String object;
    private String smallUrl;
    private String mediumUrl;
    private String originalUrl;

    public Thumbnail(String object, String smallUrl, String mediumUrl, String originalUrl) {
        if (object == null || object.isBlank()) {
            System.out.println(object);
            throw new IllegalArgumentException("Object cannot be null or blank");
        }
        if (smallUrl == null || isInvalidUrl(smallUrl)) {
            System.out.println(smallUrl);
            throw new IllegalArgumentException("Small URL must be a valid URL");
        }
        if (mediumUrl == null || isInvalidUrl(mediumUrl)) {
            System.out.println(mediumUrl);
            throw new IllegalArgumentException("Medium URL must be a valid URL");
        }
        if (originalUrl == null || isInvalidUrl(originalUrl)) {
            System.out.println(originalUrl);
            throw new IllegalArgumentException("Original URL must be a valid URL");
        }

        this.object = object;
        this.smallUrl = smallUrl;
        this.mediumUrl = mediumUrl;
        this.originalUrl = originalUrl;
    }

    private boolean isInvalidUrl(String url) {
        try {
            URI uri = new URI(url);
            return uri.getScheme() == null || uri.getHost() == null;
        } catch (Exception e) {
            return true;
        }
    }
}

@Data
class Property {
    private String object;
    private Id id;
    private Map<String, String> name;
}

@Data
class ArticleCategory {
    private String object;
    private String id;
    private String treeNodeId;
    private String name;
    private Description description;
    private Thumbnail thumbnail;
    private boolean archived;
}
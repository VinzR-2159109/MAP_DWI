package be.uhasseslt.test_mqtt_server;

import org.eclipse.paho.client.mqttv3.*;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.*;
import static org.mockito.Mockito.*;

class MqttServiceTest {

    @Mock
    private MqttClient mqttClient;

    @InjectMocks
    private MqttService mqttService;

    private AutoCloseable mocks;

    @BeforeEach
    void setUp() {
        mocks = MockitoAnnotations.openMocks(this);
    }

    @AfterEach
    void tearDown() throws Exception {
        if (mocks != null) {
            mocks.close();
        }
    }

    @Test
    void testSendMessage() throws MqttException {
        String topic = "test/topic";
        String message = "Hello, MQTT!";

        mqttService.sendMessage(topic, message);

        verify(mqttClient).publish(eq(topic), any(MqttMessage.class));
    }

    @Test
    void testSubscribe() throws MqttException {
        String topic = "test/topic";

        mqttService.subscribe(topic);

        verify(mqttClient).subscribe(eq(topic), any(IMqttMessageListener.class));
    }
}

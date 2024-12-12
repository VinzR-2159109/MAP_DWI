package be.uhasseslt.test_mqtt_server;

import org.eclipse.paho.client.mqttv3.*;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class MqttConfig {

    @Bean
    public MqttClient mqttClient() throws MqttException {
        String brokerUrl = "tcp://192.168.1.10:1883";
        String clientId = MqttClient.generateClientId();
        MqttClient client = new MqttClient(brokerUrl, clientId);

        MqttConnectOptions options = new MqttConnectOptions();
        options.setCleanSession(true);
        client.connect(options);

        return client;
    }
}

package be.uhasseslt.test_mqtt_server;

import org.eclipse.paho.client.mqttv3.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class MqttService {

    @Autowired
    private MqttClient mqttClient;

    public void sendMessage(String topic, String message) {
        try {
            MqttMessage mqttMessage = new MqttMessage(message.getBytes());
            mqttMessage.setQos(1);
            mqttClient.publish(topic, mqttMessage);
        } catch (MqttException e) {
            e.printStackTrace();
        }
    }

    public void subscribe(String topic) {
        try {
            mqttClient.subscribe(topic, (t, msg) -> {
                System.out.println("Received message: " + new String(msg.getPayload()) + " from topic: " + t);
            });
        } catch (MqttException e) {
            e.printStackTrace();
        }
    }
}

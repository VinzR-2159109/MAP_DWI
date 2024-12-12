package be.uhasseslt.test_mqtt_server;

import org.eclipse.paho.client.mqttv3.MqttException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class TestMqttServerApplication implements CommandLineRunner {

    @Autowired
    private MqttService mqttService;

    public static void main(String[] args) {
        SpringApplication.run(TestMqttServerApplication.class, args);
    }

    @Override
    public void run(String... args) throws Exception {
        mqttService.subscribe("test/topic");
        System.out.println("Successfully subscribed to test/topic");
    }
}

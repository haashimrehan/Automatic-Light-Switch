
const char* mqttServer = MQTT_Server;
const int mqttPort = 1883;
const char* mqttUser = MQTT_User;
const char* mqttPassword = MQTT_Password;

long elapsedTime = 0;
long elapsedTime2 = 0;
long elapsedTime3 = 0;
bool sleep = false;
bool sentState = false;

void setupMQTT() {

  client.subscribe("esp/test");
  client.subscribe("esp/sleep");
  client.subscribe("esp/light");
  //  client.publish("home-assistant/cover/availability", "online");
  client.publish("esp/status", "on");
}

void awake() {
  if ((millis() - elapsedTime > 2000) && !sleep) {
    Serial.println("awake");
    client.publish("esp/status", "awake");
    elapsedTime = millis();
  }
}

void callback(char* topic, byte * payload, unsigned int length) {
  String newTopic = topic;

  String message = "";

  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

 // Serial.println("Message arrived in topic: ");
//  Serial.println(newTopic);
//  Serial.print("Message:");
//  Serial.println(message);
//  Serial.println("-----------------------");
 //  client.publish("esp/debug", (char*) newTopic.c_str());
//  client.publish("esp/debug", (char*) message.c_str());
  
  if (newTopic == "esp/light") {
    if (message == "on") {
      switchOn();
      return;
    } else if (message == "off") {
      switchOff();
      return;
    }
  } else if (newTopic == "esp/sleep") {
    if (message == "online") {
      Serial.println("online");
      sleep = false;
      return;
    }  else if (message == "offline") {
      Serial.println("offline");
      sleep = true;
      return;
    }
  }
}

void serverConnect() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
      Serial.println("connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

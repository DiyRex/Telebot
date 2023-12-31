//Telebot.ino

#include <ESP8266WiFi.h>
#include "Telebot.h"

const char* ssid = "XXXXXXX";
const char* password = "XXXXXXX";
const String bot_token = "XXXXXXXX:XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
const String chat_id = "XXXXXXXXX";

void setup() {
    Serial.begin(115200);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    delay(2000);
    // Initialize the Telebot class
    Telebot telebot(bot_token, chat_id);

    // Send a message
    telebot.SendMessage("Hello from NodeMCU!");
    
    // Read a message
    Telebot::MessageData res = telebot.ReadMessage();
  
    // Print the message data
    Serial.println("Update ID: " + String(res.updateId));
    Serial.println("Chat ID: " + String(res.chatId));
    Serial.println("Message ID: " + String(res.messageId));
    Serial.println("Message: " + res.messageText);

    // Your other code here...
}

void loop() {
    // Your other code here...
}
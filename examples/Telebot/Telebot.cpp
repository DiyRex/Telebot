// Telebot.cpp
#include "Telebot.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

Telebot::Telebot(String bot_token, String chat_id) {
    this->bot_token = bot_token;
    this->chat_id = chat_id;
}



void Telebot::SendMessage(String message) {
  String url = "https://api.telegram.org/bot" + bot_token + "/sendMessage?chat_id=" + chat_id + "&text=" + message;
  WiFiClientSecure client;
  client.setInsecure();
  HTTPClient https;
  if (https.begin(client, url)) {
    int httpCode = https.GET();
    Serial.println("============== Response code: " + String(httpCode));
    if (httpCode > 0) {
      Serial.println(https.getString());
    }
    https.end();
    delay(500);
  }
  Serial.println("Sending message: ");
}

String Telebot::ReadMessage() {
    // Your implementation to read a message using bot_token
    // Return the read message
    return "0";
}

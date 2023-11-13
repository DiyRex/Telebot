// Telebot.cpp
#include "Telebot.h"
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

Telebot::Telebot(String bot_token, String chat_id) {
    this->bot_token = bot_token;
    this->chat_id = chat_id;
}

void Telebot::processJsonResponse(const String& jsonResponse, MessageData& result) {
  // Parse JSON document
  DynamicJsonDocument jsonDoc(2048);  // Adjust the size based on the response size
  DeserializationError error = deserializeJson(jsonDoc, jsonResponse);

  // Check for parsing errors
  if (error) {
    Serial.print("Failed to parse JSON: ");
    Serial.println(error.c_str());
    return;
  }

  // Access values in the JSON document
  bool ok = jsonDoc["ok"];
  Serial.println("OK: " + String(ok));

  JsonArray resultArray = jsonDoc["result"].as<JsonArray>();

  // Initialize variables to store the latest message data
  long latestUpdateId = -1;
  long latestChatId = -1;
  long latestMessageId = -1;
  String latestMessageText;

  for (JsonObject update : resultArray) {
    // Access values inside the "result" array
    long updateId = update["update_id"];
    // Serial.println("Update ID: " + String(updateId));

    // If the update contains "my_chat_member"
    if (update.containsKey("my_chat_member")) {
      JsonObject myChatMember = update["my_chat_member"];
      JsonObject chat = myChatMember["chat"];
      long chatId = chat["id"];
      // Serial.println("Chat ID: " + String(chatId));

      // Access other values as needed
    }

    // If the update contains "message"
    if (update.containsKey("message")) {
      JsonObject message = update["message"];
      long messageId = message["message_id"];
      Serial.println("Message ID: " + String(messageId));
      String text_msg = message["text"];
      // Serial.println("Message: " + text_msg);

      // Update variables with the latest message data
      if (updateId > latestUpdateId) {
        latestUpdateId = updateId;
        latestChatId = message["chat"]["id"];
        latestMessageId = messageId;
        latestMessageText = text_msg;
      }
    }
  }

  // Print the data of the last message
  Serial.println("Latest Update ID: " + String(latestUpdateId));
  Serial.println("Latest Chat ID: " + String(latestChatId));
  Serial.println("Latest Message ID: " + String(latestMessageId));
  Serial.println("Latest Message: " + latestMessageText);

  // Set values in the result structure
  result.updateId = latestUpdateId;
  result.chatId = latestChatId;
  result.messageId = latestMessageId;
  result.messageText = latestMessageText;
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

Telebot::MessageData Telebot::ReadMessage() {
  MessageData result;
  String url = "https://api.telegram.org/bot" + bot_token + "/getUpdates";
  WiFiClientSecure client;
  client.setInsecure();
  HTTPClient https;
  if (https.begin(client, url)) {
    int httpCode = https.GET();
    Serial.println("============== Response code: " + String(httpCode));
    if (httpCode > 0) {
      Serial.println(https.getString());
      processJsonResponse(https.getString(), result);
    }
    https.end();
    delay(500);
  }
  Serial.println("Received message: ");
  return result;
}


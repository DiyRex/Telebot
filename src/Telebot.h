// Telebot.h
#ifndef Telebot_h
#define Telebot_h
#include "Arduino.h"

class Telebot {
public:
    struct MessageData {
      long updateId;
      long chatId;
      long messageId;
      String messageText;
    };
    Telebot(String bot_token, String chat_id); //constructor
    void SendMessage(String message);
    MessageData ReadMessage();

private:
  String bot_token;
  String chat_id;
  bool enableLog = true;
  void processJsonResponse(const String& jsonResponse, MessageData& result);
};

#endif 
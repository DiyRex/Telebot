// Telebot.h
#ifndef Telebot_h
#define Telebot_h

#include "Arduino.h"

class Telebot {
public:
    Telebot(String bot_token, String chat_id); //constructor
    void SendMessage(String message);
    String ReadMessage();

private:
  String bot_token;
  String chat_id;
};

#endif 
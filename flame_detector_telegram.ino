#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

#include "secrets.h"

#define flamePin D5

bool flameDetected = false;
bool messageSent = false;

unsigned long noFlameTime = 0;
const unsigned long resetTime = 3000;


void connectWiFi() {

  Serial.print("Connecting to WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}


void sendTelegram(String message) {

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
    return;
  }

  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient https;

  String url = "https://api.telegram.org/bot";
  url += botToken;
  url += "/sendMessage?chat_id=";
  url += chatId;
  url += "&text=";

  message.replace(" ", "%20");
  url += message;

  if (https.begin(client, url)) {

    int response = https.GET();

    if (response > 0) {
      Serial.println("Telegram message sent");
    } else {
      Serial.println("Telegram message failed");
    }

    https.end();
  }
}


void setup() {

  Serial.begin(115200);

  pinMode(flamePin, INPUT);

  connectWiFi();

  Serial.println("Flame detector is ready");
}


void loop() {

  int sensor = digitalRead(flamePin);

  if (sensor == LOW) {

    noFlameTime = 0;

    if (!flameDetected) {

      flameDetected = true;

      Serial.println("🔥 Flame detected");

      if (!messageSent) {

        sendTelegram("WARNING! Flame detected!");

        messageSent = true;
      }
    }
  }

  else {

    if (flameDetected) {

      if (noFlameTime == 0) {
        noFlameTime = millis();
        Serial.println("Flame removed");
      }

      if (millis() - noFlameTime >= resetTime) {

        flameDetected = false;
        messageSent = false;
        noFlameTime = 0;

        Serial.println("No flame detected");
        Serial.println("System ready");
      }
    }

    else {
      Serial.println("No flame detected");
    }
  }

  delay(500);
}

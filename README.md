# 🔥 ESP8266 Flame Detector with Telegram Alert

An IoT-based flame detection system using an ESP8266 NodeMCU and an IR flame detector sensor.

When a flame is detected, the ESP8266 sends a real-time warning message to a Telegram bot using Wi-Fi.

## 🚀 Features

- 🔥 Flame detection using IR flame sensor
- 📡 ESP8266 Wi-Fi connectivity
- 📱 Telegram alert notification
- 🔄 Automatic reset after flame disappears
- 🚫 Prevents repeated alerts while flame remains detected
- 💻 Serial Monitor monitoring

## 🛠️ Components

- ESP8266 NodeMCU
- IR Flame Detector Sensor
- Jumper Wires
- USB Cable
- Wi-Fi
- Telegram Bot

## 🔌 Circuit Connection

| Flame Sensor | ESP8266 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| DO | D5 |
| AO | Not connected |

## ⚙️ Working

```text
🔥 Flame
   ↓
IR Flame Sensor
   ↓
ESP8266
   ↓
Wi-Fi
   ↓
Telegram Bot
   ↓
📱 Warning Message

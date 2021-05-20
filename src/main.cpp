#include <Arduino.h>
#include "CTBot.h"
#define relay D1
int nyala = LOW;
int mati = HIGH;
char perintah;

const int SensorPin = A0;
int soilMoistureValue = 0;
int soilmoisturepercent = 0;
const int AirValue = 600;
const int WaterValue = 350;

CTBot myBot;

// spesifikasi wifi dan tele bot mu
String ssid = "synxhronous";
String pass = "";
String token = "";
const int id = ;

void setup()
{
  Serial.begin(115200);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, mati);
  Serial.println("Starting TelegramBot...");
  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);

  if (myBot.testConnection())
  {
    Serial.println("Good Connection");
  }
  else
  {
    Serial.println("Bad Connection, reconnecting");
  }
  delay(1000);
}

void loop()
{
  if (myBot.testConnection())
  {
    Serial.println("Good Connection");
  }
  else
  {
    Serial.println("Bad Connection, reconnecting");
  }

  TBMessage msg;
  if (myBot.getNewMessage(msg))
  {
    Serial.println("Pesan Masuk : " + msg.text);
  }

  String command = msg.text;
  if (command == "/start")
  {
    String welcome = "📜List Perintah Bot📜 \n";
    welcome += "/start : Menunjukan List Perintah🔧\n";
    welcome += "/siram_tanaman : Siram Tanaman🌻\n";
    welcome += "/cek_kelembaban : Informasi Kelembaban Tanah🔎\n";
    myBot.sendMessage(id, welcome);
  }
  else if (command == "/siram_tanaman")
  {
    Serial.println("Menyiram Tanaman...");
    digitalWrite(relay, nyala);
    delay(3500);
    digitalWrite(relay, mati);
    myBot.sendMessage(id, "Tanaman Telah Disiram 🌼");
    Serial.println("Tanaman Telah Disiram");
  }
  else if (command == "/cek_kelembaban")
  {
    soilMoistureValue = analogRead(SensorPin);
    soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
    Serial.println(soilmoisturepercent + String("%"));
    String info_kelembaban = "Informasi Kelembaban Tanah : \n";
    float moisture = soilmoisturepercent;
    info_kelembaban += "Kelembaban Tanah : ";
    info_kelembaban += moisture;
    info_kelembaban += "%\n";
    if (moisture >= 65)
    {
      Serial.println("Lembab");
      info_kelembaban += "Kategori Kelembaban : Lembab/Tidak Perlu Disiram🌸";
      myBot.sendMessage(id, info_kelembaban);
    }
    else if (moisture < 65 && moisture >= 26)
    {
      Serial.println("Sedang");
      info_kelembaban += "Kategori Kelembaban : Sedang/Tidak Perlu Disiram🌷";
      myBot.sendMessage(id, info_kelembaban);
    }
    else if (moisture <= 25)
    {
      Serial.println("Sedang");
      info_kelembaban += "Kategori Kelembaban : Kering/Perlu Disiram🥀";
      myBot.sendMessage(id, info_kelembaban);
    }
    delay(1000);
  }
  else if (command == "/about")
  {
    String info_team = "Bot ini dibuat oleh: \n";
    info_team += "👨‍💻 Ardan Anjung Kusuma  (TI-3D)\n";
    info_team += "👨‍💻 Moh. Riza Zulfahnur (TI-3D)\n";
    info_team += "Untuk memenuhi nilai mata kuliah Digital Entrepreneurship\n";
    myBot.sendMessage(id, info_team);
  }

  delay(1000);
}
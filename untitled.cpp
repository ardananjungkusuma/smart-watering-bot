#include "CTBot.h"
#include "DHT.h"
#include <Adafruit_Sensor.h>
#define dht_dpin 2    //GPIO 2
#define DHTTYPE DHT11 // DHT 11
DHT dht(dht_dpin, DHTTYPE);
byte led = 5; //pin GPIO 5

CTBot myBot;

String ssid = "synxhronous";
String pass = "kjkszpj29";
String token = "1647200647:AAEUGqE1YHYqy2iWAItbY6qDdpVO5Sno6YM";
const int id = 474657516;

void setup()
{
    pinMode(led, OUTPUT);
    pinMode(dht_dpin, INPUT);
    dht.begin();
    Serial.begin(115200);
    Serial.println("Starting TelegramBot...");
    myBot.wifiConnect(ssid, pass);
    myBot.setTelegramToken(token);

    if (myBot.testConnection())
    {
        Serial.println("Good Connection");
    }
    else
    {
        Serial.println("Bad Connection");
    }
    delay(1000);
}

void loop()
{
    float humid = dht.readHumidity();
    float temp = dht.readTemperature();

    TBMessage msg;
    if (myBot.getNewMessage(msg))
    {
        Serial.println("Pesan Masuk : " + msg.text);
    }

    String command = msg.text;

    Serial.println(temp);
    Serial.println(humid);

    if (command == "/led_on")
    {
        digitalWrite(led, HIGH);
        myBot.sendMessage(id, "LED ON");
        Serial.println("LED ON");
    }
    else if (command == "/led_off")
    {
        digitalWrite(led, LOW);
        myBot.sendMessage(id, "LED OFF");
        Serial.println("LED OFF");
    }
    else if (command == "/temperature_check")
    {
        String message = "Temperature : ";
        message += temp;
        message += " C";
        myBot.sendMessage(id, message, "");
        Serial.println(message);
    }
    else if (command == "/humidity_check")
    {
        String message = "Humidity : ";
        message += humid;
        message += " %";
        myBot.sendMessage(id, message, "");
        Serial.println(message);
    }
    delay(1000);
}
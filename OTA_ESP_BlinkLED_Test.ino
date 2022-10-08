/*
;---------------------
; Title: OTA on ESP8266
;---------------------
;Program Detail: Enableing functionality of Over The Air programming on the ESP8266 Microcontroller.
;                Here we have used ArduinoIDE and ESP8266WiFi header file.
;---------------------
; Purpose: The purpose of the program is to able to send program over the air
           on the ESP8266 module which make a process very easier and efficient.
           This would be very useful when you want to program multiple ESP at once.
; Inputs: Communication to the local network.
; Outputs: Blinking LED over the Air.
; Dates: Oct 07, 2022
; Compiler: Arduino Version 2.0.0
; Author: Het Patel and John LaBarge in the collaboration.
; Versions:
;           V1 - Establishing the connection with the module and network. 
;           V2 - Blinking LED program sneding it over the air.
;---------------------
; File Dependencies: 
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
;--------------------- 
; Main Porgam
;---------------------
*/


#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>

#define ledPin BUILTIN_LED  // led to blink

const char* ssid = "G36-CFC5"; // Your WiFi Username
const char* password = "297068486899"; // Your WiFi Password

void setup() {      
  Serial.begin(9600);

  // start with led OFF
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);   

  // join WiFi network
  Serial.println();
  Serial.println("Joining WiFI...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("Het's ESP8266");  // Not neccessary to have

  // Below I have added password. Each time when you upload, 
  // it will ask to enter password. No authentication by default.

  ArduinoOTA.setPassword("admin");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
    ESP.restart();            // It restarts every time you upload a sketch. That way you have a chance to reupload your sketch anytime.
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });

  ArduinoOTA.onError([](ota_error_t error) {    // different error messages prints out when error occurs.
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  
  // initialize OTA capability
  ArduinoOTA.begin();
}

void loop() {
  // handle any OTA requests. (Critical part to add)
  ArduinoOTA.handle();

  // Add any normal sketch from below



  // Testing OTA by simple Blinking LED skecth,

  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
}
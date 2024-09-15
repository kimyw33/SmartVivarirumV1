#define BLYNK_TEMPLATE_ID  "TMPL6xQ5btb2J"   // Blynk template ID
#define BLYNK_AUTH_TOKEN   "R0f9Z-7VEkCk3TUDCu5S-vjX-2Ug5ZCh"  // Blynk auth token

#include <WiFi.h>               // WiFi library for ESP32
#include <BlynkSimpleEsp32.h>    // Blynk library for ESP32

// WiFi credentials
char ssid[] = "4층 메이커실";    
char pass[] = "ksm1234567";      

void setup()
{
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);  // Connect to WiFi and Blynk
}

void loop()
{
  Blynk.run();  // Keep Blynk connection active
}
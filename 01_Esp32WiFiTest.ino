/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL6xQ5btb2J"
#define BLYNK_TEMPLATE_NAME         "SmartFarmTest00"
#define BLYNK_AUTH_TOKEN            "R0f9Z-7VEkCk3TUDCu5S-vjX-2Ug5ZCh"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "4층 메이커실";
char pass[] = "ksm1234567";

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();
}
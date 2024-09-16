#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Blynk 서버와 연결을 위한 정보
#define BLYNK_TEMPLATE_ID "TMPL689_V4Ouk"                    // Blynk 템플릿 ID
#define BLYNK_TEMPLATE_NAME "SmartVivariumV1"                // Blynk 템플릿 이름
#define BLYNK_AUTH_TOKEN "ZZ6kgbjkx892h8YXiIK-ctpuh1IM6ETQ"  // Blynk 인증 토큰
#define BUILT_IN_LED 2

// WiFi 정보
char ssid[] = "homesweethome";  // WiFi SSID
char pass[] = "micasa202";      // WiFi 비밀번호

void setup() {
  Serial.begin(9600);                         // 시리얼 통신 시작, 디버깅을 위한 설정
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);  // Blynk 서버와 연결 시작

  pinMode(BUILT_IN_LED, OUTPUT);  // 내부 LED 핀을 출력 모드로 설정
}

void loop() {
  Blynk.run();  // Blynk 라이브러리 함수 호출

  // Blynk가 성공적으로 연결된 경우
  if (Blynk.connected()) {
    // WiFi가 연결된 경우 LED를 1초 간격으로 깜빡이게 함
    if (WiFi.status() == WL_CONNECTED) {
      digitalWrite(BUILT_IN_LED, HIGH);  // LED 켜기
      delay(1000);                       // 1초 대기
      digitalWrite(BUILT_IN_LED, LOW);   // LED 끄기
      delay(1000);                       // 1초 대기
    } else {
      // WiFi가 연결되지 않은 경우 LED를 꺼놓음
      digitalWrite(BUILT_IN_LED, LOW);  // LED 끄기
    }
  } else {
    // Blynk가 연결되지 않은 경우 LED를 꺼놓음
    digitalWrite(BUILT_IN_LED, LOW);  // LED 끄기
  }
}
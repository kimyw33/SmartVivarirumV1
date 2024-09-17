#define BLYNK_PRINT Serial                                   // 꼭 필요하진 않지만 내부 LED를 깜빡거리는 것 외에, 잘 안결되었을 경우 시리얼 모니터를 통해 연결된 IP, 포트번호, ping 등을 확인하기 위해 추가하였습니다.
// Blynk 서버와 연결을 위한 정보
#define BLYNK_TEMPLATE_ID "TMPL689_V4Ouk"                    // Blynk 템플릿 ID, Blynk 클라우드와의 연결을 위해 필요한 고유 ID
#define BLYNK_TEMPLATE_NAME "SmartVivariumV1"                // Blynk 템플릿 이름, 클라우드에서 사용하는 템플릿의 이름
#define BLYNK_AUTH_TOKEN "ZZ6kgbjkx892h8YXiIK-ctpuh1IM6ETQ"  // Blynk 인증 토큰, 앱에서 생성한 고유 토큰을 사용하여 기기와 서버를 인증함
#define BUILT_IN_LED 2                                       // 내장된 LED의 핀 번호를 정의합니다. ESP32의 내장 LED는 2번 핀에 연결되어 있습니다.

// 필요한 라이브러리 포함
#include <WiFi.h>            // ESP32의 WiFi 연결을 위한 라이브러리
#include <WiFiClient.h>       // WiFi 클라이언트 기능을 제공하는 라이브러리
#include <BlynkSimpleEsp32.h> // Blynk와 ESP32 간의 연결을 간단히 구현하기 위한 라이브러리

// WiFi 정보
char ssid[] = "homesweethome";  // 연결할 WiFi의 SSID(네트워크 이름)
char pass[] = "micasa202";      // 연결할 WiFi의 비밀번호

void setup() {
  Serial.begin(9600);                         // 시리얼 통신 시작, 9600bps의 속도로 설정하여 디버깅을 위해 시리얼 통신 준비
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);  // Blynk 서버에 WiFi를 통해 연결, 인증 토큰, SSID, 비밀번호를 사용하여 인증

  pinMode(BUILT_IN_LED, OUTPUT);  // 내장된 LED 핀을 출력 모드로 설정 (HIGH 또는 LOW 값을 통해 LED 켜기/끄기 가능)
}

void loop() {
  Blynk.run();  // Blynk 라이브러리 함수 호출, 서버와의 통신을 유지하고 데이터를 주고받음

  // Blynk가 성공적으로 연결된 경우
  if (Blynk.connected()) {
    // WiFi가 연결된 경우, LED를 1초 간격으로 깜빡임
    if (WiFi.status() == WL_CONNECTED) {
      digitalWrite(BUILT_IN_LED, HIGH);  // LED 켜기
      delay(1000);                       // 1초 대기
      digitalWrite(BUILT_IN_LED, LOW);   // LED 끄기
      delay(1000);                       // 1초 대기
    } else {
      // WiFi가 연결되지 않은 경우 LED를 끔
      digitalWrite(BUILT_IN_LED, LOW);  // LED 끄기
    }
  } else {
    // Blynk가 연결되지 않은 경우 LED를 끔
    digitalWrite(BUILT_IN_LED, LOW);  // LED 끄기
  }
}
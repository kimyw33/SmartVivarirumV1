#define BUILT_IN_LED 2  // 내장된 LED의 핀 번호를 정의합니다. ESP32의 내장 LED는 2번 핀에 연결되어 있습니다.

void setup() {
  pinMode(BUILT_IN_LED, OUTPUT);  // LED가 출력 장치이므로, 해당 핀을 출력 모드로 설정합니다.
}

void loop() {
  digitalWrite(BUILT_IN_LED, HIGH);  // LED를 켭니다 (전압을 HIGH로 설정).
  delay(1000);  // 1초 동안 대기합니다 (1000밀리초).
  
  digitalWrite(BUILT_IN_LED, LOW);  // LED를 끕니다 (전압을 LOW로 설정).
  delay(1000);  // 다시 1초 동안 대기합니다.
}
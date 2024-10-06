#define RELAY_PIN  5  // GPIO 5핀에 릴레이 연결

void setup() {
  // 시리얼 통신을 시작하여 디버깅 정보를 확인할 수 있도록 설정
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT); // 릴레이 핀을 출력 모드로 설정
  digitalWrite(RELAY_PIN, LOW); // 시작 시 팬을 끈 상태로 설정 (릴레이를 OFF 상태로 설정)
}

void loop() {
  Serial.println("Fan ON"); // 팬을 켜기 (릴레이 ON)
  digitalWrite(RELAY_PIN, HIGH);  // 릴레이에 신호를 반대로 보내서 팬 ON
  delay(5000);  // 5초 동안 팬 작동

  
  Serial.println("Fan OFF"); // 팬을 끄기 (릴레이 OFF)
  digitalWrite(RELAY_PIN, LOW);   // 릴레이 신호를 반대로 보내서 팬 OFF
  delay(5000);  // 5초 동안 팬 멈춤
}
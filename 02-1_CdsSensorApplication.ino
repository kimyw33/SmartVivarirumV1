#define Cds 39  // GPIO 39번에 조도 센서 연결 (ESP32의 아날로그 입력 핀 중 하나)

void setup() {
  Serial.begin(9600);  // 시리얼 통신을 시작하여 센서 값을 모니터링할 수 있도록 설정 (9600 baud rate)
}

void loop() {
  int Cds_value = analogRead(Cds);  // 조도 센서로부터 아날로그 값을 읽어들임 (0 ~ 4095)

  // 조도 값을 5단계로 구분
  String brightness;
  if (Cds_value < 820) {
    brightness = "VeryDark";  // 조도 값이 매우 낮으면 매우 어두운 상태
  } else if (Cds_value < 1630) {
    brightness = "Dark";  // 조도 값이 낮으면 어두운 상태
  } else if (Cds_value < 2450) {
    brightness = "Normal";  // 조도 값이 중간이면 보통 상태
  } else if (Cds_value < 3270) {
    brightness = "Bright";  // 조도 값이 높으면 밝은 상태
  } else {
    brightness = "VeryBright";  // 조도 값이 매우 높으면 매우 밝은 상태
  }

  Serial.println(brightness);  // 구분된 밝기 값을 시리얼 모니터에 출력
  delay(1000);  // 1초마다 값을 읽고 출력하여 과도한 출력 방지
}
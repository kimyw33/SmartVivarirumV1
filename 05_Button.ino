#define BUTTON 23  // BUTTON을 연결하기 위한 핀 번호(GPIO 23)

void setup() {
  pinMode(BUTTON, INPUT);  // BUTTON 핀을 입력 모드로 설정합니다.
  Serial.begin(9600);      // 시리얼 통신의 전송 속도를 9600bps로 설정합니다.
}

void loop() {
  int buttonState = digitalRead(BUTTON);  // BUTTON 핀의 디지털 입력 값을 읽어 buttonState 변수에 저장합니다.
  Serial.println(buttonState);            // buttonState 값을 시리얼 모니터에 출력합니다.
  delay(100);                             // 100밀리초 지연을 추가하여 다음 읽기 전까지 잠시 대기합니다.
}
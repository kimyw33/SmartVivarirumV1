#define BUTTON 23 // 핀 23을 BUTTON으로 정의합니다.

bool lastButtonState = LOW; // 마지막 버튼 상태를 저장할 변수, 초기값은 LOW입니다.
bool currentButtonState = LOW; // 현재 버튼 상태를 저장할 변수
bool buttonState = LOW; // 버튼의 현재 상태를 저장할 변수

void setup() {
  pinMode(BUTTON, INPUT);  // BUTTON 핀을 입력 모드로 설정합니다.
  Serial.begin(9600);     // 시리얼 통신의 전송 속도를 9600bps로 설정합니다.
}

void loop() {
  currentButtonState = digitalRead(BUTTON); // BUTTON 핀의 디지털 입력 값을 읽어 currentButtonState 변수에 저장합니다.

  // 버튼 상태가 변화한 경우
  if (currentButtonState != lastButtonState) {
    // 버튼이 눌렸을 때 상태를 변경
    if (currentButtonState == HIGH) {
      buttonState = !buttonState; // 버튼 상태를 토글
    }
    delay(50); // 버튼 상태 변화에 대한 노이즈를 방지하기 위한 짧은 지연
  }
  
  // 버튼 상태를 시리얼 모니터에 출력
  Serial.println(buttonState);

  // 마지막 버튼 상태를 현재 상태로 업데이트
  lastButtonState = currentButtonState;

  delay(100); // 100밀리초 지연을 추가하여 다음 읽기 전까지 잠시 대기합니다.
}
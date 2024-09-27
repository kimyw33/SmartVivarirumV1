#include <Adafruit_NeoPixel.h>  // NeoPixel 스트립을 제어하기 위한 헤더파일 호출

#define PIN 4          // NeoPixel 스트립을 위한 GPIO 4
#define BUTTON_PIN 23  // 버튼을 위한 GPIO 23
#define NUMPIXELS 18   // NeoPixel의 픽셀 수

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

bool isOn = false;              // LED 상태를 저장하는 변수
bool lastButtonState = LOW;     // 마지막 버튼 상태를 저장하는 변수
bool currentButtonState = LOW;  // 현재 버튼 상태를 저장하는 변수

void setup() {
  pinMode(BUTTON_PIN, INPUT);  // 버튼 핀을 입력 모드로 설정합니다.
  // 버튼을 눌렀을 때, Led가 오작동하거나, 깜빡깜빡 거릴 경우, 위 코드를 주석처리하고, 아래 코드의 주석을 제거하여 코드 작성
  //pinMode(BUTTON_PIN, INPUT_PULLUP);  // 버튼 핀을 풀업 저항과 함께 입력 모드로 설정
  pixels.begin();  // NeoPixel 스트립을 초기화합니다.
}

void loop() {
  currentButtonState = digitalRead(BUTTON_PIN);  // 현재 버튼 상태를 읽어 currentButtonState 변수에 저장합니다.

  // 버튼 상태가 변화한 경우
  if (currentButtonState != lastButtonState) {
    // 버튼이 눌렸을 때 상태를 변경합니다.
    if (currentButtonState == HIGH) {
      isOn = !isOn;  // LED 상태를 토글합니다.
    }
    delay(50);  // 버튼 상태 변화에 대한 노이즈를 방지하기 위한 짧은 지연
  }

  // LED 상태에 따라 NeoPixel 색상을 설정합니다.
  if (isOn) {
    for (int i = 0; i < NUMPIXELS; i += 2) {
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));  // 짝수 픽셀을 빨간색으로 설정합니다.
    }
    for (int i = 1; i < NUMPIXELS; i += 2) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 255));  // 홀수 픽셀을 파란색으로 설정합니다.
    }
    pixels.show();  // 색상 변경 사항을 디스플레이합니다.
  } else {
    pixels.clear();  // 모든 픽셀을 꺼서 LED를 끕니다.
    pixels.show();   // 색상 변경 사항을 디스플레이합니다.
  }

  lastButtonState = currentButtonState;  // 마지막 버튼 상태를 현재 상태로 업데이트합니다.
  delay(100);                            // 버튼 디바운싱을 위한 지연
}
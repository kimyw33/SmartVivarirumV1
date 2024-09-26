#include <Wire.h>              // I2C 통신을 위한 라이브러리
#include <Adafruit_GFX.h>      // 그래픽 관련 기능을 제공하는 라이브러리
#include <Adafruit_SSD1306.h>  // SSD1306 OLED 디스플레이를 제어하는 라이브러리
#include <DHT.h>               // DHT 센서를 사용하기 위한 라이브러리

#define SCREEN_WIDTH 128     // OLED 디스플레이의 너비 (픽셀 단위)
#define SCREEN_HEIGHT 64     // OLED 디스플레이의 높이 (픽셀 단위)
#define OLED_RESET -1        // OLED 디스플레이의 리셋 핀 (-1은 리셋 핀 공유를 의미)
#define SCREEN_ADDRESS 0x3C  // I2C 주소 (128x64 OLED 디스플레이의 기본 주소는 0x3C)
#define DHTPIN 14            // DHT 센서를 연결한 핀 번호 (GPIO 14)
#define DHTTYPE DHT11        // DHT 센서의 종류 (DHT11)
#define Cds 39               // GPIO 39번에 조도 센서 연결 (ESP32의 아날로그 입력 핀 중 하나)

// Adafruit_SSD1306 객체 생성: 디스플레이의 크기, I2C 통신을 위한 Wire 객체, 리셋 핀을 지정
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT dht(DHTPIN, DHTTYPE);  // DHT 객체 생성, 핀 번호와 센서 타입을 설정

void setup() {
  Serial.begin(9600);  // 시리얼 통신을 9600 baud rate로 설정
  dht.begin();         // DHT 센서 시작

  // 디스플레이 초기화. 초기화 실패 시 에러 메시지 출력 후 무한 루프
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));  // 시리얼 모니터에 오류 메시지 출력
    for (;;)
      ;  // 오류 발생 시 프로그램 중단
  }

  // 디스플레이 초기화 및 텍스트 설정
  display.clearDisplay();               // 버퍼를 초기화하여 화면을 지움
  display.setTextSize(1);               // 텍스트 크기를 기본으로 설정
  display.setTextColor(SSD1306_WHITE);  // 텍스트 색상을 흰색으로 설정
  display.display();                    // 화면에 버퍼 내용 출력
}

void loop() {
  delay(2000);  // 센서 값을 읽기 전에 2초 대기 (DHT11 센서 특성상 최소 2초 딜레이 필요)

  // 온도와 습도 값 읽기
  float h = dht.readHumidity();     // 습도 값을 읽음
  float t = dht.readTemperature();  // 온도 값을 읽음

  // 조도 값 읽기 및 단계 구분
  int Cds_value = analogRead(Cds);  // 조도 센서로부터 아날로그 값을 읽어들임
  String brightness;
  if (Cds_value < 820) {
    brightness = "So Dark";  // 조도 값이 매우 낮으면 "So Dark"(매우 어두움)
  } else if (Cds_value < 1630) {
    brightness = "Dark";  // 조도 값이 낮으면 "Dark"(어두움)
  } else if (Cds_value < 2450) {
    brightness = "Normal";  // 조도 값이 중간이면 "Normal"(보통)
  } else if (Cds_value < 3270) {
    brightness = "Bright";  // 조도 값이 높으면 "Bright"(밝음)
  } else {
    brightness = "So Bright";  // 조도 값이 매우 높으면 "So Bright"매우 밝음
  }

  // 디스플레이에 온도, 습도, 조도 값 출력
  display.clearDisplay();   // 화면을 지움
  display.setCursor(0, 0);  // 첫 번째 줄에 커서 위치 설정
  display.println("Smart Vivarium");
  display.setTextSize(2);  // 텍스트 크기를 2배로 설정
  display.print("T: ");
  display.print(t);
  display.println(" C");
  display.print("H: ");
  display.print(h);
  display.println(" %");
  display.println(brightness);
  display.setTextSize(1);       // 텍스트 크기를 다시 1배로 설정
  display.print("by kimyw33");  // 네 번째(마지막) 텍스트 라인 출력
  display.display();            // 화면에 버퍼 내용 출력
}
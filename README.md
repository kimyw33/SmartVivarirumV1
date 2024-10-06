# 스마트 비바리움 제작 프로젝트
**목적**<br>
본 프로젝트는 비바리움(구체적으로는 테라리움)과 IoT 구현을 위한 도구로서 ESP32 개발보드 및 각종 모듈들을 종합하여 스마트 비바리움을 제작하고, 이러한 과정에서 "메이킹 활동을 통한 즐거움"과 "IoT에 대한 이해(나아가 적용)"을 도모하기 위해 시작했습니다.<br>
지속적인 발전을 기대하며, 이를 위한 공부 및 공유를 함께하고 싶습니다.<br>
**준비물**<br>
ESP32 개발보드, USB 5핀 케이블(데이터 송수신용), ESP32 쉴드(DOIT ESP32 DEVKIT V1), 온/습도 센서, 조도 센서, 푸쉬버튼 스위치, OLED, NeoPixel LED, 각각의 모듈과 쉴드를 연결 할 3선/4선 케이블, 무선 네트워크 환경, 구글 계정 등<br>
세부 준비물 내역은 아래 소단위 프로젝트마다 제시함.<br>
**프로젝트의 흐름**<br>
01~07까지 소단위 프로젝트를 순차적으로 실행해가며, ESP32, 각종 센서 및 액추에이터의 활용 방법, 무선 네트워크를 통한 Blynk 연동 방법 등을 살펴볼 수 있습니다.<br>
이후 08번 프로젝트에서는 스마트 비바리움의 IoT 파트를 구현할 수 있도록 구성하였습니다.<br>
추가로 10번 프로젝트에서는 앞선 08번 프로젝트에 5[V] DC 팬을 추가함으로써 식생에 도움을 줄 수 있는 환기 기능을 추가하였고, 이를 위해 릴레이를 활용하였습니다.(릴레이의 기초 사용 방법은 09번 프로젝트 참고)
<details>
  <summary>환경 구축(최초 1회 수행)</summary>
  1. OS에 맞는 Arduino IDE 설치
  <a href="https://www.arduino.cc/en/software">설치 링크</a><br>
  2. 필요한 경우 시스템 언어 변경(File/Arduino IED->Preferences->재시작)<br>
  3. 기본 설정->추가 보드 관리자 URL->"비공식 보드 지원 URL 목록을 보려면 클릭하십시오." 클릭->"Espressif ESP32" 검색->해당 "*.json"파일 복사/붙여넣기 후 확인<br>
  4. 보드 매니저->"esp32 by Espressif Systems"설치<br>
  5. PC와 ESP32 연결<br>
  6. 보드 및 포트를 아래와 같이 연결<br>
     - 보드: DOIT ESP32 DEVKIT V1<br>
     - 포트: Serial Port(USB), 포트 번호는 COM4, COM3 등으로 다를 수 있음.<br>
  7. ESP32 업로드 에러 발생 시
  <a href="https://docs.google.com/presentation/d/1MqSPEBPEWeh-agVcmBz7CRioSePWG-13oV_nJNzy-uo/edit?usp=sharing">문제 해결 방법</a>
</details>
<details>
  <summary>최종 프로젝트 완성 과정까지 겪었던 주요 문제점과 해결 방안</summary>

  **1. 문제점: LED가 계속 깜빡거림**  
  - **원인**: `LedOnOff()` 함수가 타이머에 의해 주기적으로 호출되어 버튼을 누르지 않아도 LED가 반복해서 깜빡거리는 문제가 발생.
  - **해결 방안**: 타이머에서 `LedOnOff()` 호출을 제거하고, 버튼 입력을 확인하는 `handleButtonPress()` 함수로 버튼이 눌렸을 때만 LED 상태를 변경하도록 수정.

  **2. 문제점: Blynk 앱에서 LED 제어가 정상적으로 동작하지 않음**  
  - **원인**: Blynk 핸들러에서 `led_state` 값을 업데이트하는 과정에서 LED 상태가 제대로 반영되지 않음.
  - **해결 방안**: `BLYNK_WRITE(V3)` 핸들러에서 받은 값을 기반으로 `updateLEDState()` 함수를 호출하여, Blynk 앱에서 보낸 값에 맞게 LED 상태를 정확히 제어하도록 수정.

  **3. 문제점: 버튼 입력 시 LED 상태가 불안정함**  
  - **원인**: 버튼 디바운싱 처리가 부족하여, 빠르게 버튼을 누르면 LED 상태가 불안정하게 변하는 문제가 발생.
  - **해결 방안**: `handleButtonPress()` 함수에서 **디바운싱 처리**를 강화하고, 버튼이 눌릴 때와 떼었을 때만 LED 상태를 변경하도록 로직을 개선. 또한, **풀업(Pull-up) 저항**을 활성화하여, GPIO 핀의 불안정한 상태(floating)를 방지하기 위해 `pinMode(BUTTON_PIN, INPUT_PULLUP)`을 적용. 이로 인해 버튼 입력이 안정적으로 처리됨.

  **4. 문제점: OLED 화면에 값이 제대로 갱신되지 않음**  
  - **원인**: 디스플레이 버퍼가 제대로 초기화되지 않거나, 센서 데이터를 읽는 주기와 디스플레이 업데이트 주기가 맞지 않음.
  - **해결 방안**: `showDisplay()` 함수에서 디스플레이를 초기화한 후 값을 출력하도록 하고, 타이머로 주기적으로 값을 갱신하여 문제가 해결됨.

  **5. 문제점: WiFi 연결 오류**  
  - **원인**: WiFi 연결 시, 일부 설정이 제대로 적용되지 않아 ESP32가 네트워크에 연결되지 않거나 Blynk 서버와 통신하지 못하는 문제가 발생.
  - **해결 방안**: WiFi 및 Blynk 관련 설정은 `#define`으로 먼저 정의한 후 관련 함수들을 `#include`로 호출함으로써 `Blynk.begin()`에서 올바르게 호출되도록 수정. 이로 인해 WiFi 및 Blynk 연결 오류가 해결됨.

</details>


# 01_BuiltInLedControl

**목적**  
이 프로젝트의 목적은 **ESP32 보드가 제대로 작동하는지 확인**하는 것입니다. 이를 위해 **내장된 LED를 제어**하여 **1초 간격**으로 켜고 끄는 동작을 실행시킵니다.

<details>
  <summary>준비물</summary>
  - ESP32 보드 1개<br>
  - USB 케이블(ESP32와 PC 연결용) 1개<br>
  - Arduino IDE(코드 작성 및 업로드)<br>
</details>

<details>
  <summary>코드 설명</summary>
  이 실습에서는 ESP32 내장 LED를 활용하여 간단한 점멸 제어를 수행합니다.<br>
  GPIO 2번 핀에 연결된 내장 LED를 1초마다 켜고 끄는 동작을 반복하게 됩니다.<br>
</details>

---

# 02_CdsSensor

**목적**  
이 프로젝트의 목적은 ESP32와 조도 센서(Cds)를 이용하여 주변 빛의 양을 측정하고, 측정된 값을 시리얼 모니터를 통해 확인하는 것입니다.<br>
이를 통해 빛이 얼마나 밝고 어두운지를 실시간으로 확인할 수 있으며, 이를 바탕으로 "밝기에 따른 LED 제어" 실습을 수행하게 됩니다.

<details>
  <summary>준비물</summary>
  - ESP32 보드 1개<br>
  - EPS32 쉴드(DOIT ESP32 DEVKIT V1) 1개<br>
  - USB 케이블(ESP32와 PC 연결용) 1개<br>
  - 조도 센서(Cds) 1개<br>
  - 점퍼 와이어(쉴드와 조도 센서 모듈 연결용) 1개<br>
  - Arduino IDE(코드 작성 및 업로드)<br>
</details>

<details>
  <summary>코드 설명</summary>
  - 쉴드의 입력 전용(Input Only) 중, GPIO 39번 핀을 사용하여 조도 센서의 값을 아날로그 신호 형태로 읽어들입니다.<br>
  - 읽어들인 아날로그 값(0 ~ 4095)은 빛의 양에 따라 변화하며, 값이 낮을수록 어두운 상태, 값이 높을수록 밝은 상태를 의미합니다.<br>
  - 시리얼 모니터를 통해 실시간으로 주변 환경의 밝기를 모니터링합니다.<br>
</details>

  <summary>응용(02-1_CdsSensorApplication)</summary>
  - 본 응용 프로젝트의 목적은 ESP32와 조도 센서를 사용하여 주변의 빛의 밝기를 측정하고, 그 값을 5단계로 구분하여 시리얼 모니터에 출력하는 것입니다.<br>
  이를 바탕으로 "밝고 어두운 정도에 따른 LED ON/OFF제어" 실습을 수행하게 됩니다.

---

# 03_DhtSensor

**목적**  
이 프로젝트의 목적은 **ESP32와 온/습도센서**를 사용하여 **주변 환경의 온도와 습도를 측정**하고, 그 값을 **시리얼 모니터**를 통해 실시간으로 확인하는 것입니다.<br>
이를 바탕으로 "실시간으로 측정된 온도와 습도값을 OLED 및 App에서 확인하는" 실습을 수행하게 됩니다.

<details>
  <summary>준비물</summary>
  - ESP32 보드 1개<br>
  - EPS32 쉴드(DOIT ESP32 DEVKIT V1) 1개<br>
  - USB 케이블(ESP32와 PC 연결용) 1개<br>
  - 온/습도 센서(DHT11) 1개
  - 점퍼 와이어(쉴드와 온/습도 센서 모듈 연결용) 1개<br>
  - Arduino IDE (코드 작성 및 업로드)<br>
  - DHT 라이브러리(Arduino IDE에서 설치, 본 실습에서는 "DHT sensor library" by Adafruit 사용)
</details>

<details>
  <summary>코드 설명</summary>
  - GPIO 14번 핀에 연결된 DHT11 센서로부터 온도와 습도 데이터를 읽어들입니다.<br>
  - 'DHT.h'헤더파일에 포함된 `dht.readTemperature()` 함수로 온도 값을, `dht.readHumidity()` 함수로 습도 값을 읽습니다.<br>
  - 읽어들인 값은 시리얼 모니터를 통해 출력되며, DHT11 센서는 특성 상 최소 2초 이상의 지연이 필요하므로, 'delay(2000)'를 사용합니다.<br>
</details>

---

# 04_OledTest

**목적**  
이 프로젝트의 목적은 **I2 통신C**을 통해 **OLED 디스플레이**에 특정 텍스트를 출력하는 것입니다.

<details>
  <summary>준비물</summary>
  - ESP32 보드 1개<br>
  - EPS32 쉴드(DOIT ESP32 DEVKIT V1) 1개<br>
  - USB 케이블(ESP32와 PC 연결용) 1개<br>
  - 128x64 OLED 디스플레이(SSD1306) 1개
  - 점퍼 와이어(쉴드와 OLED 모듈 연결용, 4핀) 1개<br>
  - Arduino IDE (코드 작성 및 업로드)<br>
  - Adafruit BusIO, Adafruit GFX 및 Adafruit SSD1306 라이브러리(Arduino IDE에서 설치, 본 실습에서는 "Adafruit SSD1306" by Adafruit 사용)
</details>

<details>
  <summary>코드 설명</summary>
  - I2C 통신을 사용하여 SSD1306 OLED 디스플레이에 텍스트를 출력합니다.<br>
  - 디스플레이의 해상도(128x64)를 설정하고, 디스플레이 객체를 초기화한 후 텍스트를 출력합니다.<br>
  - 텍스트는 총 4줄로 구성되어 있으며, "Smart Vivarium Test"와 "프로젝트 제작자 이름/닉네임"을 포함합니다.<br>
  - 'display.clearDisplay()'로 화면을 지우고(초기화), "display.setTextSize(2)"로 텍스트 크기를 두 배로 설정합니다.<br>
  - 'display.println()'과 'display.print()'를 사용하여 각 줄에 텍스트를 출력하며, 'display.display()'를 호출하여 내용을 OLED 화면에 텍스트를 출력합니다.<br>
  - 또한 프로그램이 정상적으로 작동하지 않을 경우, 시리얼 모니터에 오류 메시지를 출력한 후 무한 루프에 빠져 오류를 디버깅할 수 있게 설정되어 있습니다.<br>
</details>

  <summary>응용(04-1_OledControl)</summary>
  - 이 프로젝트의 목적은 위에서 살펴본 OLED에 Cds, DHT11 센서로 읽어들인 값을 출력함으로써 현재의 온도, 습도 및 밝기 정도(5단계)를 실시간으로 모니터링하는 것입니다.<br>

  ---

# 05_Button

**목적**  
이 프로젝트의 목적은 **버튼의 상태를 읽고 시리얼 모니터에 출력**하는 것입니다.<br>
버튼을 눌렀을때: 1, 누르지 않았을때: 0

<details>
  <summary>준비물</summary>
  - ESP32 보드 1개<br>
  - EPS32 쉴드(DOIT ESP32 DEVKIT V1) 1개<br>
  - USB 케이블(ESP32와 PC 연결용) 1개<br>
  - BUTTON 모듈 1개
  - 점퍼 와이어(쉴드와 BUTTON 모듈 연결용) 1개<br>
  - Arduino IDE (코드 작성 및 업로드)<br>
</details>

<details>
  <summary>코드 설명</summary>
  - 버튼 핀 설정: 'pinMode(BUTTON, INPUT)'을 사용하여 버튼 핀을 입력 모드로 설정합니다.<br>
  - 버튼 상태 읽기: 'digitalRead(BUTTON)'으로 버튼 핀의 디지털 입력 값을 읽어옵니다.<br>
  - 버튼 상태 출력: 읽어온 버튼 상태를 'Serial.println(buttonState)'을 사용하여 시리얼 모니터에 출력합니다.<br>
  - 디바운싱: 'delay(100)'을 사용하여 버튼 상태를 읽는 간격을 0.1초로 설정하여 입력 노이즈를 방지합니다.<br>
</details>

  <summary>응용(05-1_MaintainingButtonState)</summary>
 이 프로젝트의 목적은 "버튼을 한 번 눌렀을 때 버튼 상태를 0 또는 1로 유지하는 것"입니다. 버튼이 눌릴 때마다 상태를 토글하여 시리얼 모니터에 출력합니다.

 ---

 # 06_ButtonControlLed

**목적**  
이 프로젝트의 목적은 위에서 살펴본 **BUTTON을 활용**하여 **NeoPixel LED 스트립의 전원을 제어**하는 것입니다. 버튼을 눌렀을 때, NeoPixel LED가 켜지며, 버튼을 다시 누르면 NeoPixel LED 꺼집니다.<br>
추가로 NeoPixel Led의 색상은 식물의 광합성에 가장 효율적인 **청색**과 **적색**으로 설정하였습니다.<br>
참고: 본 프로젝트에서 제작할 비바리움의 크기(200*200*200)을 고려하여 LED(9구)*2개 = 18구를 직렬 연결(모듈 1개의 OUT 단자와 추가한 모듈의 IN 단자를 연결)하여 사용하였습니다. LED 출력 개수를 변경하고자 할 경우 'NUMPIXELS 18'의 개수 부분을 필요한 만큼 변경 가능합니다.

<details>
  <summary>준비물</summary>
  - ESP32 보드 1개<br>
  - EPS32 쉴드(DOIT ESP32 DEVKIT V1) 1개<br>
  - USB 케이블(ESP32와 PC 연결용) 1개<br>
  - BUTTON 모듈 1개
  - NeoPixel LED 스트립 모듈 2개(픽셀 수: 9구*2개 = 총 18구)<br>
  - 점퍼 와이어(쉴드와 BUTTON 모듈, LED 모듈 연결용) 총 3개<br>
  - Arduino IDE (코드 작성 및 업로드)<br>
  - Adafruit NeoPixel 라이브러리(Arduino IDE에서 설치, 본 실습에서는 "Adafruit NeoPixel" by Adafruit 사용)
</details>

<details>
  <summary>코드 설명</summary>
  - 버튼 상태 읽기: `digitalRead(BUTTON_PIN)`을 사용하여 버튼의 현재 상태를 읽어옵니다.<br>
  - 버튼 상태 변화 감지: 버튼의 상태가 변화했는지 확인하고, 상태가 `HIGH`일 때 LED 상태를 토글합니다.<br>
  - LED 색상 설정: `isOn` 변수에 따라 LED의 색상을 설정합니다. 버튼이 눌리면 짝수 인덱스의 LED를 빨간색으로, 홀수 인덱스의 LED를 파란색으로 설정합니다. 버튼이 눌리지 않으면 모든 LED를 꺼서 LED를 끕니다.<br>
  - 디바운싱: 버튼 입력의 노이즈를 방지하기 위해 짧은 지연을 추가합니다.<br>
</details>

---

# 07_ConnetingToBlynkByWifi

**목적**  
이 프로젝트의 목적은 **ESP32와 Blynk 클라우드 서버**를 이용하기 위해 기본적인 무선 **네트워크 연결 상태를 확인**하는 것입니다.

<details>
  <summary>준비물</summary>
  - ESP32 보드 1개<br>
  - EPS32 쉴드(DOIT ESP32 DEVKIT V1) 1개<br>
  - USB 케이블(ESP32와 PC 연결용) 1개<br>
  - 무선 네트워크 환경(ssid 입력 시 5[Ghz]는 불가능함에 유의, 2.4[Ghz] 사용)<br>
  - Arduino IDE (코드 작성 및 업로드)<br>
  - Blynk 라이브러리 (Arduino IDE에서 설치, 본 실습에서는 "Blynk" by Volodymyr Shymanskyy 사용)
</details>

<details>
  <summary>코드 설명</summary>
  - `Blynk.begin()` 함수를 사용하여 ESP32가 WiFi 네트워크와 Blynk 서버에 연결되도록 설정합니다.<br>
  - 내장 LED(2번 핀)를 제어하여 WiFi 및 Blynk 서버의 연결 상태를 시각적으로 확인할 수 있습니다.<br>
  - `Blynk.run()` 함수는 Blynk 라이브러리가 원활하게 동작하고, 서버와의 통신을 지속적으로 유지하도록 합니다.<br>
  - 연결 상태에 따라 ESP32에 내장된 LED를 깜빡이도록 하여, WiFi 연결 및 Blynk 서버에 연결된 상태를 육안으로 확인할 수 있습니다.<br>
  - WiFi가 연결된 경우: LED가 1초 간격으로 깜빡입니다.<br>
  - WiFi가 연결되지 않았거나, Blynk 서버에 연결되지 않은 경우: LED가 꺼져 있습니다.<br>
  - 참고로 `Serial.begin(9600)`은 시리얼 모니터에서 디버깅 정보를 확인할 수 있도록 설정하였으며, Blynk 서버와의 통신 상태를 확인하는 데 사용할 수 있습니다.
</details>

---

# 08_SmartVivariumV1

**목적**  
이 프로젝트의 목적은 **ESP32 개발보드**, **Blynk 서버**, **온/습도 센서**, **조도 센서**, **NeoPixel LED**, 그리고 **OLED 디스플레이**를 이용하여 **Smart Vivarium Version 1.0** 시스템을 구축하는 것입니다.<br>
이를 통해 실시간으로 스마트 비바리움의 환경 조건을 모니터링하고, Blynk 앱을 통해 원격으로 제어할 수 있습니다.

<details>
  <summary>준비물</summary>
  - ESP32 보드 1개<br>
  - 온/습도 센서 모듈 1개(DHT11)<br>
  - 조도 센서 모듈 1개<br>
  - NeoPixel LED (9개)<br>
  - SSD1306 OLED 디스플레이<br>
  - 버튼 (GPIO 23에 연결)<br>
  - USB 케이블 (ESP32와 PC 연결용)<br>
  - WiFi 네트워크 (SSID 및 비밀번호 필요)<br>
  - Blynk 템플릿 (Blynk 계정 및 인증 토큰 필요)<br>
  - Arduino IDE (코드 작성 및 업로드)<br>
  - 필요한 라이브러리 (Blynk, Adafruit SSD1306, Adafruit GFX, Adafruit NeoPixel, DHT)
</details>

<details>
  <summary>코드 설명</summary>
  - WiFi 및 Blynk 연결: `Blynk.begin()`을 사용하여 ESP32가 WiFi 네트워크와 Blynk 서버에 연결되도록 설정합니다.<br>
  - 온습도 측정: `dhtEvent()` 함수는 DHT11 센서를 사용하여 실시간으로 온도와 습도를 측정하고, 측정된 데이터를 Blynk 앱으로 전송합니다.<br>
  - 조도 측정: `cdsEvent()` 함수는 조도 센서(Cds)를 사용하여 빛의 밝기를 측정하고, 이를 Blynk 앱으로 전송합니다.<br>
  - OLED 디스플레이: `showDisplay()` 함수는 OLED 디스플레이에 실시간으로 측정된 온도, 습도, 조도 값을 출력합니다.<br>
  - NeoPixel 제어: `updateLEDState()` 함수는 NeoPixel LED의 상태를 제어하며, Blynk 앱 또는 버튼을 통해 켜고 끌 수 있습니다.<br>
  - 버튼 제어: `handleButtonPress()` 함수는 버튼을 눌렀을 때 NeoPixel LED 상태를 토글합니다. 버튼이 눌릴 때 LED 상태가 바뀌고, 변경된 상태는 Blynk 앱으로 전송됩니다.<br>
  - Blynk 앱 제어: `BLYNK_WRITE(V3)` 핸들러는 Blynk 앱에서 V3 가상 핀을 통해 LED를 제어하며, 앱에서 보내온 값을 기반으로 NeoPixel LED의 상태를 제어합니다.<br>
  - 타이머 설정: `timer.setInterval()` 함수를 사용하여 일정 시간마다 센서 데이터를 읽고, OLED 디스플레이를 갱신하며, Blynk 서버와 통신합니다.
</details>

---

# 09_RelayControlFan

**목적**  
이 프로젝트의 목적은 ESP32와 1채널 이상의 릴레이를 이용하여 5V 팬(DC)를 켜고 끄는 것입니다.<br>
이를 통해 릴레이의 목적 및 하드웨어 구성에 대해 이해하게 되며, 이후 스마트 비바리움의 환기 기능을 추가하기 위한 팬 및 이를 구동시키기 위한 릴레이의 구성에 대해 이해할 수 있습니다.

<details>
  <summary>준비물</summary>
  - ESP32 보드 1개<br>
  - EPS32 쉴드(DOIT ESP32 DEVKIT V1) 1개<br>
  - USB 케이블(ESP32와 PC 연결용) 1개<br>
  - DC 5V 팬 1개<br>
  - 1채널 이상의 릴레이 1개<br>
  - 외부 전압 공급원(DC 5V)<br>
  - 케이블(쉴드와 릴레이 연결용 최소 3개, 필요 시 외부 전압과 릴레이 및 팬 연결용 케이블 추가로 필요)<br>
  - Arduino IDE(코드 작성 및 업로드)<br>
</details>

<details>
  <summary>코드 설명</summary>
  - 쉴드의 입력 GPIO 5번 핀을 사용하여 릴레이 구동 신호를 보냅니다.<br>
  - 릴레이 및 팬이 올바르게 작동하는지를 육안으로 동시에 살펴보기 위해 5초 단위 릴레이 작동 명령 및 이를 살펴볼 수 있는 Serial Monitoring 기능을 활용합니다.<br>
  - 하드웨어 연결은 릴레이를 기준으로 하여 구동부는 ESP32 쉴드와 연결하고 동작부는 팬 및 외부 전원 공급원과 연결(외부 전원의 -단자와 릴레이의 COM단자 연결 및 외부 전원의 +단자에서 팬의 +단자, 이어서 팬의 -단자에서 릴레이의 NO단자와 연결) 합니다.<br>
</details>

---

# 10_SmartVivariumV1.1

**목적**  
이 프로젝트의 목적은 위에서 살펴본 V1의 하드웨어에 **릴레이와 5V 팬**을 추가하여 환기 기능을 사용할 수 있도록 발전시킨 것입니다.<br>
이를 통해 Blynk 앱(Datastream V4, Switch 기능 추가)을 통해 팬을 켜고 끌 수 있어, **과습 및 건조**의 문제 해결에 도움이 될 수 있습니다.

<details>
  <summary>준비물</summary>
  - 08_SmartVivariumV1에 해당하는 준비물
  - 위 준비물 외에 DC 5V 팬 1개, 1채널 이상의 릴레이 1개, 외부 전압 공급원(DC 5V), 케이블(쉴드와 릴레이 연결용 최소 3개, 필요 시 외부 전압과 릴레이 및 팬 연결용 케이블 추가로 필요)
</details>

<details>
  <summary>코드 설명</summary>
  - WiFi 및 Blynk 연결: `Blynk.begin()` 함수를 사용하여 ESP32가 WiFi 네트워크 및 Blynk 서버와 연결됩니다.<br>
  - 온습도 측정: `dhtEvent()` 함수는 DHT11 센서를 사용해 온도와 습도를 측정하고, Blynk 앱으로 전송합니다.<br>
  - 조도 측정: `cdsEvent()` 함수는 조도 센서(Cds)로 빛의 밝기를 측정하고, 그 값을 Blynk 앱으로 전송합니다.<br>
  - OLED 디스플레이: `showDisplay()` 함수는 OLED 디스플레이에 실시간으로 온도, 습도, 조도 값을 출력합니다.<br>
  - NeoPixel 제어* `updateLEDState()` 함수는 NeoPixel LED를 제어하며, Blynk 앱과 버튼을 통해 제어할 수 있습니다.<br>
  - 팬 제어: `updateFanState()` 함수는 릴레이를 사용하여 팬을 제어하며, Blynk 앱의 V4 가상 핀을 통해 원격으로 팬을 켜고 끕니다.<br>
  - 버튼 제어: `handleButtonPress()` 함수는 버튼을 통해 NeoPixel LED 상태를 변경하며, 그 값을 Blynk 앱으로 전송합니다.<br>
  - Blynk V3 핸들러: 앱에서 V3 가상 핀으로 NeoPixel LED를 제어합니다.<br>
  - Blynk V4 핸들러: 앱에서 V4 가상 핀으로 팬을 제어합니다.<br>
  - 타이머 설정: `timer.setInterval()` 함수를 사용하여 주기적으로 센서 데이터를 읽고, OLED 디스플레이를 갱신하며, Blynk 서버와 통신합니다.
</details>


# 스마트 비바리움 제작 프로젝트
**목적**<br>
이 프로젝트는 초/중등 교원을 대상으로 스마트 비비리움 제작 연수를 위해 시작하였습니다.<br>
**준비물**<br>
ESP32 보드, DOIT ESP32 DEVKIT V1, 온/습도 센서, 조도 센서, 버튼, OLED, NeoPixel LED, 무선 네트워크 환경, 구글 계정 등(세부 준비물 내역은 아래 소단위 프로젝트마다 제시함.)<br>
**프로젝트의 흐름**<br>
01~07까지 소단위 프로젝트를 순차적으로 실행해가며, ESP32 및 각종 센서, 액추에이터의 활용 방법, Blynk 연동 방법 등을 살펴볼 수 있고, 최종 목적지인 08번 프로젝트에서는 스마트 비바리움의 IoT 파트를 완성할 수 있도록 구성하였습니다.<br>
<details>
  <summary>환경 구축(최초 1회)</summary>
  1. OS에 맞는 [Arduino IDE 설치](https://www.arduino.cc/en/software)<br>
  2. 필요한 경우 시스템 언어 변경(File/Arduino IED->Preferences->재시작)<br>
  3. 기본 설정->추가 보드 관리자 URL->'비공식 보드 지원 URL 목록을 보려면 클릭하십시오.' 클릭->'Espressif ESP32' 검색->해당 '*.json'파일 복사/붙여넣기 후 확인<br>
  4. 보드 매니저->'esp32 by Espressif Systems'설치<br>
  5. PC와 ESP32 연결<br>
  6. 보드 및 포트를 아래와 같이 연결<br>
     - 보드: DOIT ESP32 DEVKIT V1<br>
     - 포트: Serial Port(USB), 포트 번호는 COM4, COM3 등으로 다를 수 있음.<br>
  7. [ESP32 업로드 에러 발생 시][https://docs.google.com/presentation/d/1MqSPEBPEWeh-agVcmBz7CRioSePWG-13oV_nJNzy-uo/edit?usp=sharing]<br>
  <summary>7. (When ESP32 upload error occurs)</summary>
  <a href="https://docs.google.com/presentation/d/1MqSPEBPEWeh-agVcmBz7CRioSePWG-13oV_nJNzy-uo/edit?usp=sharing">Google Slides Presentation</a>
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
이 프로젝트의 목적은 **ESP32 보드가 제대로 작동하는지 확인**하는 것입니다. 이를 위해 **내장된 LED를 제어**하여 **1초 간격**으로 켜고 끄는 동작을 수행합니다. 학생들은 이를 통해 **디지털 출력 제어**와 **기본적인 딜레이 함수**의 사용법을 학습할 수 있습니다.

<details>
  <summary>준비물</summary>
  - ESP32 개발 보드<br>
  - USB 케이블(ESP32와 PC 연결용)<br>
  - Arduino IDE (코드 작성 및 업로드)<br>
</details>

<details>
  <summary>코드 설명</summary>
  이 실습에서는 ESP32 내장 LED를 활용하여 간단한 점멸 제어를 수행합니다.<br>
  GPIO 2번 핀에 연결된 내장 LED를 1초마다 켜고 끄는 동작을 반복하게 됩니다.<br>
  이를 통해 ESP32가 **정상적으로 작동하는지** 확인할 수 있습니다.  
</details>

---

# 02_CdsSensor

**목적**  
이 프로젝트의 목적은 **ESP32와 조도 센서(Cds)**를 이용하여 **주변 빛의 양**을 측정하고, **시리얼 모니터**를 통해 실시간으로 확인하는 것입니다. 조도 센서를 통해 빛이 얼마나 **밝거나 어두운지** 확인할 수 있으며, 이를 기반으로 **조명 제어** 등의 스마트 홈 시스템으로 확장할 수 있습니다.

<details>
  <summary>준비물</summary>
  - ESP32 개발 보드<br>  
  - 조도 센서(Cds)<br>
  - 점퍼 와이어<br>
  - USB 케이블(ESP32와 PC 연결용)<br>
  - Arduino IDE(코드 작성 및 업로드)<br>
</details>

<details>
  <summary>코드 설명</summary>
  - GPIO 39번 핀을 사용하여 조도 센서의 아날로그 값을 읽어들입니다.<br> 
  - 시리얼 모니터를 통해 실시간으로 빛의 강도를 모니터링합니다.<br>
  - delay(1000)을 사용해 1초 간격으로 값을 출력하여 효율적인 모니터링을 구현합니다.<br>
  - 읽어들인 아날로그 값(0 ~ 4095)은 빛의 양에 따라 변화하며, 값이 낮을수록 어두운 상태, 값이 높을수록 밝은 상태를 의미합니다.<br>
</details>

  <summary>응용(02-1_CdsSensorApplication)</summary>
  - ESP32와 조도 센서를 사용하여 주변의 빛의 밝기를 측정하고, 그 값을 5단계(매우 어두움, 어두움, 보통, 밝음, 매우 밝음)로 구분하여 시리얼 모니터에 출력하는 것입니다. 이 코드를 통해 조도 값을 기반으로 환경의 밝기 상태를 효과적으로 모니터링할 수 있습니다.

---

# 03_DhtSensor

**목적**  
이 프로젝트의 목적은 **ESP32와 DHT11 센서**를 사용하여 **주변 환경의 온도와 습도를 측정**하고, 그 값을 **시리얼 모니터**를 통해 실시간으로 확인하는 것입니다. 이 프로젝트는 **온도와 습도 데이터를 활용한 환경 모니터링** 시스템의 기초가 됩니다.

<details>
  <summary>준비물</summary>
  - ESP32 개발 보드<br>
  - DHT11 온습도 센서<br>
  - 점퍼 와이어<br>
  - USB 케이블 (ESP32와 PC 연결용)<br>
  - Arduino IDE (코드 작성 및 업로드)<br>
  - DHT 라이브러리 (Arduino IDE에서 설치, 본 실습에서는 DHT sensor library by Adafruit 사용)<br>
</details>

<details>
  <summary>코드 설명</summary>
  - GPIO 14번 핀에 연결된 DHT11 센서로부터 온도와 습도 데이터를 읽어들입니다.<br>
  - `dht.readTemperature()` 함수로 온도 값을, `dht.readHumidity()` 함수로 습도 값을 읽습니다.<br>
  - 읽어들인 값은 시리얼 모니터를 통해 출력되며, 2초 간격으로 데이터를 갱신합니다.<br>
  - DHT11 센서는 2초 이상의 딜레이가 필요하므로, 각 데이터 읽기 전 `delay(2000)`을 사용합니다.<br>
  - 9600 baud rate로 시리얼 통신을 설정하여, 읽어들인 데이터를 출력합니다.<br>
</details>

---

# 04_OledTest

**목적**  
이 프로젝트의 목적은 **ESP32와 OLED 디스플레이**를 이용하여 **스마트 비바리움(Smart Vivarium)**의 텍스트를 화면에 출력하는 것입니다. 학생들이 **I2C 통신**을 통해 디스플레이를 제어하는 방법과, **텍스트 출력**을 배울 수 있습니다.

<details>
  <summary>준비물</summary>
  - ESP32 개발 보드<br>
  - 128x64 OLED 디스플레이 (SSD1306)<br>
  - 점퍼 와이어<br>
  - USB 케이블(ESP32와 PC 연결용)<br>
  - Arduino IDE (코드 작성 및 업로드)<br>
  - Adafruit GFX 및 Adafruit SSD1306 라이브러리** (Arduino IDE에서 설치, 본 실습에서는 Adafruit SSD1306 by Adafruit 사용)<br>
</details>

<details>
  <summary>코드 설명</summary>
  - I2C 통신을 사용하여 SSD1306 OLED 디스플레이에 텍스트를 출력합니다.<br>
  - 디스플레이의 해상도(128x64)를 설정하고, 디스플레이 객체를 초기화한 후 텍스트를 출력합니다.<br>
  - 텍스트는 3줄로 구성되어 있으며, "Smart Vivarium"과 프로젝트 제작자 이름/닉네임을 포함합니다.<br>
  - `display.clearDisplay()`로 화면을 지우고, `display.setTextSize(2)`로 텍스트 크기를 두 배로 설정합니다.<br>
  - `display.println()`과 `display.print()`를 사용하여 각 줄에 텍스트를 출력하며, `display.display()`를 호출하여 내용을 OLED 화면에 실제로 출력합니다.<br>
  - 프로그램이 정상적으로 작동하지 않을 경우, 시리얼 모니터에 오류 메시지를 출력한 후 무한 루프에 빠져 오류를 디버깅할 수 있게 설정되어 있습니다.<br>
</details>

  <summary>응용(04-1_OledControl)</summary>
  - 이 프로젝트의 목적은 위에서 살펴본 Cds 센서와 DHT 센서로 읽어들인 값을 OLED를 활용하여 현재의 온도, 습도, 조도 상태를 실시간으로 모니터링하는 것입니다.<br>

  ---

# 05_Button

**목적**  
이 프로젝트의 목적은 **버튼의 상태를 읽고 시리얼 모니터에 출력**하는 것입니다. 버튼을 눌렀을 때의 상태를 모니터링하고, 이를 통해 버튼 입력 처리의 기본을 이해할 수 있습니다.

<details>
  <summary>준비물</summary>
  - ESP32 개발 보드<br>
  - 버튼<br>
  - 점퍼 와이어<br>
  - USB 케이블 (ESP32와 PC 연결용)<br>
  - Arduino IDE (코드 작성 및 업로드)<br>
</details>

<details>
  <summary>코드 설명</summary>
  - 버튼 핀 설정: `pinMode(BUTTON, INPUT)`을 사용하여 버튼 핀을 입력 모드로 설정합니다.<br>
  - 시리얼 통신 설정: `Serial.begin(9600)`으로 시리얼 통신의 전송 속도를 9600bps로 설정합니다.<br>
  - 버튼 상태 읽기: `digitalRead(BUTTON)`으로 버튼 핀의 디지털 입력 값을 읽어옵니다.<br>
  - 버튼 상태 출력: 읽어온 버튼 상태를 `Serial.println(buttonState)`를 사용하여 시리얼 모니터에 출력합니다.<br>
  - 딜레이 추가: `delay(100)`을 사용하여 버튼 상태를 읽는 간격을 100밀리초로 설정하여 입력 노이즈를 방지합니다.<br>
</details>

  <summary>응용(05-1_MaintainingButtonState)</summary>
 이 프로젝트의 목적은 버튼을 한 번 눌렀을 때 버튼 상태를 0 또는 1로 유지하는 것입니다. 버튼이 눌릴 때마다 상태를 토글하여 시리얼 모니터에 출력합니다.

 ---

 # 06_ButtonControlLed

**목적**  
이 프로젝트의 목적은 위에서 살펴본 **버튼을 활용**하여 **NeoPixel LED 스트립의 전원을 제어**하는 것입니다. 버튼을 눌렀을 때, NeoPixel LED가 켜지며, 버튼을 다시 누르면 NeoPixel LED 꺼집니다.<br>
추가로 NeoPixel Led의 색상은 식물의 광합성에 가장 효율적인 **청색**과 **적색**으로 설정하였습니다.

<details>
  <summary>준비물</summary>
  - ESP32 개발 보드<br>
  - NeoPixel LED 스트립 (픽셀 수: 9)<br>
  - 버튼<br>
  - 점퍼 와이어<br>
  - USB 케이블 (ESP32와 PC 연결용)<br>
  - Arduino IDE (코드 작성 및 업로드)<br>
  - Adafruit NeoPixel 라이브러리(Arduino IDE에서 설치, 본 실습에서는 Adafruit NeoPixel by Adafruit 사용)<br>
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
  - ESP32 개발 보드<br>
  - USB 케이블(ESP32와 PC 연결용)<br>
  - WiFi 네트워크 (SSID 및 비밀번호 필요. 5G는 연결이 안되므로 주의할 것)<br>
  - Blynk 템플릿 (Blynk 계정 및 인증 토큰 필요)<br>
  - Arduino IDE (코드 작성 및 업로드)<br>
  - Blynk 라이브러리 (Arduino IDE에서 설치, 본 실습에서는 Blynk by Volodymyr Shymanskyy 사용)<br>
</details>

<details>
  <summary>코드 설명</summary>
  - `Blynk.begin()` 함수를 사용하여 ESP32가 WiFi 네트워크와 Blynk 서버에 연결되도록 설정합니다.<br>
  - 내장 LED(2번 핀)를 제어하여 WiFi 및 Blynk 서버의 연결 상태를 시각적으로 확인할 수 있습니다.<br>
  - `Blynk.run()` 함수는 Blynk 라이브러리가 원활하게 동작하고, 서버와의 통신을 지속적으로 유지하도록 합니다.<br>
  - 연결 상태에 따라 LED를 깜빡이도록 하여, WiFi가 연결된 상태와 Blynk 서버에 연결된 상태를 눈으로 확인할 수 있습니다.<br>
  - WiFi가 연결된 경우: LED가 1초 간격으로 깜빡입니다.<br>
  - WiFi가 연결되지 않았거나, Blynk 서버에 연결되지 않은 경우: LED가 꺼져 있습니다.<br>
  - `Serial.begin(9600)`은 시리얼 모니터에서 디버깅 정보를 확인할 수 있도록 설정하였으며, Blynk 서버와의 통신 상태를 확인하는 데 사용할 수 있습니다.<br>
</details>

---

# 08_SmartVivariumV1

**목적**  
이 프로젝트의 목적은 **ESP32**, **Blynk**, **DHT11 센서**, **조도 센서(Cds)**, **NeoPixel**, 그리고 **OLED 디스플레이**를 이용하여 **스마트 비바리움(Smart Vivarium)** 시스템을 구축하는 것입니다. 이 시스템을 통해 실시간으로 환경 데이터를 모니터링하고, Blynk 앱을 통해 원격으로 제어할 수 있습니다.

<details>
  <summary>준비물</summary>
  - ESP32 개발 보드<br>
  - DHT11 온습도 센서<br>
  - 조도 센서(Cds)<br>
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

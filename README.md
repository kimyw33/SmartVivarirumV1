# 01_BuiltInLedControl

**목적**  
이 프로젝트의 목적은 **ESP32 보드가 제대로 작동하는지 확인**하는 것입니다. 이를 위해 **내장된 LED를 제어**하여 **1초 간격**으로 켜고 끄는 동작을 수행합니다. 학생들은 이를 통해 **디지털 출력 제어**와 **기본적인 딜레이 함수**의 사용법을 학습할 수 있습니다.

<details>
  <summary>준비물</summary>
  - ESP32 개발 보드<br>
  - USB 케이블 (ESP32와 PC 연결용)<br>
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
  - 조도 센서 (Cds)<br>
  - 점퍼 와이어<br>
  - USB 케이블 (ESP32와 PC 연결용)<br>
  - Arduino IDE (코드 작성 및 업로드)<br>
</details>

<details>
  <summary>코드 설명</summary>
  - GPIO 39번 핀을 사용하여 조도 센서의 아날로그 값을 읽어들입니다.<br> 
  - 시리얼 모니터를 통해 실시간으로 빛의 강도를 모니터링합니다.<br>
  - `delay(1000)`을 사용해 1초 간격으로 값을 출력하여 효율적인 모니터링을 구현합니다.<br>
  - 읽어들인 아날로그 값(0 ~ 4095)은 빛의 양에 따라 변화하며, 값이 낮을수록 어두운 상태, 값이 높을수록 밝은 상태를 의미합니다.<br>
</details>

<details>
  <summary>응용(02-1_CdsSensorApplication)</summary>
  - ESP32와 조도 센서를 사용하여 주변의 빛의 밝기를 측정하고, 그 값을 5단계로 구분하여 시리얼 모니터에 출력하는 것입니다. 이 코드를 통해 조도 값을 기반으로 환경의 밝기 상태를 효과적으로 모니터링할 수 있습니다.<br>
  - 읽어들인 값을 5단계로 구분하여:<br>
    - 매우 어두움: 0 ~ 819<br>
    - 어두움: 820 ~ 1629<br>
    - 보통: 1630 ~ 2449<br>
    - 밝음: 2450 ~ 3269<br>
    - 매우 밝음: 3270 ~ 4095<br>
  - 각 단계에 맞는 밝기 상태를 시리얼 모니터에 출력합니다.<br>
  - `delay(1000)`을 통해 1초 간격으로 값을 출력하여 효율적인 모니터링을 구현합니다.  
</details>

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
  - 읽어들인 값은 시리얼 모니터를 통해 출력되며, **2초 간격**으로 데이터를 갱신합니다.<br>
  - DHT11 센서는 2초 이상의 딜레이가 필요하므로, 각 데이터 읽기 전 `delay(2000)`을 사용합니다.<br>
  - 9600 baud rate로 시리얼 통신을 설정하여, 읽어들인 데이터를 출력합니다.<br>
</details>

---

# 04_OledTest

**목적**  
이 프로젝트의 목적은 **ESP32와 OLED 디스플레이**를 이용하여 **스마트 비바리움(Smart Vivarium)**의 텍스트를 화면에 출력하는 것입니다. 학생들이 **I2C 통신**을 통해 디스플레이를 제어하는 방법과, **텍스트 출력**을 배울 수 있습니다.

<details>
  <summary>준비물</summary>
  - **ESP32 개발 보드**<br>
  - **128x64 OLED 디스플레이 (SSD1306)**<br>
  - **점퍼 와이어**<br>
  - **USB 케이블 (ESP32와 PC 연결용)**<br>
  - **Arduino IDE (코드 작성 및 업로드)**<br>
  - **Adafruit GFX 및 Adafruit SSD1306 라이브러리** (Arduino IDE에서 설치, 본 실습에서는 Adafruit SSD1306 by Adafruit 사용)<br>
</details>

<details>
  <summary>코드 설명</summary>
  - **I2C 통신**을 사용하여 **SSD1306 OLED 디스플레이**에 텍스트를 출력합니다.<br>
  - 디스플레이의 **해상도(128x64)**를 설정하고, 디스플레이 객체를 초기화한 후 텍스트를 출력합니다.<br>
  - 텍스트는 3줄로 구성되어 있으며, "Smart Vivarium"과 **프로젝트 제작자 이름/닉네임**을 포함합니다.<br>
  - `display.clearDisplay()`로 화면을 지우고, `display.setTextSize(2)`로 텍스트 크기를 두 배로 설정합니다.<br>
  - `display.println()`과 `display.print()`를 사용하여 각 줄에 텍스트를 출력하며, `display.display()`를 호출하여 내용을 OLED 화면에 실제로 출력합니다.<br>
  - 프로그램이 정상적으로 작동하지 않을 경우, 시리얼 모니터에 오류 메시지를 출력한 후 무한 루프에 빠져 오류를 디버깅할 수 있게 설정되어 있습니다.<br>
</details>

<details>
  <summary>응용(04-1_OledControl)</summary>
  - 이 프로젝트의 목적은 위에서 살펴본 Cds 센서와 DHT 센서로 읽어들인 값을 OLED를 활용하여 현재의 온도, 습도, 조도 상태를 실시간으로 모니터링하는 것입니다.<br>
</details>
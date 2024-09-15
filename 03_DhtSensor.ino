#include <DHT.h>  // DHT 센서를 사용하기 위한 라이브러리

#define DHTPIN 14  // DHT 센서를 연결한 핀 번호 (GPIO 14)
#define DHTTYPE DHT11  // DHT 센서의 종류 (DHT11)

DHT dht(DHTPIN, DHTTYPE);  // DHT 객체 생성, 핀 번호와 센서 타입을 설정

void setup() {
  Serial.begin(9600);  // 시리얼 통신 시작 (9600 baud rate)
  dht.begin();  // DHT 센서 시작
}

void loop() {
  delay(2000);  // 센서 값을 읽기 전에 2초 대기 (DHT11 센서 특성상 최소 2초 딜레이 필요)
  float h = dht.readHumidity();  // 습도 값을 읽음
  float t = dht.readTemperature();  // 온도 값을 읽음
  
  Serial.print("Temp: ");  // 온도 출력
  Serial.print(t);  // 읽어들인 온도 값 출력
  Serial.print(", ");  
  Serial.print("Humi: ");  // 습도 출력
  Serial.println(h);  // 읽어들인 습도 값 출력
}

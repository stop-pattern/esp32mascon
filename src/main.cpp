#include <Arduino.h>
#include <USB.h>
#include <USBHIDGamepad.h>

USBHIDGamepad gamepad;

void testAxises();
void testKeys();
void testHats();

void setup() {
    Serial.begin(115200);
    log_d("setup");
    gamepad.begin();
    USB.begin();
    delay(1000);
}

void loop() {
    log_d("test: leftStick");
    testAxises();
    delay(1000);
    log_d("test: hat");
    testHats();
    delay(1000);
    gamepad.hat(0);
    log_d("test: btn");
    delay(1000);
    testKeys();
}

void testAxises(){
  // -255から255までの値を1つずつ入力
  for(int i = INT8_MIN; i <= INT8_MAX; i++){
    gamepad.leftStick(i, i);
    delay(10);
  }
  delay(100);
  for(int i = INT8_MIN; i <= INT8_MAX; i++){
    gamepad.rightStick(i, i);
    delay(10);
  }
  delay(100);
  for(int i = INT8_MIN; i <= INT8_MAX; i++){
    gamepad.leftTrigger(i);
    delay(10);
  }
  delay(100);
  for(int i = INT8_MIN; i <= INT8_MAX; i++){
    gamepad.rightTrigger(i);
    delay(10);
  }
  gamepad.leftStick(0, 0);
  gamepad.rightStick(0, 0);
  gamepad.leftTrigger(0);
  gamepad.rightTrigger(0);
}
void testKeys(){
  // 0から32までのキーを1つずつ押す
  for(int i = 0; i < 32; i++){
    gamepad.pressButton(i);
    delay(100);
    gamepad.releaseButton(i);
  }
}
void testHats(){
  // 0から7までのキーを1つずつ押す
  for(int i = 0; i < 8; i++){
    gamepad.hat(i);
    delay(100);
  }
  gamepad.hat(0);
}
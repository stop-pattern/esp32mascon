#include "USBHID.h"

#if CONFIG_TINYUSB_HID_ENABLED

#include "Descriptor.h"
#include "Gamepad.h"

static const uint8_t report_descriptor[] = {
    HID_REPORT_DESC_GAMEPAD(HID_REPORT_ID(HID_REPORT_ID_GAMEPAD))
};

Gamepad::Gamepad(): hid(), _x(0), _y(0), _z(0), _rx(0), _ry(0), _rz(0), _slider(0), _dial(0), _hat(0), _buttons(0){
    static bool initialized = false;
    if(!initialized){
        initialized = true;
        hid.addDevice(this, sizeof(report_descriptor));
    }
}

uint16_t Gamepad::_onGetDescriptor(uint8_t* dst){
    memcpy(dst, report_descriptor, sizeof(report_descriptor));
    return sizeof(report_descriptor);
}

void Gamepad::begin(){
    hid.begin();
}

void Gamepad::end(){
    hid.end();
}

bool Gamepad::write(){
    gamepad_report_t report = {
        .x       = _x,
        .y       = _y,
        .z       = _z,
        .rx      = _rx,
        .ry      = _ry,
        .rz      = _rz,
        .slider  = _slider,
        .dial    = _dial,
        .hat     = _hat,
        .buttons = _buttons
    };
    return hid.SendReport(HID_REPORT_ID_GAMEPAD, &report, sizeof(report));
}

bool Gamepad::leftStick(int16_t x, int16_t y){
    _x = x;
    _y = y;
    return write();
}

bool Gamepad::rightStick(int16_t z, int16_t rz){
    _z = z;
    _rz = rz;
    return write();
}

bool Gamepad::leftTrigger(int16_t rx){
    _rx = rx;
    return write();
}

bool Gamepad::rightTrigger(int16_t ry){
    _ry = ry;
    return write();
}

bool Gamepad::hat(uint8_t hat){
    if(hat > 9){
        return false;
    }
    _hat = hat;
    return write();
}

bool Gamepad::pressButton(uint8_t button){
    if(button > 31){
        return false;
    }
    _buttons |= (1 << button);
    return write();
}

bool Gamepad::releaseButton(uint8_t button){
    if(button > 31){
        return false;
    }
    _buttons &= ~(1 << button);
    return write();
}

bool Gamepad::send(int16_t x, int16_t y, int16_t z, int16_t rz, int16_t rx, int16_t ry, uint8_t hat, uint32_t buttons){
    if(hat > 9){
        return false;
    }
    _x = x;
    _y = y;
    _z = z;
    _rz = rz;
    _rx = rx;
    _ry = ry;
    _hat = hat;
    _buttons = buttons;
    return write();
}

bool Gamepad::send(int16_t x, int16_t y, int16_t z, int16_t rz, int16_t rx, int16_t ry, int16_t slider, int16_t dial, uint8_t hat, uint32_t buttons){
    if(hat > 9){
        return false;
    }
    _x = x;
    _y = y;
    _z = z;
    _rz = rz;
    _rx = rx;
    _ry = ry;
    _slider = slider;
    _dial = dial;
    _hat = hat;
    _buttons = buttons;
    return write();
}

bool Gamepad::setAxes(int16_t x, int16_t y, int16_t z, int16_t rz, int16_t rx, int16_t ry) {
    _x = x;
    _y = y;
    _z = z;
    _rz = rz;
    _rx = rx;
    _ry = ry;
    return write();
}

bool Gamepad::setAxes(int16_t x, int16_t y, int16_t z, int16_t rz, int16_t rx, int16_t ry, int16_t slider, int16_t dial){
    _x = x;
    _y = y;
    _z = z;
    _rz = rz;
    _rx = rx;
    _ry = ry;
    _slider = slider;
    _dial = dial;
    return write();
}

bool Gamepad::setAxesX(int16_t x){
    _x = x;
    return write();
}

bool Gamepad::setAxesY(int16_t y){
    _y = y;
    return write();
}

bool Gamepad::setAxesZ(int16_t z){
    _z = z;
    return write();
}

bool Gamepad::setAxesRz(int16_t rz){
    _rz = rz;
    return write();
}

bool Gamepad::setAxesRx(int16_t rx){
    _rx = rx;
    return write();
}

bool Gamepad::setAxesRy(int16_t ry){
    _ry = ry;
    return write();
}

bool Gamepad::setSlider(int16_t slider){
    _slider = slider;
    return write();
}

bool Gamepad::setDial(int16_t dial){
    _dial = dial;
    return write();
}

bool Gamepad::setHat(uint8_t hat){
    _hat = hat;
    return write();
}

bool Gamepad::setButton(uint8_t button, bool pressed){
    if(button > 31){
        return false;
    }
    _buttons |= (pressed << button);
    return write();
}

bool Gamepad::setButtons(uint32_t buttons){
    _buttons = buttons;
    return write();
}

#endif /* CONFIG_TINYUSB_HID_ENABLED */

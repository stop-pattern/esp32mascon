#ifndef GAMEPAD_H
#define GAMEPAD_H

#pragma once
#include <USBHID.h>
#if CONFIG_TINYUSB_HID_ENABLED

typedef struct TU_ATTR_PACKED
{
    int16_t  x;        ///< Delta x  movement of left analog-stick
    int16_t  y;        ///< Delta y  movement of left analog-stick
    int16_t  z;        ///< Delta z  movement of right analog-joystick
    int16_t  rx;       ///< Delta Rx movement of analog left trigger
    int16_t  ry;       ///< Delta Ry movement of analog right trigger
    int16_t  rz;       ///< Delta Rz movement of right analog-joystick
    int16_t  slider;   ///< Delta Slider movement
    int16_t  dial;     ///< Delta Dial movement
    uint8_t hat;       ///< Buttons mask for currently pressed buttons in the DPad/hat
    uint32_t buttons;  ///< Buttons mask for currently pressed buttons
} gamepad_report_t;

/**
 * @brief Represents a gamepad device that communicates via a USB HID interface.
 *
 * The Gamepad class provides methods for controlling gamepad components such as analog sticks,
 * triggers, DPad (hat), and buttons. It extends the USBHIDDevice to send HID reports corresponding
 * to the current state of the gamepad.
 *
 * @note The class encapsulates both the state of the axes (sticks and triggers) and button presses,
 *       providing convenient methods to update and send the state.
 * @note compatible with TinyUSB HID class driver.
 */
class Gamepad : public USBHIDDevice {
private:
    /**
     * @brief USB HID instance used for communication.
     */
    USBHID hid;

    /**
     * @brief Delta x movement of the left analog stick.
     */
    int16_t  _x;

    /**
     * @brief Delta y movement of the left analog stick.
     */
    int16_t  _y;

    /**
     * @brief Delta z movement of the right analog stick.
     */
    int16_t  _z;

    /**
     * @brief Delta Rx movement of the left trigger (analog).
     */
    int16_t  _rx;

    /**
     * @brief Delta Ry movement of the right trigger (analog).
     */
    int16_t  _ry;

    /**
     * @brief Delta Rz movement of the right analog stick.
     */
    int16_t  _rz;

    /**
     * @brief Delta slider movement of the right trigger (analog).
     */
    int16_t  _slider;

    /**
     * @brief Delta Dial movement of the right trigger (analog).
     */
    int16_t  _dial;

    /**
     * @brief Buttons mask for the currently pressed buttons in the DPad/hat.
     */
    uint8_t _hat;

    /**
     * @brief Buttons mask for the currently pressed buttons.
     */
    uint32_t _buttons;

    /**
     * @brief Writes the current state to the USB HID device.
     *
     * Internal use function that sends the updated gamepad state.
     *
     * @return true if the data was successfully sent, false otherwise.
     */
    bool write();

public:
    /**
     * @brief Constructs a new Gamepad object.
     */
    Gamepad(void);

    /**
     * @brief Initializes the gamepad and sets up USB HID communication.
     * @note compatible with TinyUSB HID class driver.
     */
    void begin(void);

    /**
     * @brief Terminates the gamepad's USB HID communication.
     */
    void end(void);

    /**
     * @brief Updates the left analog stick position.
     *
     * @param x The x-axis position.
     * @param y The y-axis position.
     * @return true if the position was successfully updated, false otherwise.
     * @note compatible with TinyUSB HID class driver.
     */
    bool leftStick(int16_t x, int16_t y);

    /**
     * @brief Updates the right analog stick position.
     *
     * @param z The z-axis position.
     * @param rz The Rz-axis position.
     * @return true if the position was successfully updated, false otherwise.
     * @note compatible with TinyUSB HID class driver.
     */
    bool rightStick(int16_t z, int16_t rz);

    /**
     * @brief Updates the left trigger analog value.
     *
     * @param rx The left trigger axis value.
     * @return true if the value was successfully updated, false otherwise.
     * @note compatible with TinyUSB HID class driver.
     */
    bool leftTrigger(int16_t rx);

    /**
     * @brief Updates the right trigger analog value.
     *
     * @param ry The right trigger axis value.
     * @return true if the value was successfully updated, false otherwise.
     * @note compatible with TinyUSB HID class driver.
     */
    bool rightTrigger(int16_t ry);

    /**
     * @brief Updates the hat (D-pad) state.
     *
     * @param hat The hat value representing the current DPad/hat direction.
     * @return true if the hat state was successfully updated, false otherwise.
     * @note compatible with TinyUSB HID class driver.
     */
    bool hat(uint8_t hat);

    /**
     * @brief Presses a specified button.
     *
     * @param button The identifier of the button to press.
     * @return true if the button state was successfully updated, false otherwise.
     * @note compatible with TinyUSB HID class driver.
     */
    bool pressButton(uint8_t button);

    /**
     * @brief Releases a specified button.
     *
     * @param button The identifier of the button to release.
     * @return true if the button state was successfully updated, false otherwise.
     * @note compatible with TinyUSB HID class driver.
     */
    bool releaseButton(uint8_t button);

    /**
     * @brief Sends the complete state of the gamepad.
     *
     * Updates and transmits the state including analog sticks, triggers, DPad/hat, and buttons.
     *
     * @param x The left analog stick x-axis value.
     * @param y The left analog stick y-axis value.
     * @param z The right analog stick z-axis value.
     * @param rz The right analog stick Rz-axis value.
     * @param rx The left trigger analog value.
     * @param ry The right trigger analog value.
     * @param hat The DPad/hat state.
     * @param buttons The bitmask representing the state of all buttons.
     * @return true if the state was successfully sent, false otherwise.
     * @note compatible with TinyUSB HID class driver.
     */
    bool send(int16_t x, int16_t y, int16_t z, int16_t rz, int16_t rx, int16_t ry, uint8_t hat, uint32_t buttons);

    /**
     * @brief Sends the complete state of the gamepad.
     *
     * Updates and transmits the state including analog sticks, triggers, DPad/hat, and buttons.
     *
     * @param x The left analog stick x-axis value.
     * @param y The left analog stick y-axis value.
     * @param z The right analog stick z-axis value.
     * @param rz The right analog stick Rz-axis value.
     * @param rx The left trigger analog value.
     * @param ry The right trigger analog value.
     * @param slider The slider value.
     * @param dial The dial value.
     * @param hat The DPad/hat state.
     * @param buttons The bitmask representing the state of all buttons.
     * @return true if the state was successfully sent, false otherwise.
     * @note compatible with TinyUSB HID class driver.
     */
    bool send(int16_t x, int16_t y, int16_t z, int16_t rz, int16_t rx, int16_t ry, int16_t slider, int16_t dial, uint8_t hat, uint32_t buttons);

    /**
     * @brief Retrieves the HID descriptor.
     *
     * Internal function used to fill the buffer with the USB HID descriptor.
     *
     * @param buffer Pointer to the buffer where the descriptor will be stored.
     * @return uint16_t The length of the HID descriptor.
     */
    uint16_t _onGetDescriptor(uint8_t* buffer);

    /**
     * @brief Sets all analog axes of the gamepad.
     *
     * Simultaneously updates the positions of both analog sticks and triggers.
     *
     * @param x The left analog stick x-axis value.
     * @param y The left analog stick y-axis value.
     * @param z The right analog stick z-axis value.
     * @param rz The right analog stick Rz-axis value.
     * @param rx The left trigger analog value.
     * @param ry The right trigger analog value.
     * @return true if the axes were successfully updated, false otherwise.
     */
    bool setAxes(int16_t x, int16_t y, int16_t z, int16_t rz, int16_t rx, int16_t ry);

    /**
     * @brief Sets all analog axes of the gamepad.
     *
     * Simultaneously updates the positions of both analog sticks and triggers.
     *
     * @param x The left analog stick x-axis value.
     * @param y The left analog stick y-axis value.
     * @param z The right analog stick z-axis value.
     * @param rz The right analog stick Rz-axis value.
     * @param rx The left trigger analog value.
     * @param ry The right trigger analog value.
     * @param slider The slider value.
     * @param dial The dial value.
     * @return true if the axes were successfully updated, false otherwise.
     */
    bool setAxes(int16_t x, int16_t y, int16_t z, int16_t rz, int16_t rx, int16_t ry, int16_t slider, int16_t dial);

    /**
     * @brief Sets the left analog stick x-axis value.
     *
     * @param x The new x-axis value.
     * @return true if the x-axis was successfully updated, false otherwise.
     */
    bool setAxesX(int16_t x);

    /**
     * @brief Sets the left analog stick y-axis value.
     *
     * @param y The new y-axis value.
     * @return true if the y-axis was successfully updated, false otherwise.
     */
    bool setAxesY(int16_t y);

    /**
     * @brief Sets the right analog stick z-axis value.
     *
     * @param z The new z-axis value.
     * @return true if the z-axis was successfully updated, false otherwise.
     */
    bool setAxesZ(int16_t z);

    /**
     * @brief Sets the right analog stick Rz-axis value.
     *
     * @param rz The new Rz-axis value.
     * @return true if the Rz-axis was successfully updated, false otherwise.
     */
    bool setAxesRz(int16_t rz);

    /**
     * @brief Sets the left trigger analog value.
     *
     * @param rx The new left trigger value.
     * @return true if the left trigger value was successfully updated, false otherwise.
     */
    bool setAxesRx(int16_t rx);

    /**
     * @brief Sets the right trigger analog value.
     *
     * @param ry The new right trigger value.
     * @return true if the right trigger value was successfully updated, false otherwise.
     */
    bool setAxesRy(int16_t ry);

    /**
     * @brief Sets the slider value.
     *
     * @param slider The new slider value.
     * @return true if the slider value was successfully updated, false otherwise.
     */
    bool setSlider(int16_t slider);

    /**
     * @brief Sets the dial value.
     *
     * @param dial The new dial value.
     * @return true if the dial value was successfully updated, false otherwise.
     */
    bool setDial(int16_t dial);

    /**
     * @brief Sets the DPad/hat state of the gamepad.
     *
     * @param hat The new hat state.
     * @return true if the hat state was successfully updated, false otherwise.
     */
    bool setHat(uint8_t hat);

    /**
     * @brief Sets the state of an individual button.
     *
     * @param button The identifier of the button.
     * @param pressed True to mark the button as pressed, false to release it.
     * @return true if the button state was successfully updated, false otherwise.
     */
    bool setButton(uint8_t button, bool pressed);

    /**
     * @brief Sets the state of all buttons.
     *
     * Simultaneously updates the bitmask for all buttons.
     *
     * @param buttons A bitmask representing the desired state of each button.
     * @return true if the buttons state was successfully updated, false otherwise.
     */
    bool setButtons(uint32_t buttons);
};

#endif // CONFIG_TINYUSB_HID_ENABLED
#endif // GAMEPAD_H
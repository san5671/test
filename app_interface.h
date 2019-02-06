#ifndef APP_INTERFACE_INCLUDED_H__
#define APP_INTERFACE_INCLUDED_H__

#include <stdint.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>

//typedef float float32_t;
//typedef uint8_t bool;

/** \brief Types of digital inputs supported.
*/
typedef enum
{
    ALERT_BUTTON, /**< Alert/Emergency Button. Pin 6 on automotive connector */
    DIGITAL_IN_1, /**< Digital Input 1. Pin 19 on automotive connector. Likely to be connected to a "Low Air Pressure" switch. */
    DIGITAL_IN_2, /**< Digital Input 2. Pin 20 on automotive connector. Likely to be connected to a "Low Oil Pressure" switch. */
    DIGITAL_IN_3, /**< Digital Input 3. Pin 21 on automotive connector. */
    DIGITAL_IN_4, /**< Digital Input 4. Pin 22 on automotive connector. */
    DIGITAL_IN_5, /**< Digital Input 5. Pin 23 on automotive connector. */
    FREQUENCY_IN, /**< Frequency Inputi. Pin 4 on automotive connector. Likely to connect to alternator W terminal for RPM detection.  */
} DigitalInput;

/** \brief Digital State
*/
typedef enum
{
    STATE_LOW, /**< OFF/Input Line Low */
    STATE_HIGH, /**< ON/Input Line High */
} DigitalState;

/** \brief Types of analog inputs supported

*/
typedef enum
{
    ANALOG_INPUT_1, /**< ANALOG_IN1_IG in schematic */
    ANALOG_INPUT_2, /**< ANALOG_IN2_CT in schematic. Likely usage: detect Coolant Temperature */
    ANALOG_INPUT_3  /**< ANALOG_IN3_FL in schematic. Likely usage: Fuel level */
} AnalogInput;

/** \brief State of a digital input
*/
typedef struct
{
    DigitalState digitalValue; /**< Applicable to input pin & button */
    uint16_t frequencyValue; /**< Value in Hz. Applicable to frequence input */
} InputState;

/** \brief An Input Event

Input events are generated when the state of that
input changes.
*/
typedef struct
{
    DigitalInput which; /**< Which input happened */
    struct timeval when; /**< When did the event happen */
    InputState state; /**< The new state of the input */
} InputEvent;

/** \brief Information about this Desi Device

*/
typedef struct
{
    const char *modelName; /**< Model Name */
    const char *modelNumber; /**< Model Number */
    const char *partNumber; /**< Part Number */
    const char *hardwareVersion; /**< Hardware Version */
    const char *vendorId; /**< Vendor Id */
    const char *deviceSerialNumber; /**< Serial Number of the device. Configured in the factory. */
    const char *mdmSoftwareVersion; /**< Version of software running on the MDM.  This is a single identifier for apps, modem, etc. */
    const char *mcuSoftwareVersion; /**< Version of software running on the SAMC21 MCU. */
} DeviceInfo;

/** \brief Vehicle Battery Voltage

This information is required for Analog to Digital conversion in the software.
*/
typedef enum
{
    BATTERY_12V, /**< 12 volts */
    BATTERY_24V, /**< 24 volts */
} VehicleBattery;

/** \brief Information about the Vehicle
*/
typedef struct
{
    VehicleBattery voltage; /**< Maximum voltage of vehicle battery */
} VehicleInfo;

/** \brief Inputs related to power
*/
typedef enum
{
    VIRTUAL_IGNITION, /**< Virtual Ignition */
    VEHICLE_BATTERY, /**< Vehicle Battery */
    INTERNAL_BATTERY, /**< Desi Internal Battery */
    FUEL_GAUGE /**< Fuel Gauge */
} PowerInput;

/** \brief Information related to change of a state of a PowerInput
*/
typedef struct
{
    DigitalState digitalValue; /**< Applicable for VIRTUAL_IGNITION only */
    float voltage; /**< Applicable to VEHICLE_BATTERY, INTERNAL_BATTERY */
    uint8_t capacity; /**< Applicable to FUEL_GAUGE */
} PowerState;

/** \brief A power event
*/
typedef struct
{
    PowerInput which; /* State of which input changed */
    PowerState state; /* The new state */
} PowerEvent;

/** \brief Digital Outputs on Desi
*/
typedef enum
{
    LED_RED, /**< Red LED - for Power status */
    LED_GREEN, /**< Green LED - for GPS fix ? */
    LED_BLUE, /**< Blue LED - for cellular camping ? */
    LED_AMBER, /**< Amber LED */
    DIGITAL_OUT_1, /**< Pin 15 on automotive connector. 300 mA high side drive. */
    DIGITAL_OUT_2, /**< Pin 16 on automotive connector. 300 mA high side drive. */
    DIGITAL_OUT_3, /**< Pin 30 on automotive connector. 300 mA low side drive. */
    DIGITAL_OUT_4, /**< Pin 11 on automotive connector. 50 mA current sink. */
} DigitalOutput;

/** \brief A single IMU event - accelerometer & gyro combined.

The accelerometer & gyroscope are separate devices in the IMU chip.
The MCU will sample them one after the other (i.e. almost simultaneously) & send
a continuous stream of events.
*/
typedef struct
{
    struct timeval when; /**< Timestamp of event */
    float32_t accel_x; /**< Accelerometer X */
    float32_t accel_y; /**< Accelerometer Y */
    float32_t accel_z; /**< Accelerometer Z */
    float32_t gyro_x; /**< Gyro X */
    float32_t gyro_y; /**< Gyro Y */
    float32_t gyro_z; /**< Gyro Z */
} ImuEvent;

/** \brief Rate of IMU reporting

*/
typedef enum
{
    RATE_52_HZ, /**< 52 Hz sampling */
    RATE_104_HZ, /**< 104 Hz sampling */
} ImuRate;

#ifdef __cplusplus
extern "C"
{
#endif

/** \brief Return information about the Desi device.
*/
void getDeviceInfo(DeviceInfo *info);

/** \brief Return vehicle registration number.
*/
const char* getVehicleRegistrationNumber();

/** \brief Wait till "timeout" for an input event.

An input event is filled if it becomes available inside the timeout.
If timeout is NULL, then the function will wait indefinitely till an
event becomes available.

Returns false if a timeout, or some other error happened.
*/
bool waitInputEvent(InputEvent* ev, struct timeval *timeout);

/** \brief Queries & returns the current state of a digital input.

Returns false on error.
*/
bool getInputState(DigitalInput which, InputState *state);

/** \brief Reads & returns value of an analog input.

Return value is an absolute voltage ranging, with a maximum
of battery voltage (12/24V)
*/
float32_t readAnalogInput(AnalogInput which); // poll one value at a time

/** \brief Sets a digital output to a specific state.

*/
bool setDigitalOutput(DigitalOutput which, DigitalState state);

/** \brief Wait till "timeout" for a power event.

A power event is filled if it becomes available inside the timeout.
If timeout is NULL, then the function will wait indefinitely till an
event becomes available.

Returns false on timeout, or if some other error happened.
*/
bool waitPowerEvent(PowerEvent* ev, struct timeval *timeout);

/** \brief Queries and return the current state of a power input.

Return false on error.
*/
bool getPowerState(PowerInput which, PowerState* state);

/** \brief Sets the rate of data output from the IMU.
*/
bool setImuRate(ImuRate rate);

/** \brief Wait till "timeout" for an IMU event.

An IMU event is filled if it becomes available inside the timeout.
If timeout is NULL, then the function will wait indefinitely till an
event becomes available.
*/
bool waitIMUEvent(ImuEvent* state, struct timeval *timeout);

/** \brief Returns true if the MCU detected a tamper event (lid open).
*/
bool isDeviceTampered();

#ifdef __cplusplus
}
#endif

#endif // APP_INTERFACE_INCLUDED

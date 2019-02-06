/* @file  ais140ExternalSensor.h
 * @brief Main header file for ais140ExternalSensor application.
 *
 * @copyright 2018, PeopleNet
 */

#ifndef AIS140EXTERNALSENSOR_H__
#define AIS140EXTERNALSENSOR_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define APP_NAME "ais140ExternalSensor"
#define FW_VERSION "1.0.0"

 // PVT Timer Interval used in application.
 #define AIS140EXTERNALSENSOR_NORMAL_PUBLISH_INTERVAL 10000

 // ais140ExternalSensor application data vars length.
 #define NULL_TERMINATOR_LEN (1u)
 #define MAX_FW_VERSION_LEN (20u)


 /**
  * @brief Structure to hold ExternalSensor data.
  */

 typedef struct
 {
     int32_t digitalinput1;
     int32_t digitalinput2;
     int32_t digitalinput3;
     int32_t digitalinput4;
     float64_t analoginput1;
     float64_t analoginput2;
 }ExternalSensorData;

 /**
  * @brief Common structure for vars used by ais140ExternalSensor application.
  *
  */
 typedef struct
 {
     char fwVersion[MAX_FW_VERSION_LEN + NULL_TERMINATOR_LEN]; // Firmware Version
     ExternalSensorData externalsensordata;
  } Ais140ExternalSensorVars;


#ifdef __cplusplus
}
#endif

#endif // AIS140EXTERNALSENSOR_H



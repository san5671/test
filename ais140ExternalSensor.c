/* @file  ais140ExternalSensor.c
 *
 * @brief Routines used to get Device, ExtenalSensor at periodic intervals.
 *
 * @copyright 2018, PeopleNet
 */

#ifndef __MAKE_DEPEND__
#include <string.h>
#endif //  __MAKE_DEPEND__

#include "vtpApp.h"
#include "ais140ExternalSensor.h"
#include "ais140ExternalSensorTopics.h"
#include "logger.h"
#include "pcgUtils.h"
#include "app_interface.h"


// ais140ExternalSensor application object
UT_STATIC Ais140ExternalSensorVars ais140ExternalSensorVars;

UT_STATIC int32_t (*Ais140ExternalSensor_VtpMain)(const char *appName, int32_t argc, char* const * argv) = VtpMain;
UT_STATIC _Bool (*Ais140ExternalSensor_TimerStart)(Timer* timer, uint32_t timeout) = TimerStart;
//UT_STATIC void (*Ais140ExternalSensor_VtpMqttMessage)(void) = VtpMqttMessage;
//UT_STATIC _Bool (*Ais140ExternalSensor_VtpMqttPublish)(const char *topic, uint32_t qos, _Bool retain) = VtpMqttPublish;
//UT_STATIC const char* (*Ais140ExternalSensor_GetDsn)(void) = GetDsn;



		/**
		* @brief Periodic Timer expired Callback function.
		** @param[in] timer The timer that expired.
		* @param[in] timerId The ID of the timer that expired.
		* @param[in][optional] data The data provided when the timer was created or configured.
		*
		* @return None
		*/
UT_STATIC void Ais140ExternalSensortimerExpired(Timer *timer, int32_t timerId, void *data)
		{
	   (void) data;
/*
		    //DEBUG("Timer Expired - Callback Invoked with ID:%d", timerId);
			InputState *state;
			getInputState(DigitalInput.DIGITAL_IN_1, state);
			//write state info to structure
			Ais140ExternalSensorVars.digitalInput1 = state.digitalValue;
*/
	 DEBUG("Timer Expired - Callback Invoked with ID:%d", timerId);
	   (void)Ais140ExternalSensor_TimerStart(timer,0u);
		}


UT_STATIC _Bool InitApp(TimerGroup *timerGrp)
{
    (void) timerGrp;
    _Bool retStatus = true;

    //(void) memset(&Ais140ExternalSensorVars, 0, sizeof(Ais140ExternalSensorVars));
    (void) strncpy(ais140ExternalSensorVars.fwVersion, FW_VERSION, MAX_FW_VERSION_LEN);

    return retStatus;
}


/**
* @brief Main Entry function to start ais140ExternalSensor application.
*
* @param[in] argc Count of argument data.
* @param[in] argv Input argument data (like debug)
*
* @return
* return value of VtpMain().
*
*/

#if defined(__DOXYGEN_FALSE__) && !defined(__UNIT_TEST__)
extern int32_t main(int32_t argc, char* const * argv);
int32_t main(int32_t argc, char* const * argv)
#else
int32_t Ais140ExternalSensorMain(int32_t argc, char** argv)
#endif
{
    static VtpMqttTopic topics [] =
    {
        {AIS140_DESI_ALSENSORS_TOPICS, 0, NULL, NULL},
        {NULL, 0, NULL, NULL }
    };
//Ais140SensorData
    static VtpTimer timers [] =
    {
        {NULL, 0, AIS140EXTERNALSENSOR_NORMAL_PUBLISH_INTERVAL, Ais140ExternalSensortimerExpired,  NULL, true},
        {NULL, 0, 0, NULL, NULL, false},
    };

    VtpTimers(timers);
    VtpMqttSubscribe(topics);
    VtpOnInit(InitApp);

    return Ais140ExternalSensor_VtpMain(APP_NAME, argc, argv);
}

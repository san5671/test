/*! \file ais140ExternalSensorTest.cpp
 \copyright Peoplenet 2017
 */
#ifndef __MAKE_DEPEND__
#include "CppUTest/TestHarness.h"
#include <string.h>
#endif // __MAKE_DEPEND__
#include "mocks.h"
#include "vtpdef.h"
#include "ais140.h"
#include "vtpApp.h"

extern "C"
{
UT_STATIC Ais140ExternalSensorVars ais140ExternalSensorVars;
extern int Ais140ExternalSensorMain(int argc, char** argv);
extern void Ais140ExternalSensorMain(Timer *timer, int32_t timerId, void *data);

}

/*
 * Server_calls.h
 *
 *  Created on: Jan 22, 2015
 *      Author: tackticaldude
 */

#ifndef SRC_SERVER_CALLS_H_
#define SRC_SERVER_CALLS_H_

#include "json-rpc.h"

void getSensorValue(char[]);
void setSensorValue(int, int, char*);
void setActuatorValue(char[]);
void confirmActuatorValue(int, int, char *);
void enableDeviceOnServer(int, int);
void disaleDeviceOnServer(int, int);
void enableModuleOnServer(int);
void registerSensorOnServer();

#endif /* SRC_SERVER_CALLS_H_ */

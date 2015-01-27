/*
 * server_calls.c
 *
 *  Created on: Jan 22, 2015
 *      Author: tackticaldude
 */

#include "server_calls.h"

void getSensorValue(char params[]) {
	int moduleId = 0, devId = 0;
	char value[12];
	//in te vullen door module Beheerders
	setSensorValue(moduleId, devId, value);
}

void setSensorValue(int moduleId, int devId, char *value) {
	struct tuple json_call;
	char json_string[256];
	char methodName[20] = "setSensorValue";
	char parameters[200];
	char param_format[20] = "%d%d%s";

	sprintf(parameters, "%d,%d,%s", moduleId, devId, value);

	json_call.call.method = methodName;
	json_call.call.params = parameters;
	json_call.call.params_format = param_format;
	json_call.a = JSON_RPC_CALL;

	encode_json_rpc(&json_call, json_string, module_ipaddress);
	send_to_server(json_string);
}

void setActuatorValue(char params[]) {
	int moduleId = 0, devId = 0;
	char value[12];
	//als het is gelukt roep confirmActuatorValue aan met de waarde die is geset.
	confirmActuatorValue(moduleId, devId, value);
}

void confirmActuatorValue(int moduleId, int devId, char *value) {
	struct tuple json_call;
	char methodName[20] = "getActuatorValue";
	char parameters[200];
	char json_string[256];
	char param_format[20] = "%d%d%s";

	sprintf(parameters, "%d,%d,%s", moduleId, devId, value);

	json_call.call.method = methodName;
	json_call.call.params = parameters;
	json_call.call.params_format = param_format;
	json_call.a = JSON_RPC_CALL;

	encode_json_rpc(&json_call, json_string, module_ipaddress);
	send_to_server(json_string);
}

void enableDeviceOnServer(int moduleId, int devId) {
	struct tuple json_call;
	char methodName[20] = "enableDevice";
	char parameters[200];
	char json_string[256];
	char param_format[20] = "%d%d";

	sprintf(parameters, "%d,%d", moduleId, devId);

	json_call.call.method = methodName;
	json_call.call.params = parameters;
	json_call.call.params_format = param_format;
	json_call.a = JSON_RPC_CALL;

	encode_json_rpc(&json_call, json_string, module_ipaddress);
	send_to_server(json_string);
}

void disableDeviceOnServer(int moduleId, int devId) {
	struct tuple json_call;
	char methodName[20] = "disableDevice";
	char parameters[200];
	char json_string[256];
	char param_format[20] = "%d%d";

	sprintf(parameters, "%d,%d", moduleId, devId);

	json_call.call.method = methodName;
	json_call.call.params = parameters;
	json_call.call.params_format = param_format;
	json_call.a = JSON_RPC_CALL;

	encode_json_rpc(&json_call, json_string, module_ipaddress);
	send_to_server(json_string);
}

void enableModeleOnServer(int moduleId) {
	struct tuple json_call;
	char methodName[20] = "disableDevice";
	char parameters[200];
	char json_string[256];
	char param_format[20] = "%d";

	sprintf(parameters, "%d", moduleId);

	json_call.call.method = methodName;
	json_call.call.params = parameters;
	json_call.call.params_format = param_format;
	json_call.a = JSON_RPC_CALL;

	encode_json_rpc(&json_call, json_string, module_ipaddress);
	send_to_server(json_string);
}

void registerSensorOnServer(int moduleId, int deviceId, char icon[],
		char interface[], char variableType[], char unit[], char name[],
		char min[], char max[], int logging_time) {
	struct tuple json_call;
	char methodName[20] = "addSensor";
	char parameters[200];
	char json_string[300];
	char param_format[50] = "%d%d%s%s%s%s%s%s%s%d";
	sprintf(parameters, param_format, moduleId, deviceId, icon, interface,
			variableType, unit, name, min, max, logging_time);

	json_call.call.method = methodName;
	json_call.call.params = parameters;
	json_call.call.params_format = param_format;
	json_call.a = JSON_RPC_CALL;

	encode_json_rpc(&json_call, json_string, module_ipaddress);
	printf("%s\n", json_string);
	send_to_server(json_string);
}

void registerActuatorOnServer(int moduleID, int deviceId, char type[],
		char interface[], char variableType[], char unit[], char name[],
		char min[], char max[], int logging_time) {
	struct tuple json_call;
	char methodName[20] = "addActuator";
	char parameters[200];
	char json_string[256];
	char param_format[50] = "%d%d%s%s%s%s%s%s%s";
	sprintf(parameters, param_format, moduleID, deviceId, type, interface,
			variableType, unit, name, min, max);

	json_call.call.method = methodName;
	json_call.call.params = parameters;
	json_call.call.params_format = param_format;
	json_call.a = JSON_RPC_CALL;

	encode_json_rpc(&json_call, json_string, module_ipaddress);
	send_to_server(json_string);
}

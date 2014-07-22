/*
 * ObdCommands.h
 *
 *  Created on: Jun 27, 2014
 *      Author: luuke
 */

#ifndef OBDCOMMANDS_H_
#define OBDCOMMANDS_H_

//Diagnostic test modes
#define SHOW_CURRENT_DATA 					"01"
#define SHOW_FREEZE_FRAME_DATA 				"02"
#define SHOW_DIAGNOSTIC_TROUBLE_CODES 		"03"
#define CLEAR_TROUBLE_CODES 				"04"
#define OXYGEN_SENSORS_TEST_RESULTS 		"05"
#define NON_CONT_MONITORED_TEST_RESULTS 	"06"
#define SHOW_PENDING_TROUBLE_CODES 			"07"
#define SPECIAL_CONTROL_MODE  				"08"
#define REQUEST_VEHICLE_INFORMATION 		"09"
#define REQUEST_PERMANENT_TROUBLE_CODES 	"0A"

//Parameters identifications

#define ENGINE_RPM							"OC"
#define VEHICLE_SPEED						"0D"

#endif /* OBDCOMMANDS_H_ */

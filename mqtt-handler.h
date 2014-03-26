/* 
 * File:   mqtt-handler.h
 * Author: karlp
 *
 * Created on March 26, 2014, 12:22 PM
 */

#ifndef MQTT_HANDLER_H
#define	MQTT_HANDLER_H

#include "snmp-mqtt-ietfwg.h"

#ifdef	__cplusplus
extern "C" {
#endif


void mosq_snmp_setup(struct snmp_mqtt_ietfwg_state_ *st);
void mosq_snmp_cleanup(struct snmp_mqtt_ietfwg_state_ *st);

#ifdef	__cplusplus
}
#endif

#endif	/* MQTT_HANDLER_H */


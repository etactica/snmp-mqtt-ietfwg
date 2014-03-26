/* 
 * General application config and defines
 * Karl Palsson <karlp@remake.is>
 *
 */

#ifndef SNMP_MQTT_IETFWG_H
#define	SNMP_MQTT_IETFWG_H

#include <mosquitto.h>

struct snmp_mqtt_ietfwg_state_ {
	struct mosquitto *mosq;
	netsnmp_tdata *ietfwg_tdata;
};


#ifdef	__cplusplus
extern "C" {
#endif


#ifdef	__cplusplus
}
#endif

#endif	/* SNMP_MQTT_IETFWG_H */


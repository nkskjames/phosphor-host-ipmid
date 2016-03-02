#ifndef __HOST_IPMID_IPMI_H__
#define __HOST_IPMID_IPMI_H__
#include "ipmid-api.h"
#include <stdio.h>
#include "host-services.h"

// When the requester sends in a netfn and a command along with data, this
// function will look for registered handlers that will handle that [netfn,cmd]
// and will make a call to that plugin implementation and send back the response.
ipmi_ret_t ipmi_netfn_router(const ipmi_netfn_t, const ipmi_cmd_t, ipmi_request_t,
                             ipmi_response_t, unsigned int *data_len);

// Plugin libraries need to _end_ with .so
#define IPMI_PLUGIN_EXTN ".so"

// The BT FIFO in the AST2400 can only handle 64 bytes.  
// Can only allow 63 because the BT interface still 
// needs 1 byte for the length field. 
#define MAX_IPMI_BUFFER 64

#define _cleanup_(x) __attribute__((cleanup(x)))
#define _SD_DEFINE_POINTER_CLEANUP_FUNC(type, func)             \
        static inline void func##p(type **p) {                  \
                if (*p)                                         \
                        func(*p);                               \
        }                                                       \
        struct _sd_useless_struct_to_allow_trailing_semicolon_

extern FILE *ipmiio, *ipmidbus, *ipmicmddetails;

int set_sensor_dbus_state_s(uint8_t , const char *, const char *);
int set_sensor_dbus_state_y(uint8_t , const char *, const uint8_t);
_SD_DEFINE_POINTER_CLEANUP_FUNC(sd_bus_message, sd_bus_message_unref);
#endif

/*
 * Copyright (c) 2014 Microsoft Open Technologies, Inc. 
 *   
 *    Licensed under the Apache License, Version 2.0 (the "License"); you may 
 *    not use this file except in compliance with the License. You may obtain 
 *    a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *    THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR 
 *    CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
 *    LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS 
 *    FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 *    See the Apache Version 2.0 License for specific language governing 
 *    permissions and limitations under the License. 
 *
 *    Microsoft would like to thank the following companies for their review and
 *    assistance with these files: Intel Corporation, Mellanox Technologies Ltd,
 *    Dell Products, L.P., Facebook, Inc
 *
 *
 */
#ifndef __DUMMY_SWITCH_H_
#define __DUMMY_SWITCH_H_

#include "dummy.h"
#include "dummy_internal.h"

void
dummy_hndlr_switch_state_change(
    _In_ sai_switch_oper_status_t switch_oper_status);

void
dummy_hndlr_fdb_event(
    _In_ sai_fdb_event_t event_type,
    _In_ sai_fdb_entry_t* fdb_entry,
    _In_ uint32_t attr_count,
    _In_ sai_attribute_t* attr_list);

void
dummy_hndlr_port_state_change(
    _In_ sai_object_id_t port_id,
    _In_ sai_port_oper_status_t port_status);


void 
dummy_hndlr_shutdown_request (void);

void
dummy_hndlr_port_event(
    _In_ sai_object_id_t port_id,
    _In_ sai_port_event_t port_event);


/*---------------------------------------------*/
/* SWITCH */
/*---------------------------------------------*/

sai_status_t
dummy_init_switch(
    _In_ sai_switch_profile_id_t profile_id,
    _In_reads_z_(SAI_MAX_HARDWARE_ID_LEN) char* switch_hardware_id,
    _In_reads_opt_z_(SAI_MAX_FIRMWARE_PATH_NAME_LEN) char* firmware_path_name,
    _In_ sai_switch_notification_t* switch_notifications);


void 
dummy_shutdown_switch(
    _In_ bool war_restart_hint);


sai_status_t 
dummy_connect_switch(
    _In_ sai_switch_profile_id_t profile_id,
    _In_reads_z_(SAI_MAX_HARDWARE_ID_LEN) char* switch_hardware_id,
    _In_ sai_switch_notification_t* switch_notifications);

void
dummy_disconnect_switch(void);

sai_status_t
dummy_set_switch_attr(
    _In_ const sai_attribute_t *attr);


sai_status_t
dummy_get_switch_attr(
        _In_ uint32_t attr_count,
        _Inout_ sai_attribute_t *attr_list);

sai_switch_api_t dummy_switch_method_table;


#endif //__DUMMY_SWITCH_H_

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
#ifndef __DUMMY_INIT_H_
#define __DUMMY_INIT_H_

#include "../../src/dummy/test.h"
#include "dummy_switch.h"
#include "dummy_port.h"
#include "dummy_fdb.h"
#include "dummy_vlan.h"
#include "dummy_vrtr.h"
#include "dummy_route.h"
#include "dummy_nexthop.h"
#include "dummy_nexthop_grp.h"
#include "dummy_rtr_intf.h"
#include "dummy_nbr.h"
#include "dummy_qos.h"
#include "dummy_acl.h"
#include "dummy_host_intf.h"
#include "dummy_mirror_sess.h"
#include "dummy_smpl_pkt_sess.h"
#include "dummy_stp.h"
#include "dummy_lag.h"


/*---------------------------------------------*/
/* INITIALIZE SERVICE TABLE */
/*---------------------------------------------*/
const char* 
dummy_profile_get_value (
    _In_ sai_switch_profile_id_t profile_id,
    _In_ const char* variable);

int 
dummy_profile_get_next_value (
    _In_ sai_switch_profile_id_t profile_id,
    _Out_ const char** variable,
    _Out_ const char** value);

service_method_table_t  dummy_service_method_table;

sai_status_t 
sai_api_initialize(
    _In_ uint64_t flags,
    _In_ const service_method_table_t* services);

sai_status_t
sai_log_set(
    _In_ sai_api_t sai_api_id,
    _In_ sai_log_level_t log_level);

/*---------------------------------------------*/
/* SAI_API Query */
/*---------------------------------------------*/


sai_status_t 
sai_api_query(
    _In_ sai_api_t sai_api_id,
    _Out_ void** api_method_table);

/*---------------------------------------------*/
/* Initialize L3 */
/*---------------------------------------------*/
bool InitializeL3(void);

#endif // __DUMMY_INIT_H_

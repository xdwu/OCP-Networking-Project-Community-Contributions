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

#include "dummy.h"
#include "dummy_internal.h"

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



/*---------------------------------------------*/
/* Internal Data Structure */
/*---------------------------------------------*/

/*---------------------------------------------*/
/* Create an instance of switch db, 
      storing attributes */
/*---------------------------------------------*/
//switch_db_t dummy_switch_db;



#endif // __DUMMY_INIT_H_

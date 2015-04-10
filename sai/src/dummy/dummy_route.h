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
#ifndef __DUMMY_ROUTE_H_
#define __DUMMY_ROUTE_H_

#include "test.h"

sai_status_t
dummy_create_route(
    _In_ const sai_unicast_route_entry_t* ucast_rt_entry,
    _In_ uint32_t attr_count,
    _In_ const sai_attribute_t* attr_list);

sai_status_t
dummy_remove_route(
    _In_ const sai_unicast_route_entry_t* ucast_rt_entry);

sai_status_t
dummy_set_route_attr(
    _In_ const sai_unicast_route_entry_t* ucast_rt_entry,
    _In_ const sai_attribute_t* attr);

sai_status_t
dummy_get_route_attr(
    _In_ const sai_unicast_route_entry_t* ucast_rt_entry,
    _In_ uint32_t attr_count,
    _Inout_ sai_attribute_t* attr_list);


sai_route_api_t dummy_route_method_table;

#endif //__DUMMY_ROUTE_H_

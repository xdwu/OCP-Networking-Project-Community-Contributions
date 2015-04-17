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
#include "dummy_vlan.h"

sai_status_t
dummy_create_vlan(
    _In_ sai_vlan_id_t vlan_id)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_remove_vlan(
    _In_ sai_vlan_id_t vlan_id)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_set_vlan_attr(
    _In_ sai_vlan_id_t vlan_id,
    _In_ const sai_attribute_t* attr)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_get_vlan_attr(
    _In_ sai_vlan_id_t vlan_id,
    _In_ uint32_t attr_count,
    _Inout_ sai_attribute_t* attr_list)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_add_ports_to_vlan(
    _In_ sai_vlan_id_t vlan_id,
    _In_ uint32_t port_count,
    _In_ const sai_vlan_port_t* port_list)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_remove_ports_from_vlan(
    _In_ sai_vlan_id_t vlan_id,
    _In_ uint32_t port_count,
    _In_ const sai_vlan_port_t* port_list)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_remove_all_vlan(void)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_get_vlan_stats(
    _In_ sai_vlan_id_t vlan_id,
    _In_ const sai_vlan_stat_counter_t* counter_ids,
    _In_ uint32_t number_of_counters,
    _Out_ uint64_t* counters)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_vlan_api_t dummy_vlan_method_table = {
    dummy_create_vlan,
    dummy_remove_vlan,
    dummy_set_vlan_attr,
    dummy_get_vlan_attr,
    dummy_add_ports_to_vlan,
    dummy_remove_ports_from_vlan,
    dummy_remove_all_vlan,
    dummy_get_vlan_stats
};

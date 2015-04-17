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
#include "dummy_qos.h"

sai_status_t
dummy_set_cos_attr(
    _In_ sai_object_id_t port_id,
    _In_ sai_cos_t cos_value,
    _In_ const sai_attribute_t* attr)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_get_cos_attr(
    _In_ sai_object_id_t port_id,
    _In_ sai_cos_t cos_value,
    _In_ uint32_t attr_count,
    _Inout_ sai_attribute_t* attr_list)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_set_cos_mapping(
    _In_ sai_object_id_t port_id,
    _In_ sai_qos_map_t qos_map_selector,
    _In_ uint32_t value_to_map,
    _In_ sai_cos_t cos_value)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_get_cos_mapping(
    _In_ sai_object_id_t port_id,
    _In_ sai_qos_map_t qos_map_selector,
    _In_ uint32_t value_to_map,
    _Out_ sai_cos_t* cos_value)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_qos_api_t dummy_qos_method_table = {
    dummy_set_cos_attr,
    dummy_get_cos_attr,
    dummy_set_cos_mapping,
    dummy_get_cos_mapping
};

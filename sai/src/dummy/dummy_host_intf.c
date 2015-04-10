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
#include "dummy_host_intf.h"

sai_status_t
dummy_create_host_intf(
    _Out_ sai_object_id_t* hif_id,
    _In_ uint32_t attr_count,
    _In_ sai_attribute_t* attr_list)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_remove_host_intf(
    _In_ sai_object_id_t hif_id)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}


sai_status_t
dummy_set_host_intf_attr(
    _In_ sai_object_id_t hif_id,
    _In_ const sai_attribute_t* attr)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_get_host_intf_attr(
    _In_ sai_object_id_t hif_id,
    _In_ uint32_t attr_count,
    _Out_ sai_attribute_t* attr_list)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_host_interface_api_t dummy_host_interface_method_table = {
    dummy_create_host_intf,
    dummy_remove_host_intf,
    dummy_set_host_intf_attr,
    dummy_get_host_intf_attr
};

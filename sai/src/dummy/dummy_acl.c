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
#include "dummy_acl.h"

sai_status_t
dummy_create_acl_table(
    _Out_ sai_object_id_t* acl_table_id,
    _In_ uint32_t attr_count,
    _In_ const sai_attribute_t* attr_list)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_delete_acl_table(
    _In_ sai_object_id_t acl_table_id)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_set_acl_table_attr(
    _In_ sai_object_id_t acl_table_id,
    _In_ const sai_attribute_t* attr)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_get_acl_table_attr(
    _In_ sai_object_id_t acl_table_id,
    _In_ uint32_t attr_count,
    _Out_ sai_attribute_t* attr_list)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_create_acl_entry(
    _Out_ sai_object_id_t* acl_entry_id,
    _In_ uint32_t attr_count,
    _In_ const sai_attribute_t* attr_list)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_delete_acl_entry(
    _In_ sai_object_id_t acl_entry_id)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_set_acl_entry_attr(
    _In_ sai_object_id_t acl_entry_id,
    _In_ const sai_attribute_t* attr)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_get_acl_entry_attr(
    _In_ sai_object_id_t acl_entry_id,
    _In_ uint32_t attr_count,
    _Out_ sai_attribute_t* attr_list)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_create_acl_counter(
    _Out_ sai_object_id_t* acl_cntr_id,
    _In_ uint32_t attr_count,
    _In_ const sai_attribute_t* attr_list)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_delete_acl_counter(
    _In_ sai_object_id_t acl_cntr_id)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_set_acl_counter_attr(
    _In_ sai_object_id_t acl_cntr_id,
    _In_ const sai_attribute_t* attr)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_get_acl_counter_attr(
    _In_ sai_object_id_t acl_cntr_id,
    _In_ uint32_t attr_count,
    _Out_ sai_attribute_t* attr_list)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_acl_api_t dummy_acl_method_table = {
    dummy_create_acl_table,
    dummy_delete_acl_table,
    dummy_set_acl_table_attr,
    dummy_get_acl_table_attr,
    dummy_create_acl_entry,
    dummy_delete_acl_entry,
    dummy_set_acl_entry_attr,
    dummy_get_acl_entry_attr,
    dummy_create_acl_counter,
    dummy_delete_acl_counter,
    dummy_set_acl_counter_attr,
    dummy_get_acl_counter_attr
};


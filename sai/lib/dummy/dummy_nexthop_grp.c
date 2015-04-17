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
#include "dummy_nexthop_grp.h"

sai_status_t
dummy_create_nexthop_grp(
    _Out_ sai_object_id_t* nexthop_grp_id,
    _In_ uint32_t attr_count,
    _In_ const sai_attribute_t* attr_list)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_remove_nexthop_grp(
    _In_ sai_object_id_t nexthop_grp_id)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_set_nexthop_grp_attr(
    _In_ sai_object_id_t nexthop_grp_id,
    _In_ const sai_attribute_t* attr)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_get_nexthop_grp_attr(
    _In_ sai_object_id_t nexthop_grp_id,
    _In_ uint32_t attr_count,
    _Inout_ sai_attribute_t* attr_list)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_add_nexthop_to_grp(
    _In_ sai_object_id_t nexthop_grp_id,
    _In_ uint32_t nexthop_count,
    _In_ const sai_object_id_t* nexthops)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_remove_nexthop_from_grp(
    _In_ sai_object_id_t nexthop_grp_id,
    _In_ uint32_t nexthop_count,
    _In_ const sai_object_id_t* nexthops)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_next_hop_group_api_t dummy_next_hop_group_method_table = {
    dummy_create_nexthop_grp,
    dummy_remove_nexthop_grp,
    dummy_set_nexthop_grp_attr,
    dummy_get_nexthop_grp_attr,
    dummy_add_nexthop_to_grp,
    dummy_remove_nexthop_from_grp
};

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
#include "dummy_init.h"

/*---------------------------------------------*/
/* INITIALIZE SERVICE TABLE */
/*---------------------------------------------*/
const char* 
dummy_profile_get_value (
    _In_ sai_switch_profile_id_t profile_id,
    _In_ const char* variable)
{
    printf("%s\n", __FUNCTION__);
    if( variable == NULL) {
        return NULL;
    }
    return NULL;
}

int 
dummy_profile_get_next_value (
    _In_ sai_switch_profile_id_t profile_id,
    _Out_ const char** variable,
    _Out_ const char** value)
{
    printf("%s\n", __FUNCTION__);
    return -1;
}

service_method_table_t  dummy_service_method_table = {
    dummy_profile_get_value,
    dummy_profile_get_next_value
};

sai_status_t 
sai_api_initialize(
    _In_ uint64_t flags,
    _In_ const service_method_table_t* services)
{
    printf("%s\n", __FUNCTION__);

    if (services == NULL) {
        return SAI_STATUS_FAILURE;
    }

    return SAI_STATUS_SUCCESS;
}

sai_status_t
sai_log_set(
    _In_ sai_api_t sai_api_id,
    _In_ sai_log_level_t log_level)
{
    printf("%s SAI_API_ID %2X log_level %2X\n", __FUNCTION__, 
            sai_api_id, log_level);

    switch(sai_api_id) {
        case SAI_API_SWITCH:
        case SAI_API_PORT:
        case SAI_API_FDB:
        case SAI_API_VLAN:
        case SAI_API_VIRTUAL_ROUTER:

        case SAI_API_ROUTE:
        case SAI_API_NEXT_HOP:
        case SAI_API_NEXT_HOP_GROUP:
        case SAI_API_ROUTER_INTERFACE:
        case SAI_API_NEIGHBOR:

        case SAI_API_QOS:
        case SAI_API_ACL:
        case SAI_API_HOST_INTERFACE:
        case SAI_API_MIRROR:
        case SAI_API_SAMPLEPACKET:
        case SAI_API_STP:
        case SAI_API_LAG:
            break;

        case SAI_API_UNSPECIFIED:
        default:
            break;
    }
    return SAI_STATUS_SUCCESS;
}


/*---------------------------------------------*/
/* SAI_API Query */
/*---------------------------------------------*/


sai_status_t 
sai_api_query(
    _In_ sai_api_t sai_api_id,
    _Out_ void** api_method_table)
{
    printf("%s SAI_API_ID %2X\n", __FUNCTION__, sai_api_id);

    if (api_method_table == NULL) {
        printf("Fail to sai_api_query, api_method_table==NULL\n");
        return SAI_STATUS_FAILURE;
    }

    switch(sai_api_id) {
        case SAI_API_SWITCH:
            *api_method_table = &dummy_switch_method_table;
            break;

        case SAI_API_PORT:
            *api_method_table = &dummy_port_method_table;
            break;

        case SAI_API_FDB:
            *api_method_table = &dummy_fdb_method_table;
            break;

        case SAI_API_VLAN:
            *api_method_table = &dummy_vlan_method_table;
            break;

        case SAI_API_VIRTUAL_ROUTER:
            *api_method_table = &dummy_vrtr_method_table;
            break;

        case SAI_API_ROUTE:
            *api_method_table = &dummy_route_method_table;
            break;

        case SAI_API_NEXT_HOP:
            *api_method_table = &dummy_next_hop_method_table;
            break;

        case SAI_API_NEXT_HOP_GROUP:
            *api_method_table = &dummy_next_hop_group_method_table;
            break;

        case SAI_API_ROUTER_INTERFACE:
            *api_method_table = &dummy_router_interface_method_table;
            break;

        case SAI_API_NEIGHBOR:
            *api_method_table = &dummy_neighbor_method_table;
            break;

        case SAI_API_QOS:
            *api_method_table = &dummy_qos_method_table;
            break;

        case SAI_API_ACL:
            *api_method_table = &dummy_acl_method_table;
            break;

        case SAI_API_HOST_INTERFACE:
            *api_method_table = &dummy_host_interface_method_table;
            break;

        case SAI_API_MIRROR:
            *api_method_table = &dummy_mirror_method_table;
            break;

        case SAI_API_SAMPLEPACKET:
            *api_method_table = &dummy_smpl_pkt_method_table;
            break;

        case SAI_API_STP:
            *api_method_table = &dummy_stp_method_table;
            break;

        case SAI_API_LAG:
            *api_method_table = &dummy_lag_method_table;
            break;

        case SAI_API_UNSPECIFIED:
        default:
            *api_method_table = NULL;
            break;
    }

    if (*api_method_table == NULL) {
        return SAI_STATUS_FAILURE;
    }

    return SAI_STATUS_SUCCESS;

}

/*---------------------------------------------*/
/* Initialize L3 */
/*---------------------------------------------*/
bool InitializeL3(void)
{
    printf("%s\n", __FUNCTION__);
    sai_status_t status;
    sai_attribute_t attr;
    sai_object_id_t g_vr_id;

    attr.id = SAI_SWITCH_ATTR_CPU_PORT;
    status = sai_switch_api->get_switch_attribute(1, &attr);

    if (status != SAI_STATUS_SUCCESS) {
        printf("Fail to get cpu port. status =%x\n", status);
        return false;
    }


    status = sai_vr_api->create_virtual_router(&g_vr_id, 0, NULL);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Fail to create virtual router. status =%x\n", status);
        return false;
    }

    return true;
}


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
#include "dummy_vrtr.h"

sai_status_t
dummy_create_vrtr(
    _Out_ sai_object_id_t* vr_oid,
    _In_ uint32_t attr_count,
    _In_ const sai_attribute_t* attr_list)
{
    printf("%s\n", __FUNCTION__);

    vrtr_t *p, *tmp;
    p = (vrtr_t*) malloc(sizeof(vrtr_t));

    if(p == NULL) {
        return SAI_STATUS_FAILURE;
    }

    if(!init_vrtr(p)) {
        return SAI_STATUS_FAILURE;
    }

    if(dummy_switch.vrtr_ll == NULL) {
        dummy_switch.vrtr_ll = p;
    } else {
        tmp = dummy_switch.vrtr_ll;
        dummy_switch.vrtr_ll = p;
        p->next = tmp;
    }

    *vr_oid = p->oid;


    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_remove_vrtr(
    _In_ sai_object_id_t vr_oid)
{
    printf("%s\n", __FUNCTION__);
    release_oid(vr_oid);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_set_vrtr_attr(
    _In_ sai_object_id_t vr_oid,
    _In_ const sai_attribute_t* attr)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_get_vrtr_attr(
    _In_ sai_object_id_t vr_oid,
    _In_ uint32_t attr_count,
    _Inout_ sai_attribute_t* attr_list)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

sai_virtual_router_api_t dummy_vrtr_method_table = {
    dummy_create_vrtr,
    dummy_remove_vrtr,
    dummy_set_vrtr_attr,
    dummy_get_vrtr_attr
};


/* Internal functions */
bool init_vrtr(vrtr_t *vrtr_p)
{
    if( vrtr_p == NULL ) {
        return false;
    }

    vrtr_p->next = NULL;

    if(!acquire_oid(&(vrtr_p->oid))) {
        return false;
    }

    vrtr_p->admin_v4_state = true;
    vrtr_p->admin_v6_state = true;

    mac_copy(vrtr_p->src_mac, dummy_switch.default_mac);

    vrtr_p->act_ttl_one = SAI_PACKET_ACTION_TRAP;

    vrtr_p->act_ip_opt = SAI_PACKET_ACTION_TRAP;

    return true;
}

void show_vrtr(vrtr_t *vrtr_p)
{
    if( vrtr_p == NULL ) {
        return;
    }

    printf("======== virtual router  ===========\n");

    printf("  oid: 0x%8lx\n", vrtr_p->oid);
    printf("  admin ipv4 state: %s\n", vrtr_p->admin_v4_state?"true":"false");
    printf("  admin ipv6 state: %s\n", vrtr_p->admin_v6_state?"true":"false");

    printf("  src mac addr: ");
    print_mac(vrtr_p->src_mac);

    print_action_pkt(vrtr_p->act_ttl_one);
    print_action_pkt(vrtr_p->act_ip_opt);
    
}

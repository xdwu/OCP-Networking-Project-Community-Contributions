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

static bool
set_single_vrtr_attr(
    vrtr_t  *vrtr_p, 
    const sai_attribute_t* attr)
{
    if( vrtr_p == NULL || attr == NULL) {
        return false;
    }

    switch(attr->id) {
        case SAI_VIRTUAL_ROUTER_ATTR_ADMIN_V4_STATE:
            vrtr_p->enbl_admin_v4 = attr->value.booldata;
            break;

        case SAI_VIRTUAL_ROUTER_ATTR_ADMIN_V6_STATE:
            vrtr_p->enbl_admin_v6 = attr->value.booldata;
            break;

        case SAI_VIRTUAL_ROUTER_ATTR_SRC_MAC_ADDRESS:
            mac_copy(vrtr_p->src_mac, attr->value.mac);
            break;

        case SAI_VIRTUAL_ROUTER_ATTR_VIOLATION_TTL1_ACTION:
            vrtr_p->act_ttl_one = attr->value.u8;
            break;

        case SAI_VIRTUAL_ROUTER_ATTR_VIOLATION_IP_OPTIONS:
            vrtr_p->act_ip_opt = attr->value.u8;
            break;

        default:
            return false;
    }

    return true;
}

sai_status_t
dummy_create_vrtr(
    _Out_ sai_object_id_t* vr_oid,
    _In_ uint32_t attr_count,
    _In_ const sai_attribute_t* attr_arr)
{
    printf("%s\n", __FUNCTION__);

    if (attr_count == 0) {
        return SAI_STATUS_SUCCESS;
    }

    if( attr_count >0 && attr_arr == NULL) {
        return SAI_STATUS_FAILURE;
    }


    vrtr_t *vrtr_p;
    int i;

    if(!new_vrtr(&vrtr_p)) {
        return SAI_STATUS_FAILURE;
    }

    for(i=0; i<attr_count; i++) {
        if(!set_single_vrtr_attr(vrtr_p, attr_arr+i)) {
            return SAI_STATUS_FAILURE;
        }
    }

    ll_add_end((node_t **)&(dummy_switch.vrtr_ll), (node_t*) vrtr_p);
    *vr_oid = vrtr_p->oid;

    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_remove_vrtr(
    _In_ sai_object_id_t vr_oid)
{
    printf("%s\n", __FUNCTION__);
    
    vrtr_t *vrtr_p;
    
    vrtr_p = (vrtr_t*) ll_unlink((node_t**)&(dummy_switch.vrtr_ll), vr_oid);

    if(vrtr_p == NULL) {
        return SAI_STATUS_FAILURE;
    }

    erase_vrtr(vrtr_p);

    return SAI_STATUS_SUCCESS;
}



sai_status_t
dummy_set_vrtr_attr(
    _In_ sai_object_id_t vr_oid,
    _In_ const sai_attribute_t* attr)
{
    printf("%s\n", __FUNCTION__);

    vrtr_t *vrtr_p;
    
    vrtr_p = (vrtr_t*) ll_search((node_t*)(dummy_switch.vrtr_ll), vr_oid);

    if(vrtr_p == NULL) {
        return SAI_STATUS_FAILURE;
    }

    switch(attr->id) {
        case SAI_VIRTUAL_ROUTER_ATTR_ADMIN_V4_STATE:
            vrtr_p->enbl_admin_v4 = attr->value.booldata;
            break;

        case SAI_VIRTUAL_ROUTER_ATTR_ADMIN_V6_STATE:
            vrtr_p->enbl_admin_v6 = attr->value.booldata;
            break;

        case SAI_VIRTUAL_ROUTER_ATTR_SRC_MAC_ADDRESS:
            mac_copy(vrtr_p->src_mac, attr->value.mac);
            break;

        case SAI_VIRTUAL_ROUTER_ATTR_VIOLATION_TTL1_ACTION:
            vrtr_p->act_ttl_one = attr->value.u8;
            break;

        case SAI_VIRTUAL_ROUTER_ATTR_VIOLATION_IP_OPTIONS:
            vrtr_p->act_ip_opt = attr->value.u8;
            break;

        default:
            return SAI_STATUS_FAILURE;
    }

    return SAI_STATUS_SUCCESS;
}


static bool
get_single_vrtr_attr(
    vrtr_t  *vrtr_p, 
    sai_attribute_t* attr)
{
    if( vrtr_p == NULL || attr == NULL) {
        return false;
    }

    switch(attr->id) {
        case SAI_VIRTUAL_ROUTER_ATTR_ADMIN_V4_STATE:
            attr->value.booldata = vrtr_p->enbl_admin_v4;
            break;

        case SAI_VIRTUAL_ROUTER_ATTR_ADMIN_V6_STATE:
            attr->value.booldata = vrtr_p->enbl_admin_v6;
            break;

        case SAI_VIRTUAL_ROUTER_ATTR_SRC_MAC_ADDRESS:
            mac_copy(attr->value.mac, vrtr_p->src_mac);
            break;

        case SAI_VIRTUAL_ROUTER_ATTR_VIOLATION_TTL1_ACTION:
            attr->value.u8 = vrtr_p->act_ttl_one;
            break;

        case SAI_VIRTUAL_ROUTER_ATTR_VIOLATION_IP_OPTIONS:
            attr->value.u8 = vrtr_p->act_ip_opt;
            break;

        default:
            return false;
    }

    return true;
}

sai_status_t
dummy_get_vrtr_attr(
    _In_ sai_object_id_t vr_oid,
    _In_ uint32_t attr_count,
    _Inout_ sai_attribute_t* attr_arr)
{
    printf("%s\n", __FUNCTION__);

    if(attr_count == 0) {
        return SAI_STATUS_SUCCESS;
    }

    if(attr_count >0 && attr_arr == NULL ) {
        return SAI_STATUS_FAILURE;
    }

    vrtr_t *vrtr_p;
    int i;
    
    vrtr_p = (vrtr_t*) ll_search((node_t*)(dummy_switch.vrtr_ll), vr_oid);

    if(vrtr_p == NULL) {
        return SAI_STATUS_FAILURE;
    }

    for(i=0; i<attr_count; i++) {
        if(!get_single_vrtr_attr(vrtr_p, attr_arr+i)) {
            return SAI_STATUS_FAILURE;
        }
    }

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

    vrtr_p->enbl_admin_v4 = true;
    vrtr_p->enbl_admin_v6 = true;
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

    printf("  oid: 0x%08lx\n", vrtr_p->oid);
    printf("  admin ipv4 state: %s\n", vrtr_p->enbl_admin_v4?"true":"false");
    printf("  admin ipv6 state: %s\n", vrtr_p->enbl_admin_v6?"true":"false");

    printf("  src mac addr: ");
    print_mac(vrtr_p->src_mac);

    print_action_pkt(vrtr_p->act_ttl_one);
    print_action_pkt(vrtr_p->act_ip_opt);
    
}

bool new_vrtr(vrtr_t **vrtr_pp)
{
    printf("%s\n", __FUNCTION__);
    vrtr_t  *p;
    p = (vrtr_t*)malloc(sizeof(vrtr_t));
    if(p == NULL) {
        return false;
    }

    if(!acquire_oid(&(p->oid))) {
        free(p);
        return false;
    }

    if(!init_vrtr(p)) {
        release_oid(p->oid);
        free(p);
    }

    p->next = NULL;
    *vrtr_pp = p;

    return true;
}

void erase_vrtr(vrtr_t *p)
{
    printf("%s\n", __FUNCTION__);

    if(p == NULL) {
        return;
    }

    release_oid(p->oid);
    free(p);
}

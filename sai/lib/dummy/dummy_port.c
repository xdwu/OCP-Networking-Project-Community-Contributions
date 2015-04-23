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
#include "dummy_port.h"
#include "dummy_init.h"

sai_status_t
dummy_set_port_attr(
    _In_ sai_object_id_t port_id,
    _In_ const sai_attribute_t* attr)
{
    printf("%s\n", __FUNCTION__);

    if(attr == NULL || port_id < 0 
            || port_id > dummy_switch_db.num_max_port) {
        return SAI_STATUS_FAILURE;
    }

    port_db_t *dummy_port_db_p;

    dummy_port_db_p = dummy_switch_db.ports;
    for(; dummy_port_db_p != NULL; ) {
        if (port_id == dummy_port_db_p->id) {
            break;
        }
        dummy_port_db_p = dummy_port_db_p->next;
    }

    if (dummy_port_db_p == NULL) {
        return SAI_STATUS_FAILURE;
    }

    switch(attr->id) {
        //Read Only
        case SAI_PORT_ATTR_TYPE:
        case SAI_PORT_ATTR_OPER_STATUS:
        case SAI_PORT_ATTR_HW_LANE_LIST:
        case SAI_PORT_ATTR_SUPPORTED_BREAKOUT_MODE:
        case SAI_PORT_ATTR_CURRENT_BREAKOUT_MODE:
            break;

        //Read Write
        case SAI_PORT_ATTR_SPEED:
            dummy_port_db_p->speed = attr->value.u32;
            break;

        case SAI_PORT_ATTR_ADMIN_STATE:
            dummy_port_db_p->enable_admin_mode = attr->value.booldata;
            break;

        case SAI_PORT_ATTR_MEDIA_TYPE:
            dummy_port_db_p->type_media = attr->value.u8;
            break;

        case SAI_PORT_ATTR_DEFAULT_VLAN:
            dummy_port_db_p->default_vlan_id = attr->value.u16;
            break;

        case SAI_PORT_ATTR_DEFAULT_VLAN_PRIORITY:
            dummy_port_db_p->default_vlan_pri = attr->value.u8;
            break;

        case SAI_PORT_ATTR_INGRESS_FILTERING:
            dummy_port_db_p->enable_ingress_filtering = attr->value.booldata;
            break;

        case SAI_PORT_ATTR_DROP_UNTAGGED:
            dummy_port_db_p->enable_drop_untagged = attr->value.booldata;
            break;

        case SAI_PORT_ATTR_DROP_TAGGED:
            dummy_port_db_p->enable_drop_tagged = attr->value.booldata;
            break;

        case SAI_PORT_ATTR_INTERNAL_LOOPBACK:
            dummy_port_db_p->mode_int_lpbk = attr->value.u8;
            break;

        case SAI_PORT_ATTR_FDB_LEARNING:
            dummy_port_db_p->mode_fdb_learning = attr->value.u8;
            break;

        case SAI_PORT_ATTR_UPDATE_DSCP:
            dummy_port_db_p->enable_update_dscp = attr->value.booldata;
            break;

        case SAI_PORT_ATTR_MTU:
            dummy_port_db_p->mtu = attr->value.u32;
            break;

        case SAI_PORT_ATTR_FLOOD_STORM_CONTROL:
            dummy_port_db_p->enable_flood_storm_cntl = attr->value.booldata;
            break;

        case SAI_PORT_ATTR_BROADCAST_STORM_CONTROL:
            dummy_port_db_p->enable_bcast_storm_cntl = attr->value.booldata;
            break;

        case SAI_PORT_ATTR_MULTICAST_STORM_CONTROL:
            dummy_port_db_p->enable_mcast_storm_cntl = attr->value.booldata;
            break;

        case SAI_PORT_ATTR_GLOBAL_FLOW_CONTROL:
            dummy_port_db_p->mode_globle_flow_cntl = attr->value.u8;
            break;

        case SAI_PORT_ATTR_MAX_LEARNED_ADDRESSES:
            dummy_port_db_p->num_max_learned_addr = attr->value.u32;
            break;

        case SAI_PORT_ATTR_FDB_LEARNING_LIMIT_VIOLATION:
            dummy_port_db_p->act_fdb_learn_limit = attr->value.u8;
            break;

        case SAI_PORT_ATTR_INGRESS_MIRROR_SESSION:
            dummy_port_db_p->ingress_mir_sess_lst = attr->value.objlist;
            break;

        case SAI_PORT_ATTR_EGRESS_MIRROR_SESSION:
            dummy_port_db_p->egress_mir_sess_lst = attr->value.objlist;
            break;

        case SAI_PORT_ATTR_INGRESS_SAMPLEPACKET_ENABLE:
            dummy_port_db_p->ingress_smpl_pkt_id = attr->value.oid;
            break;

        case SAI_PORT_ATTR_EGRESS_SAMPLEPACKET_ENABLE:
            dummy_port_db_p->egress_smpl_pkt_id = attr->value.oid;
            break;

        default:
            return SAI_STATUS_FAILURE;
    }

    return SAI_STATUS_SUCCESS;
}


static sai_status_t
dummy_get_single_port_attr( 
    _In_ port_db_t *dummy_port_db_p, 
    _Inout_ sai_attribute_t* attr)
{
    if (dummy_port_db_p == NULL || attr == NULL) {
        return SAI_STATUS_FAILURE;
    }

    switch(attr->id) {
        //Read Only
        case SAI_PORT_ATTR_TYPE:
            attr->value.u8 = dummy_port_db_p->type;
            break;

        case SAI_PORT_ATTR_OPER_STATUS:
            attr->value.u8 = dummy_port_db_p->state_port;
            break;

        case SAI_PORT_ATTR_HW_LANE_LIST:
            attr->value.u32list = dummy_port_db_p->hw_lane_lst;
            break;

        case SAI_PORT_ATTR_SUPPORTED_BREAKOUT_MODE:
            attr->value.u32list = dummy_port_db_p->sptd_brkout_mode_lst;
            break;

        case SAI_PORT_ATTR_CURRENT_BREAKOUT_MODE:
            attr->value.u8 = dummy_port_db_p->mode_curr_brkout;
            break;

        //Read Write
        case SAI_PORT_ATTR_SPEED:
            attr->value.u32 = dummy_port_db_p->speed;
            break;

        case SAI_PORT_ATTR_ADMIN_STATE:
            attr->value.booldata = dummy_port_db_p->enable_admin_mode;
            break;

        case SAI_PORT_ATTR_MEDIA_TYPE:
            attr->value.u8 = dummy_port_db_p->type_media;
            break;

        case SAI_PORT_ATTR_DEFAULT_VLAN:
            attr->value.u16 = dummy_port_db_p->default_vlan_id;
            break;

        case SAI_PORT_ATTR_DEFAULT_VLAN_PRIORITY:
            attr->value.u8 = dummy_port_db_p->default_vlan_pri;
            break;

        case SAI_PORT_ATTR_INGRESS_FILTERING:
            attr->value.booldata = dummy_port_db_p->enable_ingress_filtering;
            break;

        case SAI_PORT_ATTR_DROP_UNTAGGED:
            attr->value.booldata = dummy_port_db_p->enable_drop_untagged;
            break;

        case SAI_PORT_ATTR_DROP_TAGGED:
            attr->value.booldata = dummy_port_db_p->enable_drop_tagged;
            break;

        case SAI_PORT_ATTR_INTERNAL_LOOPBACK:
            attr->value.u8 = dummy_port_db_p->mode_int_lpbk;
            break;

        case SAI_PORT_ATTR_FDB_LEARNING:
            attr->value.u8 = dummy_port_db_p->mode_fdb_learning;
            break;

        case SAI_PORT_ATTR_UPDATE_DSCP:
            attr->value.booldata = dummy_port_db_p->enable_update_dscp;
            break;

        case SAI_PORT_ATTR_MTU:
            attr->value.u32 = dummy_port_db_p->mtu;
            break;

        case SAI_PORT_ATTR_FLOOD_STORM_CONTROL:
            attr->value.booldata = dummy_port_db_p->enable_flood_storm_cntl;
            break;

        case SAI_PORT_ATTR_BROADCAST_STORM_CONTROL:
            attr->value.booldata = dummy_port_db_p->enable_bcast_storm_cntl;
            break;

        case SAI_PORT_ATTR_MULTICAST_STORM_CONTROL:
            attr->value.booldata = dummy_port_db_p->enable_mcast_storm_cntl;
            break;

        case SAI_PORT_ATTR_GLOBAL_FLOW_CONTROL:
            attr->value.u8 = dummy_port_db_p->mode_globle_flow_cntl;
            break;

        case SAI_PORT_ATTR_MAX_LEARNED_ADDRESSES:
            attr->value.u32 = dummy_port_db_p->num_max_learned_addr;
            break;

        case SAI_PORT_ATTR_FDB_LEARNING_LIMIT_VIOLATION:
            attr->value.u8 = dummy_port_db_p->act_fdb_learn_limit;
            break;

        case SAI_PORT_ATTR_INGRESS_MIRROR_SESSION:
            attr->value.objlist = dummy_port_db_p->ingress_mir_sess_lst;
            break;

        case SAI_PORT_ATTR_EGRESS_MIRROR_SESSION:
            attr->value.objlist = dummy_port_db_p->egress_mir_sess_lst;
            break;

        case SAI_PORT_ATTR_INGRESS_SAMPLEPACKET_ENABLE:
            attr->value.oid = dummy_port_db_p->ingress_smpl_pkt_id;
            break;

        case SAI_PORT_ATTR_EGRESS_SAMPLEPACKET_ENABLE:
            attr->value.oid = dummy_port_db_p->egress_smpl_pkt_id;
            break;

        default:
            return SAI_STATUS_FAILURE;
    }
    
    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_get_port_attr(
    _In_ sai_object_id_t port_id,
    _In_ uint32_t attr_count,
    _Inout_ sai_attribute_t* attr_arr)
{
    printf("%s\n", __FUNCTION__);

    if(attr_arr == NULL || port_id < 0 
            || port_id > dummy_switch_db.num_max_port) {
        return SAI_STATUS_FAILURE;
    }


    port_db_t *dummy_port_db_p;

    int i;

    dummy_port_db_p = dummy_switch_db.ports;
    for(; dummy_port_db_p != NULL; ) {
        if (port_id == dummy_port_db_p->id) {
            break;
        }
        dummy_port_db_p = dummy_port_db_p->next;
    }

    if (dummy_port_db_p == NULL) {
        return SAI_STATUS_FAILURE;
    }

    sai_status_t ret;

    for (i =0; i< attr_count ; i++) {
        ret = dummy_get_single_port_attr(dummy_port_db_p, (attr_arr+i));
        if (ret != SAI_STATUS_SUCCESS) {
            return SAI_STATUS_FAILURE;
        }
    }

    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_get_port_stats(
    _In_ sai_object_id_t port_id,
    _In_ const sai_port_stat_counter_t *counter_ids,
    _In_ uint32_t number_of_counters,
    _Out_ uint64_t* counters)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}


sai_port_api_t dummy_port_method_table = {
    dummy_set_port_attr,
    dummy_get_port_attr,
    dummy_get_port_stats
};


bool
init_port_db(port_db_t *port_db_p)
{
    return true;
}


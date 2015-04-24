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
#include "dummy_switch.h"

void
dummy_hndlr_switch_state_change(
    _In_ sai_switch_oper_status_t switch_oper_status)
{
    printf("%s state -> ", __FUNCTION__ );
    print_switch_state(switch_oper_status);
}

void
dummy_hndlr_fdb_event(
    _In_ sai_fdb_event_t event_type,
    _In_ sai_fdb_entry_t* fdb_entry,
    _In_ uint32_t attr_count,
    _In_ sai_attribute_t* attr_list)
{
    printf("%s\n", __FUNCTION__);
}

void
dummy_hndlr_port_state_change(
    _In_ sai_object_id_t port_id,
    _In_ sai_port_oper_status_t port_status)
{
    printf("%s port[0x%8lx] -> ", __FUNCTION__, port_id);
    print_switch_state(port_status);

}


void 
dummy_hndlr_shutdown_request (void)
{
    printf("%s\n", __FUNCTION__);
}

void
dummy_hndlr_port_event(
    _In_ sai_object_id_t port_id,
    _In_ sai_port_event_t port_event)
{
    printf("%s\n", __FUNCTION__);
}

sai_switch_notification_t dummy_switch_notification_handlers = {
    dummy_hndlr_switch_state_change,
    dummy_hndlr_fdb_event,
    dummy_hndlr_port_state_change,
    dummy_hndlr_port_event,
    dummy_hndlr_shutdown_request
};

/*---------------------------------------------*/
/* SWITCH */
/*---------------------------------------------*/
#define MAX_PORT            2
#define MAX_VRTR            2
#define SIZE_FORWARD_TABLE  32768

sai_status_t
dummy_init_switch(
    _In_ sai_switch_profile_id_t profile_id,
    _In_reads_z_(SAI_MAX_HARDWARE_ID_LEN) char* switch_hardware_id,
    _In_reads_opt_z_(SAI_MAX_FIRMWARE_PATH_NAME_LEN) char* firmware_path_name,
    _In_ sai_switch_notification_t* switch_notifications)
{
    printf("%s\n", __FUNCTION__);

    
    dummy_switch.state_oper = SAI_SWITCH_OPER_STATUS_UNKNOWN;
    dummy_switch.num_max_port = MAX_PORT;

    dummy_switch.port_list.count = dummy_switch.num_max_port; //Not Sure where to get info
    dummy_switch.port_list.list = 
        (sai_object_id_t*)malloc(sizeof(sai_object_id_t)*
                dummy_switch.port_list.count);

    if (dummy_switch.port_list.list == NULL) {
        return SAI_STATUS_FAILURE;
    }

    int i;
    uint64_t id;
    for(i=0; i<dummy_switch.port_list.count; i++) {
        if(!acquire_id(&id)){
            return SAI_STATUS_FAILURE;
        }
        dummy_switch.port_list.list[i] = id;
    }
    
    dummy_switch.cpu_port = 0;
    dummy_switch.num_max_vrtr = MAX_VRTR;
    dummy_switch.size_fdb_tbl = SIZE_FORWARD_TABLE;
    dummy_switch.enable_link_route = false;
    dummy_switch.max_temp = -1;
    dummy_switch.min_pri_acl_tbl = 1;
    dummy_switch.max_pri_acl_tbl = 7;
    dummy_switch.min_pri_acl_ent = 1;
    dummy_switch.max_pri_acl_ent = 7;
    dummy_switch.default_stp_inst_id = 0;

    dummy_switch.mode_switch = SAI_SWITCHING_MODE_STORE_AND_FORWARD;
    dummy_switch.enable_bcast_cpu_flood = false;
    dummy_switch.enable_mcast_cpu_flood = false;
    dummy_switch.act_ttl_one = SAI_PACKET_ACTION_TRAP;
    dummy_switch.default_port_vlan_id = 1;


    dummy_switch.default_mac_addr[0] = 0x00;
    dummy_switch.default_mac_addr[1] = 0x10;
    dummy_switch.default_mac_addr[2] = 0x20;
    dummy_switch.default_mac_addr[3] = 0x30;
    dummy_switch.default_mac_addr[4] = 0x40;
    dummy_switch.default_mac_addr[5] = 0x50;

    dummy_switch.num_max_learned_addr = 0;
    dummy_switch.time_aging_fdb = 0;
    dummy_switch.act_fdb_ucast_miss = SAI_PACKET_ACTION_FORWARD;
    dummy_switch.act_fdb_bcast_miss = SAI_PACKET_ACTION_FORWARD;
    dummy_switch.act_fdb_mcast_miss = SAI_PACKET_ACTION_FORWARD;

    srand(time(NULL));
    dummy_switch.algo_lag_hash = SAI_HASH_CRC;
    dummy_switch.seed_lag_hash = rand();
    dummy_switch.fields_lag_hash.count = 0;        //type sai_s32_list_t
    dummy_switch.fields_lag_hash.list = NULL;      

    dummy_switch.algo_ecmp_hash = SAI_HASH_CRC;
    dummy_switch.seed_ecmp_hash = rand();
    dummy_switch.fields_ecmp_hash.count = 0;       //type sai_s32_list_t
    dummy_switch.fields_ecmp_hash.list = NULL;

    dummy_switch.num_max_path_ecmp = 64;

    dummy_switch.mode_port_brkout.breakout_mode =  SAI_PORT_BREAKOUT_MODE_1_LANE;
    dummy_switch.mode_port_brkout.port_list.count = 0;
    dummy_switch.mode_port_brkout.port_list.list = NULL;

    /* initialize ports */

    bool ret;
    port_t   *port_p, *last;

    last = dummy_switch.ports;

    for (i=0; i< dummy_switch.port_list.count; i++) {
        port_p = (port_t *)malloc(sizeof(port_t));
        if(port_p == NULL) {
            return SAI_STATUS_FAILURE;
        }

        port_p->id = dummy_switch.port_list.list[i];
        port_p->next = NULL;
        ret = init_port(port_p);

        if(i==0) {
            port_p->type = SAI_PORT_TYPE_CPU;
        }

        if (!ret ) {
            return SAI_STATUS_FAILURE;
        }
        
        if(dummy_switch.ports == NULL) {
            dummy_switch.ports = port_p;
            last = port_p;
        } else {
            last->next = port_p;
            last = port_p;
        }

        // Change State of Ports 
        dummy_switch_notification_handlers.on_port_state_change(
                port_p->id, SAI_PORT_OPER_STATUS_UP);
    }


    /* Change the State of Switch to Up */
    dummy_switch.state_oper = SAI_SWITCH_OPER_STATUS_UP;
    dummy_switch_notification_handlers.on_switch_state_change(SAI_SWITCH_OPER_STATUS_UP);

    show_switch();
    return SAI_STATUS_SUCCESS;
}


void 
dummy_shutdown_switch(
    _In_ bool war_restart_hint)
{
    printf("%s\n", __FUNCTION__);

    /* Release the Memory */
    //To Do:
    //Change State of Ports 
    /* ... Release Port_DB */

    free(dummy_switch.port_list.list);
    free(dummy_switch.fields_lag_hash.list);
    free(dummy_switch.fields_ecmp_hash.list);
    free(dummy_switch.mode_port_brkout.port_list.list);

    /* Change the State of Switch to Down */
    dummy_switch.state_oper = SAI_SWITCH_OPER_STATUS_DOWN;
    dummy_switch_notification_handlers.on_switch_state_change(SAI_SWITCH_OPER_STATUS_DOWN);
}


sai_status_t 
dummy_connect_switch(
    _In_ sai_switch_profile_id_t profile_id,
    _In_reads_z_(SAI_MAX_HARDWARE_ID_LEN) char* switch_hardware_id,
    _In_ sai_switch_notification_t* switch_notifications)
{
    printf("%s\n", __FUNCTION__);
    return SAI_STATUS_SUCCESS;
}

void
dummy_disconnect_switch(void)
{
    printf("%s\n", __FUNCTION__);
}

sai_status_t
dummy_set_switch_attr(
    _In_ const sai_attribute_t *attr)
{
    printf("%s\n", __FUNCTION__);

    if(attr == NULL) {
        return SAI_STATUS_FAILURE;
    }

    switch(attr->id) {
        //Read Only
        case SAI_SWITCH_ATTR_PORT_NUMBER:
        case SAI_SWITCH_ATTR_PORT_LIST:
        case SAI_SWITCH_ATTR_CPU_PORT:
        case SAI_SWITCH_ATTR_MAX_VIRTUAL_ROUTERS:
        case SAI_SWITCH_ATTR_FDB_TABLE_SIZE:
        case SAI_SWITCH_ATTR_ON_LINK_ROUTE_SUPPORTED:
        case SAI_SWITCH_ATTR_OPER_STATUS:
        case SAI_SWITCH_ATTR_MAX_TEMP:
        case SAI_SWITCH_ATTR_ACL_TABLE_MINIMUM_PRIORITY:
        case SAI_SWITCH_ATTR_ACL_TABLE_MAXIMUM_PRIORITY:
        case SAI_SWITCH_ATTR_ACL_ENTRY_MINIMUM_PRIORITY:
        case SAI_SWITCH_ATTR_ACL_ENTRY_MAXIMUM_PRIORITY:
        case SAI_SWITCH_ATTR_DEFAULT_STP_INST_ID:
            break;

        //Read Write
        case SAI_SWITCH_ATTR_SWITCHING_MODE:
            dummy_switch.mode_switch = attr->value.u32;
            break;

        case SAI_SWITCH_ATTR_BCAST_CPU_FLOOD_ENABLE:
            dummy_switch.enable_bcast_cpu_flood = attr->value.booldata;
            break;

        case SAI_SWITCH_ATTR_MCAST_CPU_FLOOD_ENABLE:
            dummy_switch.enable_mcast_cpu_flood = attr->value.booldata;
            break;

        case SAI_SWITCH_ATTR_VIOLATION_TTL1_ACTION:
            dummy_switch.act_ttl_one = attr->value.u8;
            break;

        case SAI_SWITCH_ATTR_DEFAULT_PORT_VLAN_ID:
            dummy_switch.default_port_vlan_id = attr->value.u16;
            break;

        case SAI_SWITCH_ATTR_SRC_MAC_ADDRESS:
            dummy_switch.default_mac_addr[0] = attr->value.mac[0];
            dummy_switch.default_mac_addr[1] = attr->value.mac[1];
            dummy_switch.default_mac_addr[2] = attr->value.mac[2];
            dummy_switch.default_mac_addr[3] = attr->value.mac[3];
            dummy_switch.default_mac_addr[4] = attr->value.mac[4];
            dummy_switch.default_mac_addr[5] = attr->value.mac[5];
            break;

        case SAI_SWITCH_ATTR_MAX_LEARNED_ADDRESSES:
            dummy_switch.num_max_learned_addr = attr->value.u32;
            break;

        case SAI_SWITCH_ATTR_FDB_AGING_TIME:
            dummy_switch.time_aging_fdb = attr->value.u32;
            break;

        case SAI_SWITCH_ATTR_FDB_UNICAST_MISS_ACTION:
            dummy_switch.act_fdb_ucast_miss = attr->value.u8;
            break;

        case SAI_SWITCH_ATTR_FDB_BROADCAST_MISS_ACTION:
            dummy_switch.act_fdb_bcast_miss = attr->value.u8;
            break;

        case SAI_SWITCH_ATTR_FDB_MULTICAST_MISS_ACTION:
            dummy_switch.act_fdb_mcast_miss = attr->value.u8;
            break;

        case SAI_SWITCH_ATTR_LAG_HASH_ALGO:
            dummy_switch.algo_lag_hash = attr->value.u8;
            break;

        case SAI_SWITCH_ATTR_LAG_HASH_SEED:
            dummy_switch.seed_lag_hash = attr->value.u32;
            break;

        case SAI_SWITCH_ATTR_LAG_HASH_FIELDS:
            dummy_switch.fields_lag_hash = attr->value.s32list;
            break;

        case SAI_SWITCH_ATTR_ECMP_HASH_ALGO:
            dummy_switch.algo_ecmp_hash = attr->value.u8;
            break;

        case SAI_SWITCH_ATTR_ECMP_HASH_SEED:
            dummy_switch.seed_ecmp_hash = attr->value.u32;
            break;

        case SAI_SWITCH_ATTR_ECMP_HASH_FIELDS:
            dummy_switch.fields_ecmp_hash = attr->value.s32list;
            break;

        case SAI_SWITCH_ATTR_ECMP_MAX_PATHS:
            dummy_switch.num_max_path_ecmp = attr->value.u32;
            break;

        //Write
        case SAI_SWITCH_ATTR_PORT_BREAKOUT:
            dummy_switch.mode_port_brkout = attr->value.portbreakout;
            break;

        case SAI_SWITCH_ATTR_CUSTOM_RANGE_BASE:
            dummy_switch.custom_range_base = attr->value.u64;
            break;

        default:
            return SAI_STATUS_FAILURE;
    }

    return SAI_STATUS_SUCCESS;
}


static sai_status_t
dummy_get_single_sw_attr(_Inout_ sai_attribute_t *attr)
{
    printf("%s \n", __FUNCTION__);

    if(attr == NULL) {
        return SAI_STATUS_FAILURE;
    }

    switch (attr->id) {
        //Read Only
        case SAI_SWITCH_ATTR_PORT_NUMBER:
            attr->value.u32 = dummy_switch.num_max_port;
            break;

        case SAI_SWITCH_ATTR_PORT_LIST:
            attr->value.objlist = dummy_switch.port_list;
            break;

        case SAI_SWITCH_ATTR_CPU_PORT:
            attr->value.oid = dummy_switch.cpu_port;
            break;

        case SAI_SWITCH_ATTR_MAX_VIRTUAL_ROUTERS:
            attr->value.u32 = dummy_switch.num_max_vrtr;
            break;

        case SAI_SWITCH_ATTR_FDB_TABLE_SIZE:
            attr->value.u32 = dummy_switch.size_fdb_tbl;
            break;

        case SAI_SWITCH_ATTR_ON_LINK_ROUTE_SUPPORTED:
            attr->value.booldata = dummy_switch.enable_link_route;
            break;

        case SAI_SWITCH_ATTR_OPER_STATUS:
            attr->value.u8 = dummy_switch.state_oper;
            break;

        case SAI_SWITCH_ATTR_MAX_TEMP:
            attr->value.s32 = dummy_switch.max_temp;
            break;

        case SAI_SWITCH_ATTR_ACL_TABLE_MINIMUM_PRIORITY:
            attr->value.u32 = dummy_switch.min_pri_acl_tbl;
            break;

        case SAI_SWITCH_ATTR_ACL_TABLE_MAXIMUM_PRIORITY:
            attr->value.u32 = dummy_switch.max_pri_acl_tbl;
            break;

        case SAI_SWITCH_ATTR_ACL_ENTRY_MINIMUM_PRIORITY:
            attr->value.u32 = dummy_switch.min_pri_acl_ent;
            break;

        case SAI_SWITCH_ATTR_ACL_ENTRY_MAXIMUM_PRIORITY:
            attr->value.u32 = dummy_switch.max_pri_acl_ent;
            break;

        case SAI_SWITCH_ATTR_DEFAULT_STP_INST_ID:
            attr->value.oid = dummy_switch.default_stp_inst_id;
            break;

        //Read Write
        case SAI_SWITCH_ATTR_SWITCHING_MODE:
            attr->value.u32 = dummy_switch.mode_switch;
            break;

        case SAI_SWITCH_ATTR_BCAST_CPU_FLOOD_ENABLE:
            attr->value.booldata =  dummy_switch.enable_bcast_cpu_flood;
            break;

        case SAI_SWITCH_ATTR_MCAST_CPU_FLOOD_ENABLE:
            attr->value.booldata = dummy_switch.enable_mcast_cpu_flood;
            break;

        case SAI_SWITCH_ATTR_VIOLATION_TTL1_ACTION:
            attr->value.u8 = dummy_switch.act_ttl_one;
            break;

        case SAI_SWITCH_ATTR_DEFAULT_PORT_VLAN_ID:
            attr->value.u16 = dummy_switch.default_port_vlan_id;
            break;

        case SAI_SWITCH_ATTR_SRC_MAC_ADDRESS:
            attr->value.mac[0] = dummy_switch.default_mac_addr[0];
            attr->value.mac[1] = dummy_switch.default_mac_addr[1];
            attr->value.mac[2] = dummy_switch.default_mac_addr[2];
            attr->value.mac[3] = dummy_switch.default_mac_addr[3];
            attr->value.mac[4] = dummy_switch.default_mac_addr[4];
            attr->value.mac[5] = dummy_switch.default_mac_addr[5];
            break;

        case SAI_SWITCH_ATTR_MAX_LEARNED_ADDRESSES:
            attr->value.u32 = dummy_switch.num_max_learned_addr;
            break;

        case SAI_SWITCH_ATTR_FDB_AGING_TIME:
            attr->value.u32 = dummy_switch.time_aging_fdb;
            break;

        case SAI_SWITCH_ATTR_FDB_UNICAST_MISS_ACTION:
            attr->value.u8 = dummy_switch.act_fdb_ucast_miss;
            break;

        case SAI_SWITCH_ATTR_FDB_BROADCAST_MISS_ACTION:
            attr->value.u8 = dummy_switch.act_fdb_bcast_miss;
            break;

        case SAI_SWITCH_ATTR_FDB_MULTICAST_MISS_ACTION:
            attr->value.u8 = dummy_switch.act_fdb_mcast_miss;
            break;

        case SAI_SWITCH_ATTR_LAG_HASH_ALGO:
            attr->value.u8 = dummy_switch.algo_lag_hash;
            break;

        case SAI_SWITCH_ATTR_LAG_HASH_SEED:
            attr->value.u32 = dummy_switch.seed_lag_hash;
            break;

        case SAI_SWITCH_ATTR_LAG_HASH_FIELDS:
            attr->value.s32list = dummy_switch.fields_lag_hash;
            break;

        case SAI_SWITCH_ATTR_ECMP_HASH_ALGO:
            attr->value.u8 = dummy_switch.algo_ecmp_hash = attr->value.u8;
            break;

        case SAI_SWITCH_ATTR_ECMP_HASH_SEED:
            attr->value.u32 = dummy_switch.seed_ecmp_hash;
            break;

        case SAI_SWITCH_ATTR_ECMP_HASH_FIELDS:
            attr->value.s32list = dummy_switch.fields_ecmp_hash;
            break;

        case SAI_SWITCH_ATTR_ECMP_MAX_PATHS:
            attr->value.u32 = dummy_switch.num_max_path_ecmp;
            break;

        //Write
        case SAI_SWITCH_ATTR_PORT_BREAKOUT:
        case SAI_SWITCH_ATTR_CUSTOM_RANGE_BASE:
            break;

        default:
            return SAI_STATUS_FAILURE;
    }

    return SAI_STATUS_SUCCESS;
}

sai_status_t
dummy_get_switch_attr(
    _In_ uint32_t attr_count,
    _Inout_ sai_attribute_t *attr_arr)
{
    printf("%s attr count %d\n", __FUNCTION__, attr_count);

    if (attr_count == 0 || attr_arr == NULL) {
        return SAI_STATUS_FAILURE;
    }

    /*
    if (attr_count != sizeof(attr_arr)/sizeof(attr_arr[0])) {
        return SAI_STATUS_FAILURE;
    }
    */

    int i = 0;
    sai_status_t ret;

    for (i =0; i< attr_count ; i++) {
        ret = dummy_get_single_sw_attr((attr_arr+i));
        if (ret != SAI_STATUS_SUCCESS) {
            return SAI_STATUS_FAILURE;
        }
    }

    return SAI_STATUS_SUCCESS;
}

sai_switch_api_t dummy_switch_method_table = {
    dummy_init_switch,
    dummy_shutdown_switch,
    dummy_connect_switch,
    dummy_disconnect_switch,
    dummy_set_switch_attr,
    dummy_get_switch_attr
};

/* Internal Functions */

void show_switch(void)
{
    printf("======== switch ====================\n");
    printf("  state: ");
    print_switch_state(dummy_switch.state_oper);

    printf("  # of ports: %d\n", dummy_switch.num_max_port);
    printf("  CPU port: %lu\n", dummy_switch.cpu_port);
    printf("  # of virtual router: %d\n", dummy_switch.num_max_vrtr);
    printf("  size of fwd table: %d\n", dummy_switch.size_fdb_tbl);
    printf("  local subnet routing: %s\n", (dummy_switch.enable_link_route)?"true":"false");
    printf("  max temperature: %d\n", dummy_switch.max_temp);
    printf("  min priority acl table: %d\n", dummy_switch.min_pri_acl_tbl);
    printf("  max priority acl table: %d\n", dummy_switch.max_pri_acl_tbl);
    printf("  min priority acl entry: %d\n", dummy_switch.min_pri_acl_ent);
    printf("  max priority acl entry: %d\n", dummy_switch.max_pri_acl_ent);
    printf("  default STP instance id: %lu\n", dummy_switch.default_stp_inst_id);
    printf("  switching mode: " );
    print_switch_sw_mode(dummy_switch.mode_switch);

    printf("  L2 broadcast flood control to CPU port: %s\n", 
            dummy_switch.enable_bcast_cpu_flood?"true":"false");

    printf("  L2 multicast flood control to CPU port: %s\n", 
            dummy_switch.enable_mcast_cpu_flood?"true":"false");

    printf("  action for packets with TTL=0/TTL=1: ");
    print_action_pkt(dummy_switch.act_ttl_one);

    printf("  default vlan id for ports not in any group: %d\n", 
            dummy_switch.default_port_vlan_id);

    printf("  default switch MAC address: ");
    print_mac(dummy_switch.default_mac_addr);
 
    printf("  max # of learned MAC address: %d\n", dummy_switch.num_max_learned_addr);
    printf("  dynamic FDB entry aging time (sec): %d\n", dummy_switch.time_aging_fdb);

    printf("  action control w/ unknown dest addr unicast: ");
    print_action_pkt(dummy_switch.act_fdb_ucast_miss);

    printf("  action control w/ unknown dest addr broadcast: ");
    print_action_pkt(dummy_switch.act_fdb_bcast_miss);

    printf("  action control w/ unknown dest addr multicast: ");
    print_action_pkt(dummy_switch.act_fdb_bcast_miss);

    printf("  hash algorithm for all LAGs: ");
    print_switch_hash_algo(dummy_switch.algo_lag_hash);

    printf("  hash seed for all LAGs: %u\n", dummy_switch.seed_lag_hash);

    printf("  hash fields for all LAGs: count %d\n", 
            dummy_switch.fields_lag_hash.count);

    printf("  hash algorithm for all ECMPs: ");
    print_switch_hash_algo(dummy_switch.algo_ecmp_hash);

    printf("  hash seed for all ECMPs: %u\n", dummy_switch.seed_ecmp_hash);

    printf("  hash fields for all ECMPs: count %d\n", 
            dummy_switch.fields_ecmp_hash.count);

    printf("  ECMP max # of paths per group: %d\n", dummy_switch.num_max_path_ecmp);

    printf("  port breakout mode: ");
    print_port_brkout_mode(dummy_switch.mode_port_brkout.breakout_mode);

    printf("  custom range base: 0x%8x\n", SAI_SWITCH_ATTR_CUSTOM_RANGE_BASE);

    printf("  ports: ");
    int i;
    for(i=0; i<dummy_switch.port_list.count; i++) {
        printf("0x%8lx ", dummy_switch.port_list.list[i]);
    }
    printf("\n");

    port_t *p;

    p = dummy_switch.ports;
    while(p) {
        show_port(p);
        p = p->next;
    }

    printf("\n");
    return;
}

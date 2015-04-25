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

#ifndef __DUMMY_H_
#define __DUMMY_H_

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "sai.h"
#include "saitypes.h"
#include "saistatus.h"
#include "saiswitch.h"
#include "saiport.h"
#include "saivlan.h"
#include "saifdb.h"
#include "sairouter.h"
#include "sairouterintf.h"
#include "saineighbor.h"
#include "sainexthop.h"
#include "sainexthopgroup.h"
#include "sairoute.h"
#include "saiqos.h"
#include "saiacl.h"
#include "saihostintf.h"
#include "saimirror.h"
#include "saistp.h"
#include "saisamplepacket.h"
#include "sailag.h"

sai_switch_api_t* sai_switch_api;
sai_port_api_t* sai_port_api;
sai_fdb_api_t* sai_fdb_api;
sai_vlan_api_t* sai_vlan_api;
sai_virtual_router_api_t* sai_vr_api;
sai_route_api_t* sai_route_api;
sai_next_hop_api_t* sai_next_hop_api;
sai_next_hop_group_api_t* sai_next_hop_group_api;
sai_router_interface_api_t* sai_rif_api;
sai_neighbor_api_t* sai_neighbor_api;
sai_qos_api_t* sai_qos_api;
sai_acl_api_t* sai_acl_api;
sai_hostif_api_t* sai_hif_api;
sai_mirror_api_t* sai_mirror_api;
sai_samplepacket_api_t* sai_smpl_pkt_api;
sai_stp_api_t* sai_stp_api;
sai_lag_api_t* sai_lag_api;

sai_switch_notification_t dummy_switch_notification_handlers;



/* Public Data Structure */

typedef struct _vlan_t {
    /* Internal Data Structure */
    struct _vlan_t           *next;

    /* Read Write */
    uint32_t                max_learn_addr;
    sai_object_id_t         stp_inst_oid;

    /* CUSTOM RANGE BASE */ //?
} vlan_t;


typedef struct stp_t {
    /* Internal Data Structure */
    struct _stp_t           *next;
    sai_object_id_t             oid;

    /* Read Only */
    sai_vlan_list_t         vlan_lst;
} stp_t;

typedef struct _smpl_pkt_t {
    /* Internal Data Structure */
    struct _smpl_pkt_t          *next;
    sai_object_id_t             oid;

    /* Read Only */
    /* Read Write */
    uint32_t                    rate;
    sai_samplepacket_type_t     type;

} smpl_pkt_t;


typedef struct _rtr_intf_t {
    /* Internal Data Structure */
    struct _rtr_intf_t             *next;
    sai_object_id_t             oid;
    

    /* Read Only */
    sai_object_id_t                 vrtr_oid;
    sai_router_interface_type_t     type;
    sai_object_id_t                 port_oid;
    sai_vlan_id_t                   valn_id;

    /* Read Write */
    sai_mac_t                       src_mac;
    bool                            admin_v4_state;
    bool                            admin_v6_state;
    uint32_t                        mtu;

    /* CUSTOM RANGE BASE */
} rtr_intf_t;


typedef struct _vrtr_t {
    /* Internal Data Structure */
    struct _vrtr_t             *next;
    sai_object_id_t             oid;

    /* Read Only */
    /* Read Write */
    bool        enbl_admin_v4;
    bool        enbl_admin_v6;
    sai_mac_t   src_mac;
    sai_packet_action_t     act_ttl_one;
    sai_packet_action_t     act_ip_opt;     
} vrtr_t;


typedef struct _route_t {
    /* Internal Data Structure */
    struct _route_t             *next;
    sai_object_id_t             oid;

    /* Read Only */
    /* Read Write */
    sai_packet_action_t         act_fwd;
    uint8_t                     trap_pri;   //deafult 0
    sai_object_id_t             nexthop_oid;

} route_t;


typedef struct _qos_t {
    /* Internal Data Structure */
    struct _qos_t     *next;
    sai_object_id_t             oid;

    /* Read Only */
    /* Read Write */
    uint32_t                        num_cos_class;  //?
    sai_cos_port_trust_t            mode_trust;
    sai_cos_sched_t                 algo_sched;
    uint32_t                        weight_sched; //?
    uint32_t                        bw_limit;   //?
    uint32_t                        buf_limit;  //?

} qos_t;

typedef struct _next_hop_grp_t {
    /* Internal Data Structure */
    struct _next_hop_grp_t     *next;
    sai_object_id_t             oid;

    /* Read Only */
    uint32_t                        num_nexthop;

    /* Read Write */
    sai_next_hop_group_type_t       type;
    sai_object_list_t               next_hop_lst;

} next_hop_grp_t;


typedef struct _next_hop_t {
    /* Internal Data Structure */
    struct _next_hop_t     *next;
    sai_object_id_t             oid;

    /* Read Write */
    sai_next_hop_type_t         type;
    sai_ip_address_t            ip_addr_v4;
    sai_object_id_t             rtr_intf_oid;

} next_hop_t;

typedef struct _neighbor_t {
    /* Internal Data Structure */
    struct _neighbor_t     *next;
    sai_object_id_t             oid;

    /* Read Write */
    sai_mac_t               dst_mac;
    sai_packet_action_t     act_fwd;

} neighbor_t;

typedef struct _mirror_sess_t {
    /* Internal Data Structure */
    struct _mirror_sess_t     *next;
    sai_object_id_t             oid;

    /* Attribute */
    
    /* Read Only */
    /* Read Write */
    sai_mirror_type_t       type;
    sai_object_id_t         monitor_port_oid;
    uint8_t                 class_srv;
    uint16_t                vlan_tpid;
    sai_vlan_id_t           vlan_id;
    uint8_t                 vlan_pri;

    sai_erspan_encapsulation_type_t encap_type;
    uint8_t                 iphdr_ver;
    uint8_t                 tos;
    uint8_t                 ttl;
    sai_ip_address_t        src_ip_addr;
    sai_ip_address_t        dst_ip_addr;
    
    sai_mac_t               src_mac;
    sai_mac_t               dst_mac;

    uint16_t                gre_type;

} mirror_sess_t;


typedef struct _lag_t {
    /* Internal Data Structure */
    struct _lag_t     *next;
    sai_object_id_t             oid;

    /* Attribute */
    
    /* Read Only */
    /* Read Write */
    sai_object_list_t   portlst;

} lag_t;

typedef struct _host_intf_t {
    /* Internal Data Structure */
    struct _host_intf_t     *next;
    sai_object_id_t             oid;


    /* Attribute */
    
    /* Read Only */
    /* Read Write */
    sai_object_id_t assn_oid;
    char*   name;

    /*CUSTOM RANGE BASE */
} host_intf_t;


typedef struct _acl_table_t {
    /* Internal Data Structure */
    struct _acl_tbl_t   *next;
    sai_object_id_t             oid;

    /* Read Only */
    /* Read Write */
    sai_acl_stage_t     stage;
    sai_uint32_t        priority;           /*between SAI_SWITCH_ATTR_ACL_TABLE_MINIMUM_PRIORITY and
                                            SAI_SWITCH_ATTR_ACL_TABLE_MAXIMUM_PRIORITY, default
                                            SAI_SWITCH_ATTR_ACL_TABLE_MINIMUM_PRIORITY*/

    /* FIELD_START*/
    sai_ip6_t           fld_src_ipaddr6;    //default SA_ACT_TABLE_ATTR_FIELD_START
    sai_ip6_t           fld_dst_ipaddr6;

    sai_mac_t           fld_src_mac;
    sai_mac_t           fld_dst_mac;

    sai_ip4_t           fld_src_ipaddr4;
    sai_ip4_t           fld_dst_ipaddr4;

    sai_object_list_t   fld_iportlst;
    sai_object_list_t   fld_oportlst;

    sai_object_id_t     fld_iport_oid;
    sai_object_id_t     fld_oport_oid;

    sai_uint16_t        fld_ovlan_id:12;
    sai_uint16_t        fld_ovlan_pri:3;
    sai_uint16_t        fld_ovlan_cfi:1;

    sai_uint16_t        fld_ivlan_id:12;
    sai_uint16_t        fld_ivlan_pri:3;
    sai_uint16_t        fld_ivlan_cfi:1;
    
    sai_uint16_t        fld_l4_src_port;
    sai_uint16_t        fld_l4_dst_port;

    sai_uint16_t        fld_eth_type;
    sai_uint8_t         fld_ip_prot;

    sai_uint8_t         fld_dscp:6;
    sai_uint8_t         fld_ecn:2;

    sai_uint8_t         fld_ttl;
    sai_uint8_t         fld_tos;

    sai_uint8_t         fld_ip_flags:3;
    sai_uint8_t         fld_tcp_flags:6;

    sai_acl_ip_type_t   fld_ip_type;
    sai_acl_ip_frag_t   fld_ip_frag;
    sai_uint32_t        fld_ipv6_flow_lbl:20;

    sai_cos_t           fld_tc;
} acl_table_t;


typedef struct _acl_entry_t {
    /* Internal Data Structure */
    struct _acl_entry_t *next;
    sai_object_id_t             oid;

    /* READ ONLY */
    
    sai_object_id_t     tbl_oid;
    sai_uint32_t        priority;   /*between SAI_SWITCH_ATTR_ACL_ENTRY_MINIMUM_PRIORITY and
                                     SAI_SWITCH_ATTR_ACL_ENTRY_MAXIMUM_PRIORITY, default
                                     SAI_SWITCH_ATTR_ACL_ENTRY_MINIMUM_PRIORITY*/
    bool                admin_state;    /*default false */

    /* Field Attr */
    sai_ip6_t           fld_src_ipv6;       
    sai_ip6_t           fld_dst_ipv6;
    
    sai_mac_t           fld_src_mac;
    sai_mac_t           fld_dst_mac;

    sai_ip4_t           fld_src_ipv4;
    sai_ip4_t           fld_dst_ipv4;

    sai_object_list_t   fld_iportlst;
    sai_object_list_t   fld_oportlst;

    sai_object_id_t     fld_iport_oid;
    sai_object_id_t     fld_oport_oid;

    sai_uint16_t        fld_ovlan_id:12;
    sai_uint16_t        fld_ovlan_pri:3;
    sai_uint16_t        fld_ovlan_cfi:1;

    sai_uint16_t        fld_ivlan_id:12;
    sai_uint16_t        fld_ivlan_pri:3;
    sai_uint16_t        fld_ivlan_cfi:1;

    sai_uint16_t        fld_l4_src_port;
    sai_uint16_t        fld_l4_dst_port;

    sai_uint16_t        fld_eth_type;
    sai_uint8_t         fld_ip_prot;

    sai_uint8_t         fld_dscp:6;
    sai_uint8_t         fld_ecn:2;

    sai_uint8_t         fld_ttl;
    sai_uint8_t         fld_tos;

    sai_uint8_t         fld_ip_flags:3;
    sai_uint8_t         fld_tcp_flags:6;

    sai_acl_ip_type_t   fld_ip_type;
    sai_acl_ip_frag_t   fld_ip_frag;
    sai_uint32_t        fld_ipv6_flow_lbl:20;

    sai_cos_t           fld_tc;

    /* rule Action Attr */
    sai_acl_action_data_t   acn_act_fwd;
    sai_object_id_t         acn_rdrct_dst_oid;

    sai_packet_action_t     acn_act_pkt;
    bool                    acn_enbl_flood;
    sai_object_id_t         acn_counter_oid;

    sai_object_id_t         acn_ig_mirss_oid;
    sai_object_id_t         acn_eg_mirss_oid;

    sai_object_id_t         acn_policy_oid;
    bool                    acn_en_dec_ttl;
    sai_cos_t               acn_tc;

    sai_uint16_t            acn_ivlan_id:16;
    sai_uint8_t             acn_ivlan_pri:3;

    sai_uint16_t            acn_ovlan_id:16;
    sai_uint8_t             acn_ovlan_pri:3;

    sai_mac_t               acn_src_mac;
    sai_mac_t               acn_dst_mac;

    sai_ip4_t               acn_src_ipv4;
    sai_ip4_t               acn_dst_ipv4;

    sai_ip6_t               acn_src_ipv6;
    sai_ip6_t               acn_dst_ipv6;

    sai_uint8_t             acn_dscp:6;

    sai_uint16_t            acn_l4_src_port;
    sai_uint16_t            acn_l4_dst_port;

    sai_object_id_t         acn_ig_smpktss_oid;
    sai_object_id_t         acn_eg_smpktss_oid;

} acl_entry_t;

typedef struct _acl_counter_t {
    /* Internal Data Structure */
    struct _acl_counter_t *next;
    sai_object_id_t             oid;

    //Read Only
    sai_object_id_t         tbl_oid;
    bool                    enbl_pkt_count;
    bool                    enbl_byte_count;

    uint64_t                pkt_cnt;
    uint64_t                byte_cnt;
} acl_counter_t;


typedef struct _fdb_entry_t {
    /* Internal Data Structure */
    struct _fdb_entry_t *next;
    sai_object_id_t             oid;

    /* Attributes */
    /* Read Only */
    sai_fdb_entry_type_t    type;
    sai_object_id_t         port_oid;
    sai_packet_action_t     act_pkt;

} fdb_entry_t;


typedef struct _port_t {
    /* Internal Data Structure */
    struct _port_t  *next;
    sai_object_id_t oid;

    /* Attributes */
    /* Read Only */
    sai_port_type_t type;
    sai_port_oper_status_t state_port;
    sai_u32_list_t hw_lane_lst;

    sai_u32_list_t sptd_brkout_mode_lst;
    sai_port_breakout_mode_type_t mode_curr_brkout;

    /* Read Write */
    uint32_t speed;
    bool enbl_admin_mode;                 //default false
    sai_port_media_type_t type_media;       //default SAI_PORT_MEDIA_TYPE_NOT_PRESENT

    sai_vlan_id_t   default_vlan_id;
    uint8_t default_vlan_pri;               //default 0
    
    bool  enbl_ingress_filtering;         //default false
    bool  enbl_drop_untagged;             //default false
    bool  enbl_drop_tagged;               //default false

    sai_port_internal_loopback_mode_t mode_int_lpbk; //default SAI_PORT_INTERNAL_LOOPBACK_NONE
    sai_port_fdb_learning_mode_t mode_fdb_learn;  //deafult SAI_PORT_LEARN_MODE_HW

    bool enbl_update_dscp;                //default false
    uint32_t mtu;                           //default 1514

    bool enbl_flood_storm_cntl;           //default false
    bool enbl_bcast_storm_cntl;           //default false
    bool enbl_mcast_storm_cntl;           //default false

    sai_port_flow_control_mode_t mode_globle_flow_cntl;    //dafult SAI_PORT_FLOW_CONTROL_DISABLE
    
    uint32_t num_max_learned_addr;

    sai_packet_action_t act_fdb_learn_limit;    //default SAI_PACKET_ACTION_DROP
    sai_object_list_t   ingress_mir_sess_lst;
    sai_object_list_t   egress_mir_sess_lst;

    sai_object_id_t ingress_smpl_pkt_oid;        //when disabled  SAI_NULL_OBJECT_ID
    sai_object_id_t egress_smpl_pkt_oid;         //when disabled  SAI_NULL_OBJECT_ID

} port_t;


typedef struct _switch_t {
    /* Internal Data Structure */
    port_t      *port_ll;
    vrtr_t      *vrtr_ll;

    /* Attributes */
    /* Read Only */
    uint32_t num_max_port;
    sai_object_list_t portlst;
    sai_object_id_t cpu_port_oid;
    uint32_t num_max_vrtr;
    uint32_t size_fdb_tbl;
    bool enbl_link_route;
    sai_switch_oper_status_t state_oper;
    int32_t max_temp;
    sai_uint32_t min_pri_acl_tbl;
    sai_uint32_t max_pri_acl_tbl;
    sai_uint32_t min_pri_acl_ent;
    sai_uint32_t max_pri_acl_ent;
    sai_object_id_t default_stp_inst_oid;

    
    /* Read Write */
    sai_switch_switching_mode_t mode_switch; //default SAI_SWITCHING_MODE_STORE_AND_FORWARD

    bool enbl_bcast_cpu_flood;
    bool enbl_mcast_cpu_flood;
    //sai_packet_action_t act_ttl_one;
    sai_vlan_id_t default_port_vlan_id;          //default 1
    sai_mac_t default_mac;
    uint32_t num_max_learned_addr;          //default 0
    uint32_t time_aging_fdb;                //default 0

    sai_packet_action_t act_fdb_ucast_miss; //default SAI_PACKET_ACTION_FORWARD
    sai_packet_action_t act_fdb_bcast_miss; //default SAI_PACKET_ACTION_FORWARD
    sai_packet_action_t act_fdb_mcast_miss; //default SAI_PACKET_ACTION_FORWARD

    sai_switch_hash_algo_t algo_lag_hash;   //default SAI_HASH_CRC
    sai_switch_hash_seed_t seed_lag_hash;
    sai_s32_list_t fields_lag_hash;         //default all fields enbld

    sai_switch_hash_algo_t algo_ecmp_hash;  //default SAI_HASH_CRC
    sai_switch_hash_seed_t seed_ecmp_hash;
    sai_s32_list_t fields_ecmp_hash;        //default all fields enbld

    uint32_t num_max_path_ecmp;             //default 64

    /* Write Only */
    sai_port_breakout_t mode_port_brkout;
    uint64_t    custom_range_base;

} switch_t;

switch_t dummy_switch;

#endif //__DUMMY_H_

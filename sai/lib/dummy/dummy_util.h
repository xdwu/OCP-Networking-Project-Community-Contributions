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
#ifndef __DUMMY_UTIL_H_
#define __DUMMY_UTIL_H_

#include "dummy.h"
#include "dummy_internal.h"

bool init_objid_pool();
bool acquire_oid(sai_object_id_t *oid);
bool release_oid(sai_object_id_t oid);    

void print_mac(sai_mac_t mac_addr);
void print_action_pkt(sai_packet_action_t act);

void print_port_type(sai_port_type_t type);
void print_port_state(sai_port_oper_status_t state);
void print_port_media_type(sai_port_media_type_t type);
void print_port_lpbk_cntl(sai_port_internal_loopback_mode_t mode);
void print_port_fdb_lrn_mode(sai_port_fdb_learning_mode_t mode);
void print_port_flow_cntl_mode(sai_port_flow_control_mode_t mode);
void print_port_brkout_mode(sai_port_breakout_mode_type_t mode);

void print_switch_state(sai_switch_oper_status_t state);
void print_switch_sw_mode(sai_switch_switching_mode_t mode);
void print_switch_hash_algo(sai_switch_hash_algo_t algo);

void print_acl_type(sai_acl_ip_type_t type);

void print_olst(sai_object_list_t lst);

void mac_copy(sai_mac_t mac1, const sai_mac_t mac2);

#endif //__DUMMY_UTIL_H_

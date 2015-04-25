#ifndef __DUMMY_RND_H_
#define __DUMMY_RND_H_

#include "dummy.h"
#include "dummy_internal.h"

bool init_objid_pool();
bool acquire_id(uint64_t *id);
bool release_id(uint64_t id);    

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


#endif //__DUMMY_RND_H_

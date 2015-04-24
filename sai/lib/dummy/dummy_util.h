#ifndef __DUMMY_RND_H_
#define __DUMMY_RND_H_

#include "dummy.h"
#include "dummy_internal.h"

bool init_objid_pool();
bool acquire_id(uint64_t *id);
bool release_id(uint64_t id);    

void print_mac(sai_mac_t mac_addr);
void print_action_pkt(sai_packet_action_t act);

#endif //__DUMMY_RND_H_

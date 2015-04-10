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
#ifndef __DUMMY_TEST_H_
#define __DUMMY_TEST_H_

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>

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
sai_host_interface_api_t* sai_hif_api;
sai_mirror_api_t* sai_mirror_api;
sai_samplepacket_api_t* sai_smpl_pkt_api;
sai_stp_api_t* sai_stp_api;
sai_lag_api_t* sai_lag_api;

bool InitializeL3(void);

#endif  //__DUMMY_TEST_H_

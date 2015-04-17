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
#include "test.h"
#include "../../lib/dummy/dummy_switch.h"
#include "../../lib/dummy/dummy_port.h"
#include "../../lib/dummy/dummy_fdb.h"
#include "../../lib/dummy/dummy_vlan.h"
#include "../../lib/dummy/dummy_vrtr.h"
#include "../../lib/dummy/dummy_route.h"
#include "../../lib/dummy/dummy_nexthop.h"
#include "../../lib/dummy/dummy_nexthop_grp.h"
#include "../../lib/dummy/dummy_rtr_intf.h"
#include "../../lib/dummy/dummy_nbr.h"
#include "../../lib/dummy/dummy_qos.h"
#include "../../lib/dummy/dummy_acl.h"
#include "../../lib/dummy/dummy_host_intf.h"
#include "../../lib/dummy/dummy_mirror_sess.h"
#include "../../lib/dummy/dummy_smpl_pkt_sess.h"
#include "../../lib/dummy/dummy_stp.h"
#include "../../lib/dummy/dummy_lag.h"
#include "../../lib/dummy/dummy_init.h"

int main(int argc, char **argv)
{
    sai_status_t rt;
    
    printf("*******************\n");
    printf("Dummy Test Suite\n");
    printf("*******************\n");
    rt = sai_api_initialize(0, &dummy_service_method_table);

    if (rt != SAI_STATUS_SUCCESS) {
        printf("FAILURE sai_api_initialize\n");
        return rt;
    }

    printf("\n*** QUERY SAI API ***\n");

    rt = sai_api_query(SAI_API_SWITCH, (void**)&sai_switch_api);
    if (rt != SAI_STATUS_SUCCESS || sai_switch_api == NULL) {
        printf("Fail to Query SAI_API_SWITCH\n");
        return 1;
    }

    sai_api_query(SAI_API_PORT, (void**)&sai_port_api);
    if (rt != SAI_STATUS_SUCCESS || sai_port_api == NULL) {
        printf("Fail to Query SAI_API_PORT\n");
        return 1;
    }

    sai_api_query(SAI_API_FDB, (void**)&sai_fdb_api);
    if (rt != SAI_STATUS_SUCCESS || sai_fdb_api == NULL) {
        printf("Fail to Query SAI_API_FDB\n");
        return 1;
    }

    sai_api_query(SAI_API_VLAN, (void**)&sai_vlan_api);
    if (rt != SAI_STATUS_SUCCESS || sai_vlan_api == NULL) {
        printf("Fail to Query SAI_API_VLAN\n");
        return 1;
    }

    sai_api_query(SAI_API_VIRTUAL_ROUTER, (void**)&sai_vr_api);
    if (rt != SAI_STATUS_SUCCESS || sai_vr_api == NULL) {
        printf("Fail to Query SAI_API_VIRTUAL_ROUTER\n");
        return 1;
    }

    sai_api_query(SAI_API_ROUTE, (void**)&sai_route_api);
    if (rt != SAI_STATUS_SUCCESS || sai_route_api == NULL) {
        printf("Fail to Query SAI_API_ROUTE\n");
        return 1;
    }

    sai_api_query(SAI_API_NEXT_HOP, (void**)&sai_next_hop_api);
    if (rt != SAI_STATUS_SUCCESS || sai_next_hop_api == NULL) {
        printf("Fail to Query SAI_API_NEXT_HOP\n");
        return 1;
    }

    sai_api_query(SAI_API_NEXT_HOP_GROUP, (void**)&sai_next_hop_group_api);
    if (rt != SAI_STATUS_SUCCESS || sai_next_hop_group_api == NULL) {
        printf("Fail to Query SAI_API_NEXT_HOP_GROUP\n");
        return 1;
    }

    sai_api_query(SAI_API_ROUTER_INTERFACE, (void**)&sai_rif_api);
    if (rt != SAI_STATUS_SUCCESS || sai_rif_api == NULL) {
        printf("Fail to Query SAI_API_ROUTER_INTERFACE\n");
        return 1;
    }

    sai_api_query(SAI_API_NEIGHBOR, (void**)&sai_neighbor_api);
    if (rt != SAI_STATUS_SUCCESS || sai_neighbor_api == NULL) {
        printf("Fail to Query SAI_API_NEIGHBOR\n");
        return 1;
    }

    sai_api_query(SAI_API_QOS, (void**)&sai_qos_api);
    if (rt != SAI_STATUS_SUCCESS || sai_qos_api == NULL) {
        printf("Fail to Query SAI_API_QOS\n");
        return 1;
    }

    sai_api_query(SAI_API_ACL, (void**)&sai_acl_api);
    if (rt != SAI_STATUS_SUCCESS || sai_acl_api == NULL) {
        printf("Fail to Query SAI_API_ACL\n");
        return 1;
    }

    sai_api_query(SAI_API_HOST_INTERFACE, (void**)&sai_hif_api);
    if (rt != SAI_STATUS_SUCCESS || sai_hif_api == NULL) {
        printf("Fail to Query SAI_API_HOST_INTERFACE\n");
        return 1;
    }

    sai_api_query(SAI_API_MIRROR, (void**)&sai_mirror_api);
    if (rt != SAI_STATUS_SUCCESS || sai_mirror_api == NULL) {
        printf("Fail to Query SAI_API_MIRROR\n");
        return 1;
    }

    sai_api_query(SAI_API_SAMPLEPACKET, (void**)&sai_smpl_pkt_api);
    if (rt != SAI_STATUS_SUCCESS || sai_smpl_pkt_api == NULL) {
        printf("Fail to Query SAI_API_SAMPLEPACKET\n");
        return 1;
    }

    sai_api_query(SAI_API_STP, (void**)&sai_stp_api);
    if (rt != SAI_STATUS_SUCCESS || sai_stp_api == NULL) {
        printf("Fail to Query SAI_API_STP\n");
        return 1;
    }

    sai_api_query(SAI_API_LAG, (void**)&sai_lag_api);
    if (rt != SAI_STATUS_SUCCESS || sai_lag_api == NULL) {
        printf("Fail to Query SAI_API_LAG\n");
        return 1;
    }


    printf("\n*** SET LOG LEVEL ***\n");

    sai_log_set(SAI_API_SWITCH, SAI_LOG_DEBUG);
    sai_log_set(SAI_API_PORT, SAI_LOG_INFO);
    sai_log_set(SAI_API_FDB, SAI_LOG_WARN);
    sai_log_set(SAI_API_VLAN, SAI_LOG_ERROR);
    sai_log_set(SAI_API_VIRTUAL_ROUTER, SAI_LOG_CRITICAL);

    sai_log_set(SAI_API_ROUTE, SAI_LOG_DEBUG);
    sai_log_set(SAI_API_NEXT_HOP, SAI_LOG_INFO);
    sai_log_set(SAI_API_NEXT_HOP_GROUP, SAI_LOG_WARN);
    sai_log_set(SAI_API_ROUTER_INTERFACE, SAI_LOG_ERROR);
    sai_log_set(SAI_API_NEIGHBOR, SAI_LOG_CRITICAL);

    sai_log_set(SAI_API_QOS, SAI_LOG_DEBUG);
    sai_log_set(SAI_API_ACL, SAI_LOG_INFO);
    sai_log_set(SAI_API_HOST_INTERFACE, SAI_LOG_WARN);
    sai_log_set(SAI_API_MIRROR, SAI_LOG_ERROR);
    sai_log_set(SAI_API_SAMPLEPACKET, SAI_LOG_CRITICAL);


    sai_log_set(SAI_API_STP, SAI_LOG_DEBUG);
    sai_log_set(SAI_API_LAG, SAI_LOG_INFO);


    printf("\n");

    sai_status_t status = 
        sai_switch_api->initialize_switch(0, "0xb850", "",
                                        &dummy_switch_notification_handlers);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Fail to sai_initialize_switch %x\n", status);
        return 1;
    }

    sai_attribute_t attr;
    attr.id = SAI_SWITCH_ATTR_SRC_MAC_ADDRESS;
    status = sai_switch_api->get_switch_attribute(1, &attr);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Fail to get SAI_SWITCH_ATTR_SRC_MAC_ADDRESS for the switch %x\n", status);
        return 1;
    }

    status = sai_switch_api->set_switch_attribute(&attr);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Fail to set SAI_SWITCH_ATTR_SRC_MAC_ADDRESS for the switch %x\n", status);
        return 1;
    }

    status = 
        sai_switch_api->connect_switch(0, "127,0.0.1", 
                                        &dummy_switch_notification_handlers);
    if (status != SAI_STATUS_SUCCESS) {
        printf("Fail to sai_connect_switch %x\n", status);
        return 1;
    }


    printf("\n*** INITIALIZE L3 ***\n");
    if(!InitializeL3()) {
        printf("Fail to initialize L3\n");
        return 1;
    }

    printf("*******************\n");
    printf("End of Dummy Test\n");
    printf("*******************\n");
    return 0;
}


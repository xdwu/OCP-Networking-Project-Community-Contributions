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
#include <limits.h>
#include "gtest/gtest.h"

extern "C" {
#include "dummy.h"
#include "dummy_internal.h"
}


/*--------------------------------------------------------*/
class dummyUnitTest : public ::testing::Test
{
    public:
        bool initialize_L3(void);
        bool dummy_switch_max_port_get(uint32_t *max_port);
        bool dummy_port_type_is_logical(sai_object_id_t port_id);
        bool dummy_port_speed_set_get(sai_object_id_t port_id, uint32_t speed);
        bool dummy_internal_loopback_set_get(sai_object_id_t port_id,
                sai_port_internal_loopback_mode_t lpbk_mode);

    protected:
        static void SetUpDummySwitch(void)
        {
            //query API methods of all types
            EXPECT_EQ(SAI_STATUS_SUCCESS, 
                sai_api_query(SAI_API_SWITCH, (void**)&sai_switch_api));
            EXPECT_TRUE(sai_switch_api != NULL);

            EXPECT_EQ(SAI_STATUS_SUCCESS,
                sai_api_query(SAI_API_PORT, (void**)&sai_port_api));
            EXPECT_TRUE(sai_port_api != NULL);

            EXPECT_EQ(SAI_STATUS_SUCCESS, 
                sai_api_query(SAI_API_FDB, (void**)&sai_fdb_api));
            EXPECT_TRUE(sai_fdb_api != NULL);

            EXPECT_EQ(SAI_STATUS_SUCCESS, 
               sai_api_query(SAI_API_VLAN, (void**)&sai_vlan_api));
            EXPECT_TRUE(sai_vlan_api != NULL);

            EXPECT_EQ(SAI_STATUS_SUCCESS,
               sai_api_query(SAI_API_VIRTUAL_ROUTER, (void**)&sai_vr_api));
            EXPECT_TRUE(sai_vr_api != NULL);

            EXPECT_EQ(SAI_STATUS_SUCCESS,
               sai_api_query(SAI_API_ROUTE, (void**)&sai_route_api));
            EXPECT_TRUE(sai_route_api != NULL);

            EXPECT_EQ(SAI_STATUS_SUCCESS,
               sai_api_query(SAI_API_NEXT_HOP, (void**)&sai_next_hop_api));
            EXPECT_TRUE(sai_next_hop_api != NULL);

            EXPECT_EQ(SAI_STATUS_SUCCESS,
               sai_api_query(SAI_API_NEXT_HOP_GROUP, 
               (void**)&sai_next_hop_group_api));
            EXPECT_TRUE(sai_next_hop_group_api != NULL);

            EXPECT_EQ(SAI_STATUS_SUCCESS,
               sai_api_query(SAI_API_ROUTER_INTERFACE, (void**)&sai_rif_api));
            EXPECT_TRUE(sai_rif_api != NULL);

            EXPECT_EQ(SAI_STATUS_SUCCESS, 
               sai_api_query(SAI_API_NEIGHBOR, (void**)&sai_neighbor_api));
            EXPECT_TRUE(sai_neighbor_api != NULL);

            EXPECT_EQ(SAI_STATUS_SUCCESS,
               sai_api_query(SAI_API_QOS, (void**)&sai_qos_api));
            EXPECT_TRUE(sai_qos_api != NULL);

            EXPECT_EQ(SAI_STATUS_SUCCESS,
               sai_api_query(SAI_API_ACL, (void**)&sai_acl_api));
            EXPECT_TRUE(sai_acl_api != NULL);

            EXPECT_EQ(SAI_STATUS_SUCCESS,
               sai_api_query(SAI_API_HOST_INTERFACE, (void**)&sai_hif_api));
            EXPECT_TRUE(sai_hif_api != NULL);

            EXPECT_EQ(SAI_STATUS_SUCCESS,
               sai_api_query(SAI_API_MIRROR, (void**)&sai_mirror_api));
            EXPECT_TRUE(sai_mirror_api != NULL);

            EXPECT_EQ(SAI_STATUS_SUCCESS,
               sai_api_query(SAI_API_SAMPLEPACKET, (void**)&sai_smpl_pkt_api));
            EXPECT_TRUE(sai_smpl_pkt_api != NULL);

            EXPECT_EQ(SAI_STATUS_SUCCESS,
               sai_api_query(SAI_API_STP, (void**)&sai_stp_api));
            EXPECT_TRUE(sai_stp_api != NULL);

            EXPECT_EQ(SAI_STATUS_SUCCESS,
               sai_api_query(SAI_API_LAG, (void**)&sai_lag_api));
            EXPECT_TRUE(sai_lag_api != NULL);


            //set log
            EXPECT_EQ(SAI_STATUS_SUCCESS,
                sai_log_set(SAI_API_SWITCH, SAI_LOG_DEBUG));

            EXPECT_EQ(SAI_STATUS_SUCCESS,
                sai_log_set(SAI_API_PORT, SAI_LOG_INFO));

            EXPECT_EQ(SAI_STATUS_SUCCESS,
                sai_log_set(SAI_API_FDB, SAI_LOG_WARN));

            EXPECT_EQ(SAI_STATUS_SUCCESS,
                sai_log_set(SAI_API_VLAN, SAI_LOG_ERROR));

            EXPECT_EQ(SAI_STATUS_SUCCESS,
                sai_log_set(SAI_API_VIRTUAL_ROUTER, SAI_LOG_CRITICAL));

            EXPECT_EQ(SAI_STATUS_SUCCESS,
                sai_log_set(SAI_API_ROUTE, SAI_LOG_DEBUG));

            EXPECT_EQ(SAI_STATUS_SUCCESS,
                sai_log_set(SAI_API_NEXT_HOP, SAI_LOG_INFO));

            EXPECT_EQ(SAI_STATUS_SUCCESS,
                sai_log_set(SAI_API_NEXT_HOP_GROUP, SAI_LOG_WARN));

            EXPECT_EQ(SAI_STATUS_SUCCESS,
                sai_log_set(SAI_API_ROUTER_INTERFACE, SAI_LOG_ERROR));

            EXPECT_EQ(SAI_STATUS_SUCCESS,
                sai_log_set(SAI_API_NEIGHBOR, SAI_LOG_CRITICAL));

            EXPECT_EQ(SAI_STATUS_SUCCESS,
                sai_log_set(SAI_API_QOS, SAI_LOG_DEBUG));

            EXPECT_EQ(SAI_STATUS_SUCCESS,
                sai_log_set(SAI_API_ACL, SAI_LOG_INFO));

            EXPECT_EQ(SAI_STATUS_SUCCESS,
                sai_log_set(SAI_API_HOST_INTERFACE, SAI_LOG_WARN));

            EXPECT_EQ(SAI_STATUS_SUCCESS,
                sai_log_set(SAI_API_MIRROR, SAI_LOG_ERROR));

            EXPECT_EQ(SAI_STATUS_SUCCESS,
                sai_log_set(SAI_API_SAMPLEPACKET, SAI_LOG_CRITICAL));

            EXPECT_EQ(SAI_STATUS_SUCCESS,
                sai_log_set(SAI_API_STP, SAI_LOG_DEBUG));

            EXPECT_EQ(SAI_STATUS_SUCCESS,
                sai_log_set(SAI_API_LAG, SAI_LOG_INFO));
                
            //initialize switch
            ASSERT_TRUE(sai_switch_api->initialize_switch != NULL);
            EXPECT_EQ(SAI_STATUS_SUCCESS,
                sai_switch_api->initialize_switch(0, "0xb850", "",
                    &dummy_switch_notification_handlers));

            sai_attribute_t attr;
            attr.id = SAI_SWITCH_ATTR_SRC_MAC_ADDRESS;

            EXPECT_TRUE(sai_switch_api->get_switch_attribute != NULL);
            EXPECT_EQ(SAI_STATUS_SUCCESS,
                sai_switch_api->get_switch_attribute(1, &attr));


            EXPECT_TRUE(sai_switch_api->set_switch_attribute != NULL);
            EXPECT_EQ(SAI_STATUS_SUCCESS,
                sai_switch_api->set_switch_attribute(&attr));

            ASSERT_TRUE(sai_switch_api->connect_switch != NULL);
            EXPECT_EQ(SAI_STATUS_SUCCESS,
                sai_switch_api->connect_switch(0, "127,0.0.1",
                    &dummy_switch_notification_handlers));


        }

};

bool dummyUnitTest::initialize_L3(void)
{
    sai_attribute_t attr;
    sai_object_id_t g_vr_id;

    attr.id = SAI_SWITCH_ATTR_CPU_PORT;

    EXPECT_TRUE(sai_switch_api->get_switch_attribute != NULL);
    EXPECT_EQ(SAI_STATUS_SUCCESS,
        sai_switch_api->get_switch_attribute(1, &attr));


    EXPECT_TRUE(sai_vr_api->create_virtual_router != NULL);
    EXPECT_EQ(SAI_STATUS_SUCCESS,
        sai_vr_api->create_virtual_router(&g_vr_id, 0, NULL));

   return true;
}

bool dummyUnitTest::dummy_switch_max_port_get(uint32_t *max_port)
{
    sai_attribute_t attr;
    memset(&attr, 0, sizeof(sai_attribute_t));
    attr.id = SAI_SWITCH_ATTR_PORT_NUMBER;

    if (sai_switch_api->get_switch_attribute(1, &attr) != SAI_STATUS_SUCCESS) {
        return false;
    }

    *max_port = attr.value.u32;

    return true;

}


bool dummyUnitTest::dummy_port_type_is_logical(sai_object_id_t port_id)
{
    sai_attribute_t attr;

    memset(&attr, 0, sizeof(sai_attribute_t));
    attr.id = SAI_PORT_ATTR_TYPE;

    if (sai_port_api->get_port_attribute(port_id, 1, &attr) != SAI_STATUS_SUCCESS) {
        return false;
    }

    return true;
}

bool dummyUnitTest::dummy_port_speed_set_get(sai_object_id_t port_id, uint32_t speed)
{
    sai_attribute_t attr_set, attr_get;

    memset(&attr_set, 0, sizeof(sai_attribute_t));
    memset(&attr_get, 0, sizeof(sai_attribute_t));
    
    attr_set.id = SAI_PORT_ATTR_SPEED;
    attr_set.value.u32 = speed;

    if(sai_port_api->set_port_attribute(port_id, &attr_set) != SAI_STATUS_SUCCESS) {
        return false;
    }

    attr_get.id = SAI_PORT_ATTR_SPEED;

    if(sai_port_api->get_port_attribute(port_id, 1, &attr_get) != SAI_STATUS_SUCCESS) {
        return false;
    }

    if (speed != attr_get.value.u32) {
        return false;
    }

    return true;
}

bool dummyUnitTest::dummy_internal_loopback_set_get(sai_object_id_t port_id,
                sai_port_internal_loopback_mode_t lpbk_mode)
{
    sai_attribute_t attr_set, attr_get;

    memset(&attr_set, 0, sizeof(sai_attribute_t));
    memset(&attr_get, 0, sizeof(sai_attribute_t));
    
    attr_set.id = SAI_PORT_ATTR_INTERNAL_LOOPBACK;
    attr_set.value.u32 = lpbk_mode;

    if(sai_port_api->set_port_attribute(port_id, &attr_set) != SAI_STATUS_SUCCESS) {
        return false;
    }

    attr_get.id = SAI_PORT_ATTR_INTERNAL_LOOPBACK;

    if(sai_port_api->get_port_attribute(port_id, 1, &attr_get) != SAI_STATUS_SUCCESS) {
        return false;
    }

    if (lpbk_mode != attr_get.value.u32) {
        return false;
    }

    return true;
}




/*--------------------------------------------------------*/

TEST_F(dummyUnitTest, type_get)
{
    uint32_t max_port = 0;
    sai_object_id_t port_id = 0;
    sai_attribute_t attr;

    memset(&attr, 0, sizeof(sai_attribute_t));
    attr.id = SAI_PORT_ATTR_TYPE;

    ASSERT_TRUE(dummy_switch_max_port_get(&max_port));

    for(port_id = 0; port_id <= max_port; port_id) {
        EXPECT_TRUE(dummy_port_type_is_logical(port_id));
    }
}


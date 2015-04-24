#include "dummy_util.h"

#define POOL_SIZE   100

/*
uint64_t objid_arr[POOL_SIZE];
int     OBJ_RANGE;
OBJ_RANGE = POOL_SIZE;
*/

bool init_objid_pool()
{
    /*
    int i;
    for(i=0; i<OBJ_SIZE; i++) {
        //To Do
        //Make sure the new number is not dupilcated
        objid_arr[i] = rand();   
    }
    */
    return true;
}

bool acquire_id(uint64_t *id)
{
    printf("%s\n", __FUNCTION__);
    /*
    int index, last;

    if (OBJ_RANGE<1) {
        return false;
    }

    last = OBJ_RANGE -1;

    index = rand()%(last);
    
    *id = objid_arr[index];

    tmp = objid_arr[last];
    objid_arr[last] = objid_arr[index];
    objid_arr[index] = tmp;

    
    OBJ_RANGE --;
    */

    *id = rand();
    return true;
}

bool release_id(uint64_t id) 
{
    printf("%s\n", __FUNCTION__);

    return true;
}


void print_mac(sai_mac_t mac_addr)
{
    printf("0x%02x%02x %02x%02x %02x%02x \n",
        mac_addr[0],
        mac_addr[1],
        mac_addr[2],
        mac_addr[3],
        mac_addr[4],
        mac_addr[5]);
}


void print_action_pkt(sai_packet_action_t act)
{
    printf(" %s\n",
        (act == 0)? "DROP":
        (act == 1)? "FORWARD":
        (act == 2)? "TRAP":
        (act == 3)? "LOG":"??");
}

void print_port_type(sai_port_type_t type)
{
    printf(" %s \n",
        (type==0)? "LOGICAL":
        (type==1)? "CPU":
        (type==2)? "LAG":"??");
}

void print_port_state(sai_port_oper_status_t state_port)
{
    printf(" %s \n",
        (state_port==0)?"UNKNOWN":
        (state_port==1)?"UP":
        (state_port==2)?"DOWN":
        (state_port==3)?"TESTING":
        (state_port==4)?"NOT_PRESENT":"??");
}

void print_port_media_type(sai_port_media_type_t type)
{
    printf(" %s \n",
        (type==0)?"NOT_PRESENT":
        (type==1)?"UNKNOWN":
        (type==2)?"QSPF_FIBER":
        (type==3)?"QSPF_COPPER":
        (type==4)?"SPF_FIBER":
        (type==5)?"SPF_COPPER":"??");
}

void print_port_lpbk_cntl(sai_port_internal_loopback_mode_t mode)
{
    printf(" %s \n",
        (mode==0)?"LOOPBACK_NONE":
        (mode==1)?"LOOPBACK_PHY":
        (mode==2)?"LOOPBACK_MAC":"??");
}

void print_port_fdb_lrn_mode(sai_port_fdb_learning_mode_t mode)
{
    printf(" %s \n",
        (mode==0)?"DROP":
        (mode==1)?"DISABLE":
        (mode==2)?"HW":
        (mode==3)?"CPU":"??");

}

void print_port_flow_cntl_mode(sai_port_flow_control_mode_t mode)
{
    printf(" %s \n",
        (mode==0)?"DISABLE":
        (mode==1)?"TX_ONLY":
        (mode==2)?"RX_ONLY":
        (mode==3)?"BOTH_ENABLE":"??");

}

void print_port_brkout_mode(sai_port_breakout_mode_type_t mode)
{
    printf(" %s \n",
        (mode==1)? "1 LANE":
        (mode==2)? "2 LANE":
        (mode==4)? "4 LANE":"??");
}

void print_switch_state(sai_switch_oper_status_t state)
{
    printf(" %s \n",
        (state==0)?"UNKNOWN":
        (state==1)?"UP":
        (state==2)?"DOWN":
        (state==3)?"FAILED":"??");
}

void print_switch_sw_mode(sai_switch_switching_mode_t mode)
{
    printf(" %s \n",
        (mode==0)? "CUT_THROUGH":
        (mode==1)? "STORE_AND_FORWARD":"??");
}

void print_switch_hash_algo(sai_switch_hash_algo_t algo)
{
    printf(" %s \n",
        (algo==1)? "XOR":
        (algo==2)? "CRC":
        (algo==1)? "RANDOM":"??");
    
}

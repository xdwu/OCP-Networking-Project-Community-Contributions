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

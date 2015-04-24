#include "dummy_rnd.h"

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


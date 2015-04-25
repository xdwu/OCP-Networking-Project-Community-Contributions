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

#include "dummy.h"
#include "dummy_internal.h"

int main(int argc, char** argv)
{
    printf("%s\n", __FUNCTION__);

    printf("======== TEST Linked List ==================\n");
    
    node_t **listpp, *p;

    listpp = (node_t**) malloc(sizeof(node_t*));

    if(listpp == NULL) {
        printf("Failure of malloc\n");
        return 1;
    }
    
    *listpp = NULL;

    printf("\t------ Basic Test for Genaric Node -----\n");
    printf("\t---empty list--- \n");
    ll_show(*listpp);
/*-----------------------------------*/
    printf("\t---list with a single node---\n");
    node_t *n1 = NULL;

    if (!ll_new_node(&n1)) {
        printf("Failure of create a new node\n");
        return 1;
    }

    ll_show_node(n1);

    ll_add_front(listpp, n1);
    ll_show(*listpp);

/*-----------------------------------*/
    printf("\t---add a node @ head---\n");
    node_t *n2 = NULL;

    if (!ll_new_node(&n2)) {
        printf("Failure of create a new node\n");
        return 1;
    }

    ll_show_node(n2);

    ll_add_front(listpp, n2);
    ll_show(*listpp);
/*-----------------------------------*/
    printf("\t---add a node @ tail---\n");
    node_t *n3 = NULL;
    
    if (!ll_new_node(&n3)) {
        printf("Failure of create a new node\n");
        return 1;
    }

    ll_show_node(n3);

    ll_add_end(listpp, n3);
    ll_show(*listpp);
/*-----------------------------------*/
    printf("\t---locate a node---\n");
    p = ll_search(*listpp, n3->oid);

    if(p == NULL) {
        printf("Node Not Found!\n");
    } else {
        ll_show_node(p);
    }
    ll_show(*listpp);
/*-----------------------------------*/
    printf("\t---unlink a node @ tail---\n");
    p = ll_unlink(listpp, n3->oid);

    if(p == NULL) {
        printf("Node Not Found!\n");
    } else {
        ll_show_node(p);
    }
    ll_show(*listpp);

/*-----------------------------------*/
    printf("\t---double unlink a node ---\n");
    p = ll_unlink(listpp, n3->oid);

    if(p == NULL) {
        printf("Node Not Found!\n");
    } else {
        ll_show_node(p);
    }
    ll_show(*listpp);

/*-----------------------------------*/
    printf("\t---unlink a node @ head---\n");
    p = ll_unlink(listpp, n1->oid);

    if(p == NULL) {
        printf("Node Not Found!\n");
    } else {
        ll_show_node(p);
    }
    ll_show(*listpp);
/*-----------------------------------*/
    printf("\t---unlink a single node ---\n");
    p = ll_unlink(listpp, n2->oid);

    if(p == NULL) {
        printf("Node Not Found!\n");
    } else {
        ll_show_node(p);
    }
    ll_show(*listpp);
/*-----------------------------------*/
    printf("\t---list w/ 3 nodes ---\n");

    ll_add_end(listpp, n1);
    ll_add_end(listpp, n2);
    ll_add_end(listpp, n3);
    ll_show(*listpp);
/*-----------------------------------*/
    printf("\t---erase the whole list ---\n");
    ll_erase(listpp);
    ll_show(*listpp);

/*-----------------------------------*/
    printf("\t---3 nodes n1, n2, n3 ---\n");
    ll_show_node(n1);
    ll_show_node(n2);
    ll_show_node(n3);

    printf("\t------ Test for SAI port_t Node -----\n");

/*-----------------------------------*/
    printf("\t---allocate port_t, show as generic node_t and port_t ---\n");
    port_t *port1, *port2, *port3;

    if(!new_port(&port1)) {
        return 1;
    }

    ll_show_node((node_t*) port1);
    show_port(port1);
    ll_show(*listpp);
/*-----------------------------------*/
    printf("\t---add port_t to the list ---\n");
    ll_add_front(listpp, (node_t*)port1);
    ll_show(*listpp);

/*-----------------------------------*/
    printf("\t---add port_t @ head ---\n");
    if(!new_port(&port2)) {
        return 1;
    }
    ll_show_node((node_t*) port2);
    ll_add_front(listpp, (node_t*)port2);
    ll_show(*listpp);

/*-----------------------------------*/
    printf("\t---add port_t @ tail ---\n");
    if(!new_port(&port3)) {
        return 1;
    }
    ll_show_node((node_t*) port3);
    ll_add_end(listpp, (node_t*)port3);
    ll_show(*listpp);
/*-----------------------------------*/
    printf("\t---erase the whole port_t list ---\n");

    p = ll_unlink_head(listpp);

    while(p) {
        ll_show(*listpp);
        erase_port((port_t*)p);
        p = ll_unlink_head(listpp);
    }






    printf(" ======= TEST Linked List Completed ========\n");
    return 0;
}

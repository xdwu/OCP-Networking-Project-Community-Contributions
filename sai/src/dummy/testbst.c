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

#define DUMMY_LOG(DBG, msg, ...) \
    if(DBG) printf(msg, ##__VA_ARGS__) \
    else printf(msg, ##__VA_ARGS__)

        

int main(int argc, char** argv)
{
    printf("%s\n", __FUNCTION__);

    printf("======== TEST BST Tree ==================\n");

    tree_node_t **treepp, *p;

    treepp = (tree_node_t**) malloc(sizeof(tree_node_t*));

    if(treepp == NULL) {
        printf("Malloc Failure \n");
        return 1;
    }

    *treepp = NULL;

    srand(time(NULL));

printf("-------------empty tree --------------\n");
    tree_show(*treepp, 0);

printf("-------------single node --------------\n");
    tree_node_t *n1;

    if(!tree_new_node(&n1)) {
        printf("new_node Failure \n");
        return 1;
    }
    
    tree_insert(treepp, n1);
    tree_show(*treepp, 0);

printf("-------------2nd node --------------\n");
    tree_node_t *n2;

    if(!tree_new_node(&n2)) {
        printf("new_node Failure \n");
        return 1;
    }
    
    tree_insert(treepp, n2);
    tree_show(*treepp, 0);

printf("-------------3rd node --------------\n");
    tree_node_t *n3;

    if(!tree_new_node(&n3)) {
        printf("new_node Failure \n");
        return 1;
    }
    
    tree_insert(treepp, n3);
    tree_show(*treepp, 0);

printf("-------------4th node --------------\n");
    tree_node_t *n4;

    if(!tree_new_node(&n4)) {
        printf("new_node Failure \n");
        return 1;
    }
    
    tree_insert(treepp, n4);
    tree_show(*treepp, 0);

printf("-------------5th node --------------\n");
    tree_node_t *n5;

    if(!tree_new_node(&n5)) {
        printf("new_node Failure \n");
        return 1;
    }
    
    tree_insert(treepp, n5);
    tree_show(*treepp, 0);


printf("-------------lookup 5th node --------------\n");
    p = tree_lookup(*treepp, n5->oid);

    if(p == NULL) {
        printf("lookup Failure \n");
        return 1;
    }
    
    printf("target [0x%08lx] found [0x%08lx]\n", 
            n5->oid, p->oid);

printf("-------------lookup 1st node --------------\n");
    p = tree_lookup(*treepp, n1->oid);

    if(p == NULL) {
        printf("lookup Failure \n");
        return 1;
    }
    
    printf("target [0x%08lx] found [0x%08lx]\n", 
            n1->oid, p->oid);


printf("------------validate the bst --------------\n");
    if( tree_is_bst( *treepp)) {
        printf("This is a BST\n");
    } else {
        printf("This is NOT a BST\n");
    }

printf("-------------nr lookup 4th node --------------\n");
    p = tree_lookup_nr(*treepp, n4->oid);

    if(p == NULL) {
        printf("lookup Failure \n");
        return 1;
    }
    
    printf("target [0x%08lx] found [0x%08lx]\n", 
            n4->oid, p->oid);


printf("-------------nr lookup 2nd node --------------\n");
    p = tree_lookup_nr(*treepp, n2->oid);

    if(p == NULL) {
        printf("lookup Failure \n");
        return 1;
    }
    
    printf("target [0x%08lx] found [0x%08lx]\n", 
            n2->oid, p->oid);

printf("-------------6th node --------------\n");
    tree_node_t *n6;

    if(!tree_new_node(&n6)) {
        printf("new_node Failure \n");
        return 1;
    }
    
    tree_insert(treepp, n6);
    tree_show(*treepp, 0);

printf("-------------7th node --------------\n");
    tree_node_t *n7;

    if(!tree_new_node(&n7)) {
        printf("new_node Failure \n");
        return 1;
    }
    
    tree_insert(treepp, n7);
    tree_show(*treepp, 0);

printf("-------------8th node --------------\n");
    tree_node_t *n8;

    if(!tree_new_node(&n8)) {
        printf("new_node Failure \n");
        return 1;
    }
    
    tree_insert(treepp, n8);
    tree_show(*treepp, 0);



printf("------------- remove 2nd node --------------\n");

    p = tree_remove(treepp, n2->oid);

    if(p == NULL) {
        printf("remove Failure \n");
        return 1;
    }
    
#ifndef UNIT_TEST
    printf("target [0x%08lx] removed [0x%08lx]\n", 
            n2->oid, p->oid);
#else
    printf("target [%02d] removed [%02d]\n", 
            n2->oid, p->oid);
#endif

    tree_show(*treepp, 0);

    if( tree_is_bst( *treepp)) {
        printf("This is a BST\n");
    } else {
        printf("This is NOT a BST\n");
    }


printf("------------- remove 1st node --------------\n");

    p = tree_remove(treepp, n1->oid);

    if(p == NULL) {
        printf("remove Failure \n");
        return 1;
    }
    
#ifndef UNIT_TEST
    printf("target [0x%08lx] removed [0x%08lx]\n", 
            n1->oid, p->oid);
#else
    printf("target [%02d] removed [%02d]\n", 
            n1->oid, p->oid);
#endif

    tree_show(*treepp, 0);

    if( tree_is_bst( *treepp)) {
        printf("This is a BST\n");
    } else {
        printf("This is NOT a BST\n");
    }







    printf(" ======= TEST BST Tree End ==============\n");
    return 0;
}

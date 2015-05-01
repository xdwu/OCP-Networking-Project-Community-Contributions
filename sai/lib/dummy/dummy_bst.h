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

#ifndef __DUMMY_BST_H_
#define __DUMMY_BST_H_

#include "dummy.h"
#include "dummy_internal.h"

#define UNIT_TEST   true

typedef struct _generic_tree_node_t {
    struct _generic_tree_node_t *left;
    struct _generic_tree_node_t *right;
    sai_object_id_t             oid;

} tree_node_t;

bool tree_new_node(tree_node_t **npp);
void tree_erase_node(tree_node_t *np);

bool tree_insert(tree_node_t **treepp, tree_node_t *np);
tree_node_t* tree_lookup(tree_node_t *treep, sai_object_id_t key);
tree_node_t* tree_lookup_nr(tree_node_t *treep, sai_object_id_t key);

tree_node_t* tree_remove(tree_node_t **treepp, sai_object_id_t key); 

void tree_show(tree_node_t *treep, int level);
bool tree_is_bst(tree_node_t *treep);


//To Do
//1. Basic Tree Operation_
//2. Expand the test on larger node
//2. pass comp_func as the parameter



#endif //__DUMMY_BST_H_

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
#ifndef __DUMMY_LL_H_
#define __DUMMY_LL_H_

#include "dummy.h"
#include "dummy_internal.h"

typedef struct _generic_node_t {
    struct _generic_node_t *next;
    sai_object_id_t         oid;

} node_t;


bool ll_new_node(node_t** npp);

bool ll_add_front(node_t **listpp, node_t *n);
bool ll_add_end(node_t **listpp, node_t *n);
node_t* ll_search(node_t *listp, sai_object_id_t key);
node_t* ll_unlink(node_t **listpp, sai_object_id_t key);
node_t* ll_unlink_head(node_t **listpp);

void ll_erase(node_t **listpp);


void ll_show_node(node_t *n);
void ll_show(node_t *lp);

#endif //__DUMMY_LL_H_

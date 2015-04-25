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
#include "dummy_ll.h"

bool ll_new_node(node_t** npp)
{
    node_t *p;

    p = (node_t*) malloc(sizeof(node_t));

    if(p == NULL) {
        *npp = NULL;
        return false;
    }

    p->next = NULL;
    if(!acquire_oid(&(p->oid))) {
        *npp = NULL;
        free(p);
        return false;
    }

    *npp = p;
    return true;
}

bool ll_add_front(node_t **listpp, node_t *np)
{
    printf("%s\n", __FUNCTION__);

    if (np == NULL || listpp == NULL) {
        return false;
    }


    if (*listpp == NULL) {
        *listpp = np;
        return true;
    } 

    np->next = *listpp;
    *listpp = np;

    return true;
}


bool ll_add_end(node_t **listpp, node_t *np)
{
    printf("%s\n", __FUNCTION__);
    node_t *p;

    if (np == NULL || listpp == NULL) {
        return false;
    }

    
    if (*listpp == NULL) {
        *listpp = np;
        return true;
    }
    
    for(p=*listpp; p->next != NULL; p=p->next);

    p->next = np;

    return true;
}

node_t* ll_search(node_t *listp, sai_object_id_t key)
{
    node_t *p;
    printf("%s [0x%8lx]\n", __FUNCTION__, key);

    for(p = listp; p != NULL; p=p->next) {
        if(p->oid == key) {
            return p;
        }
    }

    return NULL;
}

node_t* ll_unlink(node_t **listpp, sai_object_id_t key)
{
    node_t *p, *pp, *sn;
    printf("%s [0x%8lx]\n", __FUNCTION__, key);

    if(*listpp == NULL) {
        return NULL;
    }

    if((*listpp)->next == NULL ) {
        p = *listpp;
        *listpp = NULL;
        return p;
    }
    
    for(pp= NULL, p = *listpp; p != NULL;) {
        sn = p->next;

        if(p->oid == key) {
            if(pp == NULL) {
                (*listpp) -> next = sn;
            } else {
                pp->next = sn;
            }
            p->next = NULL;
            return p;
        }
        pp = p;
        p = sn;
    }

    return NULL;
}

node_t* ll_unlink_head(node_t **listpp)
{
    node_t *head;

    if(*listpp == NULL) {
        return NULL;
    }

    head = *listpp;
    *listpp = (*listpp)->next;

    return head;
}

void ll_erase(node_t **listpp)
{
    node_t *p;
    printf("%s \n", __FUNCTION__);

    if(*listpp == NULL) {
        return;
    }

    if((*listpp)->next == NULL ) {
        p = *listpp;
        *listpp = NULL;
        release_oid(p->oid);
        free(p);
    }

    for(p=*listpp; p!=NULL; ){
        *listpp = p->next;
        
        release_oid(p->oid);
        free(p);

        p = *listpp;
    }

}

void ll_show_node(node_t *n)
{
    printf("%s\t", __FUNCTION__);
    if(n == NULL) {
        return;
    }
    printf("0x%8lx ", n->oid);
    printf("\n");
}


void ll_show(node_t *listp)
{
//    printf("%s\n", __FUNCTION__);
    node_t *p;

    if(listp == NULL) {
        printf("<empty>\n");
        return;
    }

    for(p=listp; p != NULL; p=p->next) {
        printf("[0x%08lx] -> ", p->oid);
    }
    printf("\n");
}

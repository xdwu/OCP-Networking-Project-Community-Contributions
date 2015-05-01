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
#include "dummy_bst.h"

bool tree_new_node(tree_node_t **npp)
{
    tree_node_t *p;
    
    p = (tree_node_t *)malloc(sizeof(tree_node_t));
    if( p == NULL) {
        *npp = NULL;
        return false;
    }

    p->left = NULL;
    p->right = NULL;

#ifndef UNIT_TEST
    if(!acquire_oid( &(p->oid))) {
        free(p);
        *npp = NULL;
        return false;
    }
#else 
    p->oid = rand() %100;
#endif

    *npp = p;
    return true;
}

void tree_erase_node(tree_node_t *np)
{
    if(np == NULL) {
        return;
    }

    release_oid(np->oid);
    free(np);
    return;
}

bool tree_insert(tree_node_t **treepp, tree_node_t *np)
{
    if (treepp == NULL || np == NULL) {
        return false;
    }

    if (*treepp == NULL) {
        *treepp = np;
        return true;
    }

    if(np->oid < (*treepp)->oid) {
        //smaller, left sub-tree
        return( tree_insert( &((*treepp)->left), np));
    } else if(np->oid > (*treepp)->oid) {
        //bigger, left sub-tree
        return( tree_insert( &((*treepp)->right), np));
    } else {
        //duplicated, no operation
        return true;
    }

    return true;
}

//recursive
tree_node_t * tree_lookup(tree_node_t *treep, sai_object_id_t key)
{
    if( treep == NULL ) {
        return NULL;
    }
    
    if( treep->oid == key) {
        return (treep);
    }

    if( key < treep->oid ) {
        return ( tree_lookup ( (treep->left), key));
    } else {
        return ( tree_lookup ( (treep->right), key));
    }
}


//non-recursive
tree_node_t * tree_lookup_nr(tree_node_t *treep, sai_object_id_t key)
{
    while(treep != NULL) {
        if (key == treep->oid ) {
            return treep;
        } else if ( key < treep->oid ) {
            treep = treep->left;
        } else {
            treep = treep->right;
        }
    }
    return NULL;
}

static bool
is_leaf(tree_node_t *p) 
{
    if(p == NULL) {
        return false;
    } 

    if (p->left == NULL && p->right == NULL) {
        return true;
    }

    return false;
}

tree_node_t* tree_remove(tree_node_t **treepp, sai_object_id_t key)
{
    tree_node_t *p, *pp;
    pp = NULL;
    p = *treepp;
    bool found = false;
    bool l = false;
    bool r = false;

    while(p != NULL) {
        if (key == p->oid ) {
            found = true;
            if(pp && p->oid < pp->oid) {
                l = true;
            } else if(pp && p->oid > pp->oid) {
                r = true;
            }

            break;
        } else if ( key < p->oid ) {
            pp = p;
            p = p->left;
        } else {
            pp = p;
            p = p->right;
        }
    }

    if (!found) {
        return NULL;
    }

    if (is_leaf(p)) {
        if(l) {
            pp->left = NULL;
        } else if(r) {
            pp->right = NULL;
        } else {
            *treepp = NULL;
        }
        return p;
    } else if (p->left == NULL && p->right != NULL) {
        if(l) {
            pp->left = p->right;
        } else if (r) {
            pp->right = p->right;
        } else {
            (*treepp) = p->right;
        }
        p->right = NULL;
        return p;
    } else if (p->left != NULL && p->right == NULL) {
        if(l) {
            pp->left = p->left;
        } else if (r) {
            pp->right = p->left;
        } else {
            (*treepp) = p->left;
        }
        p->left = NULL;
        return p;
    } else if (p->left != NULL && p->right != NULL) {
        //two children
        //build a new BST sub-tree, 
        //root is p->left
        //insert p->right sub-tree to this sub-tree
        tree_insert(&(p->left), p->right);
        if(l) {
            pp->left = p->left;
        } else if (r) {
            pp->right = p->left;
        } else {
            (*treepp) = p->left;
        }
        p->left = NULL;
        p->right = NULL;
        return p;
    } else {
        //impossible
        return p;
    }
}




void tree_show(tree_node_t *treep, int level)
{
    int i;

    if(treep == NULL) {
        printf("<>\n");
        return;
    }

#ifndef UNIT_TEST
    printf("[0x%08lx]\n", treep->oid);
#else
    printf("[%02d]\n", treep->oid);
#endif

    for(i=0; i<level; i++) {
        printf("  ");
    }
    printf(" +");

    tree_show(treep->left, level+1);

    for(i=0; i<level; i++) { 
        printf("  ");
    }
    printf(" +");
    tree_show(treep->right, level+1);
}

bool tree_is_bst(tree_node_t *treep)
{
    if (treep == NULL ) {
        return true;
    }

    if (!tree_is_bst(treep->left) || 
        !tree_is_bst(treep->right) ) {
        return false;
    }

    if (treep->left != NULL && treep->left->oid >= treep->oid) {
        return false;
    }

    if (treep->right != NULL && treep->right->oid <= treep->oid) {
        return false;
    }

    return true;
}

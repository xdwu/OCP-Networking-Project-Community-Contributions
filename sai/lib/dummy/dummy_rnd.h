#ifndef __DUMMY_RND_H_
#define __DUMMY_RND_H_

#include "dummy.h"
#include "dummy_internal.h"

bool init_objid_pool();
bool acquire_id(uint64_t *id);
bool release_id(uint64_t id);    

#endif //__DUMMY_RND_H_

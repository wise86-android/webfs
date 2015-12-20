/*
 * remoteStorage.h
 *
 *  Created on: Dec 20, 2015
 *      Author: wise
 */

#ifndef INCLUDE_REMOTESTORAGE_H_
#define INCLUDE_REMOTESTORAGE_H_

#include <cstdio>
#include "rapidjson/writer.h"
#include "node.h"

namespace webfs {

class RemoteService{

	virtual bool create(Node *node)=0;
	virtual std::FILE* download(Node *node)=0;
	virtual bool remove(Node *node)=0;
	virtual bool update(Node *node)=0;

	virtual ~RemoteService()=default;
};

}

#endif /* INCLUDE_REMOTESTORAGE_H_ */

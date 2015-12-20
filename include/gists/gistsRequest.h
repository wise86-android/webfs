#ifndef SRC_GISTS_GISTSREQUEST_H_
#define SRC_GISTS_GISTSREQUEST_H_

namespace webfs {
namespace gists{
	bool create(Node *node);
	bool download(Node *node);
	bool remove(Node *node);
	bool update(Node *node);
}
}




#endif /* SRC_GISTS_GISTSREQUEST_H_ */

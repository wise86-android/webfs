#include "gtest/gtest.h"
#include "node.h"
#include "gists/gistsRequest.h"

TEST(gistRequest,create){
	webfs::Node createMe("test",webfs::Node::Type::LEAF);
	EXPECT_TRUE(webfs::gists::create(&createMe));
	createMe.getRemoteInfo().getInfo("id");

	EXPECT_TRUE(webfs::gists::download(&createMe));
	EXPECT_TRUE(webfs::gists::update(&createMe));
	EXPECT_TRUE(webfs::gists::download(&createMe));
	//EXPECT_TRUE(webfs::gists::remove(&createMe));
}





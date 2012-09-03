#pragma once

#include <vector>
#include "Node.h"
/*
	Class for managine nodes.
	Singleton
*/
namespace XCNS
{


class NodeMgr
{
private:
	NodeMgr(void);
	static NodeMgr* m_instance;
	
private:
	std::vector<Node*> m_nodes;

public:
	static NodeMgr* getInstance();
	~NodeMgr(void);

public:
	Node* getNodeByID(int id);
	void initialize();
	int getNodeNum();
};
}


/*
 * BaseNode.h
 *
 *  Created on: 2013. 5. 13.
 *      Author: jiwon
 */

#ifndef BASENODE_H_
#define BASENODE_H_



enum NodeType {BlueNode = 0 , RedNode};
class BaseNode
{
public:
	BaseNode();
	virtual ~BaseNode();

	NodeType node_type;
};

#endif /* BASENODE_H_ */

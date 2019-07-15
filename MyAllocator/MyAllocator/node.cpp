#include "stdafx.h"
#include "node.h"

#include <iostream>


Node::Node(Node* pPreviousNode, Node* pNextNode, bool fChunkFree) : m_fChunkFree(fChunkFree), m_pPreviousNode(pPreviousNode),
m_pNextNode(pNextNode)
{
	if (pPreviousNode)
	{
		pPreviousNode->setNextNode(this);
	}
	if (pNextNode)
	{
		pNextNode->setPreviousNode(this);
	}
}

Node::~Node() {}

bool Node::getChunkState() const
{
	return m_fChunkFree;
}

Node* Node::getPreviousNode() const
{
	return m_pPreviousNode;
}

Node* Node::getNextNode() const
{
	return m_pNextNode;
}

size_t Node::getChunkSize() const
{
	return m_pNextNode == nullptr ? 0 : (char*)m_pNextNode - (char*)this - sizeof(Node);
}

void Node::setChunkState(bool fNewChunkState)
{
	if (fNewChunkState)
	{
		if (m_pPreviousNode && m_pPreviousNode->getChunkState())
		{
			m_pPreviousNode->setNextNode(m_pNextNode);
			m_pNextNode->setPreviousNode(m_pPreviousNode);
		}
		else if (m_pNextNode && m_pNextNode->getChunkState())
		{
			m_pNextNode = m_pNextNode->getNextNode();
			m_pNextNode->setPreviousNode(this);
		}
	}
	m_fChunkFree = fNewChunkState;
}

void Node::setPreviousNode(Node* pPreviousNode)
{
	m_pPreviousNode = pPreviousNode;

	if (m_fChunkFree && m_pPreviousNode && m_pPreviousNode->getChunkState())
	{
		m_pPreviousNode->setNextNode(m_pNextNode);
		m_pNextNode->setPreviousNode(m_pPreviousNode);
	}
}

void Node::setNextNode(Node* pNextNode)
{
	m_pNextNode = pNextNode;

	if (m_fChunkFree && m_pNextNode && m_pNextNode->getChunkState())
	{
		m_pNextNode = m_pNextNode->getNextNode();
		m_pNextNode->setPreviousNode(this);
	}
}
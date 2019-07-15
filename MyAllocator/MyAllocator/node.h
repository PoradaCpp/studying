#ifndef NODE_H
#define NODE_H

class Node
{
public:
	Node(Node* pPreviousNode, Node* pNextNode, bool fChunkFree);
	~Node();

	bool getChunkState() const;
	Node* getPreviousNode() const;
	Node* getNextNode() const;
	size_t getChunkSize() const;

	void setChunkState(bool fNewChunkState);
	void setPreviousNode(Node* pPreviousNode);
	void setNextNode(Node* pNextNode);

private:
	bool m_fChunkFree;
	Node* m_pPreviousNode;
	Node* m_pNextNode;
};

#endif //NODE_H
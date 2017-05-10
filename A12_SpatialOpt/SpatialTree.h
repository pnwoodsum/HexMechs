#pragma once

#include "RE\ReEng.h"
#include "MyBOClass.h"
#include <vector>

class Node 
{
public:
	static int colCount;
	//center of current grid spot
	vector3 position;
	//holds the x width, y width and z width of current grid section
	vector3 widths;

	std::vector<Node*> children;
	std::vector<MyBOClass*> objects;
	
	void checkCollisions();
	void split(int);
	bool containsPoint(vector3);
	bool containsObject(MyBOClass*);
	void addObject(MyBOClass*);

	Node(vector3,vector3);
	~Node();

};

class SpatialTree
{
public:
	Node* head;
	std::vector<MyBOClass*> objects;
	bool optimize = true;
	bool display = false;

	int colCount;
	
	
	vector3 m_v3Min = vector3(0.0f);
	vector3 m_v3Max = vector3(0.0f);

	void setOptimize();
	void setOptimize(bool);
	void setDisplay();
	void addObject(MyBOClass*);
	void checkCollisions();
	void displayTree(MeshManagerSingleton*);
	void displayTree(MeshManagerSingleton*, Node*);
	void generateTree(int);

	void cleanTree(Node * node);

	SpatialTree();
	~SpatialTree();
};


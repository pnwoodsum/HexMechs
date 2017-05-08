#pragma once

#include "RE\ReEng.h"
#include "MyBOClass.h"
#include <vector>

class Node 
{
public:
	//center of current grid spot
	vector3 position;
	//holds the x width, y width and z width of current grid section
	vector3 widths;

	std::vector<Node*> children;
	std::vector<MyBOClass*> objects;
	
	void checkCollisions();
	bool containsPoint(vector3);
	bool containsObject(MyBOClass*);
	void addObject(MyBOClass*);

	Node();
	~Node();


};

class SpatialTree
{
public:
	Node* head;
	std::vector<MyBOClass*> objects;
	bool optimize = true;
	
	
	vector3 m_v3Min = vector3(0.0f);
	vector3 m_v3Max = vector3(0.0f);

	void setOptimize();
	void setOptimize(bool);
	void addObject(MyBOClass*);
	void checkCollisions();

	SpatialTree();
	~SpatialTree();
};


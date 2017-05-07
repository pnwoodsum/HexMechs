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

	Node();
	~Node();


};

class SpatialTree
{
public:
	Node* head;
	std::vector<MyBOClass*> objects;
	
	
	vector3 m_v3Min = vector3(0.0f);
	vector3 m_v3Max = vector3(0.0f);


	void addObject(MyBOClass*);

	SpatialTree();
	~SpatialTree();
};


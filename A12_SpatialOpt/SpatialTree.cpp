#include "SpatialTree.h"




Node::Node(vector3 position, float width) {
	
}

Node::~Node() {

}

void Node::split(int level) {
	if (level == 0) return;
	float w = (float)(width / 2);
	float c = width / 4;
	children[0] = new Node(vector3(position.x + c, position.y + c, position.z + c), w);
	children[1] = new Node(vector3(position.x + c, position.y + c, position.z - c), w);
	children[2] = new Node(vector3(position.x + c, position.y - c, position.z - c), w);
	children[3] = new Node(vector3(position.x + c, position.y - c, position.z + c), w);
	children[4] = new Node(vector3(position.x - c, position.y + c, position.z + c), w);
	children[5] = new Node(vector3(position.x - c, position.y + c, position.z - c), w);
	children[6] = new Node(vector3(position.x - c, position.y - c, position.z + c), w);
	children[7] = new Node(vector3(position.x - c, position.y - c, position.z - c), w);

	for (int i = 0; i < 8; i++) {
		children[i]->split(level - 1);
	}

}

void Node::checkCollisions() {
	//check collisions between all the objects
	for (int i = 0; i < objects.size(); i++) {
		for (int j = 0; j < objects.size(); j++) {
			if (i == j) continue;
			if (objects[i]->IsColliding(objects[j]))
				objects[i]->colliding = true;
		}
	}
	//tell all children to checkCollisions
	for (int i = 0; i < children.size(); i++)
		children[i]->checkCollisions();
}

void SpatialTree::checkCollisions() {
	head->checkCollisions();
}
void SpatialTree::setOptimize(){
	setOptimize(!optimize);
}
void SpatialTree::setOptimize(bool newVal){
	optimize = newVal;
}

void SpatialTree::addObject(MyBOClass * object) {
	//update max
	if (m_v3Max.x < object->GetMaxG().x) m_v3Max.x = object->GetMaxG().x;
	if (m_v3Max.y < object->GetMaxG().y) m_v3Max.y = object->GetMaxG().y;
	if (m_v3Max.z < object->GetMaxG().z) m_v3Max.z = object->GetMaxG().z;

	//update min
	if (m_v3Min.x > object->GetMinG().x) m_v3Min.x = object->GetMinG().x;
	if (m_v3Min.y > object->GetMinG().y) m_v3Min.y = object->GetMinG().y;
	if (m_v3Min.z > object->GetMinG().z) m_v3Min.z = object->GetMinG().z;
	
	objects.push_back(object);
}

void SpatialTree::displayTree() {

}

void SpatialTree::generateTree(int depth) {
	head->widths.x = m_v3Max.x - m_v3Min.x;
	head->widths.y = m_v3Max.y - m_v3Min.y;
	head->widths.z = m_v3Max.z - m_v3Min.z;

	head->position = m_v3Min + head->widths / 2.0f;

	head->split(depth);
	for (int i = 0; i < objects.size; i++) {
		head->
	}
}

SpatialTree::SpatialTree()
{
	//Set size of entire tree location

	//then recursively create 8 child nodes that each have 1/2 the x, y and z widths and are positioned inside the parent node.
	// I think 3 interations should do
}


SpatialTree::~SpatialTree()
{
}

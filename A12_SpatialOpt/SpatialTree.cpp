#include "SpatialTree.h"




Node::Node(vector3 position, vector3 width) {
	widths = width;
	this->position = position;
}

Node::~Node() {

}

void Node::split(int level) {
	if (level == 0) return;
	vector3 w = widths / 2.0f;
	vector3 c = widths / 4.0f;
	children.push_back(new Node(vector3(position.x + c.x, position.y + c.y, position.z + c.z), w));
	children.push_back(new Node(vector3(position.x + c.x, position.y + c.y, position.z - c.z), w));
	children.push_back(new Node(vector3(position.x + c.x, position.y - c.y, position.z - c.z), w));
	children.push_back(new Node(vector3(position.x + c.x, position.y - c.y, position.z + c.z), w));
	children.push_back(new Node(vector3(position.x - c.x, position.y + c.y, position.z + c.z), w));
	children.push_back(new Node(vector3(position.x - c.x, position.y + c.y, position.z - c.z), w));
	children.push_back(new Node(vector3(position.x - c.x, position.y - c.y, position.z + c.z), w));
	children.push_back(new Node(vector3(position.x - c.x, position.y - c.y, position.z - c.z), w));

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
bool Node::containsPoint(vector3 point) {
	if ((point.x < position.x - widths.x / 2) ||
		(point.y < position.y - widths.y / 2) ||
		(point.z < position.z - widths.z / 2) ||
		(point.x > position.x + widths.x / 2) ||
		(point.y > position.y + widths.y / 2) ||
		(point.z > position.z + widths.z / 2)) return false;
	return true;
}
bool Node::containsObject(MyBOClass* object) {
	//must contain all 8 points of object to fully contain it 
	for (int i = 0; i < 8; i++) {
		if (!containsPoint(object->v3Corner[i])) return false;
	}
	return true;
}

void Node::addObject(MyBOClass* object) {
	for (int i = 0; i < children.size(); i++) {
		if (children[i]->containsObject(object)) {
			children[i]->addObject(object);
			return;
		}
	}
	objects.push_back(object);
}


void SpatialTree::checkCollisions() {
	if(optimize) head->checkCollisions();
	else {
		for (int i = 0; i < objects.size(); i++) {
			for (int j = 0; j < objects.size(); j++) {
				if (i == j) continue;
				if (objects[i]->IsColliding(objects[j]))
					objects[i]->colliding = true;
			}
		}
	}
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
	for (int i = 0; i < objects.size(); i++) {
		head->addObject(objects[i]);
	}
}

SpatialTree::SpatialTree()
{
	head = new Node(vector3(), vector3());
	//Set size of entire tree location

	//then recursively create 8 child nodes that each have 1/2 the x, y and z widths and are positioned inside the parent node.
	// I think 3 interations should do
}


SpatialTree::~SpatialTree()
{
}

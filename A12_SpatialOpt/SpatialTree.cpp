#include "SpatialTree.h"



int Node::colCount;

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
	if ((children.size() > 0)) {
		for (int i = 0; i < children.size(); i++) {
			if(children[i]->objects.size() > 0 || children[i]->children.size() > 0)
				children[i]->checkCollisions();
		}
	}
	else if (objects.size() > 0) {
		//check collisions between all the objects
		for (int i = 0; i < objects.size() - 1; i++) {
			for (int j = i + 1; j < objects.size(); j++) {


				if (objects[i]->IsColliding(objects[j])) {
					colCount++;
					objects[i]->colliding = true;
					objects[j]->colliding = true;
				}
			}
		}
	}
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
	//must contain any of the 8 points of object to contain it 
	for (int i = 0; i < 8; i++) {
		if (containsPoint(object->v3Corner[i])) return true;
	}
	return false;
}

void Node::addObject(MyBOClass* object) {
	if (children.size() > 0) {
		for (int i = 0; i < children.size(); i++) {
			if (children[i]->containsObject(object)) {
				MyBOClass* newObject = object;
				children[i]->addObject(newObject);
			}
		}
	}
	else {
		MyBOClass* newObject = object;
		objects.push_back(newObject);
	}
}

void SpatialTree::checkCollisions() {
	head->colCount = 0;
	colCount = 0;

	if (optimize) head->checkCollisions();
	else {
		for (int i = 0; i < objects.size()-1; i++) {
			for (int j = i+1; j < objects.size(); j++) {
				colCount++;
				//Counter::IncCollisionCount();
				if (objects[i]->IsColliding(objects[j])) {
					objects[i]->colliding = true;
				}
			}
		}
	}
}
void SpatialTree::setOptimize() {
	setOptimize(!optimize);
}
void SpatialTree::setOptimize(bool newVal) {
	optimize = newVal;
}

void SpatialTree::setDisplay() {
	display = !display;
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

void SpatialTree::displayTree(MeshManagerSingleton* Mesh) {
	if (!display) return;
	for (int i = 0; i < head->children.size(); i++) {
		Node* curr = head->children[i];
		Mesh->AddCubeToRenderList(IDENTITY_M4 * glm::translate(curr->position.x, curr->position.y, curr->position.z) * glm::scale(curr->widths.x, curr->widths.y, curr->widths.z), RERED, WIRE);
		for (int j = 0; j < curr->children.size(); j++) {
			//Node* curr2 = curr->children[j];
			displayTree(Mesh, curr->children[j]);
		}
	}
}

void SpatialTree::displayTree(MeshManagerSingleton* Mesh, Node* node) {
	// Generates smallest nodes, but only if they contain objects
	if (!display) return;
	if ((node->children.size() > 0)) {
		for (int i = 0; i < node->children.size(); i++) {
			if (node->children[i]->objects.size() > 0 || node->children[i]->children.size() > 0)
				displayTree(Mesh, node->children[i]);
		}
	}
	else if (objects.size() > 0) {
		// Draw cubes
		Mesh->AddCubeToRenderList(IDENTITY_M4 * glm::translate(node->position.x, node->position.y, node->position.z) * glm::scale(node->widths.x, node->widths.y, node->widths.z), RERED, WIRE);
	}
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

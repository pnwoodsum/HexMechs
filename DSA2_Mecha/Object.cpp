#include "Object.hpp"
#include <algorithm>

std::vector<int> Object::instanceIDs;

//Constructor
Object::Object() {
	name = "Object";
	//TODO: instance id generation
	//set the instance id to one more the the biggest one already in the vector
	//	instanceID = instanceIDs.at(std::distance(instanceIDs.begin(), std::max_element(instanceIDs.begin(), instanceIDs.end()))) + 1;
	//instanceIDs.push_back(instanceID);
}

Object::Object(const Object& other) {
	name = other.name;
	instanceID = other.GetInstanceID();
}

Object::~Object() {
	for (std::vector<int>::iterator iter = instanceIDs.begin(); iter != instanceIDs.end(); ++iter) {
		if (*iter == instanceID) {
			instanceIDs.erase(iter);
			break;
		}
	}
}

Object Object::Clone() {
	return Object(*this);
}

int Object::GetInstanceID() const {
	return instanceID;
}

std::string Object::ToString() {
	return name;
}

//Undone: Destroy
void Object::Destroy(Object obj, float delay) {}
//Undone: DontDestroyOnLoad
void Object::DontDestroyOnLoad(Object target) {}

Object Object::Instantiate(Object other) {
	return Object(other);
}

Object Object::Instantiate(Object original, vector3 position, quaternion rotation) {
	//will be overridden in lower class
	return Object();
}

bool Object::operator!=(Object& other) {
	return instanceID != other.GetInstanceID();
}

bool Object::operator==(Object& other) {
	return instanceID == other.GetInstanceID();
}

Object::operator bool() const {
	return *this != NULL;
}
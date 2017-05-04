#pragma once
#include <string>
#include <vector>
#include "RE\ReEngAppClass.h"

class Object {
private:
	static std::vector<int> instanceIDs;
	std::string name;
	int instanceID;
public:
	Object();
	Object(const Object& other);
	~Object();
	bool active = true;
	int GetInstanceID() const;
	std::string ToString();
	Object Clone();
	static void Destroy(Object obj, float delay = 0.0f);
	static void DontDestroyOnLoad(Object target);
	static Object Instantiate(Object original);
	static Object Instantiate(Object original, vector3 position, quaternion rotation);
	bool operator!=(Object& other);
	bool operator==(Object& other);
	operator bool() const;
};

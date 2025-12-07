#pragma once
#include <string>

class GameObject {
public:
    GameObject(int id = 0, const std::string& name = "") : id(id), name(name) {}
    virtual ~GameObject() {}
    int getId() const { return id; }
    std::string getName() const { return name; }
private:
    int id;
    std::string name;
};

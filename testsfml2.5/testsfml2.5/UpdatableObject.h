#pragma once

class UpdatableObject {
public:
    virtual ~UpdatableObject() {}
    virtual void update(float dt) = 0;
};

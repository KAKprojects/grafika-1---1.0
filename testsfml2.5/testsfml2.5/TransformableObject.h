#pragma once

class TransformableObject {
public:
    virtual ~TransformableObject() {}
    virtual void translate(float dx, float dy) = 0;
    virtual void rotate(float angle) = 0;
    virtual void scale(float kx, float ky) = 0;
};

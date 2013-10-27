// Transform.cpp: implementation of the Transform class.

#include "Transform.h"
#include <iostream>

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  const float theta = degrees * pi / 180.0f;
  float x = axis.x;
  float y = axis.y;
  float z = axis.z;

  mat3 axis_cross = mat3(0, -z, y,
			 z, 0, -x,
			 -y, x, 0);
  mat3 axis_axis_t = mat3(x*x, x*y, x*z,
			  y*x, y*y, y*z,
			  z*x, z*y, z*z);

  // Use Rodrigues' formula for the rotation matrix.
  mat3 rotated;
  rotated = cos(theta) * mat3(1.0) 
    + (1 - cos(theta)) * axis_axis_t
    + sin(theta) * axis_cross;

  return rotated;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  mat3 rotation = rotate(degrees, up);
  eye = rotation * eye;
  printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
  glm::normalize(eye);
  glm::normalize(up);
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  mat3 rotation = rotate(degrees, vec3(-1,0,0));
  eye = rotation * eye;
  printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
  glm::normalize(eye);
  glm::normalize(up);
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE

  // You will change this return call
  return mat4();
}

Transform::Transform()
{

}

Transform::~Transform()
{

}

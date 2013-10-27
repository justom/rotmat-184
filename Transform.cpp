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
  mat3 rotation;
  rotation = cos(theta) * mat3(1.0) 
    + (1 - cos(theta)) * axis_axis_t
    + sin(theta) * axis_cross;

  // Transpose to deal with column major orientation
  rotation = glm::transpose(rotation);

  return rotation;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  mat3 rotation = rotate(degrees, glm::normalize(up));
  eye = rotation * eye;
  up = rotation * up;
  // printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  mat3 rotation = rotate(degrees, glm::normalize(glm::cross(eye,up)));
  eye = rotation * eye;
  up = rotation * up;
  // printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // Use the eye and up vectors to create the coordinate system
  vec3 w = glm::normalize(eye);
  vec3 u = glm::normalize(glm::cross(up,w));
  vec3 v = glm::cross(w,u);
  
  mat4 coord_system;
  coord_system = mat4(u[0], u[1], u[2], -glm::dot(u,eye),
		      v[0], v[1], v[2], -glm::dot(v,eye),
		      w[0], w[1], w[2], -glm::dot(w,eye),
		      0.0, 0.0, 0.0, 1.0);
  
  coord_system = glm::transpose(coord_system);
  return coord_system;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}

#include "Camera.h"
#include "Affine.h"
#include <glm/glm.hpp>

const float PI = 4.0f*atan(1.0f);

namespace cs541{
	glm::mat4 view(const glm::vec4 &eye, const glm::vec4 &look, const glm::vec4 &rup){
		glm::vec4 nlook( look.x, look.y, look.z, 0);
		nlook = -glm::normalize(nlook);

		glm::vec4 X( cs541::cross(look, rup) );
		X = glm::normalize(X);

		glm::vec4 up( cs541::cross(nlook, X));
		glm::vec4 one(0.0, 0.0, 0.0, 1.0);
		
		glm::mat4 final(X, up, nlook, one);
		final = cs541::transpose3x3(final);
		return final * cs541::translate(-eye);
	}

	glm::mat4 perspective(float fov, float aspect, float near){
		glm::mat4 perspMat(1);
		float tFov = tan(fov * PI/360.0f);
		
		perspMat[0][0] = 1 / tFov;
		perspMat[1][1] = aspect / tFov;
		perspMat[2][2] = -1.0f;		
		perspMat[3][2] = -2.0f * near;
		perspMat[2][3] = -1.0f;
		perspMat[3][3] = 0;

		return  perspMat;
	}

	glm::mat4 perspective(float fov, float aspect, float near, float far){
		glm::mat4 perspMat(1);
		float tFov = tan(fov * (PI/360.0f));
		
		perspMat[0][0] = 1 / tFov;
		perspMat[1][1] = aspect / tFov;
		perspMat[2][2] = ( near + far )/ (near - far);
		perspMat[3][2] = ( 2 * near * far ) / ( near - far );
		perspMat[2][3] = -1.0f;
		perspMat[3][3] = 0;

		return  perspMat;
	}

}
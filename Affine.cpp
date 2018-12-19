#include "Affine.h"
#include <glm/glm.hpp>

namespace cs541{
	glm::mat4 scale(float r) {
		glm::mat4 scalingMatrix = (glm::mat4(r));
		scalingMatrix[3] = glm::vec4(0.0, 0.0, 0.0, 1.0);

		return scalingMatrix;
	}

	glm::mat4 scale(float rx, float ry, float rz) {
		glm::mat4 scalingMatrix(1.0f);
		scalingMatrix[0] = glm::vec4(rx, 0.0, 0.0, 0.0);
		scalingMatrix[1] = glm::vec4(0.0, ry, 0.0, 0.0);
		scalingMatrix[2] = glm::vec4(0.0, 0.0, rz, 0.0);
		scalingMatrix[3] = glm::vec4(0.0, 0.0, 0.0, 1.0);

		return scalingMatrix;
	}

	glm::mat4 translate(const glm::vec4& v) {
		glm::mat4 translate(0);
		translate[0] = glm::vec4(1.0, 0.0, 0.0, 0.0);
		translate[1] = glm::vec4(0.0, 1.0, 0.0, 0.0);
		translate[2] = glm::vec4(0.0, 0.0, 1.0, 0.0);
		translate[3] = glm::vec4(v.x, v.y, v.z, 1.0);

		return translate;
	}

	glm::mat4 rotate(float t, const glm::vec4& v) {
		glm::mat4 rotateMatrrix(1);
		double d = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
		glm::vec4 nV;
		t = glm::radians(t);
		
		nV.x = v.x / d;
		nV.y = v.y / d;
		nV.z = v.z / d;

		rotateMatrrix[0][0] = cos(t) + (nV.x * nV.x * (1 - cos(t)));
		rotateMatrrix[1][0] = (nV.x * nV.y) * (1 - cos(t)) - (nV.z * sin(t));
		rotateMatrrix[2][0] = (nV.x * nV.z) * (1 - cos(t)) + (nV.y * sin(t));
		rotateMatrrix[0][1] = (nV.y * nV.x) * (1 - cos(t)) + (nV.z * sin(t));
		rotateMatrrix[1][1] = cos(t) + (nV.y * nV.y * (1 - cos(t)));
		rotateMatrrix[2][1] = (nV.y * nV.z) * (1 - cos(t)) - (nV.x * sin(t));
		rotateMatrrix[0][2] = (nV.z * nV.x) * (1 - cos(t)) - (nV.y * sin(t));
		rotateMatrrix[1][2] = (nV.x * nV.y) * (1 - cos(t)) + (nV.x * sin(t));
		rotateMatrrix[2][2] = cos(t) + (nV.z * nV.z * (1 - cos(t)));
		
		return rotateMatrrix;
	}

	glm::mat4 transpose3x3(const glm::mat4& A) {
		int i, j;
		glm::mat4 result = glm::mat4(1.0f);

		for (i = 0; i < 3; ++i) {
			for (j = 0; j < 3; j++) {
				result[j][i] = A[i][j];
			}
		}

		return result;
	}

	glm::vec4 cross(const glm::vec4 &u, const glm::vec4 &v) {
		glm::vec4 result;

		result[0] = u[1] * v[2] - u[2] * v[1];
		result[1] = u[2] * v[0] - u[0] * v[2];
		result[2] = u[0] * v[1] - u[1] * v[0];
		result[3] = 0;

		return result;
	}
}
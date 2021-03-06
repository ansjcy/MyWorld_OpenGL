#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include "complex.h"
#include "vector.h"
#include "fft.h"
#include "glhelper.h"
#include "glm-0.9.2.6\glm\glm.hpp"
#include "glm-0.9.2.6\glm\gtc\matrix_transform.hpp"
#include "glm-0.9.2.6\glm\gtc\type_ptr.hpp"
struct vertex_ocean {
	GLfloat   x, y, z; // vertex
	GLfloat  nx, ny, nz; // normal
	GLfloat   a, b, c; // htilde0
	GLfloat  _a, _b, _c; // htilde0mk conjugate
	GLfloat  ox, oy, oz; // original position
};




struct complex_vector_normal {	// structure used with discrete fourier transform
	complex h;		// wave height
	vector2 D;		// displacement
	vector3 n;		// normal
};




class cOcean {
public:
	bool geometry;				// flag to render geometry or surface

	float g;				// gravity constant
	int N, Nplus1;				// dimension -- N should be a power of 2
	float A;				// phillips spectrum parameter -- affects heights of waves
	vector2 w;				// wind parameter
	float length;				// length parameter
	complex *h_tilde,			// for fast fourier transform
		*h_tilde_slopex, *h_tilde_slopez,
		*h_tilde_dx, *h_tilde_dz;
	cFFT *fft;				// fast fourier transform

	vertex_ocean *vertices;			// vertices for vertex buffer object
	unsigned int *indices;			// indicies for vertex buffer object
	unsigned int indices_count;		// number of indices to render
	GLuint vbo_vertices, vbo_indices;	// vertex buffer objects

	GLuint glProgram, glShaderV, glShaderF;	// shaders
	GLint vertex, normal, texture, light_position, projection, view, model;	// attributes and uniforms

	cOcean(const int N, const float A, const vector2 w, const float length, bool geometry);
	~cOcean();
	float dx, dz;
	void release();

	float dispersion(int n_prime, int m_prime);		// deep water
	float phillips(int n_prime, int m_prime);		// phillips spectrum
	complex hTilde_0(int n_prime, int m_prime);
	complex hTilde(float t, int n_prime, int m_prime);
	complex_vector_normal h_D_and_n(vector2 x, float t);
	void evaluateWaves(float t);
	void evaluateWavesFFT(float t);
	void render(float t, glm::vec3 light_pos, glm::mat4 Projection, glm::mat4 View, glm::mat4 Model, bool use_fft,bool iswire);
	void afterGenerate();
	void driftOcean(float deltaX, float deltaZ);
};



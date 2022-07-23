#include "Mesh.hpp"

void Mesh::make_cube(glm::vec3 size)
{
	vert_count = 36;

	mesh = (float*)malloc(sizeof(float) * vert_count * 5);

	float width  = size.x / (float)2;
	float height = size.y / (float)2;
	float depth = size.z / (float)2;

	float nwidth = width * -1;
	float nheight = height * -1;
	float ndepth = depth * -1;

	//vertexes
	glm::vec3 ufl(nwidth, height, depth); //upper front left
	glm::vec3 ufr(width,  height, depth); //upper front right
	glm::vec3 ubr(width,  height, ndepth); //upper back right
	glm::vec3 ubl(nwidth, height, ndepth); //upper back left

	glm::vec3 lfl(nwidth, nheight, depth); //lower front left
	glm::vec3 lfr(width,  nheight, depth); //lower front right
	glm::vec3 lbr(width,  nheight, ndepth); //lower back right
	glm::vec3 lbl(nwidth, nheight, ndepth); //lower back left

	float* cur = mesh;

	//top
	cur = copy_vertex3f(cur, ufl); cur = copy_tex2f(cur, 0, 0);
	cur = copy_vertex3f(cur, ufr); cur = copy_tex2f(cur, 1, 0);
	cur = copy_vertex3f(cur, ubr); cur = copy_tex2f(cur, 1, 1);
	cur = copy_vertex3f(cur, ubr); cur = copy_tex2f(cur, 1, 1);
	cur = copy_vertex3f(cur, ubl); cur = copy_tex2f(cur, 0, 1);
	cur = copy_vertex3f(cur, ufl); cur = copy_tex2f(cur, 0, 0); 
	
	//back
	cur = copy_vertex3f(cur, ubl); cur = copy_tex2f(cur, 1, 1);
	cur = copy_vertex3f(cur, ubr); cur = copy_tex2f(cur, 0, 1);
	cur = copy_vertex3f(cur, lbr); cur = copy_tex2f(cur, 0, 0);
	cur = copy_vertex3f(cur, lbr); cur = copy_tex2f(cur, 0, 0);
	cur = copy_vertex3f(cur, lbl); cur = copy_tex2f(cur, 1, 0);
	cur = copy_vertex3f(cur, ubl); cur = copy_tex2f(cur, 1, 1);

	//bottom
	cur = copy_vertex3f(cur, lbl); cur = copy_tex2f(cur, 0, 0);
	cur = copy_vertex3f(cur, lbr); cur = copy_tex2f(cur, 1, 0);
	cur = copy_vertex3f(cur, lfr); cur = copy_tex2f(cur, 1, 1);
	cur = copy_vertex3f(cur, lfr); cur = copy_tex2f(cur, 1, 1);
	cur = copy_vertex3f(cur, lfl); cur = copy_tex2f(cur, 0, 1);
	cur = copy_vertex3f(cur, lbl); cur = copy_tex2f(cur, 0, 0);

	//front
	cur = copy_vertex3f(cur, ufl); cur = copy_tex2f(cur, 0, 1);
	cur = copy_vertex3f(cur, lfl); cur = copy_tex2f(cur, 0, 0);
	cur = copy_vertex3f(cur, lfr); cur = copy_tex2f(cur, 1, 0);
	cur = copy_vertex3f(cur, lfr); cur = copy_tex2f(cur, 1, 0);
	cur = copy_vertex3f(cur, ufr); cur = copy_tex2f(cur, 1, 1);
	cur = copy_vertex3f(cur, ufl); cur = copy_tex2f(cur, 0, 1);

	//left
	cur = copy_vertex3f(cur, lfl); cur = copy_tex2f(cur, 1, 0);
	cur = copy_vertex3f(cur, lbl); cur = copy_tex2f(cur, 0, 0);
	cur = copy_vertex3f(cur, ubl); cur = copy_tex2f(cur, 0, 1);
	cur = copy_vertex3f(cur, ubl); cur = copy_tex2f(cur, 0, 1);
	cur = copy_vertex3f(cur, ufl); cur = copy_tex2f(cur, 1, 1);
	cur = copy_vertex3f(cur, lfl); cur = copy_tex2f(cur, 1, 0);

	//right
	cur = copy_vertex3f(cur, ufr); cur = copy_tex2f(cur, 0, 1);
	cur = copy_vertex3f(cur, ubr); cur = copy_tex2f(cur, 1, 1);
	cur = copy_vertex3f(cur, lbr); cur = copy_tex2f(cur, 1, 0);
	cur = copy_vertex3f(cur, lbr); cur = copy_tex2f(cur, 1, 0);
	cur = copy_vertex3f(cur, lfr); cur = copy_tex2f(cur, 0, 0);
	cur = copy_vertex3f(cur, ufr); cur = copy_tex2f(cur, 0, 1);
}
#include "snjVertex.h"





snjVertexr::snjVertexr() : snjVertexr(SNJ_NAN, SNJ_NAN, SNJ_NAN, SNJ_NAN, SNJ_NAN, SNJ_NAN, SNJ_NAN, SNJ_NAN) {}
snjVertexr::snjVertexr(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _s, float _t) :
	pos(_x, _y, _z),
	norm(_nx, _ny, _nz),
	tcoo(_s, _t),

	x(pos.x),
	y(pos.y),
	z(pos.z),

	nx(norm.x),
	ny(norm.y),
	nz(norm.z),

	s(tcoo.s),
	t(tcoo.t)
{}
snjVertexr::snjVertexr(glm::vec3 _pos, glm::vec3 _norm, glm::vec2 _tcoor) :
	pos(_pos),
	norm(_norm),
	tcoo(_tcoor),

	x(pos.x),
	y(pos.y),
	z(pos.z),

	nx(norm.x),
	ny(norm.y),
	nz(norm.z),

	s(tcoo.s),
	t(tcoo.t)
{}

snjVertexr::snjVertexr(aiVector3D _pos, aiVector3D _norm, aiVector3D _tcoor) : 
	snjVertexr(glm::vec3(_pos.x, _pos.y, _pos.z), glm::vec3(_norm.x, _norm.y, _norm.z), glm::vec2(_tcoor.x, _tcoor.y))
{}

bool snjVertexr::isPos()
{
	if (std::isnan(x) || std::isnan(y) || std::isnan(z))
		return false;
	else
		return true;
}

bool snjVertexr::isNorm()
{
	if (std::isnan(nx) || std::isnan(ny) || std::isnan(nz))
		return false;
	else
		return true;
}

bool snjVertexr::isTex()
{
	if (std::isnan(s) || std::isnan(t))
		return false;
	else
		return true;
}

unsigned int snjVertexr::CalcStride()
{
	unsigned int stride = 0;
	if (this->isPos())
		stride += 3;
	if (this->isNorm())
		stride += 3;
	if (this->isTex())
		stride += 2;

	return stride;
}



std::ostream& operator<<(std::ostream& os, const snjVertexr& vertex) noexcept
{
	os << "[(" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")";
	os << "(" << vertex.nx << ", " << vertex.ny << ", " << vertex.nz << ")";
	os << "(" << vertex.s << ", " << vertex.t << ")]";
	return os;
}

std::ostream& operator<<(std::ostream& os, const snjVertex& vertex) noexcept
{
	os << "[(" << vertex.pos.x << ", " << vertex.pos.y << ", " << vertex.pos.z << ")";
	os << "(" << vertex.nor.x << ", " << vertex.nor.y << ", " << vertex.nor.z << ")";
	os << "(" << vertex.tex.s << ", " << vertex.tex.t << ")]";
	return os;
}

snjVertex::snjVertex() :
	snjVertex(
		glm::vec3(SNJ_NAN, SNJ_NAN, SNJ_NAN), 
		glm::vec3(SNJ_NAN, SNJ_NAN, SNJ_NAN), 
		glm::vec2(SNJ_NAN, SNJ_NAN)
	)
{}

snjVertex::snjVertex(float _x, float _y, float _z, float _nx, float _ny, float _nz, float _s, float _t) :
	snjVertex(glm::vec3(_x, _y, _z), glm::vec3(_nx, _ny, _nz), glm::vec2(_s, _t))
{}

snjVertex::snjVertex(glm::vec3 _pos, glm::vec3 _norm, glm::vec2 _tcoor) :
	pos(_pos),
	nor(_norm),
	tex(_tcoor)
{}

snjVertex::snjVertex(aiVector3D _pos, aiVector3D _norm, aiVector3D _tcoor) :
	snjVertex(_pos.x, _pos.y, _pos.z, _norm.x, _norm.y, _norm.z, _tcoor.x, _tcoor.y)
{}

bool snjVertex::isPos()
{
	if (std::isnan(pos.x) || std::isnan(pos.y) || std::isnan(pos.z))
		return false;
	else
		return true;
}

bool snjVertex::isNorm()
{
	if (std::isnan(nor.x) || std::isnan(nor.y) || std::isnan(nor.z))
		return false;
	else
		return true;
}

bool snjVertex::isTex()
{
	if (std::isnan(tex.x) || std::isnan(tex.y))
		return false;
	else
		return true;
}

unsigned int snjVertex::CalcStride()
{
	unsigned int stride = 0;
	if (this->isPos())
		stride += 3;
	if (this->isNorm())
		stride += 3;
	if (this->isTex())
		stride += 2;

	return stride;
}

bool snjVertex::operator==(const snjVertex& vertex) const
{
	if (
		this->pos == vertex.pos ||
		this->nor == vertex.nor ||
		this->tex == vertex.tex
	)
		return true;
	else
		return false;
}


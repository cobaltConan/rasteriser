#include "objects.h"

cube::cube()
{
	verticies = 
	{
		Vector3d{ 1,  1,  1},
		Vector3d{-1,  1,  1},
		Vector3d{-1, -1,  1},
		Vector3d{ 1, -1,  1},
		Vector3d{ 1,  1, -1},
		Vector3d{-1,  1, -1},
		Vector3d{-1, -1, -1},
		Vector3d{ 1, -1, -1}
	};

	triangles = 
	{
		Triangle{0, 1, 2, RED},
		Triangle{0, 2, 3, RED},
		Triangle{4, 0, 3, GREEN},
		Triangle{4, 3, 7, GREEN},
		Triangle{5, 4, 7, BLUE},
		Triangle{5, 7, 6, BLUE},
		Triangle{1, 5, 6, YELLOW},
		Triangle{1, 6, 2, YELLOW},
		Triangle{4, 5, 1, PURPLE},
		Triangle{4, 1, 0, PURPLE},
		Triangle{2, 6, 7, CYAN},
		Triangle{2, 7, 3, CYAN},
	};
}

cube instance::returnModel() // use overloading to figure out a way to return different types, or maybe superclasses?
{
	switch (this->model)
	{
		case graphicalObject::cube:
			cube theCube;
			return theCube;
	}
}


void scene::addInstance(const instance& inst)
{
	this->instances.emplace_back(inst);
}

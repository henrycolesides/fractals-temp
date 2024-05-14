// Scene.h
// Scene class encapsulate scene object data in shape and light vectors
// Provides const getters for some renderer's access to objects in the scene
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <typeinfo>
#include "SceneObjects.h"


class Scene
{
	public:
		Scene();
		Scene(const std::vector<Shape *> & shapes, const std::vector<Light *> & lights);
		~Scene();
		
		const std::vector<Shape *> & get_shapes() const;
		const std::vector<Light *> & get_lights() const;
		
	private:
		std::vector<Shape *> shapes;
		std::vector<Light *> lights;
};

#endif // Scene.h
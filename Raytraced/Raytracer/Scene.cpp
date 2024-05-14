// Scene.cpp
// Provides definitions of scene class which contains a scene's shape and light data

#include "Scene.h"

Scene::Scene() : shapes({}), lights({}) {}

Scene::Scene(const std::vector<Shape*>& shapes, const std::vector<Light*>& lights) : shapes({}), lights({})
{
	for (auto shape : shapes)
	{
		Sphere * sp_ptr = dynamic_cast<Sphere *>(shape);	
		if (sp_ptr) this->shapes.push_back(new Sphere(*sp_ptr));

		Triangle* tri_ptr = dynamic_cast<Triangle*>(shape);
		if (tri_ptr) this->shapes.push_back(new Triangle(*tri_ptr));
	}

	for (auto light : lights)
	{
		AmbientLight * al_ptr = dynamic_cast<AmbientLight *>(light);
		if (al_ptr) this->lights.push_back(new AmbientLight(* al_ptr));
	
		DirectionalLight* dl_ptr = dynamic_cast<DirectionalLight*>(light);
		if (dl_ptr) this->lights.push_back(new DirectionalLight(*dl_ptr));
	
		PointLight * pl_ptr = dynamic_cast<PointLight *>(light);
		if (pl_ptr) this->lights.push_back(new PointLight(* pl_ptr));
	}
}

Scene::~Scene() 
{
	while (!shapes.empty())
	{
		delete shapes.back();
		shapes.pop_back();
	}

	while (!lights.empty())
	{
		delete lights.back();
		lights.pop_back();
	}
	return;  
}

const std::vector<Shape *> & Scene::get_shapes() const
{
	return shapes;
}

const std::vector<Light *> & Scene::get_lights() const
{
	return lights;
}

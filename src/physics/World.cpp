#include "../include/physics/World.hpp"

namespace physics
{
	void World::AddObject(const Object& o)
	{
		objects.emplace_back(new Object(o));
		objects.at(objects.size() - 1)->Start();
	}

	void World::RemoveObject(const Object& o)
	{
		for (size_t i = 0; i < objects.size(); i++)
		{
			if (o == *objects.at(i))
			{
				objects.at(i)->Destroy();
				objects.erase(objects.begin()+i);
				break;
			}
		}
	}

	void World::Update()
	{
		auto recursiveUpdate = [&](Object* o)
		{
			o->Update();
			for (auto& child: o->children)
				child->Update();
		};
		for (auto& obj: objects)
			recursiveUpdate(obj);
	}
}
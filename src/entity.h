#pragma once
#include "cube.h"
#include "rectangle.h"

namespace entities
{
	class Entity
	{
		public:
			Entity(shape::Shape *shape): shape(shape) {};
			void render() {shape->render();};
		private:
			shape::Shape *shape;
	};

}

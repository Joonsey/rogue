#pragma once
#include "shape.h"

namespace world
{
	class Tile
	{
		public:
			Tile(shape::Shape *shape): shape(shape) {};
			~Tile() {};
			void render() {shape->render();};
		private:
			shape::Shape *shape;
	};

}

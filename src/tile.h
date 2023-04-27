#pragma once
#include "shape.h"

namespace world
{
	class Tile
	{
		public:
			Tile(shape::Shape *shape): shape(shape) {};
			~Tile() {};
			void render() const {shape->render();};
			bool operator==(const Tile& other) const {
				return (shape == other.shape);
			}
			bool operator!=(const Tile& other) const {
				return !(*this == other);
			}
		private:
			shape::Shape *shape;
	};

}

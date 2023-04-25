#pragma once
#include "tile.h"
#include <vector>
#include "cube.h"

namespace world
{

	typedef std::vector<glm::vec3> MAP_DATA;
	class Map
	{
		public:
			Map() {};
			void render_tiles()
			{
				for (auto tile : m_tiles)
					tile.render();
			}
			void add_tile(Tile &tile)
			{
				m_tiles.push_back(tile);
			}
			// seeds the map with world data.
			// expected format is: [X, Y, Z]
			// will create cubes in the specified locations
			void seed_world(MAP_DATA &world_data)
			{
				for (auto position : world_data)
				{
					// the cube needs to be malloced up such that a new pointer is created.
					shape::Cube* cube = new shape::Cube(
							position,
							1.f,
							glm::vec3(0.0f, 2.0f, 1.0f));
					world::Tile new_tile(cube);

					add_tile(new_tile);
				}
			}

		private:
			std::vector<Tile> m_tiles;
	};

}

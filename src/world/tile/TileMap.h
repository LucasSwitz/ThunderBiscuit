#ifndef TILEMAP_H
#define TILEMAP_H

#include <streambuf>
#include <fstream>
#include <algorithm>
#include <math.h>
#include "src/world/tile/Tile.h"
#include "src/world/tile/LuaTileFactory.h"

#define BLANK_TILE_SCRIPT "BlankTile"

/**
Purpose: TileMap is a container for a grid of tiles. The tile grid can
be populated via a file, a std::vector, or an array. The TileMap is responsible
enabling and disabling all of its Tiles' graphics components.
**/

class TileMap
{
public:
    ~TileMap();

    void LoadFromArray(int** map, int rows, int columns);

    void LoadFromVector(std::vector<std::vector<int>> map);

    void LoadFromFile(std::string file_path);

    void SaveToFile(std::string file_name);

    //split helpers
    std::vector<std::string> split(const std::string &s, char delim) ;

    template<typename T>
    void split(const std::string &s, char delim, T result);

    //add all tiles to CUB.
    void Show();

    //remove all tiles from CUB.
    void Hide();

    bool IsActive();

    void Unload();

    Tile* TileAt(int x, int y);

    void TilesInRange(int first_x, int first_y, int last_x, int last_y, std::list<Tile*>& tiles);

    static int CoordToColumn(int x);

    static int CoordToRow(int y);

    static void Blank(TileMap&,int width, int height);

    std::string& GetFile();

    int HeightPx();

    int WidthPx();

    void Erase();

    void Copy(TileMap& map)
    {
        for(int i = 0; i < map._tiles.size(); i++)
        {
            auto row = map._tiles[i];
            for(Tile* tile : row)
            {
                if(_tiles.size() < i + 1)
                    _tiles.push_back(std::vector<Tile*>());
                _tiles[i].push_back(tile->Clone());
            }
        }
    }

 private:
    std::vector<std::vector<Tile*>> _tiles;
    std::string _file_name;
    bool _active = false;
};
#endif
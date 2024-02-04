/* Class that will save all objects from canvas to a .pnx format
(my own format that will have specification)

*/
#include "iostream";
#include "fstream"
#include "sstream"
#include "Controllers/Controller.h"
class Saver {
public:
	static void Save(const std::string& filename);
	static void Open(const std::string& filename);
};
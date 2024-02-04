#include "Saver.h"
#include "Objects/Line.h"
#include "Objects/Rectangle.h"
#include "Objects/Triangle.h"
#include "Objects/Triangle.h"
#include "Objects/Ellipse.h"
/* 
Save format
type of object(get name of derived class)
start point(float x, float y)
end point(float x, float y)
color(float r, float g, float b)
line width(float)
is filled(bool)
*/

void Saver::Save(const std::string& filename){
	// get controller objects and save them to file
	for (const auto& object : Controller::getObjects()) {
		// get object type
		std::string type = object->getType();
		// get start point
		sf::Vector2f start = object->getStart();
		// get end point
		sf::Vector2f end = object->getEnd();
		// get color
		sf::Color color = object->getColor();
		// get line width
		float lineWidth = object->getLineWidth();
		// get is filled
		bool isFilled = object->getFilled();
		// save to file
		std::ofstream file;
		file.open(filename, std::ios::app);
		file << type << " " << start.x << " " << start.y << " " << end.x << " " << end.y << " " << color.r << " " << color.g << " " << color.b << " " << lineWidth << " " << isFilled << std::endl;
		file.close();
	}
}

void Saver::Open(const std::string& filename){
	// read file and create objects
	std::ifstream file;
	file.open(filename);
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string type;
		float start_x, start_y, end_x, end_y, r, g, b, lineWidth;
		bool isFilled;
		iss >> type >> start_x >> start_y >> end_x >> end_y >> r >> g >> b >> lineWidth >> isFilled;
		sf::Vector2f start(start_x, start_y);
		sf::Vector2f end(end_x, end_y);
		sf::Color color(r, g, b);
		// create object
		if (type == "Line") {
			Controller::AddObject(new Line(start, end, color, lineWidth, isFilled));
		}
		else if (type == "Rectangle") {
			Controller::AddObject(new Rectangle(start, end, color, lineWidth, isFilled));
		}
		else if (type == "Ellipse") {
			Controller::AddObject(new Ellipse(start, end, color, lineWidth, isFilled));
		}else if(type == "Triangle")
{
			Controller::AddObject(new Triangle(start, end, color, lineWidth, isFilled));
		}
	}
	file.close();
}

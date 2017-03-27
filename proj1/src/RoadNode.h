#ifndef ROADNODE_H_
#define ROADNODE_H_

#include <string>
using namespace std;

class RoadNode
{
private:
	int id;
	float degLat, radLat, degLong, radLong;

public:
	RoadNode(int id, float degLat, float radLat, float degLong, float radLong);
	int getID() const;
	string getDegLocation() const;
	string getRadLocation() const;
};

bool operator==(const RoadNode n1, const RoadNode n2);

struct road_t
{
	string name;
	int id;
	bool twoWay;
};

#endif /* ROADNODE_H_ */

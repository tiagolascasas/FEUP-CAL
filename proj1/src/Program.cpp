/*
 * Program.cpp
 *
 *  Created on: 21/03/2017
 *      Author: Tiago
 */

#include "Program.h"
#include "Exceptions.h"
#include <fstream>
#include <sstream>
#include <algorithm>

Program::Program(char** files)
{
	this->gv = new GraphViewer(600, 600, true);
	this->running = true;

	loadGraph(files[1], files[2], files[3]);
	loadMarkets(files[4]);
}

void Program::loadGraph(char* nodesFile, char* roadInfoFile, char* roadFile)
{
	ifstream nodes(nodesFile);
	if (!nodes.is_open())
		throw new FileNotFound(nodesFile);

	ifstream roadInfo(roadInfoFile);
	if (!roadInfo.is_open())
		throw new FileNotFound(roadInfoFile);

	ifstream roads(roadFile);
	if (!roads.is_open())
		throw new FileNotFound(roadFile);

	string s;

	while (getline(nodes, s))
	{
		istringstream ss(s);
		int id, latDeg, latRad, lonDeg, lonRad;
		char marker;
		ss >> id >> marker >> latDeg >> marker >> latRad;
		ss >> marker >> lonDeg >> marker >> lonRad;
		RoadNode n(id, latDeg, latRad, lonDeg, lonRad);
		graph.addVertex(n);
	}

	while (getline(roadInfo, s))
	{
		road_t road;
		istringstream ss(s);
		char marker;
		string aux;
		ss >> road.id >> marker;
		getline(ss, aux, ';');
		if (aux == "")
			road.name = "Undefined street name";
		else
			road.name = aux;
		ss >> marker >> aux;
		if (aux == "False")
			road.twoWay = false;
		else
			road.twoWay = true;
		r.push_back(road);
	}

	while (getline(roads, s))
	{
		int id, v1, v2;
		char marker;
		istringstream ss(s);
		ss >> id >> marker >> v1 >> marker >> v2;
		road_t road;
		for (int i = 0; i < r.size(); i++)
		{
			if (r.at(i).id == id)
			{
				road = r.at(i);
				break;
			}
		}

		RoadNode aux1(v1, 0, 0, 0, 0), aux2(v2, 0, 0, 0, 0);
		graph.addEdge(aux1, aux2, 1, id);
		if (road.twoWay)
			graph.addEdge(aux2, aux1, 1, id);
	}

	nodes.close();
	roadInfo.close();
	roads.close();
}

void Program::loadMarkets(char* marketsFile)
{
	ifstream markets(marketsFile);
	if (!markets.is_open())
		throw new FileNotFound(marketsFile);

	//...
	//...

	markets.close();
}

void Program::generatePurchases(int n)
{

}

void Program::run()
{
	while (running)
	{
		displayMenu();
		cout << "Option: ";
		int choice;
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			displayGraphStatistics(graph);
			displayGraph(graph);
			break;
		}
		case 2:
			cout << "\nNumber of purchases to generate:";
			int n;
			cin >> n;
			generatePurchases(n);
			cout << n << " purchases generated\n";
			break;
		case 0:
			running = false;
			break;
		default:
			break;
		}
	}
}

void Program::displayMenu()
{
	cout << endl;
	cout << "1. Display the whole graph\n";
	cout << "2. Generate random clients/purchases\n";
	cout << "3. Check connectivity between all clients and all markets\n";
	cout << "4. Distribute from a single market to all clients\n";
	cout << "5. Distribute from all markets to all clients\n";
	cout << "0. Quit program\n";
	cout << endl;
}

void Program::displayGraph(Graph<RoadNode> g)
{
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");
	gv->defineEdgeCurved(true);
	for (int i = 0; i < g.getVertexSet().size(); i++)
	{
		gv->addNode(g.getVertexSet().at(i)->getInfo().getID());
		gv->setVertexSize(g.getVertexSet().at(i)->getInfo().getID(), 1);
	}
	int edgeID = 0;
	for (int i = 0; i < g.getVertexSet().size(); i++)
	{
		Vertex<RoadNode>* n = g.getVertexSet().at(i);
		for (int j = 0; j < n->getAdj().size(); j++)
		{
			int id1 = n->getInfo().getID();
			int id2 = n->getAdj().at(j).getDest()->getInfo().getID();
			gv->addEdge(edgeID, id1, id2, EdgeType::DIRECTED);
		//	gv->setEdgeLabel(edgeID, n->getAdj().at(i).)
			edgeID++;
		}
	}
}

void Program::displayGraphStatistics(Graph<RoadNode> g)
{
	cout << "\nGraph statistics: " << g.getNumVertex() << " nodes and ";
	int nEdges = 0;
	for (int i = 0; i < g.getVertexSet().size(); i++)
		nEdges += g.getVertexSet().at(i)->getAdj().size();
	cout << nEdges << " edges\n";
}

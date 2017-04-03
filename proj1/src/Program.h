#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "Graph.h"
#include "graphviewer.h"
#include "Purchase.h"
#include "RoadNode.h"
#include <string>

class Program
{
private:
	GraphViewer* gv;
	Graph<RoadNode> graph;
	vector<road_t> r;
	vector<RoadNode> markets;
	vector<string> marketNames;
	vector<Purchase> purchases;
	bool running;
	float avgVelocity;

	void loadGraph(char* nodesFile, char* roadInfoFile, char* roadFile);
	void loadMarkets(char* marketsFile);
	void displayMenu();
	void displayGraphStatistics(Graph<RoadNode> g);
	void displayGraph(Graph<RoadNode> g);
	void displayMarketsInfo();
	void displayPurchasesInfo();
	void generatePurchases(int n);
	void singleMarketSingleClient();
	void checkValidMarkets();
	int getIndexOfMarket(RoadNode m);
	void displayConnectivity();
	void allMarketsSingleClient();
	int calculateTime(int length);
	string getMarketName(int idx);
	string getMarketName(RoadNode n);
	void displaySubGraph(vector<Vertex<RoadNode>* > path);

public:
	Program(char** files);
	void run();
};


#endif /* PROGRAM_H_ */

#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H
#include <string>
using namespace std;

/* YUNUS EMRE TASCI/25467 CS 204 SPRING 2018-2019 HOMEWORK 3 LINKED LIST HEADER FILE*/


struct neighborNode {  


	string neighborName;      
	neighborNode * next; 
	neighborNode::neighborNode()
	{}

	neighborNode::neighborNode(const string &s, neighborNode * link)
		: neighborName(s), next(link)
	{} }; 

struct houseNode {  
	string houseName;    
	neighborNode * neighborListHead;   
	houseNode * next; 
	houseNode::houseNode()
	{}
	houseNode::houseNode(const string &s, houseNode * link, neighborNode * nlink)
		: houseName(s), next(link),neighborListHead(nlink)
	{} };


class linkedlist { 
public:  linkedlist();  
		 void addHouseNode(string hname);  //adds house node to the map with the given name
		 bool addNeighborNode (string hname, string nname);  // adds neigbor to the given house name
		 void printAll();   // prints all the map
		 bool hnExists(string hname); //Checks if the hous name exists
		 bool nnExists(string hname, string nname);  // Checks if the hosue is neighboring the given neighorname
		 void deleteAll();  //to deallocate all dynamic data  //other member functions… 
		 bool annex(string annexer, string annexed);
		 void changenames(string annexer, string annexed);
		 void deleteHouse (string tobedeleted);//Deletes house with the given name and its neighbors
		 void ownNeighbor();
		 void deleteduplicates();//Checks if a house node is neighboring with the same house more than once than deletes it
		 bool isFound(string annexer, string annexed);
		 bool pathcontrol(string path1, string path2);// checks if the path can be followed or not ,if not prompts appropriate message
private:  houseNode * head;  // any helper functions you see necessary  // ... }; 
		 };
#endif
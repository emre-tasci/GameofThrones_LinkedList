#include <iostream>
#include "etasci_Tasci_YunusEmre_hw3_linkedlist.h"
using namespace std;



/* YUNUS EMRE TASCI/25467 CS 204 SPRING 2018-2019 HOMEWORK 3 LINKED LIST CPP FILE*/




linkedlist::linkedlist()
{
	head=NULL;
}

bool linkedlist::hnExists(string hname) {//Checks if the hous name exists
	houseNode *ptr = head;
	while (ptr != NULL) {
		if (ptr->houseName == hname) {
			return true;
		}
		ptr = ptr->next;
	}
	return false;
}

bool linkedlist::nnExists(string hname, string nname) {// Checks if the hosue is neighboring the given neighorname
	houseNode *ptr = head;

	while (ptr != NULL) {//search through house nodes
		if (ptr->houseName == hname){//if equal
			neighborNode * iter=ptr->neighborListHead;//go to the neighborlist head of found house name
			while(iter!=NULL){  
				{
					if(iter->neighborName ==nname){//check if exists
						return true;
					}
					iter=iter->next;
				}
			}
		}
		ptr = ptr->next;
	}

	return false;
}

bool linkedlist::pathcontrol(string path1, string path2){//Controls the path for tyrion
	houseNode * ptr = head;
	if (hnExists(path1)==false){//if the first entry does not exists
		cout<< path1 << " does not exist in the map. ! \nPath search failed!  "<<endl;
		return false;
	}
	if (hnExists(path2)==false){//if the second entry does not exists
		cout<< path2<< "  does not exist in the map. ! \nPath search failed! "<<endl;
		return false;
	}

	if (path1==path2){//if first equals to the second
		cout<<"You are already in "<< path1<<endl;
		return false;
	}
	if (nnExists(path1,path2)==false){//if they are not neighbors
		cout<<path2<< " is not a neighbor of "<< path1<< "\nPath search failed! "<<endl;
		return false;
	}
	else{
		cout<<"Path found between " <<  path1 << " and "<< path2<<endl;
		return true;

	}		
	
}

		void linkedlist::addHouseNode(string hname){//adds house node to the map with the given name
			houseNode * ptr = head;
			houseNode *temp = new houseNode(hname, NULL,NULL);//new node
			if (hnExists(hname)==true){// if house node exists quit
				return ;
			}
			else{
				if(head == NULL)//if house is goin to be added to  head
				{
					head = temp;
				}
				else
				{
					while(ptr->next != NULL)
					{
						ptr = ptr->next;
					}
					ptr->next = temp;
				}
			}
		}


		bool linkedlist::addNeighborNode (string hname, string nname){// adds neigbor to the given house name
			houseNode*ptr= head;	
			neighborNode *temp=new neighborNode(nname,NULL);
			if(nnExists(hname,nname)==true){//if already exists quit
				return true;
			}
			else{
				while(ptr!= NULL)
				{
					if (ptr->houseName==hname)
					{	
						if(ptr->neighborListHead== NULL)
						{
							ptr->neighborListHead = temp;
						}
						else{
							neighborNode *temp2=new neighborNode(nname,NULL);
							neighborNode* iter =ptr->neighborListHead;
							while(iter->next!=NULL){
								iter=iter->next;
							}
							iter->next=temp2;
						}
					}
					ptr=ptr->next;
				}
				return false;
			}
		}

		void linkedlist::deleteHouse (string tobedeleted){//Deletes house with the given name and its neighbors

			houseNode * ptr= head;

			while (ptr != NULL) {
				if (ptr->houseName == tobedeleted){
					neighborNode * iter =ptr->neighborListHead;
					neighborNode * temp;				
					while (iter!= NULL) {				
						temp = iter->next;			
						delete iter;
						iter = temp;
					}

					if(ptr==head){
						head=head->next;
						delete ptr;
						return;
					}
					else{
						houseNode *temp2=head;
						while(temp2->next->houseName!=tobedeleted){
							temp2=temp2->next;
						}
						temp2->next=ptr->next;
						delete ptr;
						return;
					}
				}
				ptr= ptr->next;
			}
		}
		void linkedlist::deleteduplicates(){//Checks if a house node is neighboring with the same house more than once than deletes it
			houseNode * ptr= head;

			while (ptr!= NULL) {
				neighborNode *ptr1= ptr->neighborListHead;
				neighborNode *ptr2= ptr->neighborListHead;
				while(ptr1!=NULL){
					neighborNode *prev=ptr1;
					ptr2=ptr1->next;
					while(ptr2!=NULL){

						if(ptr1->neighborName==ptr2->neighborName)
						{
							prev->next=ptr2->next;
							delete ptr2;
							break;
						}
						prev=ptr2;
						ptr2=ptr2->next;
					}

					ptr1=ptr1->next;

				}
				ptr=ptr->next;
			}
		}
		void linkedlist ::ownNeighbor(){// Checks if a house is neighbor to itself after annexation if yes then deletes all occurences
			houseNode * ptr= head;
			while (ptr!= NULL) {
				string housename=ptr->houseName;
				neighborNode * iter =ptr->neighborListHead;
				while (iter!=NULL){
					if (iter->neighborName==housename){
						neighborNode * temp;	
						if(iter == ptr->neighborListHead)
						{
							ptr->neighborListHead=ptr->neighborListHead->next;
							delete iter;
							return;
						}
						else{
							neighborNode * iter2 =ptr->neighborListHead;
							while(iter2->next->neighborName!=housename){
								iter2=iter2->next;
							}
							iter2->next=iter->next;
							delete iter;
							return;
						}
					}
					iter=iter->next;
				}
				ptr=ptr->next;
			}

		}


		void linkedlist::changenames(string annexer, string annexed){// After annexation it changes the name of the annexed with annexer, in neighborlists of of the neighbors of annexed.
			houseNode * ptr= head;


			while (ptr!= NULL) {
				neighborNode * iter =ptr->neighborListHead;
				while (iter !=NULL){
					if (iter->neighborName==annexed)
					{
						iter->neighborName=annexer;
					}
					iter=iter->next;
				}
				ptr=ptr->next;
			}


			ownNeighbor();//check
			deleteduplicates();//check
		}
		void linkedlist::printAll()// Prints the map
		{
			cout<<endl;
			cout<<"######## MAP ########"<<endl; 
			houseNode* ptr = head;
			if(head == NULL)
			{
				cout << "List is empty" << endl;
			}
			else
			{
				while(ptr != NULL)
				{
					neighborNode * iter=ptr->neighborListHead;
					cout << ptr->houseName << ": ";

					while(iter!=NULL)
					{
						cout<< iter->neighborName << ", ";
						iter=iter->next;
					}
					cout <<endl;
					ptr = ptr->next;
				}
			}
			cout<<endl;
		}
		bool linkedlist::isFound(string annexer, string annexed){
			if (hnExists(annexer)==false){

				return false;
				if (hnExists(annexed)==false){

					return false;
				}
				return true;
			}
		}

		bool linkedlist::annex(string annexer, string annexed){
			houseNode* ptr = head;

			bool check =true;
			if (annexer == annexed)//if annexer and annexed are same
			{
				cout<< "A House cannot conquer itself! \nUpdate failed."<<endl;
				
				return false;
			}
			else{
				if (hnExists(annexer)==false){//if anenxer hosue does not exist
					cout<< annexer << " does not exist! \nUpdate failed."<<endl;
					return false;
				}
				else{
					if (hnExists(annexed)==false){//if annexed house does not exist
						cout<< annexed<< " does not exist! \nUpdate failed."<<endl;
						return false;
					}
					else{
						if (nnExists(annexer,annexed)==true){//if annexer and annexed are neighbors
							while(ptr != NULL)
							{
								if(ptr->houseName==annexer)//if ptr in annexer
								{
									houseNode* ptr1= head;
									while (ptr1!=NULL)//creating another pointer for finding annexed
									{
										if(ptr1->houseName==annexed){
											neighborNode* iter =ptr1->neighborListHead;// to traverse on neighborlist
											while(iter!=NULL){
												if (nnExists(annexer,iter->neighborName)==false){//if annexer and neighbors of annexed are not neigbors
													if (hnExists(annexer)==true){//if(iter->neighborName != annexer){
														addNeighborNode(annexer,iter->neighborName);

													}
												}
												iter=iter->next;
												ownNeighbor();
											}
											deleteHouse(annexed);//delete annexed house with its neighbors
											ownNeighbor();
											return true;
										}

										ptr1=ptr1->next;
									}
									return true;
								}
								ptr=ptr->next;
							}
						}
						else {

							cout<<"A house can only conquer a neighboring house!"<< annexer<<" is not a neighbor of "<< annexed <<". \nUpdate failed."<<endl;
							return false;
						}

					}
				}

			}

		}

		void linkedlist::deleteAll(){//Deletes all the map
		
		houseNode * ptr= head;
		houseNode * temp2;
			while (ptr != NULL) {
					neighborNode * iter =ptr->neighborListHead;
					neighborNode * temp;				
					while (iter!= NULL) {				
						temp = iter->next;			
						delete iter;
						iter = temp;
				}
								
				temp2 = ptr->next;			
				delete ptr;
				ptr = temp2;
			}
		}
			
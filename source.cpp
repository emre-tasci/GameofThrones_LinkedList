#include <iostream>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include "linkedlist.h"



using namespace std;

int main()
{

	linkedlist nightking;
	string filename;
	fstream input;
	string option=" ";
	cout<<"Please enter a file name: "<<endl;
	cin >> filename;
	input.open(filename);
	while(!(input.is_open()))//INPUT CHECK FOR FILE 
	{
		cout<<"Unable to open file."<<filename<<endl;
		cout<<"Please enter a file name: "<<endl;
		cin>> filename;
		input.open(filename);
	}
	cout<<"Successfully opened file " <<filename<<endl;//

	string hname;
	string nname;
	string line;
	cout<<"######## TOPOLOGY ######## "<<endl;

	while(getline(input,line))// CREATING THE MAP
	{

		istringstream reader (line);
		reader>>hname>>nname;
		cout<<"Processing "<<hname << " and "<<nname<<endl;
		nightking.addHouseNode(hname);//ADD  HOUSE WITH HNAME
		if (nightking.addNeighborNode(hname,nname)==true)//ADD NEIHGBOR
		{
			cout<< "Redundant information! An entry with "<< hname<<" and "<<nname<<" is already processed. "<<endl<<endl;
		}
		else
		{
			cout<<"Topology information successfully added. "<<endl<<endl;
		}
		nightking.addHouseNode(nname);//ADD HOUSE WITH NNAME
		nightking.addNeighborNode(nname,hname);//ADD NEIGHBOR WITH HNAME
	}

	nightking.printAll();

	string annexer,annexed;
	while(option!="3"){
		cout<<endl;
		cout<<"Please select an option [1-2-3]. \n 1. Annexation! War for the iron throne continues... \n 2. Tyrion must travel, do a path check for the famous imp. \n 3. Exit"<<endl;
		cin>>option;

		if (option == "1"){//ANNEXATION
			cout<<"Please enter two houses first the annexer and the annexed. (ex: Tyrell Stark). "<<endl;
			cin>>annexer>>annexed;
			if(nightking.annex(annexer,annexed)==true){
				cout<< annexer<< " conquered "<<annexed<<"!"<<endl;
				nightking.changenames(annexer,annexed);
				nightking.printAll();
			}

		}
		else if (option =="2"){//TYRION  TRAVELS
			cin.ignore();
			string path,path1,path2;
			cout<<"Please enter a path. (ex: Tyrell Martell Tully)"<<endl;
			getline(cin,path);
			string temp;
			istringstream iss(path);//GETTING THE INPUT AS WHOLE STRING
			int i=0;
			string p;
			iss>>path;// TAKING THE FIRST ONE MANUALLY
			path1=path;
			bool check=true;
			while (iss>>path){//THEN TAKING THE REST
				path2=path;
				if(nightking.pathcontrol(path1,path2)==false)
				{
					check=false;
					break;
				}	
				else{
				path1= path2;//UPDATE
				}
				}
			if(check==true){
				
				cout<<"Path search succeeded."<<endl;
			}
			}
			
		

		else if (option =="3"){
			nightking.deleteAll();
			cout<<"List deleted and program ended."<<endl;//END PROGRAM AND DELETE LINKED LIST
			return 0;
		}
		else{
			cout<<"Invalid option please select from the menu."<<endl; 

		}
	}

	return 0;
}


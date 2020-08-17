//Samuel P P Silveira, Fundação Universidade Federal do ABC, 2020
#include "Pythia8/Pythia.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <cstdio>
#include <cmath>

using namespace std;
using namespace Pythia8;

#define CHARM 4	
#define STRANGE 3
#define WBOSON 24


int main (int argc, char* argv[]) {

	if(argc != 5){
		cout<<"Not enough parameters were passed!"<<endl;
		return 1;
	}
	//Getting input file
	string inputFile = argv[1];
	int nEvent = stoi(argv[2],NULL,10);

	//Initializing Pythia
	Pythia pythia("");

	pythia.readFile(inputFile);
	int seed = stoi(argv[3],NULL,10);
	
	//Using seed passed by parameter
	stringstream seedString;
	seedString<<"Random:seed = "<<seed;
	pythia.readString(seedString.str());
	
	pythia.init();
	
    stringstream folder, ch, antch, str, antstr;

    int jobArrays = stoi(argv[4]);

	/*creating directory*/
    folder<<"OUTPUT_CS/"<<nEvent*jobArrays<<"_"<<jobArrays<<"/";
    mkdir((folder.str()).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	stringstream header;
	header<<folder.str()<<nEvent<<"_"<<seed;

	ofstream charmFile (header.str()+"_charm.out");
	ofstream anticharmFile (header.str()+"_anticharm.out");
	ofstream strangeFile (header.str()+"_strange.out");
	ofstream antistrangeFile (header.str()+"_antistrange.out");


	for(int iEvent = 0; iEvent < nEvent; ++iEvent){
	    if(!pythia.next()) continue;
	    for(int i = 0;i < pythia.event.size(); ++i){
            if(abs(pythia.event[i].id()) == WBOSON){
                if((abs(pythia.event[pythia.event[i].daughter1()].id()) == STRANGE && abs(pythia.event[pythia.event[i].daughter2()].id()) == CHARM) || (abs(pythia.event[pythia.event[i].daughter1()].id()) == CHARM && abs(pythia.event[pythia.event[i].daughter2()].id()) == STRANGE)){
                    switch (pythia.event[pythia.event[i].daughter1()].id()){

                        case CHARM:
                            charmFile<<iEvent<<";"<< pythia.event[pythia.event[i].daughter1()].id()<<";"<<pythia.event[pythia.event[i].daughter1()].e()<<";"<< pythia.event[pythia.event[i].daughter1()].px()<<";"<< pythia.event[pythia.event[i].daughter1()].py()<<";"<< pythia.event[pythia.event[i].daughter1()].pz()<<endl;
                            break;
                        case -CHARM:
                            anticharmFile<<iEvent<<";"<< pythia.event[pythia.event[i].daughter1()].id()<<";"<<pythia.event[pythia.event[i].daughter1()].e()<<";"<< pythia.event[pythia.event[i].daughter1()].px()<<";"<< pythia.event[pythia.event[i].daughter1()].py()<<";"<< pythia.event[pythia.event[i].daughter1()].pz()<<endl;
                            break;
                        case STRANGE:
                            strangeFile<<iEvent<<";"<< pythia.event[pythia.event[i].daughter1()].id()<<";"<<pythia.event[pythia.event[i].daughter1()].e()<<";"<< pythia.event[pythia.event[i].daughter1()].px()<<";"<< pythia.event[pythia.event[i].daughter1()].py()<<";"<< pythia.event[pythia.event[i].daughter1()].pz()<<endl;
                            break;
                        case -STRANGE:
                            antistrangeFile<<iEvent<<";"<< pythia.event[pythia.event[i].daughter1()].id()<<";"<<pythia.event[pythia.event[i].daughter1()].e()<<";"<< pythia.event[pythia.event[i].daughter1()].px()<<";"<< pythia.event[pythia.event[i].daughter1()].py()<<";"<< pythia.event[pythia.event[i].daughter1()].pz()<<endl;
                            break;

                    }

                    switch (pythia.event[pythia.event[i].daughter2()].id()){

                         case CHARM:
                            charmFile<<iEvent<<";"<< pythia.event[pythia.event[i].daughter2()].id()<<";"<<pythia.event[pythia.event[i].daughter2()].e()<<";"<< pythia.event[pythia.event[i].daughter2()].px()<<";"<< pythia.event[pythia.event[i].daughter2()].py()<<";"<< pythia.event[pythia.event[i].daughter2()].pz()<<endl;
                            break;
                        case -CHARM:
                            anticharmFile<<iEvent<<";"<< pythia.event[pythia.event[i].daughter2()].id()<<";"<<pythia.event[pythia.event[i].daughter2()].e()<<";"<< pythia.event[pythia.event[i].daughter2()].px()<<";"<< pythia.event[pythia.event[i].daughter2()].py()<<";"<< pythia.event[pythia.event[i].daughter2()].pz()<<endl;                            
                            break;
                        case STRANGE:
                            strangeFile<<iEvent<<";"<< pythia.event[pythia.event[i].daughter2()].id()<<";"<<pythia.event[pythia.event[i].daughter2()].e()<<";"<< pythia.event[pythia.event[i].daughter2()].px()<<";"<< pythia.event[pythia.event[i].daughter2()].py()<<";"<< pythia.event[pythia.event[i].daughter2()].pz()<<endl;
                            break;
                        case -STRANGE:
                            antistrangeFile<<iEvent<<";"<< pythia.event[pythia.event[i].daughter2()].id()<<";"<<pythia.event[pythia.event[i].daughter2()].e()<<";"<< pythia.event[pythia.event[i].daughter2()].px()<<";"<< pythia.event[pythia.event[i].daughter2()].py()<<";"<< pythia.event[pythia.event[i].daughter2()].pz()<<endl;
                            break;

                    } 

                }
            }
	    }
	}

	charmFile.close();
	anticharmFile.close();
	strangeFile.close();
	antistrangeFile.close();

    return 0;
} 

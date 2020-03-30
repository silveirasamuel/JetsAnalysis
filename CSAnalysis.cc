//Samuel P P Silveira, Fundação Universidade Federal do ABC, 2020
#include "Pythia8/Pythia.h"
#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <cstdio>
#include <cmath>

using namespace fastjet;
using namespace std;
using namespace Pythia8;

#define CHARM 4	
#define STRANGE 3


int main (int argc, char* argv[]) {

	string inputFile = argv[1];
	int nEvent = stoi(argv[2],NULL,10);


	vector<int> charmI;
	vector<int> anticharmI;
	vector<int> strangeI;
	vector<int> antistrangeI;

	Pythia pythia("");

	pythia.readFile(inputFile);
	pythia.init();

	double RParam = stof(argv[3]);
	Strategy strategy= Best;
	RecombinationScheme recombScheme = E_scheme;
	JetDefinition *jetDef = NULL;
	jetDef = new JetDefinition(antikt_algorithm, RParam, recombScheme, strategy);

	vector<PseudoJet> fjInputs;

  	ClusterSequence *cs; 
	vector<PseudoJet> jets;

    /*getting the localtime*/
    stringstream date, ch, antch, str, antstr;
	double deltaPhi = 0;
	double deltaEta = 0;
	double MatchParam =  stof(argv[4]);
    
	/*creating directory*/
    date<<"OUTPUT/"<<nEvent<<"_"<<RParam<<"_"<<MatchParam<<"/";
    mkdir((date.str()).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	stringstream header;
	header<<date.str()<<nEvent<<"_"<<RParam<<"_"<<MatchParam;

	ofstream charmianJetsFile (header.str()+"_charmianJets.out");
	ofstream anticharmianJetsFile (header.str()+"_anticharmianJets.out");
	ofstream strangianJetsFile (header.str()+"_strangianJets.out");
	ofstream antistrangianJetsFile (header.str()+"_antistrangianJets.out");

	ofstream charmFile (header.str()+"_charm.out");
	ofstream anticharmFile (header.str()+"_anticharm.out");
	ofstream strangeFile (header.str()+"_strange.out");
	ofstream antistrangeFile (header.str()+"_antistrange.out");


	for(int iEvent = 0; iEvent < nEvent; ++iEvent){
	    if(!pythia.next()) continue;
	    for(int i = 0;i < pythia.event.size(); ++i){
	      //no neutrinos allowed
	      	if(pythia.event[i].idAbs()!=12 && pythia.event[i].idAbs() !=14 && pythia.event[i].idAbs() != 16 && pythia.event[i].idAbs() != 18){
				//only final state particles			
				if(pythia.event[i].isFinal()){
	          		fjInputs.push_back(PseudoJet(pythia.event[i].px(),pythia.event[i].py(), pythia.event[i].pz(), pythia.event[i].e()));
				}   
	      	}    
			switch(pythia.event[i].id()){
				case CHARM:
					charmI.push_back(i);
					break;
				case -CHARM:
					anticharmI.push_back(i);
					break;
				case STRANGE:
					strangeI.push_back(i);
					break;
				case -STRANGE:
					antistrangeI.push_back(i);
					break;
			}
	    }
	    if(!fjInputs.size()){
	      cout<<"Error: event with no final state particles"<<endl;
	      continue;
	    }


	    // run the clustering, extract the jets
	    cs = new ClusterSequence(fjInputs, *jetDef);
	    jets = sorted_by_pt(cs->inclusive_jets());

	    // print out some infos
	    cout << "Clustering with " << jetDef->description() << endl;


	    for(unsigned k = 0;k < jets.size();k++){
	    	for(unsigned j = 0; j < charmI.size();j++){
	    		deltaEta = jets[k].rap() - pythia.event[charmI[j]].eta();
	    		deltaPhi = jets[k].phi() - pythia.event[charmI[j]].phi();
	    		if(sqrt((pow(deltaEta,2) + pow(deltaPhi,2)))<MatchParam){
					charmianJetsFile<<iEvent<<";"<<CHARM<<";"<<jets[k].E()<<";"<<jets[k].px()<<";"<<jets[k].py()<<";"<<jets[k].pz()<<endl;	
					charmFile<<iEvent<<";"<<pythia.event[charmI[j]].id()<<";"<<pythia.event[charmI[j]].e()<<";"<<pythia.event[charmI[j]].px()<<";"<<pythia.event[charmI[j]].py()<<";"<<pythia.event[charmI[j]].pz()<<endl;
					//cout<<charmI[j]<<endl;
	    		}
				
	    	}

			for(unsigned j = 0; j < anticharmI.size();j++){
	    		deltaEta = jets[k].rap() - pythia.event[anticharmI[j]].eta();
	    		deltaPhi = jets[k].phi() - pythia.event[anticharmI[j]].phi();
	    		if(sqrt((pow(deltaEta,2) + pow(deltaPhi,2)))<MatchParam){
					anticharmianJetsFile<<iEvent<<";"<<CHARM<<";"<<jets[k].E()<<";"<<jets[k].px()<<";"<<jets[k].py()<<";"<<jets[k].pz()<<endl;	
					anticharmFile<<iEvent<<";"<<pythia.event[anticharmI[j]].id()<<";"<<pythia.event[anticharmI[j]].e()<<";"<<pythia.event[anticharmI[j]].px()<<";"<<pythia.event[anticharmI[j]].py()<<";"<<pythia.event[anticharmI[j]].pz()<<endl;
					//cout<<anticharmI[j]<<endl;
	    		}
				
	    	}

			for(unsigned j = 0; j < strangeI.size();j++){
	    		deltaEta = jets[k].rap() - pythia.event[strangeI[j]].eta();
	    		deltaPhi = jets[k].phi() - pythia.event[strangeI[j]].phi();
	    		if(sqrt((pow(deltaEta,2) + pow(deltaPhi,2)))<MatchParam){
					strangianJetsFile<<iEvent<<";"<<CHARM<<";"<<jets[k].E()<<";"<<jets[k].px()<<";"<<jets[k].py()<<";"<<jets[k].pz()<<endl;	
					strangeFile<<iEvent<<";"<<pythia.event[strangeI[j]].id()<<";"<<pythia.event[strangeI[j]].e()<<";"<<pythia.event[strangeI[j]].px()<<";"<<pythia.event[strangeI[j]].py()<<";"<<pythia.event[strangeI[j]].pz()<<endl;
					//cout<<strangeI[j]<<endl;
	    		}
				
	    	}

			for(unsigned j = 0; j < antistrangeI.size();j++){
	    		deltaEta = jets[k].rap() - pythia.event[antistrangeI[j]].eta();
	    		deltaPhi = jets[k].phi() - pythia.event[antistrangeI[j]].phi();
	    		if(sqrt((pow(deltaEta,2) + pow(deltaPhi,2)))<MatchParam){
					antistrangianJetsFile<<iEvent<<";"<<CHARM<<";"<<jets[k].E()<<";"<<jets[k].px()<<";"<<jets[k].py()<<";"<<jets[k].pz()<<endl;	
					antistrangeFile<<iEvent<<";"<<pythia.event[antistrangeI[j]].id()<<";"<<pythia.event[antistrangeI[j]].e()<<";"<<pythia.event[antistrangeI[j]].px()<<";"<<pythia.event[antistrangeI[j]].py()<<";"<<pythia.event[antistrangeI[j]].pz()<<endl;
					//cout<<antistrangeI[j]<<endl;
	    		}
				
	    	}
	    
	    }
		strangeI.clear();
		antistrangeI.clear();
		charmI.clear();
		anticharmI.clear();
	    // print the jets
	    cout <<   "        pt y phi" << endl;
	    for (unsigned l = 0; l < jets.size(); l++) {
	      cout << "jet " << l << ": "<< jets[l].pt() << " " 
	                    << jets[l].rap() << " " << jets[l].phi() << endl;
	    }

	    fjInputs.clear();
		jets.clear();
		delete cs;
		
		

	}

	charmianJetsFile.close();
	anticharmianJetsFile.close();
	strangianJetsFile.close();
	antistrangianJetsFile.close();
	
	charmFile.close();
	anticharmFile.close();
	strangeFile.close();
	antistrangeFile.close();

	/*/*moving to the right directory
	stringstream cj,acj, sj, asj, s, c, as, ac;
    cj<<date.str()<<"/"<<date.str()<<"_charmianJets.out";
    rename((date.str()+"_charmianJets.out").c_str(), cj.str().c_str());
	acj<<date.str()<<"/"<<date.str()<<"_anticharmianJets.out";
    rename((date.str()+"_anticharmianJets.out").c_str(), acj.str().c_str());
	sj<<date.str()<<"/"<<date.str()<<"_strangianJets.out";
    rename((date.str()+"_strangianJets.out").c_str(), sj.str().c_str());
	asj<<date.str()<<"/"<<date.str()<<"_antistrangianJets.out";
    rename((date.str()+"_antistrangianJets.out").c_str(), asj.str().c_str());

	c<<date.str()<<"/"<<date.str()<<"_charm.out";
    rename((date.str()+"_charm.out").c_str(), c.str().c_str());
	ac<<date.str()<<"/"<<date.str()<<"_anticharm.out";
    rename((date.str()+"_anticharm.out").c_str(), ac.str().c_str());
	s<<date.str()<<"/"<<date.str()<<"_strange.out";
    rename((date.str()+"_strange.out").c_str(), s.str().c_str());
	as<<date.str()<<"/"<<date.str()<<"_antistrange.out";
    rename((date.str()+"_antistrange.out").c_str(), as.str().c_str());
*/
  return 0;
} 
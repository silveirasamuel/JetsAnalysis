//Samuel P P Silveira, Universidade Federal do ABC, 2020
#include "MJet.h"
#include "TLorentzVector.h"
//#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

void analysisQuarksInvariantMass(int n, int in, int jobs){

    stringstream i;
    i<<in;
    
    stringstream folders;
    folders<<n*jobs<<"_"<<jobs<<"/";
    string folder = folders.str();
    stringstream headers;
    headers<<n<<"_"<<in;
    string header = headers.str();


    ifstream charmsFile("OUTPUT_CS/"+folder+header+"_charm.out");
    ifstream anticharmsFile("OUTPUT_CS/"+folder+header+"_anticharm.out");
    ifstream strangesFile("OUTPUT_CS/"+folder+header+"_strange.out");
    ifstream antistrangesFile("OUTPUT_CS/"+folder+header+"_antistrange.out");

   
    vector<MJet*> stranges;
    vector<MJet*> antistranges;
    vector<MJet*> charms;
    vector<MJet*> anticharms;
    
    MJet* strange;
    MJet* antistrange;
    MJet* charm;
    MJet* anticharm;
 
    //vector<MJet*> wBosons;
    MJet* wBoson;
 
    string line;
    string event, flavor, e, px, py, pz;
    stringstream ss;

    TFile fout(("OUTPUT_CS/Histograms_Output/"+folder+header+"_hresultsWInvariantMass.root").c_str(),"recreate");
    TH1F *hWInvariantMass = new TH1F("wbim","W Boson Invariant Mass;m_{W} [GeV c^{-2}]; counts",200,0,150);


    if (charmsFile.is_open() && antistrangesFile.is_open() && anticharmsFile.is_open() && strangesFile.is_open()){
        cout<<"Loading charms (1/4) ..."<<endl;
        while(getline(charmsFile,line)){
            charm = new MJet(); 
            ss.str(line);           
            
            getline(ss,event,';');
            charm->event = atoi(event.c_str());
            getline(ss,flavor,';');   
            charm->flavor = atoi(flavor.c_str());
            getline(ss,e,';');
            getline(ss,px,';');
	        getline(ss,py,';');
            getline(ss,pz,';');
            charm->lv = TLorentzVector(atof(px.c_str()), atof(py.c_str()), atof(pz.c_str()), atof(e.c_str()));
            ss.clear();

            charms.push_back(charm);

        }
        cout<<" "<<charms.size()<<" charmed jets loaded"<<endl;
        cout<<"Loading antistranges (2/4) ..."<<endl;
        while(getline(antistrangesFile,line)){
            
            antistrange = new MJet();
            ss.str(line);

            getline(ss,event,';');
            antistrange->event = atoi(event.c_str());
            getline(ss,flavor,';');   
            antistrange->flavor = atoi(flavor.c_str());
            getline(ss,e,';');
            getline(ss,px,';');
	        getline(ss,py,';');
            getline(ss,pz,';');
            antistrange->lv =  TLorentzVector(atof(px.c_str()), atof(py.c_str()), atof(pz.c_str()), atof(e.c_str()));
            ss.clear();

            antistranges.push_back(antistrange);
            //cout<<antistrange->event<<","<<antistrange->flavor<<","<<antistrange->e<<","<<antistrange->px<<","<<antistrange->py<<","<<antistrange->pz<<endl;
            
        }
        cout<<" "<<antistranges.size()<<" antistranges loaded"<<endl;
        cout<<"Loading anticharms (3/4) ..."<<endl;
        while(getline(anticharmsFile,line)){
            anticharm = new MJet(); 
            ss.str(line);           
            
            getline(ss,event,';');
            anticharm->event = atoi(event.c_str());
            getline(ss,flavor,';');   
            anticharm->flavor = atoi(flavor.c_str());
            getline(ss,e,';');
            getline(ss,px,';');
	        getline(ss,py,';');
            getline(ss,pz,';');
            anticharm->lv =  TLorentzVector(atof(px.c_str()), atof(py.c_str()), atof(pz.c_str()), atof(e.c_str()));
        
            ss.clear();

            anticharms.push_back(anticharm);

        }
        cout<<" "<<anticharms.size()<<" anticharms loaded"<<endl;
        cout<<"Loading stranges (4/4) ..."<<endl;
        while(getline(strangesFile,line)){
            strange = new MJet(); 
            ss.str(line);           
            
            getline(ss,event,';');
            strange->event = atoi(event.c_str());
            getline(ss,flavor,';');   
            strange->flavor = atoi(flavor.c_str());
            getline(ss,e,';');
            getline(ss,px,';');
	        getline(ss,py,';');
            getline(ss,pz,';');
            strange->lv =  TLorentzVector(atof(px.c_str()), atof(py.c_str()), atof(pz.c_str()), atof(e.c_str()));
        
            ss.clear();

            stranges.push_back(strange);

        }
        cout<<" "<<stranges.size()<<" stranges loaded"<<endl;

    }else{
        cout<<"ERROR: FILE NOT FOUND!"<<endl;
        return;
    }

    charmsFile.close();
    anticharmsFile.close();
    strangesFile.close();
    antistrangesFile.close();

    int pointer = 0;
    cout<<"Merging W+ Jets (1/2)..."<<endl;
    for(int i = 0; i < charms.size();i++){
        for(int j = pointer;j < antistranges.size();j++){
            if(antistranges[j]->event == charms[i]->event ){
                wBoson = new MJet();
                wBoson->event = charms[i]->event;
                wBoson->flavor = 24;
                wBoson->lv = charms[i]->lv + antistranges[j]->lv;
                hWInvariantMass->Fill(wBoson->lv.M());
               
            }
            if(antistranges[j]->event > charms[i]->event){
                pointer=j;
                break;
            }
           
        }
    }
    pointer = 0;
    cout<<"Merging W- Jets (2/2)..."<<endl;
    for(int i = 0; i < anticharms.size();i++){
        for(int j = pointer;j < stranges.size();j++){
            if(anticharms[i]->event == stranges[j]->event ){
                wBoson = new MJet();
                wBoson->event = anticharms[i]->event;
                wBoson->flavor = -24;
                wBoson->lv = anticharms[i]->lv + stranges[j]->lv;
                hWInvariantMass->Fill(wBoson->lv.M());
            }
            if(stranges[j]->event > anticharms[i]->event ){
                pointer=j;
                break;
            }
           
        }
    }

    stranges.clear();
    antistranges.clear();
    charms.clear();
    anticharms.clear();


    hWInvariantMass->Rebin(2);
    hWInvariantMass->Sumw2();
    hWInvariantMass->SetLineColor(4);
    hWInvariantMass->Write();

}

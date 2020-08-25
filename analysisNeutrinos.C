#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;



void analysisNeutrinos(int n, double r, double m, int in, int jobs){

    stringstream i;
    i<<in;

    
    stringstream folders;
    folders<<n*jobs<<"_"<<r<<"_"<<m<<"_"<<jobs<<"/";
    string folder = folders.str();
    stringstream headers;
    headers<<n<<"_"<<r<<"_"<<m<<"_"<<in;
    string header = headers.str();


    ifstream neutrinos("OUTPUT_WN/"+folder+header+"_neutrinos.out");
 
    string line;
    string event, pdg, e, pt;
    stringstream ss;

    TFile fout(("OUTPUT_WN/Histograms_Output/"+folder+header+"_hresultsNeutrinos.root").c_str(),"recreate");
    TH1F *hNeutrinosE = new TH1F("ne","Jet Neutrinos' Energy;e_{#nu} [GeV]; counts",200,1,200);
    TH1F *hNeutrinospT = new TH1F("npt","Jet Neutrinos' p_{T}; p_{T}^{#nu} [GeV/c];counts",200,1,200);
    int count = 0;
    if (neutrinos.is_open()){
        cout<<"Loading neutrinos ..."<<endl;
        while(getline(neutrinos,line)){
            
            ss.str(line);           
            getline(ss, event,';');
            getline(ss, pdg, ';');
            getline(ss,e,';');
            hNeutrinosE->Fill(atof(e.c_str()));
            getline(ss,pt,';');   
            hNeutrinospT->Fill(atof(pt.c_str()));
            
            ss.clear();
            count++;
        }
        cout<<count<<" netrinos loaded"<<endl;

    }else{
        cout<<"ERROR: FILE NOT FOUND!"<<endl;
        return;
    }

    hNeutrinosE->Write();
    hNeutrinospT->Write();

}

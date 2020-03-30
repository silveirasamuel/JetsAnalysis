//Samuel P P Silveira, Universidade Federal do ABC, 2020
#include "MJet.h"
#include "TLorentzVector.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <sys/stat.h>

using namespace std;

void analysisJetsInvariantMass(string folder){
    ifstream charmianJets("OUTPUT/"+folder+"/"+folder+"_charmianJets.out");
    ifstream anticharmianJets("OUTPUT/"+folder+"/"+folder+"_anticharmianJets.out");
    ifstream strangianJets("OUTPUT/"+folder+"/"+folder+"_strangianJets.out");
    ifstream antistrangianJets("OUTPUT/"+folder+"/"+folder+"_antistrangianJets.out");

   
    vector<MJet*> strangians;
    vector<MJet*> antistrangians;
    vector<MJet*> charmians;
    vector<MJet*> anticharmians;
    
    MJet* strangian;
    MJet* antistrangian;
    MJet* charmian;
    MJet* anticharmian;
 
    //vector<MJet*> wBosons;
    MJet* wBoson;
 
    string line;
    string event, flavor, e, px, py, pz;
    stringstream ss;
   
    mkdir("OUTPUT/Histograms Output", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    TFile fout(("OUTPUT/Histograms Output/"+folder+"_resultsJetsInvariantMass.root").c_str(),"recreate");
    TH1F *hJetsInvariantMass = new TH1F("wjim","W Jets Invariant Mass;m_{cs} [GeV c^{-2}]; counts",200,0,150);


    if (charmianJets.is_open() && antistrangianJets.is_open() &&anticharmianJets.is_open() && strangianJets.is_open()){
        cout<<"Loading charmed jets (1/4) ..."<<endl;
        while(getline(charmianJets,line)){
            charmian = new MJet(); 
            ss.str(line);           
            
            getline(ss,event,';');
            charmian->event = atoi(event.c_str());
            getline(ss,flavor,';');   
            charmian->flavor = atoi(flavor.c_str());
            getline(ss,e,';');
            getline(ss,px,';');
	        getline(ss,py,';');
            getline(ss,pz,';');
            charmian->lv = TLorentzVector(atof(px.c_str()), atof(py.c_str()), atof(pz.c_str()), atof(e.c_str()));
            ss.clear();

            charmians.push_back(charmian);

        }
        cout<<" "<<charmians.size()<<" charmed jets loaded"<<endl;
        cout<<"Loading antistrange jets (2/4) ..."<<endl;
        while(getline(antistrangianJets,line)){
            
            antistrangian = new MJet();
            ss.str(line);

            getline(ss,event,';');
            antistrangian->event = atoi(event.c_str());
            getline(ss,flavor,';');   
            antistrangian->flavor = atoi(flavor.c_str());
            getline(ss,e,';');
            getline(ss,px,';');
	        getline(ss,py,';');
            getline(ss,pz,';');
            antistrangian->lv =  TLorentzVector(atof(px.c_str()), atof(py.c_str()), atof(pz.c_str()), atof(e.c_str()));
            ss.clear();

            antistrangians.push_back(antistrangian);
            //cout<<antistrangian->event<<","<<antistrangian->flavor<<","<<antistrangian->e<<","<<antistrangian->px<<","<<antistrangian->py<<","<<antistrangian->pz<<endl;
            
        }
        cout<<" "<<antistrangians.size()<<" antistrange jets loaded"<<endl;
        cout<<"Loading anticharmed jets (3/4) ..."<<endl;
        while(getline(anticharmianJets,line)){
            anticharmian = new MJet(); 
            ss.str(line);           
            
            getline(ss,event,';');
            anticharmian->event = atoi(event.c_str());
            getline(ss,flavor,';');   
            anticharmian->flavor = atoi(flavor.c_str());
            getline(ss,e,';');
            getline(ss,px,';');
	        getline(ss,py,';');
            getline(ss,pz,';');
            anticharmian->lv =  TLorentzVector(atof(px.c_str()), atof(py.c_str()), atof(pz.c_str()), atof(e.c_str()));
        
            ss.clear();

            anticharmians.push_back(anticharmian);

        }
        cout<<" "<<anticharmians.size()<<" anticharmed jets loaded"<<endl;
        cout<<"Loading strange jets (4/4) ..."<<endl;
        while(getline(strangianJets,line)){
            strangian = new MJet(); 
            ss.str(line);           
            
            getline(ss,event,';');
            strangian->event = atoi(event.c_str());
            getline(ss,flavor,';');   
            strangian->flavor = atoi(flavor.c_str());
            getline(ss,e,';');
            getline(ss,px,';');
	        getline(ss,py,';');
            getline(ss,pz,';');
            strangian->lv =  TLorentzVector(atof(px.c_str()), atof(py.c_str()), atof(pz.c_str()), atof(e.c_str()));
        
            ss.clear();

            strangians.push_back(strangian);

        }
        cout<<" "<<strangians.size()<<" strange jets loaded"<<endl;

    }else{
        cout<<"ERROR: FILE NOT FOUND!"<<endl;
        return;
    }

    charmianJets.close();
    anticharmianJets.close();
    strangianJets.close();
    antistrangianJets.close();
    int pointer = 0;
    cout<<"Merging W+ Jets (1/2)..."<<endl;
    for(int i = 0; i < charmians.size();i++){
        for(int j = pointer;j < antistrangians.size();j++){
            if(antistrangians[j]->event == charmians[i]->event ){
                wBoson = new MJet();
                wBoson->event = charmians[i]->event;
                wBoson->flavor = 24;
                wBoson->lv = charmians[i]->lv + antistrangians[j]->lv;
                hJetsInvariantMass->Fill(wBoson->lv.M());
                //cout<<wBoson->event<<","<<wBoson->flavor<<","<<wBoson->lv.Px()<<","<<wBoson->lv.Py()<<","<<wBoson->lv.Pz()<<","<<wBoson->lv.E()<<endl;
            }
            if(antistrangians[j]->event > charmians[i]->event){
                pointer=j;
                break;
            }
           
        }
    }
    pointer = 0;
    cout<<"Merging W- Jets (2/2)..."<<endl;
    for(int i = 0; i < anticharmians.size();i++){
        for(int j = pointer;j < strangians.size();j++){
            if(anticharmians[i]->event == strangians[j]->event ){
                wBoson = new MJet();
                wBoson->event = anticharmians[i]->event;
                wBoson->flavor = -24;
                wBoson->lv = anticharmians[i]->lv + strangians[j]->lv;
                hJetsInvariantMass->Fill(wBoson->lv.M());
                //cout<<wBoson->event<<","<<wBoson->flavor<<","<<wBoson->lv.Px()<<","<<wBoson->lv.Py()<<","<<wBoson->lv.Pz()<<","<<wBoson->lv.E()<<endl;           
            }
            if(strangians[j]->event > anticharmians[i]->event ){
                pointer=j;
                break;
            }
           
        }
    }

    strangians.clear();
    antistrangians.clear();
    charmians.clear();
    anticharmians.clear();


    hJetsInvariantMass->Rebin(2);
    hJetsInvariantMass->Sumw2();

    TF1 *fitFcn = new TF1("landau","landau",0,150);
    fitFcn->SetNpx(500);
    fitFcn->SetLineWidth(4);
    fitFcn->SetLineColor(kMagenta);
    fitFcn->SetParameters(1,1,1,1,1,1);
    hJetsInvariantMass->Fit(fitFcn,"R");
    
    Double_t par[6];

    TF1 *signalFcn = new TF1("gaus","gaus",60,150);
    signalFcn->SetLineColor(kBlue);
    signalFcn->SetNpx(500);
    signalFcn->SetParameters(&par[2]);
    hJetsInvariantMass->Fit(signalFcn,"R+");
    hJetsInvariantMass->SetMarkerStyle(21);
    hJetsInvariantMass->SetMarkerSize(0.5);
    hJetsInvariantMass->DrawCopy();


    TLegend *legend=new TLegend(0.6,0.65,0.88,0.85);
    legend->SetTextFont(72);
    legend->SetTextSize(0.04);
    legend->AddEntry(hJetsInvariantMass,"Data","lpe");
    legend->AddEntry(signalFcn,"Signal fit","l");
    legend->AddEntry(fitFcn,"Global Fit","l");
    legend->Draw();
    
    hJetsInvariantMass->Write();

    cout<<"Histogram is built and available in: OUTPUT/Histograms Output/"<<folder<<"_resultsJetsInvariantMass.root"<<endl;
}
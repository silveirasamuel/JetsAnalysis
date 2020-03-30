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

void analysisJetsQuarksPt(string folder){
    ifstream charmianJets("OUTPUT/"+folder+"/"+folder+"_charmianJets.out");
    ifstream anticharmianJets("OUTPUT/"+folder+"/"+folder+"_anticharmianJets.out");
    ifstream strangianJets("OUTPUT/"+folder+"/"+folder+"_strangianJets.out");
    ifstream antistrangianJets("OUTPUT/"+folder+"/"+folder+"_antistrangianJets.out");


    ifstream charmsParticles("OUTPUT/"+folder+"/"+folder+"_charm.out");
    ifstream anticharmsParticles("OUTPUT/"+folder+"/"+folder+"_anticharm.out");
    ifstream strangesParticles("OUTPUT/"+folder+"/"+folder+"_strange.out");
    ifstream antistrangesParticles("OUTPUT/"+folder+"/"+folder+"_antistrange.out");

   
    vector<MJet*> strangians;
    vector<MJet*> antistrangians;
    vector<MJet*> charmians;
    vector<MJet*> anticharmians;
    
    MJet* strangian;
    MJet* antistrangian;
    MJet* charmian;
    MJet* anticharmian;

    //It is not beautiful because the following variables are not Jets but particles. 
    //However it would be useless to write a new class with the same atributes. :P
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
   
    mkdir("OUTPUT/Histograms Output", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    TFile fout(("OUTPUT/Histograms Output/"+folder+"_resultsJetsQuarksPt.root").c_str(),"recreate");
    TH2F *hJetsQuarksCharmPt = new TH2F("cjqpt","Charm Jets and Quarks Pt;quarks;jets; counts",300,0,150,300,0,150);
    TH2F *hJetsQuarksAntiCharmPt = new TH2F("acjqpt","Anticharm Jets and Quarks Pt;quarks;jets; counts",300,0,150,300,0,150);
    TH2F *hJetsQuarksStrangePt = new TH2F("sjqpt","Strange Jets and Quarks Pt;quarks;jets; counts",300,0,150,300,0,150);
    TH2F *hJetsQuarksAntiStrangePt = new TH2F("asjqpt","Antistrange Jets and Quarks Pt;quarks;jets; counts",300,0,150,300,0,150);
    TH2F *hJetsQuarksPt = new TH2F("jqpt","Jets and Quarks Pt;quarks;jets; counts",300,0,150,300,0,150);


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


    if (charmsParticles.is_open() && antistrangesParticles.is_open() &&anticharmsParticles.is_open() && strangesParticles.is_open()){
        cout<<"Loading charms (1/4) ..."<<endl;
        while(getline(charmsParticles,line)){
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
        cout<<" "<<charms.size()<<" charms loaded"<<endl;
        cout<<"Loading antistranges (2/4) ..."<<endl;
        while(getline(antistrangesParticles,line)){
            
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
            //cout<<antistrangian->event<<","<<antistrangian->flavor<<","<<antistrangian->e<<","<<antistrangian->px<<","<<antistrangian->py<<","<<antistrangian->pz<<endl;
            
        }
        cout<<" "<<antistranges.size()<<" antistranges loaded"<<endl;
        cout<<"Loading anticharmes (3/4) ..."<<endl;
        while(getline(anticharmsParticles,line)){
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
        while(getline(strangesParticles,line)){
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

    charmianJets.close();
    anticharmianJets.close();
    strangianJets.close();
    antistrangianJets.close();

    charmsParticles.close();
    anticharmsParticles.close();
    strangesParticles.close();
    antistrangesParticles.close();

    cout<<"Building for charms(1/4)"<<endl;
    for(int i = 0; i < charmians.size();i++){
        hJetsQuarksPt->Fill(charms[i]->lv.Pt(),charmians[i]->lv.Pt());
        hJetsQuarksCharmPt->Fill(charms[i]->lv.Pt(),charmians[i]->lv.Pt());
    }
    cout<<"Building for anticharms(2/4)"<<endl;
    for(int i = 0; i < anticharmians.size();i++){
      hJetsQuarksPt->Fill(anticharms[i]->lv.Pt(),anticharmians[i]->lv.Pt());
      hJetsQuarksAntiCharmPt->Fill(anticharms[i]->lv.Pt(),anticharmians[i]->lv.Pt());
    }

    cout<<"Building for stranges(3/4)"<<endl;
    for(int i = 0; i < stranges.size();i++){
       hJetsQuarksPt->Fill(stranges[i]->lv.Pt(), strangians[i]->lv.Pt());
       hJetsQuarksStrangePt->Fill(stranges[i]->lv.Pt(), strangians[i]->lv.Pt());
    }
    cout<<"Building for antistranges(4/4)"<<endl;
    for(int i = 0; i < antistranges.size();i++){
       hJetsQuarksPt->Fill(antistranges[i]->lv.Pt(),antistrangians[i]->lv.Pt());
       hJetsQuarksAntiStrangePt->Fill(antistranges[i]->lv.Pt(),antistrangians[i]->lv.Pt());

    }

    strangians.clear();
    antistrangians.clear();
    charmians.clear();
    anticharmians.clear();

    stranges.clear();
    antistranges.clear();
    charms.clear();
    anticharms.clear();


    /*hJetsQuarksPt->Rebin(2);
    hJetsQuarksPt->Sumw2();

    TF1 *fitFcn = new TF1("landau","landau",0,150);
    fitFcn->SetNpx(500);
    fitFcn->SetLineWidth(4);
    fitFcn->SetLineColor(kMagenta);
    fitFcn->SetParameters(1,1,1,1,1,1);
    hJetsQuarksPt->Fit(fitFcn,"R");
    
    Double_t par[6];

    TF1 *signalFcn = new TF1("gaus","gaus",60,150);
    signalFcn->SetLineColor(kBlue);
    signalFcn->SetNpx(500);
    signalFcn->SetParameters(&par[2]);
    hJetsQuarksPt->Fit(signalFcn,"R+");
    hJetsQuarksPt->SetMarkerStyle(21);
    hJetsQuarksPt->SetMarkerSize(0.5);
    hJetsQuarksPt->DrawCopy();


    TLegend *legend=new TLegend(0.6,0.65,0.88,0.85);
    legend->SetTextFont(72);
    legend->SetTextSize(0.04);
    legend->AddEntry(hJetsQuarksPt,"Data","lpe");
    legend->AddEntry(signalFcn,"Signal fit","l");
    legend->AddEntry(fitFcn,"Global Fit","l");
    legend->Draw();*/
    hJetsQuarksCharmPt->Write();
    hJetsQuarksAntiCharmPt->Write();
    hJetsQuarksStrangePt->Write();
    hJetsQuarksAntiStrangePt->Write();
    hJetsQuarksPt->Write();

    cout<<"Histogram is built and available in: OUTPUT/Histograms Output/"<<folder<<"_resultsJetsQuarksPt.root"<<endl;
}
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

    auto c1 = new TCanvas("c1","c1",1000,550);
    gStyle->SetOptStat("");

    gPad->SetGridy();
    gPad->SetTickx();
    gPad->SetTicky();

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
    TH1F *hJetsInvariantMass = new TH1F("wjim","W Jets Invariant Mass;m_{W} [GeV c^{-2}]; counts",200,0,150);


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
    hJetsInvariantMass->SetLineColor(4);

    TF1 *tf = new TF1("tf","landau(0) + gaus(3)",0,150);
    tf->SetParameters(600,20,11,250,75,5);
    tf->SetLineColor(6);
    hJetsInvariantMass->Fit(tf,"R");
    hJetsInvariantMass->Draw("e1");

    TF1 *sg = new TF1("sg","gaus(0)",0,150);
    sg->SetParameters(tf->GetParameters()+3);
    sg->SetParErrors(tf->GetParErrors()+3);
    sg->SetLineColor(3);
    sg->DrawClone("same");


    TF1 *bg = new TF1("bg","landau(0)",0,150);
    bg->SetParameters(tf->GetParameters());
    bg->SetParErrors(tf->GetParErrors());
    bg->SetLineColor(2);
    bg->SetLineStyle(2);
    bg->DrawClone("same");
    

    TRatioPlot *rp = new TRatioPlot(hJetsInvariantMass);
    //rp->DrawCopy("same");

    TLegend *legend = new TLegend(0.6,0.65,0.88,0.85);
    legend->SetTextFont(72);
    legend->SetTextSize(0.02);
    legend->SetHeader("Legend","C");
    legend->AddEntry(sg,"Signal fit","l");
    legend->AddEntry(bg,"Background fit","l");
    legend->AddEntry(tf,"Global fit","l");
    legend->DrawClone();
    
   
    c1->DrawClone();

    c1->SaveAs(("OUTPUT/Histograms Output/"+folder+"_resultsJetsInvariantMass.root").c_str());
    c1->SaveAs(("OUTPUT/Histograms Output/"+folder+"_resultsJetsInvariantMass.pdf").c_str());

   // cout<<"Histogram is built and available in: OUTPUT/Histograms Output/"<<folder<<"_resultsJetsInvariantMass.root"<<endl;


    ofstream statistics;
    statistics.open("OUTPUT/"+folder+"/"+folder+"_statistics");

    statistics<<"Statistics of histogram"<<endl<<endl;
    statistics<<"Entries: "<<hJetsInvariantMass->GetEntries()<<endl;
    statistics<<"Kurtosis: "<<hJetsInvariantMass->GetKurtosis()<<endl;
    statistics<<"Skewness: "<<hJetsInvariantMass->GetSkewness()<<endl;
    statistics<<"RMS: "<<hJetsInvariantMass->GetRMS()<<endl;
    statistics<<"Mean: "<<hJetsInvariantMass->GetMean()<<endl;
    statistics<<"Integral: "<<hJetsInvariantMass->Integral()<<endl<<endl<<endl;
    statistics<<"Statistics of Global fit"<<endl<<endl;
    statistics<<"Chi square: "<<tf->GetChisquare()<<endl;
    statistics<<"NDF: "<<tf->GetNDF()<<endl;
    statistics<<"Chisquare/NDF: "<<tf->GetChisquare()/tf->GetNDF()<<endl;
    statistics<<"Parameters: "<<tf->GetParameter(0)<<","<<tf->GetParameter(1)<<","<<tf->GetParameter(2)<<","<<tf->GetParameter(3)<<","<<tf->GetParameter(4)<<","<<tf->GetParameter(5)<<endl;
    statistics<<"Parameter Errors: "<<tf->GetParError(0)<<","<<tf->GetParError(1)<<","<<tf->GetParError(2)<<","<<tf->GetParError(3)<<","<<tf->GetParError(4)<<","<<tf->GetParError(5)<<endl;
    statistics<<"Integral: "<<tf->Integral(0,150)<<endl;
    statistics<<"Mean: "<<tf->Mean(0,150)<<endl;
    statistics<<"Maximum X: "<<tf->GetMaximumX(0,150)<<endl;
    statistics<<"Maximum Y: "<<tf->GetMaximum(0,150)<<endl<<endl<<endl;
    statistics<<"Statistics of Signal fit"<<endl<<endl;
    statistics<<"Parameters: "<<sg->GetParameter(0)<<","<<sg->GetParameter(1)<<","<<sg->GetParameter(2)<<endl;
    statistics<<"Parameter Errors: "<<sg->GetParError(0)<<","<<sg->GetParError(1)<<","<<sg->GetParError(2)<<endl;
    statistics<<"Integral: "<<sg->Integral(0,150)<<endl;
    statistics<<"Signal significance: "<<sg->Integral(0,150)/TMath::Sqrt(sg->Integral(0,150))<<endl;
    statistics<<"Mean: "<<sg->Mean(0,150)<<endl;
    statistics<<"Maximum X: "<<sg->GetMaximumX(0,150)<<endl;
    statistics<<"Maximum Y: "<<sg->GetMaximum(0,150)<<endl<<endl<<endl;
    statistics<<"Statistics of Background fit"<<endl<<endl;
    statistics<<"Parameters: "<<bg->GetParameter(0)<<","<<bg->GetParameter(1)<<","<<bg->GetParameter(2)<<endl;
    statistics<<"Parameter Errors: "<<bg->GetParError(0)<<","<<bg->GetParError(1)<<","<<bg->GetParError(2)<<endl;   
    statistics<<"Integral: "<<bg->Integral(0,150)<<endl;
    statistics<<"Mean: "<<bg->Mean(0,150)<<endl;
    statistics<<"Maximum X: "<<bg->GetMaximumX(0,150)<<endl;
    statistics<<"Maximum Y: "<<bg->GetMaximum(0,150)<<endl<<endl<<endl;

    statistics.close();

}
//Samuel P P Silveira, Universidade Federal do ABC, 2020

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

const int FIRST_BIN = 30;
const int LAST_BIN = 280;
using namespace std;

void projections_wn(int n, double r, double m, int jobs){

    stringstream header, output;
    header<<"OUTPUT_WN/Histograms_Output/"<<n<<"_"<<r<<"_"<<m<<"_"<<jobs<<"/100M_"<<r<<"_"<<m<<"_JetsQuarksPt.root";
    output<<"OUTPUT_WN/Histograms_Output/"<<n<<"_"<<r<<"_"<<m<<"_"<<jobs<<"/100M_"<<r<<"_"<<m<<"_projections.root";
    TFile *file = new TFile((header.str()).c_str());
    TFile fout((output.str()).c_str(),"recreate");
    TH2F *hJetsQuarksCharmPt = (TH2F*)file->Get("cjqpt");
    TH2F *hJetsQuarksAntiCharmPt = (TH2F*)file->Get("acjqpt");
    TH2F *hJetsQuarksStrangePt = (TH2F*)file->Get("sjqpt");
    TH2F *hJetsQuarksAntiStrangePt = (TH2F*)file->Get("asjqpt");


    TH1F  *hproj;
    stringstream name;
    TGraph *gm,*gs;
    int maxbin;
    int nu = LAST_BIN - FIRST_BIN;
    int x[nu],ym[nu], ys[nu];
    for(int i = FIRST_BIN; i < LAST_BIN; i++){
        name<<"proj_cjqpt_"<<i;
        cout<<name.str()<<endl;
        hproj = (TH1F*)hJetsQuarksCharmPt->ProjectionY((name.str()).c_str(),i-10,i+10);
        maxbin = hproj->GetMaximumBin();
        
        TF1 *sgc = new TF1("sgc","gaus(0)",hproj->GetBinCenter(maxbin-5),hproj->GetBinCenter(maxbin+5));
        hproj->GetXaxis()->SetRange(maxbin-5,maxbin+5);
        sgc->SetParameters(hproj->GetMaximum(),hproj->GetBinCenter(maxbin),2);
        sgc->SetLineColor(6);
        hproj->Fit(sgc);

        x[i-FIRST_BIN] = hproj->GetXaxis()->GetBinCenter(i);
        ym[i-FIRST_BIN] = sgc->GetParameter(1);
        ys[i-FIRST_BIN] = sgc->GetParameter(2);

        name.str("");
        hproj->Write();
    }
    gm = new TGraph(nu,x,ym);
    gm->SetTitle("Mean jet p_{T} as a function of quark p_{T};quark-p_{T} [GeV/c];jet-p_{T} [GeV/c]");
    gm->SetName("graph_wn_cjqpt_mean");
    
    gs = new TGraph(nu,x,ys);
    gs->SetTitle("Jet resolution as a function of quark p_{T};quark-p_{T} [GeV/c];#sigma [GeV/c]");
    gs->SetName("graph_wn_cjqpt_sigma");
    
    gm->SetLineColor(4);
    gs->SetLineColor(4);

    gm->Write();
    gs->Write();


    for(int i = FIRST_BIN; i < LAST_BIN; i++){
        name<<"proj_acjqpt_"<<i;
        cout<<name.str()<<endl;
        hproj = (TH1F*)hJetsQuarksAntiCharmPt->ProjectionY((name.str()).c_str(),i-10,i+10);
        maxbin = hproj->GetMaximumBin();
        
        TF1 *sgac = new TF1("sgac","gaus(0)",hproj->GetBinCenter(maxbin-5),hproj->GetBinCenter(maxbin+5));
        hproj->GetXaxis()->SetRange(maxbin-5,maxbin+5);
        sgac->SetParameters(hproj->GetMaximum(),hproj->GetBinCenter(maxbin),2);
        sgac->SetLineColor(6);
        hproj->Fit(sgac);

        x[i-FIRST_BIN] = hproj->GetXaxis()->GetBinCenter(i);
        ym[i-FIRST_BIN] = sgac->GetParameter(1);
        ys[i-FIRST_BIN] = sgac->GetParameter(2);

        name.str("");
        hproj->Write();
    }
    gm = new TGraph(nu,x,ym);
    gm->SetTitle("Mean jet p_{T} as a function of quark p_{T};quark-p_{T} [GeV/c];jet-p_{T} [GeV/c]");
    gm->SetName("graph_wn_acjqpt_mean");
    
    gs = new TGraph(nu,x,ys);
    gs->SetTitle("Jet resolution as a function of quark p_{T};quark-p_{T} [GeV/c];#sigma [GeV/c]");
    gs->SetName("graph_wn_acjqpt_sigma");
    
    gm->SetLineColor(4);
    gs->SetLineColor(4);

    gm->Write();
    gs->Write();

    for(int i = FIRST_BIN; i < LAST_BIN; i++){
        name<<"proj_sjqpt_"<<i;
        cout<<name.str()<<endl;
        hproj = (TH1F*)hJetsQuarksStrangePt->ProjectionY((name.str()).c_str(),i-10,i+10);
        maxbin = hproj->GetMaximumBin();
        
        TF1 *sgs = new TF1("sgs","gaus(0)",hproj->GetBinCenter(maxbin-5),hproj->GetBinCenter(maxbin+5));
        hproj->GetXaxis()->SetRange(maxbin-5,maxbin+5);
        sgs->SetParameters(hproj->GetMaximum(),hproj->GetBinCenter(maxbin),2);
        sgs->SetLineColor(6);
        hproj->Fit(sgs);

        x[i-FIRST_BIN] = hproj->GetXaxis()->GetBinCenter(i);
        ym[i-FIRST_BIN] = sgs->GetParameter(1);
        ys[i-FIRST_BIN] = sgs->GetParameter(2);

        name.str("");
        hproj->Write();
    }
    gm = new TGraph(nu,x,ym);
    gm->SetTitle("Mean jet p_{T} as a function of quark p_{T};quark-p_{T} [GeV/c];jet-p_{T} [GeV/c]");
    gm->SetName("graph_wn_sjqpt_mean");
    
    gs = new TGraph(nu,x,ys);
    gs->SetTitle("Jet resolution as a function of quark p_{T};quark-p_{T} [GeV/c];#sigma [GeV/c]");
    gs->SetName("graph_wn_sjqpt_sigma");
    
    gm->SetLineColor(4);
    gs->SetLineColor(4);

    gm->Write();
    gs->Write();

    for(int i = FIRST_BIN; i < LAST_BIN; i++){
        name<<"proj_asjqpt_"<<i;
        cout<<name.str()<<endl;
        hproj = (TH1F*)hJetsQuarksAntiStrangePt->ProjectionY((name.str()).c_str(),i-10,i+10);
        maxbin = hproj->GetMaximumBin();
        
        TF1 *sgas = new TF1("sgas","gaus(0)",hproj->GetBinCenter(maxbin-5),hproj->GetBinCenter(maxbin+5));
        hproj->GetXaxis()->SetRange(maxbin-5,maxbin+5);
        sgas->SetParameters(hproj->GetMaximum(),hproj->GetBinCenter(maxbin),2);
        sgas->SetLineColor(6);
        hproj->Fit(sgas);

        x[i-FIRST_BIN] = hproj->GetXaxis()->GetBinCenter(i);
        ym[i-FIRST_BIN] = sgas->GetParameter(1);
        ys[i-FIRST_BIN] = sgas->GetParameter(2);

        name.str("");
        hproj->Write();
    }
    gm = new TGraph(nu,x,ym);
    gm->SetTitle("Mean jet p_{T} as a function of quark p_{T};quark-p_{T} [GeV/c];jet-p_{T} [GeV/c]");
    gm->SetName("graph_wn_asjqpt_mean");
    
    gs = new TGraph(nu,x,ys);
    gs->SetTitle("Jet resolution as a function of quark p_{T};quark-p_{T} [GeV/c];#sigma [GeV/c]");
    gs->SetName("graph_wn_asjqpt_sigma");
    
    gm->SetLineColor(4);
    gs->SetLineColor(4);

    gm->Write();
    gs->Write();
    
}

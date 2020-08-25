//Samuel P P Silveira, Universidade Federal do ABC, 2020

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


void mergingPtMatchesGraphs(int n, double r, double m, int jobs){

    auto c1 = new TCanvas("c1","c1",1000,550);
    gPad->SetGridy();
    gPad->SetTickx();
    gPad->SetTicky();

    stringstream header, output, headerwn;
    header<<"OUTPUT/Histograms_Output/"<<n<<"_"<<r<<"_"<<m<<"_"<<jobs<<"/100M_"<<r<<"_"<<m<<"_projections.root";
    headerwn<<"OUTPUT_WN/Histograms_Output/"<<n<<"_"<<r<<"_"<<m<<"_"<<jobs<<"/100M_"<<r<<"_"<<m<<"_projections.root";
    output<<"100M_"<<r<<"_"<<m<<"_mergeGraphs.root";
    
    TFile *file = new TFile((header.str()).c_str());
    TFile *filewn = new TFile((headerwn.str()).c_str());

    TFile fout((output.str()).c_str(),"recreate");

    TGraph *charmmean = (TGraph*)file->Get("graph_cjqpt_mean");
    TGraph *charmwnmean = (TGraph*)filewn->Get("graph_wn_cjqpt_mean");

    charmmean->Draw();
    charmwnmean->Draw("SAME");


    TLegend *legend = new TLegend(0.15,0.65,0.4,0.85);
    legend->SetTextFont(72);
    legend->SetTextSize(0.02);
    legend->SetHeader("Legend","C");
    legend->AddEntry(charmmean,"No neutrinos","l");
    legend->AddEntry(charmwnmean,"With neutrinos","l");
    legend->Draw("SAME");

    c1->SetName("charmsmean");
    c1->Write();



    TGraph *charmsigma = (TGraph*)file->Get("graph_cjqpt_sigma");
    TGraph *charmwnsigma = (TGraph*)filewn->Get("graph_wn_cjqpt_sigma");

    charmsigma->Draw();
    charmwnsigma->Draw("SAME");

    legend = new TLegend(0.15,0.65,0.4,0.85);
    legend->SetTextFont(72);
    legend->SetTextSize(0.02);
    legend->SetHeader("Legend","C");
    legend->AddEntry(charmsigma,"No neutrinos","l");
    legend->AddEntry(charmwnsigma,"With neutrinos","l");
    legend->Draw("SAME");

    c1->SetName("charmssigma");
    c1->Write();





    TGraph *anticharmmean = (TGraph*)file->Get("graph_acjqpt_mean");
    TGraph *anticharmwnmean = (TGraph*)filewn->Get("graph_wn_acjqpt_mean");

    anticharmmean->Draw();
    anticharmwnmean->Draw("SAME");


    legend = new TLegend(0.15,0.65,0.4,0.85);
    legend->SetTextFont(72);
    legend->SetTextSize(0.02);
    legend->SetHeader("Legend","C");
    legend->AddEntry(anticharmmean,"No neutrinos","l");
    legend->AddEntry(anticharmwnmean,"With neutrinos","l");
    legend->Draw("SAME");

    c1->SetName("anticharmsmean");
    c1->Write();



    TGraph *anticharmsigma = (TGraph*)file->Get("graph_acjqpt_sigma");
    TGraph *anticharmwnsigma = (TGraph*)filewn->Get("graph_wn_acjqpt_sigma");

    anticharmsigma->Draw();
    anticharmwnsigma->Draw("SAME");

    legend = new TLegend(0.15,0.65,0.4,0.85);
    legend->SetTextFont(72);
    legend->SetTextSize(0.02);
    legend->SetHeader("Legend","C");
    legend->AddEntry(anticharmsigma,"No neutrinos","l");
    legend->AddEntry(anticharmwnsigma,"With neutrinos","l");
    legend->Draw("SAME");

    c1->SetName("anticharmssigma");
    c1->Write();




    TGraph *strangemean = (TGraph*)file->Get("graph_sjqpt_mean");
    TGraph *strangewnmean = (TGraph*)filewn->Get("graph_wn_sjqpt_mean");

    strangemean->Draw();
    strangewnmean->Draw("SAME");


    legend = new TLegend(0.15,0.65,0.4,0.85);
    legend->SetTextFont(72);
    legend->SetTextSize(0.02);
    legend->SetHeader("Legend","C");
    legend->AddEntry(strangemean,"No neutrinos","l");
    legend->AddEntry(strangewnmean,"With neutrinos","l");
    legend->Draw("SAME");

    c1->SetName("strangesmean");
    c1->Write();



    TGraph *strangesigma = (TGraph*)file->Get("graph_sjqpt_sigma");
    TGraph *strangewnsigma = (TGraph*)filewn->Get("graph_wn_sjqpt_sigma");

    strangesigma->Draw();
    strangewnsigma->Draw("SAME");

    legend = new TLegend(0.15,0.65,0.4,0.85);
    legend->SetTextFont(72);
    legend->SetTextSize(0.02);
    legend->SetHeader("Legend","C");
    legend->AddEntry(strangesigma,"No neutrinos","l");
    legend->AddEntry(strangewnsigma,"With neutrinos","l");
    legend->Draw("SAME");

    c1->SetName("strangessigma");
    c1->Write();





    TGraph *antistrangemean = (TGraph*)file->Get("graph_asjqpt_mean");
    TGraph *antistrangewnmean = (TGraph*)filewn->Get("graph_wn_asjqpt_mean");

    antistrangemean->Draw();
    antistrangewnmean->Draw("SAME");


    legend = new TLegend(0.15,0.65,0.4,0.85);
    legend->SetTextFont(72);
    legend->SetTextSize(0.02);
    legend->SetHeader("Legend","C");
    legend->AddEntry(antistrangemean,"No neutrinos","l");
    legend->AddEntry(antistrangewnmean,"With neutrinos","l");
    legend->Draw("SAME");

    c1->SetName("antistrangesmean");
    c1->Write();



    TGraph *antistrangesigma = (TGraph*)file->Get("graph_asjqpt_sigma");
    TGraph *antistrangewnsigma = (TGraph*)filewn->Get("graph_wn_asjqpt_sigma");

    antistrangesigma->Draw();
    antistrangewnsigma->Draw("SAME");

    legend = new TLegend(0.15,0.65,0.4,0.85);
    legend->SetTextFont(72);
    legend->SetTextSize(0.02);
    legend->SetHeader("Legend","C");
    legend->AddEntry(antistrangesigma,"No neutrinos","l");
    legend->AddEntry(antistrangewnsigma,"With neutrinos","l");
    legend->Draw("SAME");

    c1->SetName("antistrangessigma");
    c1->Write();


}
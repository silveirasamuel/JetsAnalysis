{
   TCanvas *c1 = new TCanvas("c1","c1",600,400);
   // create/fill draw h1
   gStyle->SetOptStat(kFALSE);
   TH1F *h1 = new TH1F("h1","Superimposing two histograms with different scales",100,-3,3);
   Int_t i;
   for (i=0;i<10000;i++) h1->Fill(gRandom->Gaus(0,1));
   h1->Draw();
   c1->Update();

   return c1;
}
THStack* plot(TString detector, TString particle, TString cut, TString plottype){
  
   std::vector<TString> fname;
   fname.push_back("../../analysed_output/removeColl6AB/elastic.root");
   fname.push_back("../../analysed_output/removeColl6AB_3mmoff/elastic.root");
   fname.push_back("../../analysed_output/removeColl6AB_3mmoff_real_asymmetric/elastic.root");
  
   std::vector<TFile*> f;
   std::vector<TH1D*> h;
   THStack hs;
   for(int i=0; i<fname.size(); i++){
    TString part= fname[i]+"_"+detector+"_"+cut+"_xy_"+particle;
    f.push_back(new TFile(fname[i]));
    h.push_back((TH1D*) ((TDirectory*) f[i]->Get(detector))->Get(detector+"_"+cut+"_"+plottype+"_"+particle));
    h[i]->SetLineColor(i+1);
    h[i]->SetDirectory(0);
    std::cout<< part.Data()<< " " << h[i]->Integral()*70/1e9 << std::endl;
    hs.Add(h[i]);   
   }
  

  
return hs;  
}

int plot1D( TString particle, TString cut, TString plottype){
 std::vector<TString> det{"MD", "Col4Ent", "Col4Exit", "Col6AEnt", "Col6AMid", "Col6AExit", "Col6BEnt", "Col6BMid", "Col6BExit"};
 std::map<TString, TString> zloc{ {"MD", "22200"}, \
                                   {"Col4Ent", "3225-0.5"}, \
                                   {"Col4Exit", "3225+150+0.5"}, \
                                   {"Col6AEnt", "9555.904-0.5"}, \
                                   {"Col6AMid", "9638.454-0.5"}, \
                                   {"Col6AExit", "9638.454+69.850+0.5"}, \
                                   {"Col6BEnt", "10927.504-0.5"}, \
                                   {"Col6BMid", "11010.054-0.5"}, \
                                   {"Col6BExit", "11010.054+69.850+0.5"}  };
  TCanvas *c=new TCanvas("c", "c", 1200, 1000);
  c->Divide(3,3);
  for (int i =0 ; i< det.size(); i++){
    c->cd(i+1);
    gPad->SetMargin(0.13,0.13,0.13,0.13);
    THStack hs = plot(det[i],particle, cut, plottype);
    hs.Draw("HISTnostack");
  }
  c->cd(0);
  c->Print(particle+"_"+"_"+cut+"_"+plottype+".pdf");
  return 0;

}

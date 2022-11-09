int plotXY(TString filename, TString particle, TString cut){
  
  TFile *f = new TFile(filename+"/elastic.root");
  
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
  
  TCanvas *c=new TCanvas();
  c->Divide(3,3);
  for (int i =0 ; i< det.size(); i++){
    c[i]->cd(); 
    gPad->SetMargin(0.13,0.13,0.13,0.13);
    TH2D* h = (TH2D*) ((TDirectory*) f->Get(det[0]))->Get(det[0]+"_"+cut+"_xy_"+particle));
    h->Draw("colz");
    h->SetDirectory(0);
  }
  c->Print(filename+"/"+cut+"_"+particle);
    
  }
  
return 0;  
}

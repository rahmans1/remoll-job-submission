### Track particles from target region coming through collimator 4 bore and hitting main detector 

void isValid(std::vector<remollGenericDetectorHit_t> *fHit, std::vector<int> &det28trid, std::vector<int> &Ring5trid, std::vector<int> &Boretrid, std::vector<int> &Acceptancetrid);

int analyse(TString source, TString out, TString gen, TString detid, TString writeState)
{
  TChain T("T");
  T.Add(Form("%s", source.Data())); // Adding source file
  Int_t nEvents= T.GetEntries();  // Number of primary events
  Double_t weight= 1.0/85; // Divide by current. So, the Y-axis gets units of Hz/uA
  
  TFile* f = new TFile(Form("%s", out.Data()), writeState);
  TDirectory* subdir = f->mkdir(detid);
  
  std::vector<TString> ptype;
  ptype.push_back("all");
  ptype.push_back("electron");
  ptype.push_back("positron");
  ptype.push_back("photon");
  ptype.push_back("neutron");
  
  std::vector<TString> ctype;
  ctype.push_back("nocut");
  ctype.push_back("col4bore");
  ctype.push_back("col4boreandacceptance");
  
  std::map<TString, Int_t> nbin{ {"MD_nocut", 1500}, \
                                 {"MD_nocut", 1500}, \
                                 {"Col4Ent", 100}, \
                                 {"Col4Exit", 100}, \
                                 {"Col6AEnt", 140}, \
                                 {"Col6AMid", 140}, \
                                 {"Col6AExit", 140}, \
                                 {"Col6BEnt", 140}, \
                                 {"Col6BMid", 140}, \
                                 {"Col6BExit", 140} };
  std::map<TString, Double_t> min{ {"MD", -1500}, \
                                       {"Col4Ent", -500}, \
                                       {"Col4Exit", -500}, \
                                       {"Col6AEnt", -700}, \
                                       {"Col6AMid", -700}, \
                                       {"Col6AExit", -700}, \
                                       {"Col6BEnt", -700}, \
                                       {"Col6BMid", -700}, \
                                       {"Col6BExit", -700} };
  std::map<TString, Double_t> max{ {"MD", 1500}, \
                                       {"Col4Ent", 500}, \
                                       {"Col4Exit", 500}, \
                                       {"Col6AEnt", 700}, \
                                       {"Col6AMid", 700}, \
                                       {"Col6AExit", 700}, \
                                       {"Col6BEnt", 700}, \
                                       {"Col6BMid", 700}, \
                                       {"Col6BExit", 700} };
  
 
  
  
  std::map<TString, TH2D*> h_xy;
  std::map<TString, TH1D*> h_r;
  std::map<TString, TH1D*> h_e;

  for(Int_t i=0; i<ptype.size(); i++){
   for(Int_t j=0; j<ctype.size(); j++){
   part= Form("%s_%s_%s", detector.Data(), ptype.Data(), ctype.data());
   h_xy[part]=new TH1D(part+"_xy", Form("%s_xy rate-weighted distro, Generator=%s", part.Data(), gen.Data()), , -500, 500, 100, -500, 500);
   h_r[part]=new TH2D(part+"_r", Form("%s_r rate-weighted distro, Generator=%s", part.Data(), gen.Data()), 300, 0, 1500);
   h_e[part]=new TH2D(part+"_e", Form("%s_prpz rate-weighted distribution, Generator=%s", part.Data(), gen.Data()), 100, 0, 11000);
   }  
  }

  
  
  
  std::map<TString, Int_t> detector_cut{ {"MD", hit.det==28}, \
                                         {"Col4Ent", hit.det==44}, \
                                         {"Col4Exit", hit.det==45}, \
                                         {"Col6AEnt", hit.det==66}, \
                                         {"Col6AMid", hit.det==68}, \
                                         {"Col6AExit", hit.det==69}, \
                                         {"Col6BEnt", hit.det==72}, \
                                         {"Col6BMid", hit.det==73}, \
                                         {"Col6BExit", hit.det==74} };
  return 0; 
}

void isValid(std::vector<remollGenericDetectorHit_t> *fHit, std::vector<int> &det28trid, std::vector<int> &Ring5trid, std::vector<int> &Boretrid,  std::vector<int> &Acceptancetrid)
{
  for(size_t i=0;i<fHit->size();i++){
    remollGenericDetectorHit_t hit=fHit->at(i);
    int det = hit.det;
    int pid = hit.pid;
    if(det==28 && hit.r>=650 && hit.r<=1160 && hit.vz<=-3875){
        det28trid.push_back(hit.trid);
    }
    if(det==28 && hit.r>=920 && hit.r<=1060 && hit.vz<=-3875){
        Ring5trid.push_back(hit.trid);
    }
    if(det==44 && hit.r<=40 && hit.vz<=-3875){
        Boretrid.push_back(hit.trid);
    }
    if(det==44 && hit.r<=210 && hit.vz<=-3875){
        Acceptancetrid.push_back(hit.trid);
    }
}

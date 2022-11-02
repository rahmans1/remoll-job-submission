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
  
  std::map<TString, Int_t> nbinx_xy;
  std::map<TString, Int_t> nbiny_xy;
  std::map<TString, Double_t> minx_xy;
  std::map<TString, Double_t> maxx_xy;
  std::map<TString, Double_t> miny_xy;
  std::map<TString, Double_t> maxy_xy;
  std::map<TString, Int_t> nbin_r;
  std::map<TString, Double_t> min_r;
  std::map<TString, Double_t> max_r;
  std::map<TString, Int_t> nbin_e; 
  std::map<TString, Double_t> min_e;
  std::map<TString, Double_t> max_e;
  
  
  std::map<TString, TH2D*> h_xy;
  std::map<TString, TH1D*> h_r;
  std::map<TString, TH1D*> h_e;

  for(Int_t i=0; i<ptype.size(); i++){
   for(Int_t j=0; j<ctype.size(); j++){
   part= Form("pr_%s_%s_%s_%s_%s", detector.Data(), sector[j].Data(), pid.Data(), photon_ene[k].Data(), photon_mom[l].Data());
   h_xy[part]=new TH1D(part+"_xy", Form("%s_xy rate-weighted distro, Generator=%s", part.Data(), gen.Data()), , -500, 500, 100, -500, 500);
   h_r[part]=new TH2D(part+"_r", Form("%s_r rate-weighted distro, Generator=%s", part.Data(), gen.Data()), 300, 0, 1500);
   h_e[part]=new TH2D(part+"_e", Form("%s_prpz rate-weighted distribution, Generator=%s", part.Data(), gen.Data()), 100, 0, 11000);
   }  
  }

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

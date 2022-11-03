### Track particles from target region coming through collimator 4 bore and hitting main detector 
#include <iostream>
#include <map>
#include <tuple>
#include <vector>

using std::map;
using std::vector;
using std::string;
using std::tuple;
using std::make_tuple;
using std::cout;
using std::endl;


void isValid(std::vector<remollGenericDetectorHit_t> *fHit, std::vector<int> &det28trid, std::vector<int> &Ring5trid, std::vector<int> &Boretrid, std::vector<int> &Acceptancetrid);

int analyse(TString source, TString out, TString gen, TString detector, TString writeState)
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
  ctype.push_back("col4all");
  
  std::map<TString, std::tuple<Int_t,Double_t,Double_t>> bins{ 
                                 {"MD_nocut_xy", std::make_tuple{1500, }, \
                                 {"MD_col4bore_xy", std::make_tuple{1500, }}, \
                                 {"MD_col4all_xy", std::make_tuple{1500, }}, \
                                 {"MD_nocut_r", std::make_tuple{1500, }}, \
                                 {"MD_col4bore_r", std::make_tuple{1500, }}, \
                                 {"MD_col4all_r", std::make_tuple{1500, }}, \
                                 {"MD_nocut_e", std::make_tuple{1500, }}, \
                                 {"MD_col4bore_e", std::make_tuple{1500, }}, \
                                 {"MD_col4all_e", std::make_tuple{1500, }}, \
                                 {"Col4Ent_nocut_xy", std::make_tuple{1500, }}, \
                                 {"Col4Ent_col4bore_xy", std::make_tuple{1500, }}, \
                                 {"Col4Ent_col4all_xy", std::make_tuple{1500, }}, \
                                 {"Col4Ent_nocut_r", std::make_tuple{1500, }}, \
                                 {"Col4Ent_col4bore_r", std::make_tuple{1500, }}, \
                                 {"Col4Ent_col4all_r", std::make_tuple{1500, }}, \
                                 {"Col4Ent_nocut_e", std::make_tuple{1500, }}, \
                                 {"Col4Ent_col4bore_e", std::make_tuple{1500, }}, \
                                 {"Col4Ent_col4all_e", std::make_tuple{1500, }}, \
                                 {"Col4Exit_nocut_xy", std::make_tuple{1500, }}, \
                                 {"Col4Exit_col4bore_xy", std::make_tuple{1500, }}, \
                                 {"Col4Exit_col4all_xy", std::make_tuple{1500, }}, \
                                 {"Col4Exit_nocut_r", std::make_tuple{1500, }}, \
                                 {"Col4Exit_col4bore_r", std::make_tuple{1500, }}, \
                                 {"Col4Exit_col4all_r", std::make_tuple{1500, }}, \
                                 {"Col4Exit_nocut_e", std::make_tuple{1500, }}, \
                                 {"Col4Exit_col4bore_e", std::make_tuple{1500, }}, \
                                 {"Col4Exit_col4all_e", std::make_tuple{1500, }}, \
                                 {"Col6AEnt_nocut_xy", std::make_tuple{1500, }}, \
                                 {"Col6AEnt_col4bore_xy", std::make_tuple{1500, }}, \
                                 {"Col6AEnt_col4all_xy", std::make_tuple{1500, }}, \
                                 {"Col6AEnt_nocut_r", std::make_tuple{1500, }}, \
                                 {"Col6AEnt_col4bore_r", std::make_tuple{1500, }}, \
                                 {"Col6AEnt_col4all_r", std::make_tuple{1500, }}, \
                                 {"Col6AEnt_nocut_e", std::make_tuple{1500, }}, \
                                 {"Col6AEnt_col4bore_e", std::make_tuple{1500, }}, \
                                 {"Col6AEnt_col4all_e", std::make_tuple{1500, }}, \
                                 {"Col6AMid_nocut_xy", std::make_tuple{1500, }}, \
                                 {"Col6AMid_col4bore_xy", std::make_tuple{1500, }}, \
                                 {"Col6AMid_col4all_xy", std::make_tuple{1500, }}, \
                                 {"Col6AMid_nocut_r", std::make_tuple{1500, }}, \
                                 {"Col6AMid_col4bore_r", std::make_tuple{1500, }}, \
                                 {"Col6AMid_col4all_r", std::make_tuple{1500, }}, \
                                 {"Col6AMid_nocut_e", std::make_tuple{1500, }}, \
                                 {"Col6AMid_col4bore_e", std::make_tuple{1500, }}, \
                                 {"Col6AMid_col4all_e", std::make_tuple{1500, }}, \
                                 {"Col6AExit_nocut_xy", std::make_tuple{1500, }}, \
                                 {"Col6AExit_col4bore_xy", std::make_tuple{1500, }}, \
                                 {"Col6AExit_col4all_xy", std::make_tuple{1500, }}, \
                                 {"Col6AExit_nocut_r", std::make_tuple{1500, }}, \
                                 {"Col6AExit_col4bore_r", std::make_tuple{1500, }}, \
                                 {"Col6AExit_col4all_r", std::make_tuple{1500, }}, \
                                 {"Col6AExit_nocut_e", std::make_tuple{1500, }}, \
                                 {"Col6AExit_col4bore_e", std::make_tuple{1500, }}, \
                                 {"Col6AExit_col4all_e", std::make_tuple{1500, }}, \
                                 {"Col6BEnt_nocut_xy", std::make_tuple{1500, }}, \
                                 {"Col6BEnt_col4bore_xy", std::make_tuple{1500, }}, \
                                 {"Col6BEnt_col4all_xy", std::make_tuple{1500, }}, \
                                 {"Col6BEnt_nocut_r", std::make_tuple{1500, }}, \
                                 {"Col6BEnt_col4bore_r", std::make_tuple{1500, }}, \
                                 {"Col6BEnt_col4all_r", std::make_tuple{1500, }}, \
                                 {"Col6BEnt_nocut_e", std::make_tuple{1500, }}, \
                                 {"Col6BEnt_col4bore_e", std::make_tuple{1500, }}, \
                                 {"Col6BEnt_col4all_e", std::make_tuple{1500, }}, \
                                 {"Col6BMid_nocut_xy", std::make_tuple{1500, }}, \
                                 {"Col6BMid_col4bore_xy", std::make_tuple{1500, }}, \
                                 {"Col6BMid_col4all_xy", std::make_tuple{1500, }}, \
                                 {"Col6BMid_nocut_r", std::make_tuple{1500, }}, \
                                 {"Col6BMid_col4bore_r", std::make_tuple{1500, }}, \
                                 {"Col6BMid_col4all_r", std::make_tuple{1500, }}, \
                                 {"Col6BMid_nocut_e", std::make_tuple{1500, }}, \
                                 {"Col6BMid_col4bore_e", std::make_tuple{1500, }}, \
                                 {"Col6BMid_col4all_e", std::make_tuple{1500, }}, \
                                 {"Col6BExit_nocut_xy", std::make_tuple{1500, }}, \
                                 {"Col6BExit_col4bore_xy", std::make_tuple{1500, }}, \
                                 {"Col6BExit_col4all_xy", std::make_tuple{1500, }}, \
                                 {"Col6BExit_nocut_r", std::make_tuple{1500, }}, \
                                 {"Col6BExit_col4bore_r", std::make_tuple{1500, }}, \
                                 {"Col6BExit_col4all_r", std::make_tuple{1500, }}, \
                                 {"Col6BExit_nocut_e", std::make_tuple{1500, }}, \
                                 {"Col6BExit_col4bore_e", std::make_tuple{1500, }}, \
                                 {"Col6BExit_col4all_e", std::make_tuple{1500, }} };
                                  
  std::map<TString, TH2D*> h_xy;
  std::map<TString, TH1D*> h_r;
  std::map<TString, TH1D*> h_e;

  for(Int_t i=0; i<ptype.size(); i++){
   for(Int_t j=0; j<ctype.size(); j++){
   part= Form("%s_%s", detector.Data(), ctype.data());
   h_xy[part+"_xy"+"_"+ptype]=new TH2D(part+"_xy"+"_"+ptype, Form("%s_xy_%s rate-weighted distro, Generator=%s", part.Data(), ptype.Data(), gen.Data()), \
                                       get<0>bins[part+"_xy"],get<1>bins[part+"_xy"],get<2>bins[part+"_xy"],get<0>bins[part+"_xy"],get<1>bins[part+"_xy"],get<2>bins[part+"_xy"]);
   h_r[part+"_r"+"_"+ptype]=new TH1D(part+"_r"+"_"+ptype, Form("%s_r_%s rate-weighted distro, Generator=%s", ptype.Data(), gen.Data()), get<0>bins[part+"_r"],get<1>bins[part+"_r"],get<2>bins[part+"_r"]);
   h_e[part+"_e"+"_"+ptype]=new TH1D(part+"_e"+"_"+ptype, Form("%s_e_%s rate-weighted distro, Generator=%s", ptype.Data(), gen.Data()), get<0>bins[part+"_e"],get<1>bins[part+"_e"],get<2>bins[part+"_e"]);
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

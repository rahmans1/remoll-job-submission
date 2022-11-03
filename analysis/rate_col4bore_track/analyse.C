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
  Int_t nEvents= T.GetEntries();    // Number of primary events
  Double_t weight= 1.0/85;          // Divide by current. So, the Y-axis gets units of Hz/uA
  
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
  ctype.push_back("col4bore_MD");
  ctype.push_back("col4all_MD");
  ctype.push_back("col4bore_R5");
  ctype.push_back("col4all_R5");
  
  std::vector<TString> plottype;
  ctype.push_back("xy");
  ctype.push_back("r");
  ctype.push_back("e");
  
  std::map<TString, std::tuple<Int_t,Double_t,Double_t>> bins{ 
                                 {"MD_nocut_xy", std::make_tuple{1500, -1500, 1500}, \
                                 {"MD_col4bore_MD_xy", std::make_tuple{1500, -1500, 1500}}, \
                                 {"MD_col4all_MD_xy", std::make_tuple{1500, -1500, 1500}}, \
                                 {"MD_col4bore_R5_xy", std::make_tuple{1500, -1500, 1500}}, \
                                 {"MD_col4all_R5_xy", std::make_tuple{1500, -1500, 1500}}, \
                                 {"MD_nocut_r", std::make_tuple{800, 500, 1300}}, \
                                 {"MD_col4bore_MD_r", std::make_tuple{800, 500, 1300}}, \
                                 {"MD_col4all_MD_r", std::make_tuple{800, 500, 1300}}, \
                                 {"MD_col4bore_R5_r", std::make_tuple{800, 500, 1300}}, \
                                 {"MD_col4all_R5_r", std::make_tuple{800, 500, 1300}}, \
                                 {"MD_nocut_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"MD_col4bore_MD_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"MD_col4all_MD_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"MD_col4bore_R5_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"MD_col4all_R5_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col4Ent_nocut_xy", std::make_tuple{100, -500, 500}}, \
                                 {"Col4Ent_col4bore_MD_xy", std::make_tuple{100, -100, 100}}, \
                                 {"Col4Ent_col4all_MD_xy", std::make_tuple{100, -500, 500}}, \
                                 {"Col4Ent_col4bore_R5_xy", std::make_tuple{100, -100, 100}}, \
                                 {"Col4Ent_col4all_R5_xy", std::make_tuple{100, -500, 500}}, \
                                 {"Col4Ent_nocut_r", std::make_tuple{100, 0, 500}}, \
                                 {"Col4Ent_col4bore_MD_r", std::make_tuple{100, 0, 100}}, \
                                 {"Col4Ent_col4all_MD_r", std::make_tuple{100, 0, 500}}, \
                                 {"Col4Ent_col4bore_R5_r", std::make_tuple{100, 0, 100}}, \
                                 {"Col4Ent_col4all_R5_r", std::make_tuple{100, 0, 500}}, \
                                 {"Col4Ent_nocut_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col4Ent_col4bore_MD_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col4Ent_col4all_MD_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col4Ent_col4bore_R5_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col4Ent_col4all_R5_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col4Exit_nocut_xy", std::make_tuple{100, -500, 500}}, \
                                 {"Col4Exit_col4bore_MD_xy", std::make_tuple{100, -100, 100}}, \
                                 {"Col4Exit_col4all_MD_xy", std::make_tuple{100, -500, 500}}, \
                                 {"Col4Exit_col4bore_R5_xy", std::make_tuple{100, -100, 100}}, \
                                 {"Col4Exit_col4all_R5_xy", std::make_tuple{100, -500, 500}}, \
                                 {"Col4Exit_nocut_r", std::make_tuple{100, 0, 500}}, \
                                 {"Col4Exit_col4bore_MD_r", std::make_tuple{100, 0, 100}}, \
                                 {"Col4Exit_col4all_MD_r", std::make_tuple{100, 0, 500}}, \
                                 {"Col4Exit_col4bore_R5_r", std::make_tuple{100, 0, 100}}, \
                                 {"Col4Exit_col4all_R5_r", std::make_tuple{100, 0, 500}}, \
                                 {"Col4Exit_nocut_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col4Exit_col4bore_MD_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col4Exit_col4all_MD_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col4Exit_col4bore_R5_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col4Exit_col4all_R5_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6AEnt_nocut_xy", std::make_tuple{200, -1000, 1000}}, \
                                 {"Col6AEnt_col4bore_MD_xy", std::make_tuple{200, -200, 200}}, \
                                 {"Col6AEnt_col4all_MD_xy", std::make_tuple{120, -600, 600}}, \
                                 {"Col6AEnt_col4bore_R5_xy", std::make_tuple{200, -200, 200}}, \
                                 {"Col6AEnt_col4all_R5_xy", std::make_tuple{120, -600, 600}}, \
                                 {"Col6AEnt_nocut_r", std::make_tuple{1500, 0, 1500}}, \
                                 {"Col6AEnt_col4bore_MD_r", std::make_tuple{200, 0, 200}}, \
                                 {"Col6AEnt_col4all_MD_r", std::make_tuple{600, 0, 600}}, \
                                 {"Col6AEnt_col4bore_R5_r", std::make_tuple{200, 0, 200}}, \
                                 {"Col6AEnt_col4all_R5_r", std::make_tuple{600, 0, 600}}, \
                                 {"Col6AEnt_nocut_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6AEnt_col4bore_MD_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6AEnt_col4all_MD_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6AEnt_col4bore_R5_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6AEnt_col4all_R5_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6AMid_nocut_xy", std::make_tuple{200, -1000, 1000}}, \
                                 {"Col6AMid_col4bore_MD_xy", std::make_tuple{200, -200, 200}}, \
                                 {"Col6AMid_col4all_MD_xy", std::make_tuple{120, -600, 600}}, \
                                 {"Col6AMid_col4bore_R5_xy", std::make_tuple{200, -200, 200}}, \
                                 {"Col6AMid_col4all_R5_xy", std::make_tuple{120, -600, 600}}, \
                                 {"Col6AMid_nocut_r", std::make_tuple{1500, 0, 1500}}, \
                                 {"Col6AMid_col4bore_MD_r", std::make_tuple{200, 0, 200}}, \
                                 {"Col6AMid_col4all_MD_r", std::make_tuple{600, 0, 600}}, \
                                 {"Col6AMid_col4bore_R5_r", std::make_tuple{200, 0, 200}}, \
                                 {"Col6AMid_col4all_R5_r", std::make_tuple{600, 0, 600}}, \
                                 {"Col6AMid_nocut_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6AMid_col4bore_MD_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6AMid_col4all_MD_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6AMid_col4bore_R5_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6AMid_col4all_R5_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6AExit_nocut_xy", std::make_tuple{200, -1000, 1000}}, \
                                 {"Col6AExit_col4bore_MD_xy", std::make_tuple{200, -200, 200}}, \
                                 {"Col6AExit_col4all_MD_xy", std::make_tuple{120, -600, 600}}, \
                                 {"Col6AExit_col4bore_R5_xy", std::make_tuple{200, -200, 200}}, \
                                 {"Col6AExit_col4all_R5_xy", std::make_tuple{120, -600, 600}}, \
                                 {"Col6AExit_nocut_r", std::make_tuple{1500, 0, 1500}}, \
                                 {"Col6AExit_col4bore_MD_r", std::make_tuple{200, 0, 200}}, \
                                 {"Col6AExit_col4all_MD_r", std::make_tuple{600, 0, 600}}, \
                                 {"Col6AExit_col4bore_R5_r", std::make_tuple{200, 0, 200}}, \
                                 {"Col6AExit_col4all_R5_r", std::make_tuple{600, 0, 600}}, \
                                 {"Col6AExit_nocut_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6AExit_col4bore_MD_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6AExit_col4all_MD_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6AExit_col4bore_R5_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6AExit_col4all_R5_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6BEnt_nocut_xy", std::make_tuple{200, -1000, 1000}}, \
                                 {"Col6BEnt_col4bore_MD_xy", std::make_tuple{200, -200, 200}}, \
                                 {"Col6BEnt_col4all_MD_xy", std::make_tuple{120, -600, 600}}, \
                                 {"Col6BEnt_col4bore_R5_xy", std::make_tuple{200, -200, 200}}, \
                                 {"Col6BEnt_col4all_R5_xy", std::make_tuple{120, -600, 600}}, \
                                 {"Col6BEnt_nocut_r", std::make_tuple{1500, 0, 1500}}, \
                                 {"Col6BEnt_col4bore_MD_r", std::make_tuple{200, 0, 200}}, \
                                 {"Col6BEnt_col4all_MD_r", std::make_tuple{600, 0, 600}}, \
                                 {"Col6BEnt_col4bore_R5_r", std::make_tuple{200, 0, 200}}, \
                                 {"Col6BEnt_col4all_R5_r", std::make_tuple{600, 0, 600}}, \
                                 {"Col6BEnt_nocut_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6BEnt_col4bore_MD_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6BEnt_col4all_MD_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6BEnt_col4bore_R5_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6BEnt_col4all_R5_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6BMid_nocut_xy", std::make_tuple{200, -1000, 1000}}, \
                                 {"Col6BMid_col4bore_MD_xy", std::make_tuple{200, -200, 200}}, \
                                 {"Col6BMid_col4all_MD_xy", std::make_tuple{120, -600, 600}}, \
                                 {"Col6BMid_col4bore_R5_xy", std::make_tuple{200, -200, 200}}, \
                                 {"Col6BMid_col4all_R5_xy", std::make_tuple{120, -600, 600}}, \
                                 {"Col6BMid_nocut_r", std::make_tuple{1500, 0, 1500}}, \
                                 {"Col6BMid_col4bore_MD_r", std::make_tuple{200, 0, 200}}, \
                                 {"Col6BMid_col4all_MD_r", std::make_tuple{600, 0, 600}}, \
                                 {"Col6BMid_col4bore_R5_r", std::make_tuple{200, 0, 200}}, \
                                 {"Col6BMid_col4all_R5_r", std::make_tuple{600, 0, 600}}, \
                                 {"Col6BMid_nocut_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6BMid_col4bore_MD_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6BMid_col4all_MD_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6BMid_col4bore_R5_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6BMid_col4all_R5_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6BExit_nocut_xy", std::make_tuple{200, -1000, 1000}}, \
                                 {"Col6BExit_col4bore_MD_xy", std::make_tuple{200, -200, 200}}, \
                                 {"Col6BExit_col4all_MD_xy", std::make_tuple{120, -600, 600}}, \
                                 {"Col6BExit_col4bore_R5_xy", std::make_tuple{200, -200, 200}}, \
                                 {"Col6BExit_col4all_R5_xy", std::make_tuple{120, -600, 600}}, \
                                 {"Col6BExit_nocut_r", std::make_tuple{1500, 0, 1500}}, \
                                 {"Col6BExit_col4bore_MD_r", std::make_tuple{200, 0, 200}}, \
                                 {"Col6BExit_col4all_MD_r", std::make_tuple{600, 0, 600}}, \
                                 {"Col6BExit_col4bore_R5_r", std::make_tuple{200, 0, 200}}, \
                                 {"Col6BExit_col4all_R5_r", std::make_tuple{600, 0, 600}}, \
                                 {"Col6BExit_nocut_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6BExit_col4bore_MD_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6BExit_col4all_MD_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6BExit_col4bore_R5_e", std::make_tuple{1200, 0, 12000}}, \
                                 {"Col6BExit_col4all_R5_e", std::make_tuple{1200, 0, 12000}} };
                                  
  std::map<TString, TH1*> h;
  TString cut;
  TString part;
    
  for(Int_t i=0; i<ptype.size(); i++){
    for(Int_t j=0; j<ctype.size(); j++){
      for(Int_t j=0; k<plottype.size(); k++){ 
        cut= Form("%s_%s_%s", detector.Data(), ctype[j].data(), plottype[k].Data());
        part = Form("%s_%s", cut.Data(), ptype[i].Data());
        if(plottype[k].Sizeof()-1==2){
          h[part]=new TH2D(part, Form("%s rate-weighted distro, Generator=%s", part.Data(), gen.Data()), \
                           get<0>bins[cut],get<1>bins[cut],get<2>bins[cut],get<0>bins[cut],get<1>bins[cut],get<2>bins[cut]);
        }else{
          h[part]=new TH1D(part, Form("%s rate-weighted distro, Generator=%s", part.Data(), gen.Data()), \
                           get<0>bins[cut],get<1>bins[cut],get<2>bins[cut]);
        }
      }
    }  
  } 
    
  Double_t fRate=0;
  remollEvent_t *fEvent=0;
  std::vector<remollGenericDetectorHit_t> *fHit=0;
  std::vector<remollEventParticle_t> *fPart=0;

  T.SetBranchAddress("ev", &fEvent);
  T.SetBranchAddress("hit", &fHit);
  T.SetBranchAddress("rate", &fRate);
  T.SetBranchAddress("part", &fPart);
  
    
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

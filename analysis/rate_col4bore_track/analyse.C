### Track particles from target region coming through collimator 4 bore and hitting main detector 

void isValid(std::vector<remollGenericDetectorHit_t> *fHit, std::vector<int> &det28trid, std::vector<int> &Ring5trid, std::vector<int> &Boretrid, std::vector<int> &Acceptancetrid)
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
}

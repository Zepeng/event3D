/* 
   This software is intended to reconstruct and display
   an event from WCSim root output files in 3D.
   The intentions are for this software to provide a
   3D environment using OpenGL independent of root that
   allows the user to explore the PMT hits by zooming,
   rotating, and translating the origin.
   This software should further be able to analyze an event
   by coloring coding based upon energy as well as making
   various cuts. All of this should be packaged neatly into
   a very simple GUI so that the user doesn't need to
   know the source code to navigate.
*/
#include "handleroot.h"
#include <iostream>

using namespace std;


void handleRoot::fillGeo(TString filename, vector<float> &pmtID, 
	     vector<float> &posX, vector<float> &posY, 
	     vector<float> &posZ){

  TFile *file = new TFile(filename);
  file->cd("AnalysisExample");

  TTree *LBNEGeo = (TTree*)gDirectory->Get("LBNEGeo");
  double OpDetCenter[3];
  LBNEGeo->SetBranchAddress("OpDetCenter",OpDetCenter);

  int numPMTs = LBNEGeo->GetEntries();
  for(int i = 0; i < numPMTs; i++)
  {
    pmtID.push_back(i+1);
    LBNEGeo->GetEntry(i);
    posX.push_back(OpDetCenter[0]);
    posY.push_back(OpDetCenter[1]);
    posZ.push_back(OpDetCenter[2]);
  }
  CylinderHeight = 1400;
  CylinderRadius = 2000;


  delete file;

  return;
}


handleRoot::handleRoot(TString filename, int argc, char **argv, int aEventNum){
  
  /* Set up the LBNE10kt file */
  EventNum = aEventNum;

  fillGeo(filename, pmtID, pmtX, pmtY, pmtZ);

  TFile *f = new TFile(filename);
  f->cd("AnalysisExample");

  //Retrieve the true photon information
  TTree *Photons = (TTree*)gDirectory->Get("PhotonTruth");
  int OpChannel;
  double PhotonTime;
  double numPhotons;
  Photons->SetBranchAddress("OpChannel", &OpChannel);
  Photons->SetBranchAddress("Time", &PhotonTime);
  Photons->SetBranchAddress("PE",&numPhotons);

  //Retrieve the digitized raw data
  TTree *RawData = (TTree*)gDirectory->Get("RawData");
  //int OpChannel;
  double Time;
  int PE;
  RawData->SetBranchAddress("OpChannel",&OpChannel);
  RawData->SetBranchAddress("Time",&Time);
  RawData->SetBranchAddress("PE",&PE);

  vertexTrue[0] = 9;		// Used for error checking in main.cpp
/*
  if(FITA != NULL && truetree != NULL ){
    truetree->SetBranchAddress("vertex", &vertexTrue);
    truetree->SetBranchAddress("direction", &dirTrue);
    FITA->SetBranchAddress("vertex", &vertexReco);
    FITA->SetBranchAddress("direction", &dirReco);
    truetree->GetEntry(EventNum);
    FITA->GetEntry(EventNum);
  }
 */

  totalEvents = Photons->GetEntries();

  //int numHits = totalEvents;
  int numHits = RawData->GetEntries();
  hitX.resize(numHits);
  hitY.resize(numHits);
  hitZ.resize(numHits);
  Pe.resize(numHits);
  time.resize(numHits);


  int j=0;
  for(int i = 0; i < numHits; i ++)
  {
      //Photons->GetEntry(i);
      RawData->GetEntry(i);
      int tubeID = OpChannel;
      //time[j] = PhotonTime;
      time[j] = Time;
      hitX[j] = pmtX[tubeID];
      hitY[j] = pmtY[tubeID];
      hitZ[j] = pmtZ[tubeID];
      //Pe[j] = numPhotons;//PE;
      Pe[j] = PE;
      j++;
  }

  delete f;
  
  return;
}

void handleRoot::returnVectors(vector<float> &pmtid, vector<float> &pmtx, 
			       vector<float> &pmty, vector<float> &pmtz, 
			       vector<float> &hitx, vector<float> &hity, 
			       vector<float> &hitz, vector<float> &pe, 
			       vector<float> &TIME, float &CylHeight,
			       float &CylRadius, int &NumberofEvents,
			       double *vertexT, double *vertexR,
			       double *dirT, double *dirR){

  pmtid = pmtID;
  pmtx = pmtX;
  pmty = pmtY;
  pmtz = pmtZ;
  hitx = hitX;
  hity = hitY;
  hitz = hitZ;
  pe = Pe;
  TIME = time;
  CylHeight = CylinderHeight;
  CylRadius = CylinderRadius;
  NumberofEvents = totalEvents;
  for(int i=0; i<3; i++){
    vertexT[i] = vertexTrue[i];
    dirT[i] = dirTrue[i];
    vertexR[i] = vertexReco[i];
    dirR[i] = dirReco[i];
  }

  return;
}

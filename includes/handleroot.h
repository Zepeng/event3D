#ifndef _HANDLEROOT_
#define _HANDLEROOT_

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

#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include "TROOT.h"
#include "TClass.h"
#include "TClassTable.h"
#include "TCanvas.h"
#include "TCollection.h"
#include "TObject.h"
#include "TSystem.h"
#include "TApplication.h"
#include <cstdlib>
#include <TGClient.h>
#include <TGraph.h>
#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include <sstream>
#include <vector>
using namespace std;

class handleRoot {
  
 private:
  //Private member functions  
  vector<float> pmtID;		/* ID for each pmt */
  vector<float> pmtX;		/* X position of pmts */
  vector<float> pmtY;		/* Y position of pmts */
  vector<float> pmtZ;		/* Z position of pmts */
  vector<float> hitX;		/* X position of cherenkov hit */
  vector<float> hitY;		/* Y position of cherenkov hit */
  vector<float> hitZ;		/* Z position of cherenkov hit */
  vector<float> Pe;		/* hit photoelectrons */
  vector<float> time;		/* pmt hit time */
  float CylinderHeight;	        /* Detector Height */
  float CylinderRadius;	        /* Detector Radius */
  int EventNum;		        /* The current event being read */
  int totalEvents;		/* Total number of events in root file */

  // Reconstruction materials
  double vertexTrue[3];
  double dirTrue[3];
  double vertexReco[3];
  double dirReco[3];
  
 public:
  //Public member functions
  handleRoot(TString filename, int argc, char **argv, int aEventNum);
  void fillGeo(TString filename, vector<float> &pmtID, 
	       vector<float> &pmtX, vector<float> &pmtY, 
	       vector<float> &pmtZ);
  void returnVectors(vector<float> &pmtid, vector<float> &pmtx, 
		     vector<float> &pmty, vector<float> &pmtz, 
		     vector<float> &hitx, vector<float> &hity, 
		     vector<float> &hitz, vector<float> &pe, 
		     vector<float> &TIME, float &CylHeight,
		     float &CylRadius, int &NumberofEvents, 
		     double *vertexT, double *vertexR,
		     double *dirT, double *dirR);
};
#endif

#include "drawevent.h"
#include <iostream>

drawevent::drawevent(float aCylinderRadius, float aCylinderHeight,
		     float aReduction, float aMaxPe, float aUpperTime,
		     float aLowerTime, float aUpperPe, float aLowerPe,
		     float aUpperTimeHisto, float aLowerTimeHisto,
		     float aUpperPeHisto, float aLowerPeHisto,
		     float *aEventPosition, float *aEventDirection, 
		     float aResidualTimeBuffer, int *aRingColor,
		     float aPixel, float aTheta2D, float *aCosTheta, 
		     float *aPhi, float aConeAlpha, int aNumberOfRings,
		     int aColorMethod, float aTau,
		     vector<float> &aHitX, vector<float> &aHitY, vector<float> &aHitZ, 
		     vector<float> &aPe, vector<float> &aTrueTime ){

  PI = 4.0*atan(1);
  setCylinderRadius(aCylinderRadius);
  setCylinderHeight(aCylinderHeight);
  setReduction(aReduction);
  setMaxPe(aMaxPe);
  setUpperTime(aUpperTime);
  setLowerTime(aLowerTime);
  setUpperPeHisto(aUpperPeHisto);
  setLowerPeHisto(aLowerPeHisto);
  setTau(aTau);
  setUpperTimeHisto(aUpperTimeHisto);
  setLowerTimeHisto(aLowerTimeHisto);
  setUpperPe(aUpperPe);
  setLowerPe(aLowerPe);
  setTheta2D(aTheta2D);
  setNumberOfRings(aNumberOfRings);
  setResidualTimeBuffer(aResidualTimeBuffer);
  setPixel(aPixel);
  setHitX(aHitX);
  setHitY(aHitY);
  setHitZ(aHitZ);
  setPe(aPe);
  setTrueTime(aTrueTime);
  setCosTheta(aCosTheta);
  setPhi(aPhi);
  setConeAlpha(aConeAlpha);
  setEventDirection(aEventDirection);
  setEventPosition(aEventPosition);
  setColorMethod(aColorMethod);
  setRingColor(aRingColor);

}
void drawevent::draw2DBackground(){

  glBegin(GL_QUADS);
  glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
  glVertex3f(-2500*3/iReduction, (1500+750)*3/iReduction , 0);
  glVertex3f(-10*3/iReduction, (1500+750)*3/iReduction , 0);
  glVertex3f(-10*3/iReduction, 750*3/iReduction , 0);
  glVertex3f(-2500*3/iReduction, 750*3/iReduction , 0);
  glEnd();
}
void drawevent::draw2DEventPoints(){
  
  float R=0, G=0, B=0;
  float error = 0.01;
  float pixSize = 0;
  float topcolor, bottomcolor;
  vector<float> *colorvector;
  switch (iColorMethod) {
  case 0: // Pe
    topcolor = iUpperPeHisto;
    bottomcolor = iLowerPeHisto;
    colorvector = iPe;
    break;
  case 1: // Time
    topcolor = iUpperTimeHisto;
    bottomcolor = iLowerTimeHisto;
    colorvector = iTrueTime;
    break;
  }

  RGBcolorSpectrum rainbow(topcolor-bottomcolor);

  for ( unsigned int i=0; i < iHitX->size(); i++ ){
    pointmodification thispoint(iPe->at(i), iTrueTime->at(i), iHitX->at(i), 
				iHitY->at(i), iHitZ->at(i),
                                iMaxPe, iUpperTime, iLowerTime, iUpperPe, iLowerPe,
                                iEventPosition, iEventDirection, iTau,
                                iReduction, iResidualTimeBuffer, iPixel);
    //if ( thispoint.firstCuts() ) {
    //  if ( thispoint.secondCuts() ){
        pixSize = thispoint.varyPoints();
	glPointSize(pixSize);
        //glBegin(GL_POINTS);
        glBegin(GL_POLYGON);
	rainbow.returnSpectrum(colorvector->at(i)-bottomcolor, R, G, B);
        glColor3f(R, G, B);
       
        float POSX, POSY;
        if(iHitX->at(i) < -1000)
        {
          POSX = 3*(iHitZ->at(i)-2500)/iReduction;
          POSY = 3*iHitY->at(i)/iReduction;
        }
        else if(iHitX->at(i) < -500)
        {
          POSX = 3*(iHitZ-2500)->at(i)/(iReduction);
          POSY = 3*iHitY->at(i)/(iReduction);
        }
        else if(iHitX->at(i) < 0)
        {
          POSX = 3*(iHitZ->at(i)-2500)/(iReduction);
          POSY = 3*(iHitY->at(i)+1500)/(iReduction);
        }
        else if(iHitX->at(i) < 500)
        {
          POSX = 3*iHitZ->at(i)/(iReduction);
          POSY = 3*(iHitY->at(i)+1500)/(iReduction);
        }
        else if(iHitX->at(i) < 1000)
        {
          POSX = 3*iHitZ->at(i)/(iReduction);
          POSY = 3*iHitY->at(i)/(iReduction);
        }
        else
        {
          POSX = 3*iHitZ->at(i)/(iReduction);
          POSY = 3*(iHitY->at(i)-1500)/(iReduction);
        }
        //float theAngle = atan2(iHitX->at(i), iHitY->at(i));
        glVertex3f(POSX - 225*1.5/iReduction, POSY + 5*3/iReduction , -0.1);
        glVertex3f(POSX + 225*1.5/iReduction, POSY + 5*3/iReduction , -0.1);
        glVertex3f(POSX + 225*1.5/iReduction, POSY - 5*3/iReduction , -0.1);
        glVertex3f(POSX - 225*1.5/iReduction, POSY - 5*3/iReduction , -0.1);
        glEnd();

     // }
   // }
  }

  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_POINTS);
  glVertex3f(0,0,0);
  glEnd();


  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_LINES);
  glVertex2i(0, 10);
  glVertex2i(0, -10);
  glEnd();

  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_LINES);
  glVertex3f(-2500*3/iReduction,750*3/iReduction, 0);
  glVertex3f(2500*3/iReduction, 750*3/iReduction,0);
  glEnd();

  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_LINES);
  glVertex3f(-2500*3/iReduction,-750*3/iReduction, 0);
  glVertex3f(2500*3/iReduction, -750*3/iReduction,0);
  glEnd();
}


void drawevent::draw3DDetector(){
  //LBNE Cryostat dimensions
  float Height = 1500/iReduction;
  float Width  = 1500/iReduction;
  float Length = 2500/iReduction;

  float cR = 1.0, cG = 1.0, cB = 1.0;
  float detectorAlpha = 0.3;
  //Negative X cryostat
  double shift = 150/iReduction;

  //BACK 
  glBegin(GL_POLYGON);
 
  glColor4f(cR, cG, cB, detectorAlpha);
  glVertex3f( -Width-shift, -0.5*Height, 0.  ); 
  glVertex3f( -shift, -0.5*Height , 0.  );   
  glVertex3f( -shift, 0.5*Height, 0. );     
  glVertex3f( -Width-shift, 0.5*Height, 0. );
 
  glEnd();

  //FRONT
  glBegin(GL_POLYGON);
     
  glColor4f(cR, cG, cB, detectorAlpha);
  glVertex3f( -Width-shift, -0.5*Height, Length  );
  glVertex3f( -shift, -.05*Height , Length  );    
  glVertex3f( -shift, 0.5*Height, Length );      
  glVertex3f( -Width-shift, 0.5*Height, Length );
  
  glEnd();

  //TOP
  glBegin(GL_POLYGON);

  glColor4f(cR, cG, cB, detectorAlpha);
  glVertex3f( -Width-shift, 0.5*Height, Length  );
  glVertex3f( -shift, 0.5*Height, Length  );    
  glVertex3f( -shift, 0.5*Height, 0);      
  glVertex3f( -Width-shift, 0.5*Height, 0);

  glEnd();

  //BOTTOM
  glBegin(GL_POLYGON);

  glColor4f(cR, cG, cB, detectorAlpha);
  glVertex3f( -Width-shift, -0.5*Height, Length  );
  glVertex3f( -shift, -0.5*Height, Length  );     
  glVertex3f( -shift, -0.5*Height, 0);      
  glVertex3f( -Width-shift, -0.5*Height, 0);
                                   
  glEnd(); 
 
  //LEFT
  glBegin(GL_POLYGON);

  glColor4f(cR, cG, cB, detectorAlpha);
  glVertex3f( -Width-shift, -0.5*Height, Length  );
  glVertex3f( -Width-shift, -0.5*Height, 0);     
  glVertex3f( -Width-shift, 0.5*Height, 0);      
  glVertex3f( -Width-shift, 0.5*Height, Length);

  glEnd();

  //RIGHT
  glBegin(GL_POLYGON);

  glColor4f(cR, cG, cB, detectorAlpha);
  glVertex3f( -shift, -0.5*Height, Length  );
  glVertex3f( -shift, -0.5*Height, 0);      
  glVertex3f( -shift, 0.5*Height, 0);      
  glVertex3f( -shift, 0.5*Height, Length);
                                                 
  glEnd();

  //Positive X cryostat
  //BACK 
  glBegin(GL_POLYGON);
 
  glColor4f(cR, cG, cB, detectorAlpha);
  glVertex3f( Width+shift, -0.5*Height, 0.  );
  glVertex3f( shift, -0.5*Height, 0.  );     
  glVertex3f( shift, 0.5*Height, 0. );      
  glVertex3f( Width+shift, 0.5*Height, 0. );
 
  glEnd();

  //FRONT
  glBegin(GL_POLYGON);
     
  glColor4f(cR, cG, cB, detectorAlpha);
  glVertex3f( Width+shift, -0.5*Height, Length  );
  glVertex3f( shift, -0.5*Height , Length  );    
  glVertex3f( shift, 0.5*Height, Length );     
  glVertex3f( Width+shift, 0.5*Height, Length );
  
  glEnd();

  //TOP
  glBegin(GL_POLYGON);

  glColor4f(cR, cG, cB, detectorAlpha);
  glVertex3f( Width+shift, 0.5*Height, Length  );
  glVertex3f( shift, 0.5*Height, Length  );    
  glVertex3f( shift, 0.5*Height, 0);      
  glVertex3f( Width+shift, 0.5*Height, 0);

  glEnd();

  //BOTTOM
  glBegin(GL_POLYGON);

  glColor4f(cR, cG, cB, detectorAlpha);
  glVertex3f( Width+shift, -0.5*Height, Length  );
  glVertex3f( shift, -0.5*Height, Length  );   
  glVertex3f( shift, -0.5*Height, 0);     
  glVertex3f( Width+shift, -0.5*Height, 0);     
                                   
  glEnd(); 
 
  //LEFT
  glBegin(GL_POLYGON);

  glColor4f(cR, cG, cB, detectorAlpha);
  glVertex3f( Width+shift, -0.5*Height, Length  ); 
  glVertex3f( Width+shift, -0.5*Height, 0);      
  glVertex3f( Width+shift, 0.5*Height, 0);      
  glVertex3f( Width+shift, 0.5*Height, Length);

  glEnd();

  //RIGHT
  glBegin(GL_POLYGON);

  glColor4f(cR, cG, cB, detectorAlpha);
  glVertex3f( shift, -0.5*Height, Length  );      
  glVertex3f( shift, -0.5*Height, 0);     
  glVertex3f( shift, 0.5*Height, 0);     
  glVertex3f( shift, 0.5*Height, Length);
                                                 
  glEnd(); 

}
void drawevent::draw3DEventPoints(){
 
  float R=0, G=0, B=0;
  float pixSize = 0;
  float topcolor, bottomcolor;
  vector<float> *colorvector;
  switch (iColorMethod) {
  case 0: // Pe
    topcolor = iUpperPeHisto;
    bottomcolor = iLowerPeHisto;
    colorvector = iPe;
    break;
  case 1: // Time
    topcolor = iUpperTimeHisto;
    bottomcolor = iLowerTimeHisto;
    colorvector = iTrueTime;
    break;
  }


  RGBcolorSpectrum rainbow(topcolor-bottomcolor);

  for ( unsigned int i=0; i < iHitX->size(); i++ ){
    pointmodification thispoint(iPe->at(i), iTrueTime->at(i), 
				iHitX->at(i), iHitY->at(i), iHitZ->at(i),
				iMaxPe, iUpperTime, iLowerTime, iUpperPe, iLowerPe,
                                iEventPosition, iEventDirection, iTau,
                                iReduction, iResidualTimeBuffer, iPixel);
    if ( thispoint.firstCuts() ) {
      if ( thispoint.secondCuts() ){
        rainbow.returnSpectrum(colorvector->at(i)-bottomcolor, R, G, B);
        glColor3f(R, G, B);
        double POSX = iHitX->at(i)/iReduction;
        double POSY = iHitY->at(i)/iReduction;
        double POSZ = iHitZ->at(i)/iReduction;
        double Width = 10./iReduction;
        double Length = 225./iReduction;
        glBegin(GL_POLYGON);

        glVertex3f( POSX, POSY+0.5*Width , POSZ+0.5*Length );      // P1 is red
        glVertex3f( POSX, POSY+0.5*Width , POSZ-0.5*Length  );      // P2 is green
        glVertex3f( POSX, POSY-0.5*Width , POSZ-0.5*Length);      // P3 is blue
        glVertex3f( POSX, POSY-0.5*Width , POSZ+0.5*Length);      // P4 is purple

        //pixSize = thispoint.varyPoints();
        //glPointSize(pixSize);
        
        //glBegin(GL_POINTS);
        //glVertex3f(iHitX->at(i)/iReduction, iHitY->at(i)/iReduction, iHitZ->at(i)/iReduction);
        glEnd();
      }
    }
  }

}

void drawevent::drawProjection(){
 
  float R=0, G=0, B=0;
  float pixSize = 0;
  float topcolor, bottomcolor;
  vector<float> *colorvector;
  switch (iColorMethod) {
  case 0: // Pe
    topcolor = iUpperPeHisto;
    bottomcolor = iLowerPeHisto;
    colorvector = iPe;
    break;
  case 1: // Time
    topcolor = iUpperTimeHisto;
    bottomcolor = iLowerTimeHisto;
    colorvector = iTrueTime;
    break;
  }


  RGBcolorSpectrum rainbow(topcolor-bottomcolor);

  for ( unsigned int i=0; i < iHitX->size(); i++ ){
    pointmodification thispoint(iPe->at(i), iTrueTime->at(i), 
				iHitX->at(i), iHitY->at(i), iHitZ->at(i),
				iMaxPe, iUpperTime, iLowerTime, iUpperPe, iLowerPe,
                                iEventPosition, iEventDirection, iTau,
                                iReduction, iResidualTimeBuffer, iPixel);
    if ( thispoint.firstCuts() ) {
      if ( thispoint.secondCuts() ){
        rainbow.returnSpectrum(colorvector->at(i)-bottomcolor, R, G, B);
        glColor3f(R, G, B);
        pixSize = thispoint.varyPoints();
        glPointSize(pixSize);
	// Define a Line The event vertex to the hit pmt
	double theLine[3];
	theLine[0] = iHitX->at(i)/iReduction - iEventPosition[0];
	theLine[1] = iHitY->at(i)/iReduction - iEventPosition[1];
	theLine[2] = iHitZ->at(i)/iReduction - iEventPosition[2];
	// Normalize the line to a unit sphere
	double magLine = sqrt(pow(theLine[0],2)+pow(theLine[1],2)+pow(theLine[2],2));
	double theLocation[3];
	for(int j=0; j<3; j++)
	  theLocation[j]=theLine[j]/magLine;
        glBegin(GL_POINTS);
        glVertex3f(theLocation[0], theLocation[1], theLocation[2]);
        glEnd();
      }
    }
  }

}  

void drawevent::drawProjectionPhiTheta(){
	
	float R=0, G=0, B=0;
	float pixSize = 0;
	float topcolor, bottomcolor;
	vector<float> *colorvector;
	switch (iColorMethod) {
		case 0: // Pe
			topcolor = iUpperPeHisto;
			bottomcolor = iLowerPeHisto;
			colorvector = iPe;
			break;
		case 1: // Time
			topcolor = iUpperTimeHisto;
			bottomcolor = iLowerTimeHisto;
			colorvector = iTrueTime;
			break;
	}
	
	
	RGBcolorSpectrum rainbow(topcolor-bottomcolor);
	
	for ( unsigned int i=0; i < iHitX->size(); i++ ){
		pointmodification thispoint(iPe->at(i), iTrueTime->at(i), 
									iHitX->at(i), iHitY->at(i), iHitZ->at(i),
									iMaxPe, iUpperTime, iLowerTime, iUpperPe, iLowerPe,
									iEventPosition, iEventDirection, iTau,
									iReduction, iResidualTimeBuffer, iPixel);
		if ( thispoint.firstCuts() ) {
			if ( thispoint.secondCuts() ){
				rainbow.returnSpectrum(colorvector->at(i)-bottomcolor, R, G, B);
				glColor3f(R, G, B);
				pixSize = thispoint.varyPoints();
				glPointSize(pixSize);
				// Define a Line The event vertex to the hit pmt
				double theLine[3];
				theLine[0] = iHitX->at(i)/iReduction - iEventPosition[0];
				theLine[1] = iHitY->at(i)/iReduction - iEventPosition[1];
				theLine[2] = iHitZ->at(i)/iReduction - iEventPosition[2];
				// Normalize the line to a unit sphere
				double magLine = sqrt(pow(theLine[0],2)+pow(theLine[1],2)+pow(theLine[2],2));
				double theLocation[3];
				theLocation[0]=((atan2(theLine[1]/magLine,theLine[0]/magLine)-PI/2.0)/PI +0.5 )*0.9;
				theLocation[1]=(theLine[2]/magLine)/2.0;
				theLocation[2]=0;
				glBegin(GL_POINTS);
				glVertex3f(theLocation[0], theLocation[1], theLocation[2]);
				glEnd();
			}
		}
	}
	
}  


drawevent::~drawevent(){}
void drawevent::setNewDirection(int q){
  float unitLength = sqrt( pow(iEventDirection[q*3 + 0], 2)
			   + pow(iEventDirection[q*3 + 1], 2)
			   + pow(iEventDirection[q*3 + 2], 2) )/2;
  for(int i=0; i<3; i++)
    iNewDirection[i] = (iEventPosition[q*3 + i] + iEventDirection[q*3 + i]/unitLength );
}

/*
 *  MuonGenerator.C
 *  aliroot_dev
 *
 *  Created by philippe pillot on 05/03/13.
 *  Copyright 2013 SUBATECH. All rights reserved.
 *
 */


#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include "TRandom.h"
#include "AliGenerator.h"
#include "AliGenParam.h"
#endif


static Int_t IpMuon( TRandom *ran);
static Double_t PtMuon( const Double_t *px, const Double_t * /*dummy*/ );
static Double_t YMuon( const Double_t *py,  const Double_t * /*dummy*/ );
static Double_t V2Muon( const Double_t *pv, const Double_t * /*dummy*/ );


//-------------------------------------------------------------------------
AliGenerator* CreateGenerator()
{
  AliGenParam *singleMu = new AliGenParam(1,-1,PtMuon,YMuon,V2Muon,IpMuon);
  singleMu->SetMomentumRange(0,1e6);
  singleMu->SetPtRange(4.,40.);
  singleMu->SetYRange(-4.5,-2.);
  singleMu->SetPhiRange(0., 360.);
  singleMu->SetForceDecay(kNoDecay);
  singleMu->SetTrackingFlag(1);
  return singleMu;
}

//-------------------------------------------------------------------------
Int_t IpMuon(TRandom *ran)
{
  // muon composition
  
  if (ran->Rndm() < 0.5 )
  {
    return 13;
  }
  else
  {
    return -13;
  }
}

//-------------------------------------------------------------------------
Double_t PtMuon( const Double_t *px, const Double_t * /*dummy*/ )
{
  // muon pT
  
  Double_t x=*px;
  if( x < 1. ) return 0.;
  Float_t p0,p1,p2,p3, p4, p5, p6, p7;
  
  
  p0 = 108.349;
  p1 = -0.836925;
  p2 = -0.345687;
  p3 = 0.559775;
  p4 = 3.14749;
  p5 = 514732;
  p6 = -17413.1;
  p7 = 10928.4;

 // norm
  Float_t norm = p0;
//slope
  Float_t slope = p1 * ( 1. - TMath::Exp( p2*x)) + p3;
//double 
  Float_t den = 1./TMath::Power(x,p4);
// pol
  Float_t pol = p5 + p6*x+p7*x*x;
  
  return norm * TMath::Exp( slope*x ) * den * pol;
}

//-------------------------------------------------------------------------
Double_t YMuon( const Double_t *py, const Double_t */*dummy*/ )
{
  // muon y

//   Float_t yswitch = VAR_GENPARAMCUSTOMSINGLE_Y_RAPIDITY_SWITCH;  
  Double_t x = *py;
//   x *= yswitch;
//pol4 only valid in y= -4;-2.5
  Float_t p0,p1,p2,p3, p4, p5;
  
  p0 = 4.01732e+06;
  p1 = -233742;
  p2 = -362585;
  p3 = 8383.75;
  p4 = -98.7377;
  p5 = 1.24522;

 
//   p6 = VAR_GENPARAMCUSTOMSINGLE_Y_P6; //
//   p7 = VAR_GENPARAMCUSTOMSINGLE_Y_P7; //
//   p8 = VAR_GENPARAMCUSTOMSINGLE_Y_P8; //
//   return p0 + 
//         p1* x + 
//         p2* x*x + 
//         p3* x*x*x + 
//         p4* x*x*x*x+
// 	x*x*x*x*x ;
//         + 
//         p5* x*x*x*x*x + 
//         p6* x*x*x*x*x*x + 
//         p7* x*x*x*x*x*x*x + 
//         p8* x*x*x*x*x*x*x*x; 
// return p0*TMath::Power(x,4) +  p1*TMath::Power(x,3) +  p2*TMath::Power(x,2) + p3*TMath::Power(x,1) + p4;
return p5*TMath::Power(x,8) + p4*TMath::Power(x,6) +  p3*TMath::Power(x,4) +  p2*TMath::Power(x,2) + p1*TMath::Power(x,1) + p0;
}

//-------------------------------------------------------------------------
Double_t V2Muon( const Double_t */*dummy*/, const Double_t */*dummy*/ )
{
  //muon v2
  return 0.;
}

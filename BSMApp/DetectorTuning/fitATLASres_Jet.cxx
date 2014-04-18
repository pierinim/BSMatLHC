// ICHEP JetMET talk pag 8
// http://indico.cern.ch/getFile.py/access?contribId=1121&sessionId=45&resId=2&materialId=slides&confId=73513

void fitATLASres_Jet() {
  double ey[8];
  double ex[8];
  for(int i=0; i<8; i++) {
    ex[i] = 0.;
    ey[i] = 0.01;
  }

  double x[8];
  double y[8];
  // |eta|<1.4
  int i=0;
  x[i] = 31.8;  y[i] = 0.2142; i++;
  x[i] = 36.5;  y[i] = 0.1894; i++;
  x[i] = 43.6;  y[i] = 0.1655; i++;
  x[i] = 58.7;  y[i] = 0.1342; i++;
  x[i] = 80.7;  y[i] = 0.1089; i++;
  x[i] = 105.5;  y[i] = 0.0916; i++;
  x[i] = 158.3;  y[i] = 0.0734; i++;
  x[i] = 196.7;  y[i] = 0.0649; i++;
  
 TGraphErrors * gr1 = new TGraphErrors(8,x,y,ex,ey);
 gr1->Draw("ap");
 TF1 *f1 = new TF1("f1","sqrt(pow([0]/x,2.)+pow([1],2.)/x+pow([2],2.))",0.0001,250.);
 f1->SetParameter(0,5.553);
 f1->SetParameter(0,1.251);
 f1->SetParameter(0,0.03263);

 gr1->Fit("f1");
 gr1->Fit("f1","R");
 gr1->Fit("f1","R");

}

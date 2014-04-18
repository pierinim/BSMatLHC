// ICHEP JetMET talk pag 10
// http://indico.cern.ch/getFile.py/access?contribId=1121&sessionId=45&resId=2&materialId=slides&confId=73513
void fitATLASres_MET() {
  double ey[37];
  double ex[37];
  for(int i=0; i<37; i++) {
    ex[i] = 0.0;
    ey[i] = 0.1;
  }
  
  double x[37];
  double y[37];
  int i=0;
  x[i] = 7.5;   y[i] = 1.4; i++;
  x[i] = 12.6;   y[i] = 1.7; i++;
  x[i] = 17.3;   y[i] = 2.0; i++;
  x[i] = 21.9;   y[i] = 2.3; i++;
  x[i] = 27.5;   y[i] = 2.6; i++;
  x[i] = 32.3;   y[i] = 2.8; i++;
  x[i] = 36.9;   y[i] = 3.0; i++;
  x[i] = 42.4;   y[i] = 3.2; i++;
  x[i] = 47.5;   y[i] = 3.4; i++;
  x[i] = 52.2;   y[i] = 3.6; i++;
  x[i] = 56.4;   y[i] = 3.8; i++;
  x[i] = 62.4;   y[i] = 4.0; i++;
  x[i] = 67.1;   y[i] = 4.1; i++;
  x[i] = 72.2;   y[i] = 4.3; i++;
  x[i] = 76.9;   y[i] = 4.4; i++;
  x[i] = 82.0;   y[i] = 4.5; i++;
  x[i] = 86.7;   y[i] = 4.67; i++;
  x[i] = 92.7;   y[i] = 4.84; i++;
  x[i] = 96.9;   y[i] = 4.96; i++;
  x[i] = 102.9;   y[i] = 5.09; i++;
  x[i] = 108.0;   y[i] = 5.21; i++;
  x[i] = 112.3;   y[i] = 5.32; i++;
  x[i] = 117.0;   y[i] = 5.44; i++;
  x[i] = 122.1;   y[i] = 5.57; i++;
  x[i] = 127.6;   y[i] = 5.66; i++;
  x[i] = 132.7;   y[i] = 5.78; i++;
  x[i] = 137.4;   y[i] = 5.89; i++;
  x[i] = 142.5;   y[i] = 6.02; i++;
  x[i] = 146.8;   y[i] = 6.09; i++;
  x[i] = 152.3;   y[i] = 6.18; i++;
  x[i] = 167.3;   y[i] = 6.53; i++;
  x[i] = 183.0;   y[i] = 6.80; i++;
  x[i] = 192.4;   y[i] = 7.00; i++;
  x[i] = 212.4;   y[i] = 7.34; i++;
  x[i] = 239.3;   y[i] = 7.84; i++;
  x[i] = 267.4;   y[i] = 8.32; i++;
  x[i] = 289.1;   y[i] = 8.64; i++;

  TGraphErrors * gr1 = new TGraphErrors(37,x,y,ex,ey);
  gr1->Draw("ap");
  TF1 *f1 = new TF1("f1","[0]*pow(x,0.5)+[1]",0.0001,300.);
  f1->SetParameter(0,0);
  f1->SetParameter(1,0);
  //  f1->SetParameter(2,20.);
  
  gr1->Fit("f1");
  gr1->Fit("f1","R");
  gr1->Fit("f1","R");
  
}

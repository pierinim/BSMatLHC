// to fit MET response 
void fitCMSres_MET() {
  double ey[15];
  double ex[15];
  for(int i=0; i<15; i++) {
    ex[i] = 0.01;
    ey[i] = 0.01;
  }
  
  double x[15];
  double y[15];
  // MET angular response BEFORE CORRECTION (pag 421)
  int i=0;
  x[i] = 40.;   y[i] = 21.3; i++;
  x[i] = 50.;   y[i] = 22.1; i++;
  x[i] = 60.;   y[i] = 23.3; i++;
  x[i] = 70.;   y[i] = 24.4; i++;
  x[i] = 80.;   y[i] = 25.0; i++;
  x[i] = 90.;   y[i] = 25.6; i++;
  x[i] = 100.;  y[i] = 26.7; i++;
  x[i] = 110.;  y[i] = 27.2; i++;
  x[i] = 120.;  y[i] = 27.7; i++;
  x[i] = 130.;  y[i] = 28.6; i++;
  x[i] = 140.;  y[i] = 29.1; i++;
  x[i] = 150.;  y[i] = 29.8; i++;
  x[i] = 175.;  y[i] = 31.6; i++;
  x[i] = 200.;  y[i] = 32.5; i++;
  x[i] = 220.;  y[i] = 34.3; i++;

  TGraphErrors * gr1 = new TGraphErrors(15,x,y,ex,ey);
  gr1->Draw("ap");
  TF1 *f1 = new TF1("f1","expo",0.5,4.5);
  TF1 *f1 = new TF1("f1","[0]*pow(x,2.)+[1]*x+[2]",0.0001,250.);
  f1->SetParameter(0,-1.06820e-0);
  f1->SetParameter(1,9.70528e-02);
  f1->SetParameter(2,1.77749e+01);
  

  gr1->Fit("f1");
  gr1->Fit("f1","R");
  gr1->Fit("f1","R");
  
}

// to fit MET response 
void fitCMSres_METPHI() {
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
  x[i] = 20.;   y[i] = 0.5848; i++;
  x[i] = 30.;   y[i] = 0.4553; i++;
  x[i] = 40.;   y[i] = 0.3811; i++;
  x[i] = 50.;   y[i] = 0.3207; i++;
  x[i] = 60.;   y[i] = 0.2704; i++;
  x[i] = 70.;   y[i] = 0.2426; i++;
  x[i] = 80.;   y[i] = 0.2149; i++;
  x[i] = 90.;   y[i] = 0.1922; i++;
  x[i] = 100.;  y[i] = 0.1657; i++;
  x[i] = 110.;  y[i] = 0.1531; i++;
  x[i] = 120.;  y[i] = 0.1442; i++;
  x[i] = 200.;  y[i] = 0.1328; i++;
  x[i] = 325.;  y[i] = 0.1175; i++;
  x[i] = 425.;  y[i] = 0.1073; i++;
  x[i] = 825.;  y[i] = 0.1033; i++;
  
  TGraphErrors * gr1 = new TGraphErrors(15,x,y,ex,ey);
  gr1->Draw("ap");
  TF1 *f1 = new TF1("f1","expo",0.5,4.5);
  TF1 *f1 = new TF1("f1","sqrt(pow([0]/x,2.)+pow([1]/sqrt(x),2.)+pow([2],2.))",0.0001,250.);
  f1->SetParameter(0,1.7);
  f1->SetParLimits(0,0.,100.);
  f1->SetParameter(1,1.251);
  f1->SetParameter(2,0.03263);
  
  gr1->Fit("f1");
  gr1->Fit("f1","R");
  gr1->Fit("f1","R");
  
}

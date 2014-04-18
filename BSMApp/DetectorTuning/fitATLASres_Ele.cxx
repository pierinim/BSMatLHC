void fitATLASres_Ele() {

  double ey[5];
  double ex[5];
  for(int i=0; i<6; i++) {
    ex[i] = 0.0;
    ey[i] = 0.0010;
  }
  
  double x[5];
  double y0_3[5];
  double y1_1[5];
  double y2_0[5];
  int i=0;
  x[i] = 25.;   y0_3[i] = 0.02;   y1_1[i] = 0.0312; y2_0[i] = 0.0312; i++;
  x[i] = 50.;   y0_3[i] = 0.015;  y1_1[i] = 0.0218; y2_0[i] = 0.0218; i++;
  x[i] = 75.;   y0_3[i] = 0.0127; y1_1[i] = 0.0177; y2_0[i] = 0.0183; i++;
  x[i] = 100.0; y0_3[i] = 0.0112; y1_1[i] = 0.0152; y2_0[i] = 0.0160; i++;
  x[i] = 200.;  y0_3[i] = 0.0089; y1_1[i] = 0.0110; y2_0[i] = 0.0124; i++;

  TGraphErrors * gr1 = new TGraphErrors(5,x,y0_3,ex,ey);
  TGraphErrors * gr2 = new TGraphErrors(5,x,y1_1,ex,ey);
  TGraphErrors * gr3 = new TGraphErrors(5,x,y2_0,ex,ey);
  TF1 *f1 = new TF1("f1","[0]+[1]/pow(x,0.5)",0.0001,250.);
  f1->SetParameter(0,0);
  f1->SetParameter(1,0);
  //  f1->SetParameter(2,20.);

  cout << "|eta|=0.3" << endl;

  TCanvas* c1 = new TCanvas("c1", "c1", 600, 600);
  gr1->Fit("f1");
  gr1->Fit("f1","R");
  gr1->Fit("f1","R");
  gr1->Draw("ap");

  cout << "|eta|=1.1" << endl;

  TCanvas* c2 = new TCanvas("c2", "c2", 600, 600);
  gr2->Fit("f1");
  gr2->Fit("f1","R");
  gr2->Fit("f1","R");
  gr2->Draw("ap");

  cout << "|eta|=2.0" << endl;

  TCanvas* c3 = new TCanvas("c3", "c3", 600, 600);
  gr3->Fit("f1");
  gr3->Fit("f1","R");
  gr3->Fit("f1","R");
  gr3->Draw("ap");

}

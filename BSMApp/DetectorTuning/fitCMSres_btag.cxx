// to fit jet response at pag 412
void fitCMSres_btag() {
  double ey[14];
  double ex[14];
  for(int i=0; i<14; i++) {
    ex[i] = 0.;
    ey[i] = 0.01;
  }

  double x[14];
  double b[14];
  double c[14];
  double udsg[14];
  int i=0;

  x[i] = 35; b[i] = 0.6328; c[i] = 0.1797; udsg[i] = 0.1011; i++;
  x[i] = 45; b[i] = 0.6453; c[i] = 0.1732; udsg[i] = 0.1011; i++;
  x[i] = 55; b[i] = 0.6895; c[i] = 0.1889; udsg[i] = 0.1137; i++;
  x[i] = 65; b[i] = 0.7021; c[i] = 0.1952; udsg[i] = 0.1072; i++;
  x[i] = 75; b[i] = 0.7179; c[i] = 0.1983; udsg[i] = 0.1135; i++;
  x[i] = 90; b[i] = 0.7336; c[i] = 0.2045; udsg[i] = 0.1229; i++;
  x[i] = 110; b[i] = 0.7398; c[i] = 0.2044; udsg[i] = 0.1291; i++;
  x[i] = 140; b[i] = 0.7397; c[i] = 0.2105; udsg[i] = 0.1416; i++;
  x[i] = 185; b[i] = 0.7173; c[i] = 0.1977; udsg[i] = 0.1636; i++;
  x[i] = 235; b[i] = 0.6981; c[i] = 0.1881; udsg[i] = 0.1857; i++;
  x[i] = 290; b[i] = 0.6695; c[i] = 0.1784; udsg[i] = 0.2141; i++;
  x[i] = 360; b[i] = 0.6345; c[i] = 0.1656; udsg[i] = 0.2382; i++;
  x[i] = 450; b[i] = 0.5805; c[i] = 0.1560; udsg[i] = 0.2740; i++;
  x[i] = 580; b[i] = 0.5423; c[i] = 0.1463; udsg[i] = 0.3182; i++;
  
  TGraphErrors * gr1 = new TGraphErrors(14,x,udsg,ex,ey);
  gr1->Draw("ap");
  
}

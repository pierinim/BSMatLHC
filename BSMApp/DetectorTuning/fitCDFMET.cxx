// CDF MET FROM BEDESCHI's TALK ICHEP 2002
// http://www-cdf.fnal.gov/physics/talks_transp/2002/ichep_bedeschi_plenary.pdf
void fitCDFMET() {
  double ey[31];
  double ex[31];
  for(int i=0; i<31; i++) {
    ex[i] = 0.;
  }

  double x[31];
  double y[31];

  int i=0;
  x[i] =   2.0; y[i] = 0.93; i++;
  x[i] =   7.2; y[i] = 1.48; i++;
  x[i] =  12.3; y[i] = 1.96; i++;
  x[i] =  17.4; y[i] = 2.42; i++;
  x[i] =  22.4; y[i] = 2.75; i++;
  x[i] =  27.7; y[i] = 3.10; i++;
  x[i] =  32.4; y[i] = 3.56; i++;
  x[i] =  37.4; y[i] = 3.69; i++;
  x[i] =  42.7; y[i] = 3.99; i++;
  x[i] =  48.0; y[i] = 4.20; i++;
  x[i] =  52.9; y[i] = 4.33; i++;
  x[i] =  58.2; y[i] = 4.56; i++;
  x[i] =  62.4; y[i] = 4.77; i++;
  x[i] =  68.1; y[i] = 5.02; i++;
  x[i] =  70.0; y[i] = 5.16; i++;
  x[i] =  77.9; y[i] = 5.31; i++;
  x[i] =  82.8; y[i] = 5.46; i++;
  x[i] =  87.6; y[i] = 5.66; i++;
  x[i] =  92.9; y[i] = 5.80; i++;
  x[i] =  98.2; y[i] = 5.91; i++;
  x[i] = 102.9; y[i] = 6.09; i++;
  x[i] = 107.7; y[i] = 6.22; i++;
  x[i] = 113.0; y[i] = 6.40; i++;
  x[i] = 117.9; y[i] = 6.55; i++;
  x[i] = 122.8; y[i] = 6.67; i++;
  x[i] = 128.0; y[i] = 6.78; i++;
  x[i] = 133.1; y[i] = 6.92; i++;
  x[i] = 138.2; y[i] = 7.03; i++;
  x[i] = 142.9; y[i] = 7.15; i++;
  x[i] = 148.3; y[i] = 7.33; i++;
  x[i] = 173.1; y[i] = 7.92; i++;

  for(int i=0; i<31; i++) {
    ey[i] = 0.01*y[i];
  }

  TF1 *f1 = new TF1("f1","[0]*pow(x,0.1)+[1]*pow(x,0.5)");



 TGraphErrors * gr1 = new TGraphErrors(31,x,y,ex,ey);
 gr1->Draw("ap");

 gr1->Fit("f1");
 gr1->Fit("f1","R");
 gr1->Fit("f1","R");

}

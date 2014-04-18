// to fit jet response at pag 412
void fitCDFjes() {
  double ey[20];
  double ex[20];
  for(int i=0; i<20; i++) {
    ex[i] = 0.;
  }

  // JES correction Cj = (Aj*pT+Bj)/(Cj*pT+D)
  // see Nuclear Physics B (Proc. Suppl.) 177–178 (2008) 195–199 (PAG 49)
  //   for(int i=0; i<20; i++) {
  //     ey[i] = 0.005;
  //   }
  //   double x[20];
  //   double y[20];
  //   int i=0;
  //   x[i] =   2.; y[i] = 1.4283; i++;
  //   x[i] =   5.; y[i] = 1.3993; i++;
  //   x[i] =  10.; y[i] = 1.3551; i++;
  //   x[i] =  15.; y[i] = 1.3115; i++;
  //   x[i] =  20.; y[i] = 1.2852; i++;
  //   x[i] =  25.; y[i] = 1.2618; i++;
  //   x[i] =  30.; y[i] = 1.2404; i++;
  //   x[i] =  35.; y[i] = 1.2224; i++;
  //   x[i] =  40.; y[i] = 1.2107; i++;
  //   x[i] =  45.; y[i] = 1.2010; i++;
  //   x[i] =  55.; y[i] = 1.1851; i++;
  //   x[i] =  75.; y[i] = 1.1663; i++;
  //   x[i] = 100.; y[i] = 1.1552; i++;
  //   x[i] = 150.; y[i] = 1.1398; i++;
  //   x[i] = 200.; y[i] = 1.1300; i++;
  //   x[i] = 250.; y[i] = 1.1229; i++;
  //   x[i] = 300.; y[i] = 1.1157; i++;
  //   x[i] = 350.; y[i] = 1.1128; i++;
  //   x[i] = 400.; y[i] = 1.1105; i++;
  //   x[i] = 450.; y[i] = 1.1101; i++;
  //   x[i] = 500.; y[i] = 1.1101; i++;
  //   TF1 *f1 = new TF1("f1","([0]*x+[1])/([2]*x+[3])");

  // error on JES correction ECj = EAj*log(pT+EBj)
  // see Nuclear Physics B (Proc. Suppl.) 177–178 (2008) 195–199 (PAG 49)
  double x[20];
  double y[20];
  for(int i=0; i<20; i++) {
    ey[i] = 0.001;
  }
  int i=0;
  x[i] =   2.; y[i] = 0.0180; i++;
  x[i] =  10.; y[i] = 0.0186; i++;
  x[i] =  20.; y[i] = 0.0192; i++;
  x[i] =  30.; y[i] = 0.0198; i++;
  x[i] =  40.; y[i] = 0.0204; i++;
  x[i] =  50.; y[i] = 0.0211; i++;
  x[i] =  60.; y[i] = 0.0214; i++;
  x[i] =  70.; y[i] = 0.0218; i++;
  x[i] =  80.; y[i] = 0.0223; i++;
  x[i] =  90.; y[i] = 0.0226; i++;
  x[i] = 100.; y[i] = 0.0230; i++;
  x[i] = 110.; y[i] = 0.0234; i++;
  x[i] = 120.; y[i] = 0.0238; i++;
  x[i] = 150.; y[i] = 0.0247; i++;
  x[i] = 200.; y[i] = 0.0259; i++;
  x[i] = 250.; y[i] = 0.0268; i++;
  x[i] = 300.; y[i] = 0.0275; i++;
  x[i] = 350.; y[i] = 0.0280; i++;
  x[i] = 400.; y[i] = 0.0284; i++;
  x[i] = 500.; y[i] = 0.0288; i++;
  TF1 *f1 = new TF1("f1","[0]*log(abs(x+[1]))");



 TGraphErrors * gr1 = new TGraphErrors(20,x,y,ex,ey);
 gr1->Draw("ap");

 gr1->Fit("f1");
 gr1->Fit("f1","R");
 gr1->Fit("f1","R");

}

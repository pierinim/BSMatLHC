// to fit jet response at pag 412
void fitCMSres_btagHiggs() {
  double ey[18];
  double ex[18];
  for(int i=0; i<18; i++) {
    ex[i] = 0.;
    ey[i] = 0.01;
  }

  double x[18];
  double h[18];
  double top[18];
  double z[18];
  double w[18];
  double udscg[18];
  int i=0;
  
  x[i] = 300; udscg[i] = 0.0188; w[i] = 0.0334; top[i] = 0.0935; z[i] = 0.1631; h[i] = 0.6050; i++;
  x[i] = 340; udscg[i] = 0.0262; w[i] = 0.0285; top[i] = 0.1008; z[i] = 0.1630; h[i] = 0.5768; i++;
  x[i] = 380; udscg[i] = 0.0215; w[i] = 0.0287; top[i] = 0.1017; z[i] = 0.1645; h[i] = 0.5988; i++;
  x[i] = 420; udscg[i] = 0.0252; w[i] = 0.0325; top[i] = 0.1117; z[i] = 0.1554; h[i] = 0.5710; i++;
  x[i] = 460; udscg[i] = 0.0227; w[i] = 0.0307; top[i] = 0.0997; z[i] = 0.1454; h[i] = 0.5708; i++;
  x[i] = 500; udscg[i] = 0.0282; w[i] = 0.0399; top[i] = 0.1215; z[i] = 0.1568; h[i] = 0.5841; i++;
  x[i] = 540; udscg[i] = 0.0287; w[i] = 0.0487; top[i] = 0.1322; z[i] = 0.1582; h[i] = 0.5758; i++;
  x[i] = 580; udscg[i] = 0.0334; w[i] = 0.0599; top[i] = 0.1399; z[i] = 0.1552; h[i] = 0.5594; i++;
  x[i] = 620; udscg[i] = 0.0350; w[i] = 0.0743; top[i] = 0.1596; z[i] = 0.1657; h[i] = 0.5918; i++;
  x[i] = 640; udscg[i] = 0.0380; w[i] = 0.0832; top[i] = 0.1769; z[i] = 0.1536; h[i] = 0.5972; i++;
  x[i] = 700; udscg[i] = 0.0373; w[i] = 0.0905; top[i] = 0.1837; z[i] = 0.1837; h[i] = 0.5970; i++;
  x[i] = 740; udscg[i] = 0.0468; w[i] = 0.0940; top[i] = 0.1836; z[i] = 0.1802; h[i] = 0.6375; i++;
  x[i] = 780; udscg[i] = 0.0459; w[i] = 0.0880; top[i] = 0.1979; z[i] = 0.1801; h[i] = 0.6433; i++;
  x[i] = 820; udscg[i] = 0.0570; w[i] = 0.0948; top[i] = 0.2074; z[i] = 0.1767; h[i] = 0.6678; i++;
  x[i] = 860; udscg[i] = 0.0518; w[i] = 0.1051; top[i] = 0.2236; z[i] = 0.1685; h[i] = 0.6489; i++;
  x[i] = 900; udscg[i] = 0.0620; w[i] = 0.0799; top[i] = 0.2214; z[i] = 0.1764; h[i] = 0.6800; i++;
  x[i] = 940; udscg[i] = 0.0656; w[i] = 0.1233; top[i] = 0.2432; z[i] = 0.1748; h[i] = 0.6862; i++;
  x[i] = 980; udscg[i] = 0.0681; w[i] = 0.0700; top[i] = 0.2191; z[i] = 0.1849; h[i] = 0.7056; i++;
  
  TGraphErrors * gr1 = new TGraphErrors(14,x,udscg,ex,ey);
  gr1->Draw("ap");
  
}

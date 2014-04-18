// to fit jet response at pag 412
void fitD0jes() {
  double ey[14];
  double ex[14];
  for(int i=0; i<14; i++) {
    ex[i] = 0.01;
    ey[i] = 0.01;
  }

  // JES correction ECj = EAj*log(pT+EBj)
  // CP867, XII International Conference on Calorimetry in High Energy Physics, 
  // Proceeding by J. Kvita (Pag 5)
  double x[14];
  double y[14];
  int i=0;
  x[i] =  12.; y[i] = 0.5649; i++;
  x[i] =  17.; y[i] = 0.6009; i++;
  x[i] =  22.; y[i] = 0.6134; i++;
  x[i] =  30.; y[i] = 0.6268; i++;
  x[i] =  42.; y[i] = 0.6606; i++;
  x[i] =  55.; y[i] = 0.6773; i++;
  x[i] =  68.; y[i] = 0.6932; i++;
  x[i] =  83.; y[i] = 0.7046; i++;
  x[i] = 103.; y[i] = 0.7189; i++;
  x[i] = 134.; y[i] = 0.7360; i++;
  x[i] = 190.; y[i] = 0.7559; i++;
  x[i] = 240.; y[i] = 0.7707; i++;
  x[i] = 275.; y[i] = 0.7786; i++;
  x[i] = 330.; y[i] = 0.7886; i++;
  TF1 *f1 = new TF1("f1","[0]+[1]*log(x+[2])");

 TGraphErrors * gr1 = new TGraphErrors(14,x,y,ex,ey);
 gr1->Draw("ap");

 gr1->Fit("f1");
 gr1->Fit("f1","R");
 gr1->Fit("f1","R");

}

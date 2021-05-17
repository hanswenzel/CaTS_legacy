#include "TF1.h"
#include "TSystem.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMath.h"
#include "TAxis.h"
#include <cmath>
// Data from: 
// Eur. Phys. J. C (2018) 78:329
//

Double_t myfunction(Double_t *x, Double_t *par) {
    Float_t xx = x[0];
    double f = 0.5 * par[0] * par[1] * exp(0.5 * par[1]*(2. * par[3] + par[1] * par[2] * par[2] - 2 * xx)) * TMath::Erfc((par[3] + par[1] * par[2] * par[2] - xx) / (sqrt(2) * par[2]))
            + (1 - par[0]) / sqrt(2. * par[4] * par[4] * M_PI) * exp((-1.0 * (xx - par[5])*(xx - par[5])) / (2. * par[4] * par[4]));
    return f;
}

void wls() {
    double A = 0.782;
    double alpha = 3.7e-2;
    double sig1 = 15.43;
    double mu1 = 418.1;
    double sig2 = 9.72;
    double mu2 = 411.2;
    TGraph* tg1 = new TGraph("FitReemissionSpect.csv", "%lf,%lf");
    tg1->SetLineWidth(2);
    tg1->SetLineColor(2);
    tg1->GetXaxis()->SetTitle("#lambda [nm]");
    tg1->GetYaxis()->SetTitle("Quantum efficiency Qeff");
    tg1->SetMinimum(0.);
    tg1->Draw();
    //TF1 *f1 = new TF1("myfunc", myfunction, 370., 560., 6);
    //f1->SetParameters(0.782, 3.7e-2, 15.43, 418.1, 9.72, 411.2);
    //f1->SetParNames("A", "alpha", "sig1", "mu1", "sig2", "mu2");
    //f1->Draw("SAME");
}

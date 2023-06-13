// c++ -o 19gennaio 19gennaio.cpp `root-config --glibs --cflags`


#include <iostream>
#include <cmath>
#include "TGraphErrors.h"
#include "TApplication.h"
#include <fstream>
#include "TAxis.h"
#include "TF1.h"
#include <TFitResult.h>
#include "TStyle.h"
#include "TLatex.h"

using namespace std;

int main (int argc, char ** argv)
{
	ifstream input_file;
	input_file.open ("19gennaio.txt", ios::in);
	
	TApplication app ("app", &argc, argv);
	TGraphErrors *g = new TGraphErrors("19gennaio.txt", "%lg %lg %lg %lg");
	g->Draw("AP");

	
	TF1 * funzione = new TF1 ("secante", "[0]*1/cos(x) + [1]", -1.57, 1.57);
        funzione-> SetParName(0, "parametro1");
	funzione-> SetParName(1, "offset");
        TFitResultPtr fit_result = g -> Fit ("secante","S");
	gStyle -> SetOptFit (1111) ;

	g->SetTitle("CMB");
	g->GetXaxis()->SetTitle("elevazione");
	g->GetYaxis()->SetTitle("rad [adu]");
	
	g->SetMarkerStyle(5);
	
	cout << fit_result->Chi2() << endl;

	app.Run();

	delete g;
	delete funzione;
	
	return 0;
}


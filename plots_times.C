//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include <time.h>

using namespace std;

void read_file(TString name, TH1D *h1_s, TH1D *h1_h, TGraph *gr_s, TGraph *gr_h);

Int_t plots_times(){
  ////////////////////
  TString fileN0101;
  ////////////////////
  //
  fileN0101 = "sacct_output_clean_h_min_sec.csv";
  ////////////////////
  TH1D *h1_time_sec = new TH1D( "h1_time_sec", "h1_time_sec", 1000, 0, 30000);
  TH1D *h1_time_h = new TH1D( "h1_time_sec", "h1_time_sec", 300, 0, 10.0);
  TGraph *gr_time_sec = new TGraph();
  gr_time_sec->SetNameTitle("gr_time_sec","gr_time_sec");
  TGraph *gr_time_h = new TGraph();
  gr_time_h->SetNameTitle("gr_time_h","gr_time_h");
  ////////////////////
  TCanvas *c1 = new TCanvas("c1",fileN0101.Data(), 10, 10, 800, 800);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);
  ////////////////////
  ////////////////////
  read_file( fileN0101, h1_time_sec, h1_time_h, gr_time_sec, gr_time_h);
  ////////////////////
  ////////////////////
  //
  ////////////////////
  /*
  h1_fadc_val_386MHz->SetLineColor(kBlack);
  h1_fadc_val_386MHz->SetLineWidth(3);
  h1_fadc_val_simtel_386MHz->SetLineColor(kRed);
  h1_fadc_val_simtel_386MHz->SetLineWidth(3);
  h1_fadc_val_268MHz->SetLineColor(kBlack);
  h1_fadc_val_268MHz->SetLineWidth(3);
  h1_fadc_val_simtel_268MHz->SetLineColor(kRed);
  h1_fadc_val_simtel_268MHz->SetLineWidth(3);
  //
  h1_fadc_val_386MHz_norm->SetLineColor(kBlack);
  h1_fadc_val_386MHz_norm->SetLineWidth(3);
  h1_fadc_val_simtel_386MHz_norm->SetLineColor(kRed);
  h1_fadc_val_simtel_386MHz_norm->SetLineWidth(3);
  h1_fadc_val_268MHz_norm->SetLineColor(kBlack);
  h1_fadc_val_268MHz_norm->SetLineWidth(3);
  h1_fadc_val_simtel_268MHz_norm->SetLineColor(kRed);
  h1_fadc_val_simtel_268MHz_norm->SetLineWidth(3);
  //
  h1_fadc_val_386MHz_proton_norm->SetLineColor(kBlue);
  h1_fadc_val_386MHz_proton_norm->SetLineWidth(3);
  //
  h1_fadc_val_268MHz_proton_norm->SetLineColor(kBlue);
  h1_fadc_val_268MHz_proton_norm->SetLineWidth(3);
  */
  ////////////////////
  //
  //h1_fadc_val_386MHz->Draw();
  //h1_fadc_val_simtel_386MHz->Draw("same");
  //
  //h1_fadc_val_386MHz_norm->Draw();
  //h1_fadc_val_simtel_386MHz_norm->Draw("sames");
  //h1_fadc_val_386MHz_proton_norm->Draw("sames");
  //
  //h1_time_h->Draw();
  gr_time_h->Draw("AP");
  //h1_fadc_val_simtel_268MHz_norm->Draw("sames");
  //h1_fadc_val_268MHz_proton_norm->Draw("sames");
  //
  //h1_fadc_val_268MHz->Draw();
  //h1_fadc_val_386MHz->Draw("same");
  //
  //h1_fadc_val_simtel_268MHz->Draw();
  //h1_fadc_val_simtel_386MHz->Draw("same");
  //
  //TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  //leg->AddEntry(h1_fadc_val_386MHz, "Stand alone simulation", "apl");
  //leg->AddEntry(h1_fadc_val_simtel_386MHz, "sim_telarray ", "apl");
  //leg->Draw();  
  //
  //
  /*
  //
  //
  h1_eff_area_01->SetTitle("");
  h1_eff_area_01->Draw();
  h1_eff_area_02->Draw("same");
  h1_eff_area_01->SetMinimum(1.0e+4);
  h1_eff_area_01->SetMinimum(1.0e+7);
  //
  //h1_protons->SetTitle("");
  //h1_protons->Draw();
  h1_protons02->Draw("same");
  //
  //h1_protons->Draw("same");
  h1_NSB->Draw("same");
  //
  //h1_tot->SetMinimum(1.0e+3);
  //
  h1_tot->GetXaxis()->SetTitle("Number of points in the cluster");
  h1_tot->GetYaxis()->SetTitle("Rate, Hz");
  //
  //TString file_out = fileN01;
  //file_out += ".pdf";
  //c1->SaveAs(file_out.Data());
  //
  */
  return 0;
}

void read_file(TString name, TH1D *h1_s, TH1D *h1_h, TGraph *gr_s, TGraph *gr_h){
  //
  //JobID         AllocCPUS    Elapsed_h Elapsed_m Elapsed_s  
  //28750347              1       00        09       10 
  //28750348              1       00        09       09 
  //
  std::ifstream fFile(name.Data());
  std::string mot;
  Double_t JobID, AllocCPUS, Elapsed_h, Elapsed_m, Elapsed_s;  
  Double_t time_in_s = 0.0;
  Double_t time_in_h = 0.0;
  Double_t time_in_h_tot = 0.0;
  Double_t time_in_s_MAX = 0.0;
  Int_t i = 0;
  if(fFile.is_open()){
    fFile>>mot>>mot>>mot>>mot>>mot;
    while(fFile>>JobID>>AllocCPUS>>Elapsed_h>>Elapsed_m>>Elapsed_s){
      //cout<<val<<endl;
      time_in_s = 3600.0*Elapsed_h + 60.0*Elapsed_m + Elapsed_s;
      time_in_h = time_in_s/3600.0;
      time_in_h_tot += time_in_h;
      h1_s->Fill(time_in_s);
      h1_h->Fill(time_in_h);
      //
      gr_s->SetPoint(gr_s->GetN(),gr_s->GetN(),time_in_s);
      gr_h->SetPoint(gr_h->GetN(),gr_h->GetN(),time_in_h);
      //
      if(time_in_s_MAX<time_in_s)
	time_in_s_MAX=time_in_s;
    }
    fFile.close();
  }
  cout<<"time_in_s_MAX "<<time_in_s_MAX<<endl
      <<"time_in_h_tot "<<time_in_h_tot<<endl;      
}

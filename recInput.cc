#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include "TString.h"
#include "TFile.h"
#include "TGraph.h"
#include "NP.hh"

#define gPI 3.141592653589793

NP<double>* make_pmtpos_array(int ni, int nj) {
    // Get the position of each PMT
    std::string m_filename= "/afs/ihep.ac.cn/soft/juno/JUNO-ALL-SLC6/Release/J17v1r1/offline/Simulation/DetSimV2/DetSimOptions/data/PMTPos_Acrylic.csv";
    std::ifstream pmtsrc(m_filename.c_str());
    std::string tmp_line;
    int m_line= 0;
    int m_copyno;
    double m_theta, m_phi;

    NP<double>* a= new NP<double>(ni, nj);
    std::cout << "PMT Position " << a->desc() << std::endl;
    int m_pmtID= 0;
    while (pmtsrc.good()) {
        std::getline(pmtsrc, tmp_line);
        if (pmtsrc.fail()) break;

        std::stringstream ss;
        ss << tmp_line;
        ss >> m_copyno >> m_theta >> m_phi;
        if (ss.fail()) continue;
        m_line++;
        if (m_line>7) {
            a->data[2*m_pmtID]= m_theta;
            a->data[2*m_pmtID+1]= m_phi;
            m_pmtID++;
        }
    }

    return a;
}

NP<double>* make_resFunc_array(int ni, int nj) {
    // Get response functions
    int CalibPosition[28] = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000, 14000, 15000, 16000, 16200, 16400, 16600, 16800, 17000, 17100, 17200, 17300, 17400, 17500, 17600};
    TString m_dir= "/afs/ihep.ac.cn/users/w/wenjie/workfs/workdir/anajuno/OMILREC/share/J16v1r4/WOStrut_WOChimney_x/top/";
    NP<double>* a= new NP<double>(ni, nj);
    std::cout << "response functions " << a->desc() << std::endl;
    for (int i= 0; i< 28; ++i) {
        TString m_filename= m_dir + Form("PE-theta-distribution-%dmm.root", CalibPosition[i]);
        TFile* PELikeFunFile= new TFile(m_filename);
        TGraph* PELikeFunGraph= (TGraph*)PELikeFunFile->Get("Graph");
        if (PELikeFunGraph->GetN()!=nj) {
            std::cerr << "Wrong length of response function!" << std::endl;
            break;
        }
        if (i==0) {
            double* xAxis= PELikeFunGraph->GetX();
            for (int j= 0; j< nj; ++j) {
                a->data[nj*i+j]= xAxis[j];
            }
        }
        double* yAxis= PELikeFunGraph->GetY();
        for (int j= 0; j< nj; ++j) {
            a->data[nj*(i+1)+j]= yAxis[j];
        }
        delete PELikeFunFile;
    }

    return a;
}

int main(int argc, char** argv) {
    // Position of each PMT
    const char* pmtPosPath= "./output/pmtPos.npy";
    NP<double>* pmtPos= make_pmtpos_array(17739, 2);
    pmtPos->save(pmtPosPath) ; 
    //std::cout << NPU::check(pmtPosPath) << std::endl ; 

    // Position of the vertex
    const char* vrtPath= "./output/vrt.npy";
    NP<double>* vrt= new NP<double>(1, 3);
    vrt->data[0]= 0.;
    vrt->data[1]= 0.;
    vrt->data[2]= 0.;
    vrt->save(vrtPath);

    // 28 response functions
    const char* resFuncPath= "./output/resFunction.npy";
    NP<double>* resFunc= make_resFunc_array(29, 1242);
    resFunc->save(resFuncPath);

    return 0 ; 
}

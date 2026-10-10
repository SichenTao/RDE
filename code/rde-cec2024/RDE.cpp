#include <math.h>
#include <time.h>

#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "cec17_test_func.cpp"

using namespace std;
unsigned globalseed = unsigned(time(NULL));
//unsigned globalseed = 2018;
unsigned seed1 = globalseed + 0;
unsigned seed2 = globalseed + 100;
unsigned seed3 = globalseed + 200;
unsigned seed4 = globalseed + 300;
unsigned seed5 = globalseed + 400;
std::mt19937 generator_uni_i(seed1);
std::mt19937 generator_uni_r(seed2);
std::mt19937 generator_norm(seed3);
std::mt19937 generator_cachy(seed4);
std::mt19937 generator_uni_i_2(seed5);
std::uniform_int_distribution<int> uni_int(0, 32768);
std::uniform_real_distribution<double> uni_real(0.0, 1.0);
std::normal_distribution<double> norm_dist(0.0, 1.0);
std::cauchy_distribution<double> cachy_dist(0.0, 1.0);
const char* algName = "RDE_CEC2024";
double EB_flag = 1;
double EB_hybrid_rate = 0.5;
double A_flag = 1; //stragegy A- the last memory of F and CR are both fixed to 0.9.
double Cs_flag = 1; //strategy Cs - initial psize and its decreasing.
double G_flag = 1; //strategy G- limit F and CR in some stages of the FEval.
double H_flag = 1; //strategy H- select Rand1 and Rand2 by rand-based selective pressure strategy (RSP).
double Hp_flag = 1; //strategy Hp- select Prand by rand-based selective pressure strategy (RSP).
double Ha_flag = 1; //strategy Ha- select the Archive part Rand2_arch by rand-based selective pressure strategy (RSP).
double I_flag = 1; //strategy I- cauchy_distribution strategy in iLSHADE-RSP for some of dimensions of which are not selective to do crossover.
double jumping_rate = 0.2;
int NP;
int LM_NFES;
double fitlim;

void columnMeans(double** matrix, int rows, int cols, double* means) {
    for (int j = 0; j < cols; ++j) {
        double sum = 0.0;
        for (int i = 0; i < rows; ++i) {
            sum += matrix[i][j];
        }
        means[j] = sum / rows;
    }
}

void columnStd(double** matrix, double* xmean, int rows, int cols, double* stds) {
    for (int j = 0; j < cols; ++j) {
        double mean = xmean[j];
        double sumSq = 0.0;
        for (int i = 0; i < rows; ++i) {
            sumSq += (matrix[i][j] - mean) * (matrix[i][j] - mean);
        }
        stds[j] = sqrt(sumSq / rows);
    }
}

void findMinAndIndex(const double arr[], int size, double& minVal, int& minIndex) {
    if (size <= 0) {
        std::cerr << "array contains none" << std::endl;
        return;
    }

    minVal = arr[0];
    minIndex = 0;

    for (int i = 1; i < size; ++i) {
        if (arr[i] < minVal) {
            minVal = arr[i];
            minIndex = i;
        }
    }
}

int IntRandom(int target) {
    if (target == 0)
        return 0;
    return uni_int(generator_uni_i) % target;
}
double Random(double minimal, double maximal) {
    return uni_real(generator_uni_r) * (maximal - minimal) + minimal;
}
double NormRand(double mu, double sigma) {
    return norm_dist(generator_norm) * sigma + mu;
}
double CachyRand(double mu, double sigma) {
    return cachy_dist(generator_cachy) * sigma + mu;
}
void qSort2int(double* Mass, int* Mass2, int low, int high) {
    int i = low;
    int j = high;
    double x = Mass[(low + high) >> 1];
    do {
        while (Mass[i] < x) ++i;
        while (Mass[j] > x) --j;
        if (i <= j) {
            double temp = Mass[i];
            Mass[i] = Mass[j];
            Mass[j] = temp;
            double temp2 = Mass2[i];
            Mass2[i] = Mass2[j];
            Mass2[j] = temp2;
            i++;
            j--;
        }
    } while (i <= j);
    if (low < j) qSort2int(Mass, Mass2, low, j);
    if (i < high) qSort2int(Mass, Mass2, i, high);
}

void cec17_test_func(double*, double*, int, int, int);
double *OShift, *M, *y, *z, *x_bound;
int ini_flag = 0, n_flag, func_flag, *SS;
int GNVars;
std::vector<double> generateSequence(double start, double end, double step) {
    std::vector<double> sequence;
    for (int i_sequence = start; i_sequence <= end; i_sequence += step) {
        sequence.push_back(i_sequence/end);
    }
    sequence[0] = 1.0/300000.0;
    return sequence;
}
std::vector<double> stepsFEval = generateSequence(0, 1000, 1);

double ResultsArray[25][1001];
int LastFEcount;
int NFEval = 0;
int MaxFEval = 0;
double tempF[1];
double fopt[1];
char buffer[30];
double globalbest;
bool globalbestinit;
bool initfinished;
vector<double> FitTemp;

void GetOptimum(int func_num, double* xopt, double* fopt) {
    FILE* fpt;
    char FileName[30];
    sprintf(FileName, "input_data/shift_data_%d.txt", func_num);
    fpt = fopen(FileName, "r");
    if (fpt == NULL)
        printf("\n Error: Cannot open input file for reading \n");
    for (int k = 0; k < GNVars; k++)
        fscanf(fpt, "%lf", &xopt[k]);
    fclose(fpt);
    cec17_test_func(xopt, fopt, GNVars, 1, func_num);
}
void SaveBestValues(int RunN, double newbestfit) {
    for (int stepFEcount = LastFEcount; stepFEcount < 1001; stepFEcount++) {
        if (NFEval == int(stepsFEval[stepFEcount] * MaxFEval)) {
            double temp = globalbest - fopt[0];
            if (temp <= 10E-8)
                temp = 0;
            ResultsArray[RunN][stepFEcount] = temp;
            LastFEcount = stepFEcount;
        }
    }
}
void FindLimits(double* Ind, double* Parent, int CurNVars, double CurLeft, double CurRight) {
    for (int j = 0; j < CurNVars; j++) {
        if (Ind[j] < CurLeft)
            Ind[j] = (CurLeft + Parent[j]) / 2.0;
        if (Ind[j] > CurRight)
            Ind[j] = (CurRight + Parent[j]) / 2.0;
    }
}
class Optimizer {
   public:
    bool FitNotCalculated;
    double F;
    double F2;
    double Cr;
    int Int_ArchiveSizeParam;
    int MemorySize;
    int MemoryIter;
    int SuccessFilled;
    int MemoryCurrentIndex;

    int NVars;
    int NInds;
    int NIndsMax;
    int NIndsMin;

    double bestfit;
    int besti;

    int func_num;
    int TheChosenOne;
    int Generation;
    double ArchiveSizeParam;
    double psize;
    double psizeParam;
    int ArchiveSize;
    int CurrentArchiveSize;
    double ArchiveProb;

    double* Donor;
    double* Trial;
    int* Rands;

    double** Popul;
    double** PopulTemp;
    double* FitMass;
    double* FitMassTemp;
    double* FitMassCopy;
    double* BestInd;
    int* Indexes;
    double** Archive;
    double* FitMassArch;

    // EB_order
    // double EB_hybrid_rate;
    double* ord_best_arch;
    double* ord_medium_arch;
    double* ord_worst_arch;
    double* ord_best_popul;
    double* ord_medium_popul;
    double* ord_worst_popul;
    // EB_order
	void EB_order(int prand, int Rand1, int Rand2);
    double* EB_hybrid_flag;
    void UpdateEB_hybrid_param(double* EB_hybrid_flag, double* FitMass, vector<double> FitTemp);

    double* tempSuccessCr;
    double* tempSuccessF;

    double Right;
    double Left;

    double* MemoryCr;
    double* MemoryF;
    double* FitDelta;

    void Initialize(int newNInds, int newNVars, int func_num,
                    double NewArchSizeParam, double NewArchiveProbParam, double NewPSize);
    void Clean();
    void MainCycle(int RunN);
    void FindNSaveBest(bool init);

    void PSO_MoveP();
    void PSO_UpdateBests(int TheChosenOne);

    void CopyToArchive(double* RefusedParent, double RefusedFitness);
    void SaveSuccessCrF(double Cr, double F, double FitD);
    void UpdateMemoryCrF();
    double MeanWL(double* Vector, double* TempWeights, int Size);
    void RemoveWorst(int NInds, int NewNInds);

    int GetImprState();
    bool GetFitState();

    int SelectWorst();
    int SelectBest();
};
double cec_17_(double* HostVector, int func_num) {
    cec17_test_func(HostVector, tempF, GNVars, 1, func_num);
    NFEval++;
    return tempF[0];
}
void Optimizer::Initialize(int newNInds, int newNVars, int newfunc_num,
                           double NewArchSizeParam, double NewArchiveProbParam, double NewPSize) {
    FitNotCalculated = true;
    NInds = newNInds;
    NIndsMax = NInds;
    NIndsMin = 4;
    NVars = newNVars;
    Left = -100;
    Right = 100;
    Cr = 0.5;
    F = 0.8;
    besti = 0;
    Generation = 0;
    TheChosenOne = 0;
    CurrentArchiveSize = 0;
    psizeParam = NewPSize;
    ArchiveSizeParam = NewArchSizeParam;
    Int_ArchiveSizeParam = ceil(ArchiveSizeParam);
    ArchiveSize = NIndsMax * ArchiveSizeParam;
    ArchiveProb = NewArchiveProbParam;
    func_num = newfunc_num;

    Popul = new double*[NIndsMax];
    for (int i = 0; i != NIndsMax; i++)
        Popul[i] = new double[NVars];
    PopulTemp = new double*[NIndsMax];
    for (int i = 0; i != NIndsMax; i++)
        PopulTemp[i] = new double[NVars];
    Archive = new double*[NIndsMax * Int_ArchiveSizeParam];
    for (int i = 0; i != NIndsMax * Int_ArchiveSizeParam; i++)
        Archive[i] = new double[NVars];
    FitMassArch = new double[NIndsMax * Int_ArchiveSizeParam];
    FitMass = new double[NIndsMax];
    FitMassTemp = new double[NIndsMax];
    FitMassCopy = new double[NIndsMax];
    Indexes = new int[NIndsMax];
    BestInd = new double[NVars];

    // EB_order
    EB_hybrid_flag = new double[NIndsMax];

    for (int i = 0; i < NIndsMax; i++)
        for (int j = 0; j < NVars; j++)
            Popul[i][j] = Random(Left, Right);

    Donor = new double[NVars];
    Trial = new double[NVars];
    Rands = new int[NIndsMax];

    tempSuccessCr = new double[NIndsMax];
    tempSuccessF = new double[NIndsMax];
    FitDelta = new double[NIndsMax];

    for (int i = 0; i != NIndsMax; i++) {
        tempSuccessCr[i] = 0;
        tempSuccessF[i] = 0;
    }

    MemorySize = 5;
    MemoryIter = 0;
    SuccessFilled = 0;

    MemoryCr = new double[MemorySize];
    MemoryF = new double[MemorySize];
    for (int i = 0; i != MemorySize; i++) {
        MemoryCr[i] = 0.8 + 0.0 * Random(0, 1);
        MemoryF[i] = 0.3 + 0.0 * Random(0, 1);
    }
}
void Optimizer::SaveSuccessCrF(double Cr, double F, double FitD) {
    tempSuccessCr[SuccessFilled] = Cr;
    tempSuccessF[SuccessFilled] = F;
    FitDelta[SuccessFilled] = FitD;
    SuccessFilled++;
}
void Optimizer::UpdateMemoryCrF() {
    if (SuccessFilled != 0) {
        double Old_F = MemoryF[MemoryIter];
        double Old_Cr = MemoryCr[MemoryIter];
        double tempmax = tempSuccessCr[0];
        for (int i = 0; i != SuccessFilled; i++)
            if (tempSuccessCr[i] > tempmax)
                tempmax = tempSuccessCr[i];
        if (MemoryCr[MemoryIter] == -1 || tempmax == 0)
            MemoryCr[MemoryIter] = -1;
        else
            MemoryCr[MemoryIter] = (MeanWL(tempSuccessCr, FitDelta, SuccessFilled) + Old_Cr) / 2.0;
            MemoryF[MemoryIter] = MeanWL(tempSuccessF, FitDelta, SuccessFilled);
        MemoryIter++;
        if (MemoryIter >= MemorySize)
            MemoryIter = 0;
    }
}
double Optimizer::MeanWL(double* Vector, double* TempWeights, int Size) {
    double SumWeight = 0;
    double SumSquare = 0;
    double Sum = 0;
    for (int i = 0; i != SuccessFilled; i++)
        SumWeight += TempWeights[i];
    double* Weights = new double[SuccessFilled];

    for (int i = 0; i != SuccessFilled; i++)
        Weights[i] = TempWeights[i] / SumWeight;
    for (int i = 0; i != SuccessFilled; i++)
        SumSquare += Weights[i] * Vector[i] * Vector[i];
    for (int i = 0; i != SuccessFilled; i++)
        Sum += Weights[i] * Vector[i];
    delete Weights;
    if (fabs(Sum) > 0.000001)
        return SumSquare / Sum;
    else
        return 0.5;
}
void Optimizer::CopyToArchive(double* RefusedParent, double RefusedFitness) {
    if (CurrentArchiveSize < ArchiveSize) {
        for (int i = 0; i != NVars; i++)
            Archive[CurrentArchiveSize][i] = RefusedParent[i];
        FitMassArch[CurrentArchiveSize] = RefusedFitness;
        CurrentArchiveSize++;
    } else {
        int RandomNum = IntRandom(ArchiveSize);
        for (int i = 0; i != NVars; i++)
            Archive[RandomNum][i] = RefusedParent[i];
        FitMassArch[RandomNum] = RefusedFitness;
    }
}
void Optimizer::FindNSaveBest(bool init) {
    if (FitMass[TheChosenOne] <= bestfit || init) {
        bestfit = FitMass[TheChosenOne];
        besti = TheChosenOne;
        for (int j = 0; j != NVars; j++)
            BestInd[j] = Popul[besti][j];
    }
    if (bestfit < globalbest)
        globalbest = bestfit;
}
void Optimizer::RemoveWorst(int NInds, int NewNInds) {
    int PointsToRemove = NInds - NewNInds;
    for (int L = 0; L != PointsToRemove; L++) {
        double WorstFit = FitMass[0];
        int WorstNum = 0;
        for (int i = 1; i != NInds; i++) {
            if (FitMass[i] > WorstFit) {
                WorstFit = FitMass[i];
                WorstNum = i;
            }
        }
        for (int i = WorstNum; i != NInds - 1; i++) {
            for (int j = 0; j != NVars; j++)
                Popul[i][j] = Popul[i + 1][j];
            FitMass[i] = FitMass[i + 1];
        }
    }
}

void Optimizer::EB_order(int prand, int Rand1, int Rand2) {//double* pos1, double* pos2, double* pos3, double* pos4, double* pos1_Fit, double* pos2_Fit, double* pos3_Fit, double* pos4_Fit
    double* pos1 = Popul[prand];
    double pos1Fit = FitMass[prand];
    // double* pos2 = Popul[TheChosenOne];
    // double pos2Fit = FitMass[TheChosenOne];
    double* pos3 = Popul[Rand1];
    double pos3Fit = FitMass[Rand1];
    double* pos4_arch = Archive[Rand2];
    double pos4Fit_arch = FitMassArch[Rand2];
    if (pos1Fit <= pos3Fit && pos1Fit <= pos4Fit_arch){
        ord_best_arch = pos1;
        if (pos3Fit <= pos4Fit_arch){
            ord_medium_arch = pos3;
            ord_worst_arch = pos4_arch;
        }
        else{
            ord_medium_arch = pos4_arch;
            ord_worst_arch = pos3;
        }
    }
    else if (pos3Fit <= pos1Fit && pos3Fit <= pos4Fit_arch){
        ord_best_arch = pos3;
        if (pos1Fit <= pos4Fit_arch){
            ord_medium_arch = pos1;
            ord_worst_arch = pos4_arch;
        }
        else{
            ord_medium_arch = pos4_arch;
            ord_worst_arch = pos1;
        }
    }
    else if (pos4Fit_arch <= pos1Fit && pos4Fit_arch <= pos3Fit){
        ord_best_arch = pos4_arch;
        if (pos1Fit <= pos3Fit){
            ord_medium_arch = pos1;
            ord_worst_arch = pos3;
        }
        else{
            ord_medium_arch = pos3;
            ord_worst_arch = pos1;
        }
    }


    double* pos4_popul = Popul[Rand2];
    double pos4Fit_popul = FitMass[Rand2];
    if (pos1Fit <= pos3Fit && pos1Fit <= pos4Fit_popul){
        ord_best_popul = pos1;
        if (pos3Fit <= pos4Fit_popul){
            ord_medium_popul = pos3;
            ord_worst_popul = pos4_popul;
        }
        else{
            ord_medium_popul = pos4_popul;
            ord_worst_popul = pos3;
        }
    }
    else if (pos3Fit <= pos1Fit && pos3Fit <= pos4Fit_popul){
        ord_best_popul = pos3;
        if (pos1Fit <= pos4Fit_popul){
            ord_medium_popul = pos1;
            ord_worst_popul = pos4_popul;
        }
        else{
            ord_medium_popul = pos4_popul;
            ord_worst_popul = pos1;
        }
    }
    else if (pos4Fit_popul <= pos1Fit && pos4Fit_popul <= pos3Fit){
        ord_best_popul = pos4_popul;
        if (pos1Fit <= pos3Fit){
            ord_medium_popul = pos1;
            ord_worst_popul = pos3;
        }
        else{
            ord_medium_popul = pos3;
            ord_worst_popul = pos1;
        }
    }
}

void Optimizer::UpdateEB_hybrid_param(double* EB_hybrid_flag, double* FitMass, vector<double> FitTemp) {
    double SumEB_DeltaFit = 0;
    double SumOrigin_DeltaFit = 0;
    // cout << "EB_hybrid_rate = " << EB_hybrid_rate << "\n";
    for (int TheChosenOne = 0; TheChosenOne != NInds; TheChosenOne++) {
        // cout << "EB_hybrid_flag[TheChosenOne] = " << EB_hybrid_flag[TheChosenOne] << "\n";
        if (EB_hybrid_flag[TheChosenOne] == 1) {
            if (FitTemp[TheChosenOne] <= FitMass[TheChosenOne]) {
                SumEB_DeltaFit += FitMass[TheChosenOne] - FitTemp[TheChosenOne];
                // cout << "SumEB_DeltaFit = " << SumEB_DeltaFit << "\n";
            }
        }
        else{
            if (FitTemp[TheChosenOne] <= FitMass[TheChosenOne]) {
                SumOrigin_DeltaFit += FitMass[TheChosenOne] - FitTemp[TheChosenOne];
                // cout << "SumOrigin_DeltaFit = " << SumOrigin_DeltaFit << "\n";
            }
        }
    }

    if (SumEB_DeltaFit != 0 && SumOrigin_DeltaFit != 0){
        EB_hybrid_rate = SumEB_DeltaFit / (SumEB_DeltaFit + SumOrigin_DeltaFit);
        double EB_limit_min = 0;
        double EB_limit_max = 1;
        if (EB_hybrid_rate > EB_limit_max){
            EB_hybrid_rate = EB_limit_max;
        }
        else if (EB_hybrid_rate < EB_limit_min){
            EB_hybrid_rate = EB_limit_min;
        }
    }
    else{
        EB_hybrid_rate = 0.5;
    }
    // cout << "EB_hybrid_rate = " << EB_hybrid_rate << "\n";
}

void Optimizer::MainCycle(int RunN) {
    for (int TheChosenOne = 0; TheChosenOne != NInds; TheChosenOne++) {
        FitMass[TheChosenOne] = cec_17_(Popul[TheChosenOne], func_num);
        FindNSaveBest(TheChosenOne == 0);
        if (!globalbestinit || bestfit < globalbest) {
            globalbest = bestfit;
            globalbestinit = true;
        }
        SaveBestValues(RunN, bestfit);
    }
    do {
        double minfit = FitMass[0];
        double maxfit = FitMass[0];
        int prand;
        minfit = FitMass[0];
        maxfit = FitMass[0];
        for (int i = 0; i != NInds; i++) {
            FitMassCopy[i] = FitMass[i];
            Indexes[i] = i;
            if (FitMass[i] >= maxfit)
                maxfit = FitMass[i];
            if (FitMass[i] <= minfit)
                minfit = FitMass[i];
        }
        if (minfit != maxfit)
            qSort2int(FitMassCopy, Indexes, 0, NInds - 1);
        FitTemp.resize(NInds);
        for (int i = 0; i != NInds; i++)
            FitTemp[i] = 3.0 * (NInds - i);
        std::discrete_distribution<int> ComponentSelector(FitTemp.begin(), FitTemp.end());

        psize = psizeParam * (1 - 0.5 * (double)NFEval / (double)MaxFEval);

        int psizeval = NInds * psize;
        if (psizeval <= 1)
            psizeval = 2;

        std::discrete_distribution<int> ComponentSelector1(FitTemp.begin(), FitTemp.begin() + psizeval);
        
        int* IndexesArch;
        IndexesArch = new int[CurrentArchiveSize];
        vector<double> FitMassArch_RSP;
        if (Ha_flag == 1){
            double minfitArch = FitMassArch[0];
            double maxfitArch = FitMassArch[0];
            minfitArch = FitMassArch[0];
            maxfitArch = FitMassArch[0];
            double* FitMassArchCopy;
            FitMassArchCopy = new double[CurrentArchiveSize];
            for (int i = 0; i != CurrentArchiveSize; i++) {
                FitMassArchCopy[i] = FitMassArch[i];
                IndexesArch[i] = i;
                if (FitMassArch[i] >= maxfitArch)
                    maxfitArch = FitMassArch[i];
                if (FitMassArch[i] <= minfitArch)
                    minfitArch = FitMassArch[i];
            }
            if (minfitArch != maxfitArch)
                qSort2int(FitMassArchCopy, IndexesArch, 0, CurrentArchiveSize - 1);
            // double* FitMassArch_RSP;
            // FitMassArch_RSP = new double[CurrentArchiveSize];
            
            FitMassArch_RSP.resize(CurrentArchiveSize);
            for (int i = 0; i != CurrentArchiveSize; i++)
                FitMassArch_RSP[i] = 3.0 * (CurrentArchiveSize - i);
        }
        std::discrete_distribution<int> ComponentSelector2(FitMassArch_RSP.begin(), FitMassArch_RSP.end());

        for (int TheChosenOne = 0; TheChosenOne != NInds; TheChosenOne++) {
            MemoryCurrentIndex = IntRandom(MemorySize + 1);
            do
                if (Hp_flag == 1){
                    prand = Indexes[ComponentSelector1(generator_uni_i_2)];
                }
                else{
                    prand = Indexes[IntRandom(psizeval)];
                }
            while (prand == TheChosenOne && (double)NFEval / (double)MaxFEval < 0.5);

            int Rand1;
            int Rand2;

            //strategy H
            if (H_flag == 1){
                do
                    Rand1 = Indexes[ComponentSelector(generator_uni_i_2)];
                while (Rand1 == prand);
                do
                    Rand2 = Indexes[ComponentSelector(generator_uni_i_2)];
                while (Rand2 == prand || Rand2 == Rand1);
            }
            else{
		        // cout << "H_flag = " << H_flag << "\n";
                do
                    Rand1 = IntRandom(NInds);
                while (Rand1 == prand);
                do
                    Rand2 = IntRandom(NInds);
                while (Rand2 == prand || Rand2 == Rand1);
            }

            //strategy A
			if (A_flag == 1){
				// cout << "A_flag_F = " << A_flag << "\n";
                do {
                    if (MemoryCurrentIndex < MemorySize)
                        F = CachyRand(MemoryF[MemoryCurrentIndex], 0.1);
                    else
                        F = CachyRand(0.9, 0.1);
                } while (F < 0.0);
            }
            else{
                do {
                    F = CachyRand(MemoryF[MemoryCurrentIndex], 0.1);
                } while (F < 0.0);
            }

            if (F > 1.0)
                F = 1.0;

            //strategy G
            if (G_flag == 1){
		        // cout << "G_flag_F = " << G_flag << "\n";
                if ((double)NFEval / (double)MaxFEval < 0.6 && F > 0.7)
                    F = 0.7;
            }

            F2 = 1.0 * F;

            if (EB_flag == 1) {
                double Rand_EB = Random(0, 1);
                // cout << "Rand_EB = " << Rand_EB << "\n";
                if (Rand_EB < EB_hybrid_rate){
                    // cout << "EB_hybrid_rate = " << EB_hybrid_rate << "\n";
                    EB_hybrid_flag[TheChosenOne] = 1;
                    // cout << "EB_hybrid_flag[TheChosenOne] = " << EB_hybrid_flag[TheChosenOne] << "\n";
                    if (Random(0, 1) < (double)CurrentArchiveSize / ((double)CurrentArchiveSize + (double)NInds)) {
                        if (Ha_flag == 1){
                            Rand2 = IndexesArch[ComponentSelector2(generator_uni_i_2)];
                        }
                        else{
                            Rand2 = IntRandom(CurrentArchiveSize);
                        }
                        EB_order(prand, Rand1, Rand2);
                        for (int j = 0; j != NVars; j++) {
                            Donor[j] = Popul[TheChosenOne][j] +
                                    F2 * (ord_best_arch[j] - Popul[TheChosenOne][j]) +
                                    F * (ord_medium_arch[j] - ord_worst_arch[j]);
                        }
                    } else {
                        EB_order(prand, Rand1, Rand2);
                        for (int j = 0; j != NVars; j++) {
                            Donor[j] = Popul[TheChosenOne][j] +
                                    F2 * (ord_best_popul[j] - Popul[TheChosenOne][j]) +
                                    F * (ord_medium_popul[j] - ord_worst_popul[j]);
                        }
                    }
                }
                else{
                    EB_hybrid_flag[TheChosenOne] = 0;
                    if (Random(0, 1) < (double)CurrentArchiveSize / ((double)CurrentArchiveSize + (double)NInds)) {
                        if (Ha_flag == 1){
                            Rand2 = IndexesArch[ComponentSelector2(generator_uni_i_2)];
                        }
                        else{
                            Rand2 = IntRandom(CurrentArchiveSize);
                        }
                        for (int j = 0; j != NVars; j++) {
                            Donor[j] = Popul[TheChosenOne][j] +
                                    F2 * (Popul[prand][j] - Popul[TheChosenOne][j]) +
                                    F * (Popul[Rand1][j] - Archive[Rand2][j]);
                        }
                    } else {
                        for (int j = 0; j != NVars; j++) {
                            Donor[j] = Popul[TheChosenOne][j] +
                                    F2 * (Popul[prand][j] - Popul[TheChosenOne][j]) +
                                    F * (Popul[Rand1][j] - Popul[Rand2][j]);
                        }
                    }
                }
            }
            else{
                if (Random(0, 1) < (double)CurrentArchiveSize / ((double)CurrentArchiveSize + (double)NInds)) {
                    Rand2 = IntRandom(CurrentArchiveSize);
                    for (int j = 0; j != NVars; j++) {
                        Donor[j] = Popul[TheChosenOne][j] +
                                F2 * (Popul[prand][j] - Popul[TheChosenOne][j]) +
                                F * (Popul[Rand1][j] - Archive[Rand2][j]);
                    }
                } else {
                    for (int j = 0; j != NVars; j++) {
                        Donor[j] = Popul[TheChosenOne][j] +
                                F2 * (Popul[prand][j] - Popul[TheChosenOne][j]) +
                                F * (Popul[Rand1][j] - Popul[Rand2][j]);
                    }
                }
            }
        
            FindLimits(Donor, Popul[TheChosenOne], NVars, Left, Right);

            int WillCrossover = IntRandom(NVars);

            //strategy A
            if (A_flag == 1){
				// cout << "A_flag_CR = " << A_flag << "\n";
                if (MemoryCurrentIndex < MemorySize) {
                    if (MemoryCr[MemoryCurrentIndex] < 0)
                        Cr = 0;
                    else
                        Cr = NormRand(MemoryCr[MemoryCurrentIndex], 0.1);
                } else
                    Cr = NormRand(0.9, 0.1);
            }
            else{
				// cout << "A_flag_CR = " << A_flag << "\n";
                if (MemoryCr[MemoryCurrentIndex] < 0)
                    Cr = 0;
                else
                    Cr = NormRand(MemoryCr[MemoryCurrentIndex], 0.1);
            }

            if (Cr >= 1)
                Cr = 1;
            if (Cr <= 0)
                Cr = 0;
            
            //strategy G
            if (G_flag == 1){
		        // cout << "G_flag_CR = " << G_flag << "\n";
                if ((double)NFEval / (double)MaxFEval < 0.25)
                    Cr = max(Cr, 0.7);
                if ((double)NFEval / (double)MaxFEval < 0.5)
                    Cr = max(Cr, 0.6);
            }

            //strategy I
            if (I_flag == 1){
		        // cout << "I_flag = " << I_flag << "\n";
                bool perturbation = rand() / (double)RAND_MAX < jumping_rate;
                for (int j = 0; j != NVars; j++) {
                    if (Random(0, 1) < Cr || WillCrossover == j)
                        PopulTemp[TheChosenOne][j] = Donor[j];
                    else
                        PopulTemp[TheChosenOne][j] = perturbation ? CachyRand(Popul[TheChosenOne][j], 0.1) : Popul[TheChosenOne][j];
                }
            }
            else{
		        // cout << "I_flag = " << I_flag << "\n";
                for (int j = 0; j != NVars; j++) {
                    if (Random(0, 1) < Cr || WillCrossover == j)
                        PopulTemp[TheChosenOne][j] = Donor[j];
                }
            }

            FindLimits(PopulTemp[TheChosenOne], Popul[TheChosenOne], NVars, Left, Right);
            FitTemp[TheChosenOne] = cec_17_(PopulTemp[TheChosenOne], func_num);
            if (FitTemp[TheChosenOne] <= globalbest)
                globalbest = FitTemp[TheChosenOne];
            if (FitTemp[TheChosenOne] <= FitMass[TheChosenOne])
                SaveSuccessCrF(Cr, F, fabs(FitMass[TheChosenOne] - FitTemp[TheChosenOne]));
            SaveBestValues(RunN, bestfit);
        }
        if (EB_flag == 1){
            UpdateEB_hybrid_param(EB_hybrid_flag, FitMass, FitTemp);
        }

        for (int TheChosenOne = 0; TheChosenOne != NInds; TheChosenOne++) {
            if (FitTemp[TheChosenOne] <= FitMass[TheChosenOne]) {
                CopyToArchive(Popul[TheChosenOne], FitMass[TheChosenOne]);
                for (int j = 0; j != NVars; j++)
                    Popul[TheChosenOne][j] = PopulTemp[TheChosenOne][j];
                FitMass[TheChosenOne] = FitTemp[TheChosenOne];
            }
        }

        int newNInds = int(double(NIndsMin - NIndsMax) / MaxFEval * NFEval + NIndsMax);
        if (newNInds < NIndsMin)
            newNInds = NIndsMin;
        if (newNInds > NIndsMax)
            newNInds = NIndsMax;
        int newArchSize = double(MaxFEval - NFEval) / (double)MaxFEval * (ArchiveSizeParam * (NIndsMax - NIndsMin));
        if (newArchSize < NIndsMin)
            newArchSize = NIndsMin;
        ArchiveSize = newArchSize;
        if (CurrentArchiveSize >= ArchiveSize)
            CurrentArchiveSize = ArchiveSize;
        RemoveWorst(NInds, newNInds);
        NInds = newNInds;
        UpdateMemoryCrF();

        SuccessFilled = 0;
        Generation++;
    } while (NFEval < MaxFEval);
}
void Optimizer::Clean() {
    delete Donor;
    delete Trial;
    delete Rands;
    for (int i = 0; i != NIndsMax; i++) {
        delete Popul[i];
        delete PopulTemp[i];
    }
    for (int i = 0; i != NIndsMax * Int_ArchiveSizeParam; i++){
        delete Archive[i];
    }

    delete Archive;

    delete Popul;

    delete PopulTemp;
    delete FitMass;
    delete FitMassTemp;
    delete FitMassCopy;
    delete BestInd;
    delete Indexes;
    delete tempSuccessCr;
    delete tempSuccessF;
    delete FitDelta;
    delete MemoryCr;
    delete MemoryF;
}
int main() {
    cout << "Random seeds are:" << endl;
    cout << seed1 << "\t" << seed2 << "\t" << seed3 << "\t" << seed4 << "\t" << seed5 << "\n";

	int GNVarsIter = 1; {
        if (GNVarsIter == 0)
            GNVars = 10;
        if (GNVarsIter == 1)
            GNVars = 30;
        if (GNVarsIter == 2)
            GNVars = 50;
        if (GNVarsIter == 3)
            GNVars = 100;
        MaxFEval = GNVars * 10000;
        cout << "Run D_" << GNVars << "\n";
        Optimizer OptZ;
        double* xopt = new double[GNVars];

        for (int func_num = 1; func_num < 31; func_num++) {
            if (false){
                if (func_num == 2)
                    continue;  //F2 is excluded from the competition!
            }
            cout << "Function " << func_num << "\t"
                 << "D" << GNVars << "\n"
                 << "Runs: " << endl;
            sprintf(buffer, "%s_D%d_F%d.txt", algName, GNVars, func_num);
            ofstream fout(buffer);
            for (int RunN = 0; RunN != 25; RunN++) {
                cout << RunN << "\t";
                GetOptimum(func_num, xopt, fopt);
                globalbestinit = false;
                initfinished = false;
                LastFEcount = 0;
                NFEval = 0;
                double NewPopSize;
                NewPopSize = int(18 * GNVars);
                double NewArchSize = 1.0;
                double NewArchProb = 0.25;
                double NewPsize;
                NewPsize = 0.25;
                OptZ.Initialize(NewPopSize, GNVars, func_num, NewArchSize, NewArchProb, NewPsize);
                OptZ.MainCycle(RunN);
                OptZ.Clean();
            }
            cout << endl;
            for (int i = 0; i != 1001; i++) {
                for (int j = 0; j != 25; j++)
                    fout << ResultsArray[j][i] << "\t";
                fout << "\n";
            }
        }
        cout << endl;
        delete xopt;
    }
    return 0;
}

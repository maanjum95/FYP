#ifndef PPGWORKER_H
#define PPGWORKER_H

#include <QObject>
#include <QThread>
#include <QtTest/QtTest>
#include <cmath>

#include <fstream>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "PPG_C++/ppg_analysis.h"
#include "MAX117/max30102.h"

class PPGWorker : public QObject
{
    Q_OBJECT
signals:
    void resultsReady(double *ppg_red, double *ppg_ir, double hr, double rr, double rr_std, double spo2, bool anomaly);
    void return_ppg_status(const bool &status);
    void ppg_samples(const int &samples);
    void ppg_device_fail();

public slots:
    void ppg_work();
    void ppg_stop();
    void ppg_status();
    void ppg_save(const int &id);
    void ppg_update(const int &update);

private:
    PPG::PPGAnalysis ppg_analysis;
    bool exec_ppg_thread = false;
    double *linear_interp_10(vector<double> to_interp, int start_index);
    vector<double> ppg_red;
    vector<double> ppg_ir;
    signed int last_index = 0, update=125;
    int handle; // serial communication handler

    double anomaly_gauss(double x, double mu, double sig);
    bool anomaly(double hr, double rr, double rr_dev);
    void sendSerialData(double hr, double rr, double rr_dev, double spo2);

public:
    PPGWorker();
};

#endif // PPGWORKER_H

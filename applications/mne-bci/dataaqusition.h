#pragma once

#include <iostream>
#include <string>
#include <Eigen>
#include <boost>

#include <QtCore/QtPlugin>
#include <QDebug>
#include <QSharedPointer>
#include <QVector>
#include <QList>
#include <QMutex>
#include <QMutexLocker>

#include <QSharedPointer>
#include <QMetaType>

#include <dummytoolbox.h>
#include <pluginoutputdata.h>
#include <realtimemultisamplearray.h>

#include "MatlabEngine.hpp"
#include "MatlabDataArray.hpp"

using namespace matlab::engine;

class DataAquisition {

private:
	QSharedPointer<DummyToolbox> Aquier;
	QSharedPointer<RealTimeMultiSampleArray> DataMultiSampleArray;

	std::unique_ptr<MATLABEngine> matlabPtr;
	matlab::data::ArrayFactory factory;

public:
	void DataAquisition();
	void ~DataAquisition();

	bool Start();
	void Run();
	bool Stop();

	QList<Eigen::MatrixXd> getData();

	QSharedPointer<RealTimeMultiSampleArray>  MSPCI (QList<Eigen::MatrixXd> Array, int LEVEL, string WNAME,int NPC);
	std::tuple EMD(QList<Eigen::MatrixXd> Array);

};
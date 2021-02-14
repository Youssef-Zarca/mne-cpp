#pragma once

#include <iostream>
#include <string>
#include <Eigen>
#include <boost>

#include <dataaqusition.h>

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


class FeatureExtraction {
private:
	QSharedPointer<DataAquisition> DataOutput;

public:
	std::tuple Average(std::tupley IMFs);
	float AveragePower(std::tuple IMFs);
	float STD(std::tuple IMFs);
	float RAMV(std::tuple IMFs);
	float Skewness(std::tuple IMFs);
	float Kortosis(std::tuple IMFs);
	
};
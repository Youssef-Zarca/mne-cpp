#pragma once

#include <dataaqusition.h>

void DataAqusition::DataAquisition() {
	this.Aquier.DummyToolbox();
	this.matlabPtr = startMATLAB();
};

void DataAqusition::~DataAquisition() {
	this.stop();
};

bool DataAqusition::Start() {
	return this.Aquier.start();
};

void DataAqusition::Run() {
	this.Aquier.run();
};

bool DataAqusition::Stop() {
	return this.Aquier.stop();
};

QList<Eigen::MatrixXd>  DataAqusition::getData() {
	return this.DataMultiSampleArray.getMultiSampleArray();
};

QSharedPointer<RealTimeMultiSampleArray>   DataAquisition::MSPCI (QList<Eigen::MatrixXd> Array, int LEVEL, string WNAME, int NPC)) {

	std::vector<matlab::data::Array> args({
	factory.createArray<double>(Array),
	factory.createScalar<int32_t>(LEVEL),
	factory.createCharArray(WNAME),
	factory.createScalar<int32_t>(NPC),
	});

	std::tuple<matlab::data::Array> results = matlabPtr->feval(u"wmspca", args);
	DataMultiSampleArray.setValue((Eigen::MatrixXd)std::get<0> (results));
	
	return DataMultiSampleArray;
};

std::tuple DataAquisition::EMD (QList<Eigen::MatrixXd> Array) {
	int Rows = Array.rows();

	//typedef boost::multi_array <float, Rows> imfs;
	//imfs IMFs(boost::extents[][][Rows]);



	for (int i = 0; i < Rows; i++) {
		std::vector<matlab::data::Array> args({ factory.createArray<double>(Array.row(i))});
		std::tuple<matlab::data::Array> results = matlabPtr->feval(u"emd", args);
		Eigen::MatrixXd IMF = (Eigen::MatrixXd)std::get<0> (results);
		auto IMFs = std::tuple_cat(IMFs, std::make_tuple(IMF));
	}

	return IMFs;
};
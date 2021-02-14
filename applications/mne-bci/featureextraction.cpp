#pragma once

#include <featureextraction.h>

std::tuple FeatureExtraction::Average(std::tuple IMFs) {
	int Size = std::tuple_size<decltype(IMFs)>::value;
	std::tuple AllAverage;

	for (int i = 0; i < Size; i++) {
		Eigen::MatrixXd INS = (Eigen::MatrixXd)std::get<i>(IMFs);
		float Average [INS.rows()] = 0;
		for (int j = 0; j < INS.rows(); j++) {
			Average = INS.rowwise().mean();
		}
		auto AllAverage = std::tuple_cat(AllAverage, std::make_tuple(Average));
	}
	return AllAverage;
};
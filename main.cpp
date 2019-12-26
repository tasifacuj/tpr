#include <iostream>
#include <array>
#include <map>
#include <cmath>
#include <fstream>

#include "GradientDescent.hpp"
#include "PenaltyFunction.hpp"
#include "subj_17.hpp"
#include "TrainingModel.hpp"


///**
//  * f(x) = 10 * x1^2 + x2 ^ 2
//  * df
//  * --- = 20 * x1
//  * dx1
//  * df/dx2 = 2*x2
//  */
//template<typename ValueT = float>
//class QuadF {
//public:// == CONSTANTS ==
//	static constexpr size_t N = 2;
//public: // == TYPES ==
//	using ValueType = ValueT;
//	using VectorT = std::array<ValueType, N>;
//public: // == METHODS ==
//	static ValueType apply( const VectorT& args ) {
//		return 10 * args[0] * args[0] + args[1] * args[1];
//	}
//
//	static VectorT gradient( const VectorT& args ) {
//		// 20 * x1 + 2 * x2
//		VectorT tmp;
//		tmp[ 0 ] = 20 * args[ 0 ];
//		tmp[ 1 ] = 2 * args[ 1 ];
//		return tmp;
//	}
//};
//

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// my task
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
#if 1
	assert(tpr::subj_17::model_index_to_index.size() == 18);
	using PF = tpr::PenaltyFunction<tpr::subj_17::Fx, size_t, tpr::subj_17::G1, tpr::subj_17::G2, tpr::subj_17::G3, tpr::subj_17::G4, tpr::subj_17::G5, tpr::subj_17::G6, tpr::subj_17::G7, tpr::subj_17::G8, tpr::subj_17::G9>;
	PF::VectorT x0;

	for (size_t idx = 0; idx < x0.size(); idx++)
		x0[idx] = 50;

	PF::VectorT xOpt = PF::evaluate(x0);
	std::ofstream out("x_opt.txt");

	for (size_t idx = 0; idx < PF::N; idx++) {
		int modelIndex = tpr::subj_17::index_to_model_index_converter[idx];
		out << "x[ " << modelIndex << " ]opt = " << std::round(xOpt[idx]) << " --> " << tpr::subj_17::model_index_to_description_conv[modelIndex] << '\n';
	}

	PF::ValueType sumProdA = xOpt[tpr::subj_17::model_index_to_index[111]] 
		+ xOpt[tpr::subj_17::model_index_to_index[112]]
		+ xOpt[tpr::subj_17::model_index_to_index[211]]
		+ xOpt[tpr::subj_17::model_index_to_index[212]]
		+ xOpt[tpr::subj_17::model_index_to_index[311]]
		+ xOpt[tpr::subj_17::model_index_to_index[312]]
		;
	PF::ValueType sumProdB = xOpt[tpr::subj_17::model_index_to_index[121]]
		+ xOpt[tpr::subj_17::model_index_to_index[122]]
		+ xOpt[tpr::subj_17::model_index_to_index[221]]
		+ xOpt[tpr::subj_17::model_index_to_index[222]]
		+ xOpt[tpr::subj_17::model_index_to_index[321]]
		+ xOpt[tpr::subj_17::model_index_to_index[322]]
		;
	PF::ValueType sumProdC = xOpt[tpr::subj_17::model_index_to_index[131]]
		+ xOpt[tpr::subj_17::model_index_to_index[132]]
		+ xOpt[tpr::subj_17::model_index_to_index[231]]
		+ xOpt[tpr::subj_17::model_index_to_index[232]]
		+ xOpt[tpr::subj_17::model_index_to_index[331]]
		+ xOpt[tpr::subj_17::model_index_to_index[332]]
		;

	out << "sum(A) = " << sumProdA << std::endl;
	out << "sum(B) = " << sumProdB << std::endl;
	out << "sum(C) = " << sumProdC << std::endl;
	out.flush();
#else
	using TrainPF = tpr::PenaltyFunction<tpr::TrainingModel::Fx, size_t, tpr::TrainingModel::G1, tpr::TrainingModel::G2, tpr::TrainingModel::G3, tpr::TrainingModel::G4>;
	TrainPF::VectorT x0T{ 6.0f, 7.0f };
	TrainPF::VectorT xOptT = TrainPF::evaluate(x0T);
#endif
	return 0;
}
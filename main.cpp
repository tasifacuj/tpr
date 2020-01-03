#include <iostream>
#include <array>
#include <map>
#include <cmath>
#include <fstream>

#include "GradientDescent.hpp"
#include "PenaltyFunction.hpp"
#include "subj_17.hpp"
#include "TrainingModel.hpp"
#include "subj_17_simplified.hpp"
#include "ConstPenaltyFunction.hpp"

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

static void test_subj_17(){
	assert(tpr::subj_17::model_index_to_index.size() == 18);
	using PF = tpr::PenaltyFunction<tpr::subj_17::Fx, size_t, tpr::subj_17::G1, tpr::subj_17::G2, tpr::subj_17::G3, tpr::subj_17::G4, tpr::subj_17::G5, tpr::subj_17::G6, tpr::subj_17::G7, tpr::subj_17::G8, tpr::subj_17::G9>;
	PF::VectorT x0;

	for (size_t idx = 0; idx < x0.size(); idx++)
		x0[idx] = 18;

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

	out << "sum(A) = " << sumProdA << ", threshold: " << tpr::subj_17::Config::ASum << std::endl;
	out << "sum(B) = " << sumProdB << ", threshold: " << tpr::subj_17::Config::BSum << std::endl;
	out << "sum(C) = " << sumProdC << ", threshold: " << tpr::subj_17::Config::CSum << std::endl;

	out << "g1 = " << tpr::subj_17::G1::apply(xOpt) << std::endl;
	out << "g2 = " << tpr::subj_17::G2::apply(xOpt) << std::endl;
	out << "g3 = " << tpr::subj_17::G3::apply(xOpt) << std::endl;
	out << "g4 = " << tpr::subj_17::G4::apply(xOpt) << std::endl;
	out << "g5 = " << tpr::subj_17::G5::apply(xOpt) << std::endl;
	out << "g6 = " << tpr::subj_17::G6::apply( xOpt ) << std::endl;

	out << "g7 = " << tpr::subj_17::G7::apply(xOpt) << std::endl;
	out << "g8 = " << tpr::subj_17::G8::apply(xOpt) << std::endl;
	out << "g9 = " << tpr::subj_17::G9::apply(xOpt) << std::endl;
	out.flush();
}

static void test_doc_example() {
	using TrainPF = tpr::PenaltyFunction<tpr::TrainingModel::Fx, size_t, tpr::TrainingModel::G1, tpr::TrainingModel::G2, tpr::TrainingModel::G3, tpr::TrainingModel::G4>;
	TrainPF::VectorT x0T{ 6.0f, 7.0f };
	TrainPF::VectorT xOpt = TrainPF::evaluate(x0T);

	for (size_t idx = 0; idx < TrainPF::N; idx++) {
		std::cerr << "x[ " << idx << " ]opt = " << xOpt[idx] << '\n';
	}

	std::cerr << "g1 = " << (-3.0 * xOpt[0] - 2.0 * xOpt[1] + 6.0) << std::endl;
	std::cerr << "g2 = " << (-1.0 * xOpt[0] + xOpt[1] - 3.0) << std::endl;
	std::cerr << "g3 = " << (xOpt[0] + xOpt[1] - 7.0) << std::endl;
	std::cerr << "g4 = " << ( (2.0 / 3.0 ) * xOpt[0] - xOpt[1] - ( 4.0 / 3.0 )) << std::endl;
}

static void test_subj_17_simplified() {
	namespace smp = tpr::subj_17_simplified;
	using PF = tpr::PenaltyFunction<smp::Fx, size_t, smp::G1, smp::G2, smp::G3, smp::G4, smp::G5, smp::G6, smp::G7, smp::G8, smp::G9>;
	PF::VectorT x0;

	for (size_t idx = 0; idx < x0.size(); idx++)
		x0[idx] = 15;

	PF::VectorT xOpt = PF::evaluate(x0);
	std::ofstream out("x_opt_smp.txt");
	for (size_t idx = 0; idx < PF::N; idx++) {
		int modelIndex = smp::index_to_model_index_converter[idx];
		out << "x[ " << modelIndex << " ]_opt = " << xOpt[idx] << " --> " << smp::model_index_to_description_conv[modelIndex] << '\n';
	}

	PF::ValueType sumProdA = xOpt[smp::model_index_to_index[11]]
		+ xOpt[smp::model_index_to_index[21]]
		+ xOpt[smp::model_index_to_index[31]]
		;
	PF::ValueType sumProdB = xOpt[smp::model_index_to_index[12]]
		+ xOpt[smp::model_index_to_index[22]]
		+ xOpt[smp::model_index_to_index[32]]
		;
	PF::ValueType sumProdC = xOpt[smp::model_index_to_index[13]]
		+ xOpt[smp::model_index_to_index[23]]
		+ xOpt[smp::model_index_to_index[33]]
		;

	out << "sum(A) = " << sumProdA << ", threshold: " << smp::Config::ASum << std::endl;
	out << "sum(B) = " << sumProdB << ", threshold: " << smp::Config::BSum << std::endl;
	out << "sum(C) = " << sumProdC << ", threshold: " << smp::Config::CSum << std::endl;

	out << "g1 = " << smp::G1::apply(xOpt) << std::endl;
	out << "g2 = " << smp::G2::apply(xOpt) << std::endl;
	out << "g3 = " << smp::G3::apply(xOpt) << std::endl;
	out << "g4 = " << smp::G4::apply(xOpt) << std::endl;
	out << "g5 = " << smp::G5::apply(xOpt) << std::endl;
	out << "g6 = " << smp::G6::apply(xOpt) << std::endl;

	out << "g7 = " << smp::G7::apply(xOpt) << std::endl;
	out << "g8 = " << smp::G8::apply(xOpt) << std::endl;
	out << "g9 = " << smp::G9::apply(xOpt) << std::endl;
	out.flush();
}

static void test_const_impl() {
	using PF = tpr::const_impl::ConstPenaltyFunction<double, size_t>;
	PF::VectorT x0;
	for (size_t idx = 0; idx < x0.size(); idx++)
		x0[idx] = 15.0 ;

	PF::VectorT xOpt = PF::evaluate(x0);
	std::ofstream out("x_opt_very_simplified.txt");


	for (size_t idx = 0; idx < PF::N; idx++) {
		int mi = PF::idx_to_model_idx(idx);
		out << "x[ " << mi << " ]_opt = " << xOpt[idx] << " --> " << PF::model_idx_to_descr( mi ) << '\n';
	}


	PF::ValueType sumProdA = xOpt[ PF::model_index_2_index(11) ]
		+ xOpt[PF::model_index_2_index(21)]
		+ xOpt[PF::model_index_2_index(31)]
		;
	
	PF::ValueType sumProdB = xOpt[ PF::model_index_2_index(12) ]
		+ xOpt[PF::model_index_2_index(22)]
		+ xOpt[PF::model_index_2_index(32)]
		;
	
	PF::ValueType sumProdC = xOpt[PF::model_index_2_index(13)]
		+ xOpt[PF::model_index_2_index(23)]
		+ xOpt[PF::model_index_2_index(33)]
		;

	out << "sum(A) = " << sumProdA << ", threshold: " << PF::ASum << std::endl;
	out << "sum(B) = " << sumProdB << ", threshold: " << PF::BSum << std::endl;
	out << "sum(C) = " << sumProdC << ", threshold: " << PF::CSum << std::endl;

	out << "g1 = " << PF::G1(xOpt) << std::endl;
	out << "g2 = " << PF::G2(xOpt) << std::endl;
	out << "g3 = " << PF::G3(xOpt) << std::endl;
	out << "g4 = " << PF::G4(xOpt) << std::endl;
	out << "g5 = " << PF::G5(xOpt) << std::endl;
	out << "g6 = " << PF::G6(xOpt) << std::endl;
	out << "g7 = " << PF::G7(xOpt) << std::endl;
	out << "g8 = " << PF::G8(xOpt) << std::endl;
	out << "g9 = " << PF::G9(xOpt) << std::endl;
	out.flush();
}

int main() {
	test_subj_17();
	//test_subj_17_simplified();
	//test_const_impl();
	
	return 0;
}
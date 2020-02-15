#include <iostream>
#include <array>
#include <map>
#include <cmath>
#include <fstream>

#include "GradientDescent.hpp"
#include "PenaltyFunction.hpp"
#include "subj_17.hpp"
#include "TrainingModel.hpp"
#include "subj_17_p4.hpp"

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

template<typename CfgParam>
static void test_subj_17( std::string result_name, size_t startx = 18){
	assert(tpr::subj_17::model_index_to_index.size() == 18);
	using PF = tpr::PenaltyFunction<
		tpr::subj_17::Fx, 
		size_t, 
		tpr::subj_17::G1<CfgParam>,
		tpr::subj_17::G2<CfgParam>,
		tpr::subj_17::G3<CfgParam>,
		tpr::subj_17::G4<CfgParam>,
		tpr::subj_17::G5<CfgParam>,
		tpr::subj_17::G6<CfgParam>,
		tpr::subj_17::G7<CfgParam>,
		tpr::subj_17::G8<CfgParam>,
		tpr::subj_17::G9<CfgParam>
	>;
	typename PF::VectorT x0;

	for (size_t idx = 0; idx < x0.size(); idx++)
		x0[idx] = startx;

	typename PF::VectorT xOpt = PF::evaluate(x0);
	//std::ofstream out("x_opt.txt");
	std::ofstream out(result_name.c_str());

	for (size_t idx = 0; idx < PF::N; idx++) {
		int modelIndex = tpr::subj_17::index_to_model_index_converter[idx];
		out << "x[ " << modelIndex << " ]opt = " << std::round(xOpt[idx]) << " --> " << tpr::subj_17::model_index_to_description_conv[modelIndex] << '\n';
	}

	typename PF::ValueType sumProdA = xOpt[tpr::subj_17::model_index_to_index[111]]
		+ xOpt[tpr::subj_17::model_index_to_index[112]]
		+ xOpt[tpr::subj_17::model_index_to_index[211]]
		+ xOpt[tpr::subj_17::model_index_to_index[212]]
		+ xOpt[tpr::subj_17::model_index_to_index[311]]
		+ xOpt[tpr::subj_17::model_index_to_index[312]]
		;
	typename PF::ValueType sumProdB = xOpt[tpr::subj_17::model_index_to_index[121]]
		+ xOpt[tpr::subj_17::model_index_to_index[122]]
		+ xOpt[tpr::subj_17::model_index_to_index[221]]
		+ xOpt[tpr::subj_17::model_index_to_index[222]]
		+ xOpt[tpr::subj_17::model_index_to_index[321]]
		+ xOpt[tpr::subj_17::model_index_to_index[322]]
		;
	typename PF::ValueType sumProdC = xOpt[tpr::subj_17::model_index_to_index[131]]
		+ xOpt[tpr::subj_17::model_index_to_index[132]]
		+ xOpt[tpr::subj_17::model_index_to_index[231]]
		+ xOpt[tpr::subj_17::model_index_to_index[232]]
		+ xOpt[tpr::subj_17::model_index_to_index[331]]
		+ xOpt[tpr::subj_17::model_index_to_index[332]]
		;

	out << "sum(A) = " << sumProdA << ", threshold: " << CfgParam::ASum << std::endl;
	out << "sum(B) = " << sumProdB << ", threshold: " << CfgParam::BSum << std::endl;
	out << "sum(C) = " << sumProdC << ", threshold: " << CfgParam::CSum << std::endl;

	out << "g1 = " << tpr::subj_17::G1<CfgParam>::apply(xOpt) << std::endl;
	out << "g2 = " << tpr::subj_17::G2<CfgParam>::apply(xOpt) << std::endl;
	out << "g3 = " << tpr::subj_17::G3<CfgParam>::apply(xOpt) << std::endl;
	out << "g4 = " << tpr::subj_17::G4<CfgParam>::apply(xOpt) << std::endl;
	out << "g5 = " << tpr::subj_17::G5<CfgParam>::apply(xOpt) << std::endl;
	out << "g6 = " << tpr::subj_17::G6<CfgParam>::apply( xOpt ) << std::endl;

	out << "g7 = " << tpr::subj_17::G7<CfgParam>::apply(xOpt) << std::endl;
	out << "g8 = " << tpr::subj_17::G8<CfgParam>::apply(xOpt) << std::endl;
	out << "g9 = " << tpr::subj_17::G9<CfgParam>::apply(xOpt) << std::endl;
	out.flush();
}


template<typename CfgParam>
static void test_subj_17_p4(std::string result_name, size_t startx = 24) {
	assert(tpr::subj_17_p4::model_index_to_index.size() == CfgParam::NVariables);
	using PF = tpr::PenaltyFunction<
		tpr::subj_17_p4::Fx,
		size_t,
		tpr::subj_17_p4::G1<CfgParam>,
		tpr::subj_17_p4::G2<CfgParam>,
		tpr::subj_17_p4::G3<CfgParam>,
		tpr::subj_17_p4::G4<CfgParam>,
		tpr::subj_17_p4::G5<CfgParam>,
		tpr::subj_17_p4::G6<CfgParam>,
		tpr::subj_17_p4::G7<CfgParam>,
		tpr::subj_17_p4::G8<CfgParam>,
		tpr::subj_17_p4::G9<CfgParam>,
		tpr::subj_17_p4::G10<CfgParam>
	>;
	typename PF::VectorT x0;

	for (size_t idx = 0; idx < x0.size(); idx++)
		x0[idx] = startx;

	typename PF::VectorT xOpt = PF::evaluate(x0);
	//std::ofstream out("x_opt.txt");
	std::ofstream out(result_name.c_str());

	for (size_t idx = 0; idx < PF::N; idx++) {
		int modelIndex = tpr::subj_17_p4::index_to_model_index_converter[idx];
		out << "x[ " << modelIndex << " ]opt = " << std::round(xOpt[idx]) << " --> " << tpr::subj_17_p4::model_index_to_description_conv[modelIndex] << '\n';
	}

	typename PF::ValueType sumProdA = xOpt[tpr::subj_17_p4::model_index_to_index[111]]
		+ xOpt[tpr::subj_17_p4::model_index_to_index[112]]
		+ xOpt[tpr::subj_17_p4::model_index_to_index[211]]
		+ xOpt[tpr::subj_17_p4::model_index_to_index[212]]
		+ xOpt[tpr::subj_17_p4::model_index_to_index[311]]
		+ xOpt[tpr::subj_17_p4::model_index_to_index[312]]
		;
	typename PF::ValueType sumProdB = xOpt[tpr::subj_17_p4::model_index_to_index[121]]
		+ xOpt[tpr::subj_17_p4::model_index_to_index[122]]
		+ xOpt[tpr::subj_17_p4::model_index_to_index[221]]
		+ xOpt[tpr::subj_17_p4::model_index_to_index[222]]
		+ xOpt[tpr::subj_17_p4::model_index_to_index[321]]
		+ xOpt[tpr::subj_17_p4::model_index_to_index[322]]
		;
	typename PF::ValueType sumProdC = xOpt[tpr::subj_17_p4::model_index_to_index[131]]
		+ xOpt[tpr::subj_17_p4::model_index_to_index[132]]
		+ xOpt[tpr::subj_17_p4::model_index_to_index[231]]
		+ xOpt[tpr::subj_17_p4::model_index_to_index[232]]
		+ xOpt[tpr::subj_17_p4::model_index_to_index[331]]
		+ xOpt[tpr::subj_17_p4::model_index_to_index[332]]
		;

	typename PF::ValueType sumProdD = 
		  xOpt[tpr::subj_17_p4::model_index_to_index[141]]
		+ xOpt[tpr::subj_17_p4::model_index_to_index[142]]
		+ xOpt[tpr::subj_17_p4::model_index_to_index[241]]
		+ xOpt[tpr::subj_17_p4::model_index_to_index[242]]
		+ xOpt[tpr::subj_17_p4::model_index_to_index[341]]
		+ xOpt[tpr::subj_17_p4::model_index_to_index[342]]
		;

	out << "sum(A) = " << sumProdA << std::endl;
	out << "sum(B) = " << sumProdB << std::endl;
	out << "sum(C) = " << sumProdC << std::endl;
	out << "sum(D) = " << sumProdD << std::endl;

	out << "g1 = " << tpr::subj_17_p4::G1<CfgParam>::apply(xOpt) << std::endl;
	out << "g2 = " << tpr::subj_17_p4::G2<CfgParam>::apply(xOpt) << std::endl;
	out << "g3 = " << tpr::subj_17_p4::G3<CfgParam>::apply(xOpt) << std::endl;
	out << "g4 = " << tpr::subj_17_p4::G4<CfgParam>::apply(xOpt) << std::endl;
	out << "g5 = " << tpr::subj_17_p4::G5<CfgParam>::apply(xOpt) << std::endl;
	out << "g6 = " << tpr::subj_17_p4::G6<CfgParam>::apply(xOpt) << std::endl;
	out << "g7 = " << tpr::subj_17_p4::G7<CfgParam>::apply(xOpt) << std::endl;
	out << "g8 = " << tpr::subj_17_p4::G8<CfgParam>::apply(xOpt) << std::endl;
	out << "g9 = " << tpr::subj_17_p4::G9<CfgParam>::apply(xOpt) << std::endl;
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

int main() {
	
	// 1. Try to find optimal solution for given constraints.
	test_subj_17<tpr::subj_17::Config0>("x_opt.txt", 15);
	//// 2. Let all resources were incresed 3 times.
	test_subj_17<tpr::subj_17::Config2ResourceChanged>( "x_opt2.txt" );
	// 3. add 4-th product.
	test_subj_17_p4<tpr::subj_17_p4::Config0>("x_opt_p4.txt",20);
	return 0;
}
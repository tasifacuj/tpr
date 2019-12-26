#include <iostream>
#include <array>
#include <map>
#include <cmath>

#include "GradientDescent.hpp"
#include "PenaltyFunction.hpp"
#include "subj_17.hpp"

/**
  * f(x) = 10 * x1^2 + x2 ^ 2
  * df
  * --- = 20 * x1
  * dx1
  * df/dx2 = 2*x2
  */
template<typename ValueT = float>
class QuadF {
public:// == CONSTANTS ==
	static constexpr size_t N = 2;
public: // == TYPES ==
	using ValueType = ValueT;
	using VectorT = std::array<ValueType, N>;
public: // == METHODS ==
	static ValueType apply( const VectorT& args ) {
		return 10 * args[0] * args[0] + args[1] * args[1];
	}

	static VectorT gradient( const VectorT& args ) {
		// 20 * x1 + 2 * x2
		VectorT tmp;
		tmp[ 0 ] = 20 * args[ 0 ];
		tmp[ 1 ] = 2 * args[ 1 ];
		return tmp;
	}
};

/**
 * f(x) = ( x1 - 6 )^2 + ( x2 - 7 )^2
 * dfdx1 = 2( x1 - 6 )
 * dfdx2 = 2( x2 - 7 )
 */
struct Fx {
	static constexpr size_t N = 2;
	using ValueType = double;
	using VectorT = std::array<ValueType, N>;

	static ValueType apply(const VectorT& args) {
		return (args[0] - 6) * (args[0] - 6) + (args[1] - 7)*(args[1] - 7);
	}

	static VectorT gradient(const VectorT& args) {
		VectorT tmp;
		// dfdx1 = 2( x1 - 6 )
		tmp[0] = 2 * (args[0] - 6);
		// dfdx2 = 2(x2 - 7)
		tmp[1] = 2 * (args[1] - 7);
		return tmp;
	}
};

/**
 * g1(x) = -3x1 - 2x2 + 6 <= 0
 * g1(x) = 3x1 + 2x2 - 6 >= 0
 * dfdx1 = -3
 * dfdx2 = -2
 */
struct G1 {
	static constexpr size_t N = 2;
	using ValueType = double;
	using VectorT = std::array<ValueType, N>;

	static ValueType apply(const VectorT& args) {
		auto vvv = -3.0f * args[0] - 2 * args[1] + 6;
		return -3.0f * args[0] - 2 * args[1] + 6;
		//return 3.0f * args[0] + 2 * args[1] - 6;
	}

	static VectorT gradient(const VectorT&) {
		VectorT tmp;
		tmp[0] = -3.0f;
		tmp[1] = -2.0;
		/*tmp[0] = 3.0f;
		tmp[1] = 2.0;*/
		return tmp;
	}
};

/**
 * g2(x) = -x1 + x2 - 3 <= 0
 * g2(x) = x1 - x2 + 3 >= 0
 * dfdx1 = -1
 * dfdx2 = 1
 */
struct G2 {
	static constexpr size_t N = 2;
	using ValueType = double;
	using VectorT = std::array<ValueType, N>;

	static ValueType apply(const VectorT& args) {
		auto vvv = -1.0f * args[0] + args[1] - 3.0f;
		return  -1.0f * args[0] + args[1] - 3.0f;
		//return  1.0f * args[0] - args[1] + 3.0f;
	}

	static VectorT gradient(const VectorT&) {
		VectorT tmp;
		tmp[0] = -1.0f;
		tmp[1] = 1.0f;
		/*tmp[0] = 1.0f;
		tmp[1] = -1.0f;*/
		return tmp;
	}
};

/**
 * g3(x) = x1 + x2 - 7 <= 0
 * g3(x) = -x1 - x2 + 7 >= 0
 * dfdx1 = 1
 * dfdx2 = 1
 */
struct G3 {
	static constexpr size_t N = 2;
	using ValueType = double;
	using VectorT = std::array<ValueType, N>;

	static ValueType apply(const VectorT& args) {
		auto vvv = 1.0f * args[0] + args[1] - 7;
		return   1.0f * args[0] + args[1] - 7;
		//return   -1.0f * args[0] - args[1] + 7;
	}

	static VectorT gradient(const VectorT&) {
		VectorT tmp;
		tmp[0] = 1.0f;
		tmp[1] = 1.0f;
		/*tmp[0] = -1.0f;
		tmp[1] = -1.0f;*/
		return tmp;
	}
};

/**
 * g4(x) = (2/3)x1 - x2 - 4/3 <= 0
 * g4(x) = -(2/3)x1 + x2 + 4/3 >= 0
 * dfdx1 = 2/3
 * dfdx2 = -1
 */
struct G4 {
	static constexpr size_t N = 2;
	using ValueType = double;
	using VectorT = std::array<ValueType, N>;

	static ValueType apply(const VectorT& args) {
		auto vvv = (2.0f / 3.0f) * args[0] - args[1] - (4.0f / 3.0f);
		return  (2.0f / 3.0f) * args[0] - args[1] - ( 4.0f/3.0f);
	}

	static VectorT gradient(const VectorT&) {
		VectorT tmp;
		tmp[0] = ( 2.0f / 3.0f);
		tmp[1] = -1.0f;
		return tmp;
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// my task
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
	/*using PF = tpr::PenaltyFunction<Fx, size_t, G1, G2, G3, G4> ;
	PF::VectorT x0{ 6.0f, 7.0f };
	PF::VectorT xOpt = PF::evaluate(x0);
*/
	assert(tpr::subj_17::model_index_to_index.size() == 18);
	using PF = tpr::PenaltyFunction<tpr::subj_17::Fx, size_t, tpr::subj_17::G1, tpr::subj_17::G2, tpr::subj_17::G3, tpr::subj_17::G4, tpr::subj_17::G5, tpr::subj_17::G6, tpr::subj_17::G7, tpr::subj_17::G8, tpr::subj_17::G9>;
	PF::VectorT x0;

	for (size_t idx = 0; idx < x0.size(); idx++)
		x0[idx] = 2;

	PF::VectorT xOpt = PF::evaluate(x0);
	return 0;
}
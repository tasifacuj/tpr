#include <iostream>
#include <array>

#include "GradientDescent.hpp"
#include "PenaltyFunction.hpp"

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
namespace subj_17 {
	/**
	 * f(x) = 3x0  + 3x1  + 9x2  + 9x3  + 5x4  + 5x5
	 *      + 3x6  + 3x7  + 6x8  + 6x9 + 8x10 + 8x11
	 *		+ 8x12 + 8x13 + 2x14 + 2x15 + 5x16 + 5x17
	 */
	struct Fx {
		static constexpr size_t N = 18;
		using ValueType = double;
		using VectorT = std::array<ValueType, N>;

		static ValueType apply(const VectorT& args) {
			return 3.0 * args[0]  + 3.0 * args[1]  + 9.0 * args[2] + 9.0 * args[3] + 5.0 * args[4]  + 5.0 * args[5]
				 + 3.0 * args[6]  + 3.0 * args[7]  + 6.0 * args[8] + 6.0 * args[9] + 8.0 * args[10] + 8.0 * args[11]
				 + 8.0 * args[12] + 8.0 * args[13] + 2.0 * args[8] + 2.0 * args[9] + 5.0 * args[10] + 5.0 * args[11]
				;
		}

		static VectorT gradient(const VectorT&) {
			VectorT tmp;
			// first row
			tmp[0] = 3.0f ;
			tmp[1] = 3.0f ;
			tmp[2] = 9.0f ;
			tmp[3] = 9.0f ;
			tmp[4] = 5.0f ;
			tmp[5] = 5.0f ;

			//2-nd row
			tmp[6] = 3.0f ;
			tmp[7] = 3.0f;
			tmp[8] = 6.0f;
			tmp[9] = 6.0f;
			tmp[10] = 8.0f;
			tmp[11] = 8.0f;

			//3-rd row
			tmp[12] = 8.0f;
			tmp[13] = 8.0f;
			tmp[14] = 2.0f;
			tmp[15] = 2.0f;
			tmp[16] = 5.0f;
			tmp[17] = 5.0f;
			return tmp;
		}
	};

	/**
	 * g1(x) = 1.5x111 + 0.75x121 + 2.5*x131 + 1.282* sqrt( 0.083 * x111^2 + 0.0208*x121^2 + 0.083*x131^2 ) - 250 <= 0
	 */
	struct G1 {
		static constexpr size_t N = 18;
		using ValueType = double;
		using VectorT = std::array<ValueType, N>;

		static ValueType apply(const VectorT& args) {
			return 1.5 * args[0] + 0.75 * args[2] + 2.5 * args[4] + 1.282* std::sqrt( 0.083 * args[0] * args[0] + 0.0208 * args[2] * args[2] + 0.083 * args[4] * args[ 4 ] ) - 250.0
				;
		}

		static VectorT gradient(const VectorT& xargs) {
			VectorT tmp;
			tmp[0] = 1.5 + 1.283 * 0.5 * std::pow(0.083 * xargs[0] * xargs[0] + 0.0208 * xargs[2] * xargs[2] + 0.083 * xargs[4] * xargs[4], -0.5) * 2 * 0.083 * xargs[0];
			tmp[1] = -2.0;
			return tmp;
		}
	};
}

int main() {
	using PF = tpr::PenaltyFunction<Fx, size_t, G1, G2, G3, G4> ;
	PF::VectorT x0{ 6.0f, 7.0f };
	PF::VectorT xOpt = PF::evaluate(x0);
	return 0;
}
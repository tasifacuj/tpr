#include <iostream>
#include <array>
#include <map>
#include <cmath>

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
	 * x111 - x0
	 * x112 - x1
	 * x121 - x2
	 * x122 - x3
	 * x131 - x4
	 * x132 - x5
	 * x211 - x6
	 * x212 - x7
	 * x221 - x8
	 * x222 - x9
	 * x231 - x10
	 * x232 - x11
	 * x311 - x12
	 * x312 - x13
	 * x321 - x14
	 * x322 - x15
	 * x331 - x16
	 * x332 - x17
	 */

	static std::map<int, int> model_index_to_index{
		{ 111, 0 },
		{ 112, 1 },
		{ 121, 2 },
		{ 122, 3 },
		{ 131, 4 },
		{ 132, 5 },
		{ 211, 6 },
		{ 212, 7 },
		{ 221, 8 },
		{ 222, 9 },
		{ 231, 10 },
		{ 232, 11 },
		{ 311, 12 },
		{ 312, 13 },
		{ 321, 14 },
		{ 322, 15 },
		{ 331, 16 },
		{ 332, 17 },
	};

	static std::map<int, int> index_to_model_index{
		{ 0, 111 },
		{ 1, 112 },
		{ 2, 121 },
		{ 3, 122 },
		{ 4, 131 },
		{ 5, 132 },
		{ 6, 211 },
		{ 7, 212 },
		{ 8, 221 },
		{ 9, 222 },
		{ 10, 231 },
		{ 11, 232 },
		{ 12, 311 },
		{ 13, 312 },
		{ 14, 321 },
		{ 15, 322 },
		{ 16, 331 },
		{ 17, 332 },
	};

	static constexpr double FLaplassInverse = 1.282;

	template<typename T>
	T sqr(T val) {
		return val * val;
	}

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
				 + 8.0 * args[12] + 8.0 * args[13] + 2.0 * args[14] + 2.0 * args[15] + 5.0 * args[16] + 5.0 * args[17]
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

		// g1(x) = 1.5x111 + 0.75x121 + 2.5*x131 + 1.282* sqrt( 0.083 * x111^2 + 0.0208*x121^2 + 0.083*x131^2 ) - 250 <= 0
		static ValueType apply(const VectorT& args) {
			return 1.5 * args[model_index_to_index[111]] + 0.75 * args[model_index_to_index[121]] + 2.5 * args[model_index_to_index[131]] 
				+ 1.282* std::sqrt( 0.083 * args[model_index_to_index[111]] * args[model_index_to_index[111]] 
					+ 0.0208 * args[model_index_to_index[121]] * args[model_index_to_index[121]] 
					+ 0.083 * args[model_index_to_index[131]] * args[model_index_to_index[131]] 
				) - 250.0
				;
		}

		/**
		 * g1(x) = 1.5x111 + 0.75x121 + 2.5*x131 + 1.282* sqrt( 0.083 * x111^2 + 0.0208*x121^2 + 0.083*x131^2 ) - 250 <= 0
		 * v[0]: dg1/dx111 = (1.5 + 1.282 * 0.5 * ( 0.083x111^2 + 0.0208x121^2 + 0.083x131^2 )^(-0.5)) * 2 * 0.083x111
		 * v[2]: dg1/dx121 = (0.75 + 1.282 * 0.5 * ( 0.083x111^2 + 0.0208x121^2 + 0.083x131^2 )^(-0.5)) * 2 * 0.0208x121
		 * v[4]: dg1/dx131 = (2.5 + 1.282 * 0.5 * ( 0.083x111^2 + 0.0208x121^2 + 0.083x131^2 )^(-0.5)) * 2 * 0.083x131
		 */
		static VectorT gradient(const VectorT& xargs) {
			VectorT tmp;
			memset(&tmp[0], 0, sizeof(ValueType) * N);
			//x111
			tmp[0] = (1.5 + FLaplassInverse * 0.5 
				* std::pow(
					(0.083 * sqr(xargs[model_index_to_index[111]]) + 0.0208 * sqr(xargs[model_index_to_index[121]]) + 0.083 * sqr(xargs[model_index_to_index[131]])), 
					-0.5)
				) 
				* 2 * 0.083 * xargs[ model_index_to_index[111] ];
			// 121
			tmp[2] = (0.75 + FLaplassInverse * 0.5
				* std::pow(
				(0.083 * sqr(xargs[model_index_to_index[111]]) + 0.0208 * sqr(xargs[model_index_to_index[121]]) + 0.083 * sqr(xargs[model_index_to_index[131]])),
					-0.5)
				)
				* 2 * 0.0208 * xargs[model_index_to_index[121]];

			// 131
			tmp[4] = (2.5 + FLaplassInverse * 0.5
				* std::pow(
				(0.083 * sqr(xargs[model_index_to_index[111]]) + 0.0208 * sqr(xargs[model_index_to_index[121]]) + 0.083 * sqr(xargs[model_index_to_index[131]])),
					-0.5)
				)
				* 2 * 0.083 * xargs[model_index_to_index[131]];
			return tmp;
		}
	};

	/**
	 * g1(x) = 3x112 + 3x122 + 3.0*x132 + 1.282* sqrt( 0.33 * x112^2 + 0.033*x122^2 + 0.33*x132^2 ) - 150 <= 0
	 */
	struct G2 {
		static constexpr size_t N = 18;
		using ValueType = double;
		using VectorT = std::array<ValueType, N>;

		// g2(x) = 3x112 + 3x122 + 3.0*x132 + 1.282* sqrt( 0.33 * x112^2 + 0.033*x122^2 + 0.33*x132^2 ) - 150 <= 0
		static ValueType apply(const VectorT& xargs) {
			return 3.0 * xargs[model_index_to_index[112]] + 3.0 * xargs[model_index_to_index[122]] + 3.0 * xargs[model_index_to_index[132]]
				+ FLaplassInverse * std::sqrt(
					0.33 * sqr(xargs[model_index_to_index[112]]) + 0.33 * sqr(xargs[model_index_to_index[122]]) + 0.33 * sqr(xargs[model_index_to_index[132]])
				) - 150.0
				;
		}

		/**
		 * g2(x) = 3x112 + 3x122 + 3.0*x132 + 1.282* sqrt( 0.33 * x112^2 + 0.033*x122^2 + 0.33*x132^2 ) - 150 <= 0
		 * v[1]: dg1/dx112 = (3.0 + 1.282 * 0.5 * ( 0.33 * x112^2 + 0.33*x122^2 + 0.33*x132^2 )^(-0.5)) * 2 * 0.33x112
		 * v[3]: dg1/dx122 = (3.0 + 1.282 * 0.5 * ( 0.33 * x112^2 + 0.33*x122^2 + 0.33*x132^2 )^(-0.5)) * 2 * 0.33x122
		 * v[5]: dg1/dx132 = (3.0 + 1.282 * 0.5 * ( 0.33 * x112^2 + 0.33*x122^2 + 0.33*x132^2 )^(-0.5)) * 2 * 0.33x132
		 */
		static VectorT gradient(const VectorT& xargs) {
			VectorT tmp;
			memset(&tmp[0], 0, sizeof(ValueType) * N);
			//x112
			tmp[1] = (3.0 + FLaplassInverse * 0.5
				* std::pow(
					( 0.33 * sqr( xargs[ model_index_to_index[112] ] ) + 0.33 * sqr( xargs[ model_index_to_index[122] ] ) + 0.33 * sqr( xargs[ model_index_to_index[132] ] ) ),
					-0.5
					) 
				)
				* 2 * 0.33 * xargs[model_index_to_index[112]];
			// 122
			tmp[3] = (3.0 + FLaplassInverse * 0.5
				* std::pow(
					(0.33 * sqr(xargs[model_index_to_index[112]]) + 0.33 * sqr(xargs[model_index_to_index[122]]) + 0.33 * sqr(xargs[model_index_to_index[132]])),
					-0.5
					)
				)
				* 2 * 0.33 * xargs[model_index_to_index[122]];

			// 132
			tmp[5] = (2.5 + FLaplassInverse * 0.5
				* std::pow(
					(0.33 * sqr(xargs[model_index_to_index[112]]) + 0.33 * sqr(xargs[model_index_to_index[122]]) + 0.33 * sqr(xargs[model_index_to_index[132]])),
					-0.5
					)
				)
				* 2 * 0.33 * xargs[model_index_to_index[132]];
			return tmp;
		}
	};

	/**
	 * g3(x) = 2.0x211 + 1.25x221 + 4.0*x231 + 1.282* sqrt( 0.33 * x211^2 + 0.0208*x221^2 + 0.33*x231^2 ) - 100 <= 0
	 */
	struct G3 {
		static constexpr size_t N = 18;
		using ValueType = double;
		using VectorT = std::array<ValueType, N>;

		// g3(x) = 2.0x211 + 1.25x221 + 4.0*x231 + 1.282* sqrt( 0.33 * x211^2 + 0.0208*x221^2 + 0.33*x231^2 ) - 100 <= 0
		static ValueType apply(const VectorT& args) {
			return 2.0 * args[model_index_to_index[211]] + 1.25 * args[model_index_to_index[221]] + 4.0 * args[model_index_to_index[231]]
				+ FLaplassInverse * std::sqrt(
					0.33 * sqr(args[model_index_to_index[211]])
					+ 0.0208 * sqr(args[model_index_to_index[221]])
					+ 0.33 * sqr(args[model_index_to_index[231]])
				) - 100.0;
		}

		/**
		 * g3(x) = 2.0x211 + 1.25x221 + 4.0*x231 + 1.282* sqrt( 0.33 * x211^2 + 0.0208*x221^2 + 0.33 * x231^2 ) - 100 <= 0
		 * v[6]:  dg3/dx211 = 2 + 1.282*0.5*( 0.33x211^2 + 0.0208x221^2 + 0.33x231^2 )^ (-0.5) * 2 * 0.33x211
		 * v[8]:  dg3/dx221 = 1.25 + 1.282*0.5*( 0.33x211^2 + 0.0208x221^2 + 0.33x231^2 )^ (-0.5) * 2 * 0.0208x221
		 * v[10]: dg3/dx231 = 4 + 1.282*0.5*( 0.33x211^2 + 0.0208x221^2 + 0.33x231^2 )^ (-0.5) * 2 * 0.33x231
		 */
		static VectorT gradient(const VectorT& xargs) {
			VectorT tmp;
			memset(&tmp[0], 0, sizeof(ValueType) * N);
			//x211
			tmp[6] = (2.0 + FLaplassInverse * 0.5
				* std::pow(
					(0.33 * sqr( xargs[ model_index_to_index[211] ] ) + 0.0208 * sqr( xargs[ model_index_to_index[221] ] ) + 0.33 * sqr( xargs[ model_index_to_index[231] ] )),
					-0.5
					)
				)
				* 2 * 0.33 * xargs[model_index_to_index[211]];
			// 221
			tmp[8] = (1.25 + FLaplassInverse * 0.5
				* std::pow(
					(0.33 * sqr(xargs[model_index_to_index[211]]) + 0.0208 * sqr(xargs[model_index_to_index[221]]) + 0.33 * sqr(xargs[model_index_to_index[231]])),
					-0.5
					)
				)
				* 2 * 0.0208 * xargs[model_index_to_index[221]];

			// 231
			tmp[10] = (4.0 + FLaplassInverse * 0.5
				* std::pow(
					(0.33 * sqr(xargs[model_index_to_index[211]]) + 0.0208 * sqr(xargs[model_index_to_index[221]]) + 0.33 * sqr(xargs[model_index_to_index[231]])),
					-0.5
					)
				)
				* 2 * 0.33 * xargs[model_index_to_index[231]];
			return tmp;

		}
	};

	/**
	 * g4(x) = 5.0x212 + 1.5x222 + 5.0*x232 + 1.282* sqrt( 1.33 * x212^2 + 0.083*x222^2 + 0.33*x232^2 ) - 200 <= 0
	 */
	struct G4 {
		static constexpr size_t N = 18;
		using ValueType = double;
		using VectorT = std::array<ValueType, N>;

		// g4(x) = 5.0x212 + 1.5x222 + 5.0*x232 + 1.282* sqrt( 1.33 * x212^2 + 0.083*x222^2 + 0.33*x232^2 ) - 200 <= 0
		static ValueType apply(const VectorT& args) {
			return 5.0 * args[model_index_to_index[212]] + 1.5 * args[model_index_to_index[222]] + 5.0 * args[model_index_to_index[232]]
				+ FLaplassInverse * std::sqrt(
					1.33 * sqr(args[model_index_to_index[212]])
					+ 0.083 * sqr(args[model_index_to_index[222]])
					+ 0.33 * sqr(args[model_index_to_index[232]])
				) - 200.0;
		}

		/**
		 * g4(x) = 5.0x212 + 1.5x222 + 5.0*x232 + 1.282* sqrt( 1.33 * x212^2 + 0.083*x222^2 + 0.33*x232^2 ) - 200 <= 0
		 * v[7]:  dg3/dx212 = 5 + 1.282 * 0.5 * ( 1.33 * x212^2 + 0.083*x222^2 + 0.33*x232^2 )^( -0.5 ) * 2 * 1.33x212
		 * v[9]:  dg3/dx222 = 1.5 + 1.282 * 0.5 * ( 1.33 * x212^2 + 0.083*x222^2 + 0.33*x232^2 )^( -0.5 ) * 2 * 0.083x222
		 * v[11]: dg3/dx232 = 5 + 1.282 * 0.5 * ( 1.33 * x212^2 + 0.083*x222^2 + 0.33*x232^2 )^( -0.5 ) * 2 * 0.33x232
		 */
		static VectorT gradient(const VectorT& xargs) {
			VectorT grad;
			memset(&grad[0], 0, sizeof(ValueType) * N);
			//x212
			grad[model_index_to_index[ 212 ]] = (5.0 + FLaplassInverse * 0.5
				* std::pow(
					(1.33 * sqr(xargs[model_index_to_index[212]]) + 0.083 * sqr(xargs[model_index_to_index[222]]) + 0.33 * sqr(xargs[model_index_to_index[232]])),
					-0.5
					)
				)
				* 2 * 1.33 * xargs[model_index_to_index[212]];
			// 222
			grad[model_index_to_index[222]] = (1.5 + FLaplassInverse * 0.5
				* std::pow(
					(1.33 * sqr(xargs[model_index_to_index[212]]) + 0.083 * sqr(xargs[model_index_to_index[222]]) + 0.33 * sqr(xargs[model_index_to_index[232]])),
					-0.5
					)
				)
				* 2 * 0.083 * xargs[model_index_to_index[222]];

			// 232
			grad[model_index_to_index[232]] = (5.0 + FLaplassInverse * 0.5
				* std::pow(
					(1.33 * sqr(xargs[model_index_to_index[212]]) + 0.083 * sqr(xargs[model_index_to_index[222]]) + 0.33 * sqr(xargs[model_index_to_index[232]])),
					-0.5
					)
				)
				* 2 * 0.33 * xargs[model_index_to_index[232]];
			return grad;

		}
	};

	/**
	 * g5(x) = 2.5 * x311 + 2.0 * x321 + 2.0 * x331 + 1.282 * sqrt( 0.75 * x311^2 + 0.33*x321^2 + 0.33*x331^2 ) - 240 <= 0
	 */
	struct G5 {
		static constexpr size_t N = 18;
		using ValueType = double;
		using VectorT = std::array<ValueType, N>;

		// g5(x) = 2.5 * x311 + 2.0 * x321 + 2.0 * x331 + 1.282 * sqrt( 0.75 * x311^2 + 0.33*x321^2 + 0.33*x331^2 ) - 240 <= 0
		static ValueType apply(const VectorT& args) {
			return 2.5 * args[model_index_to_index[311]] + 2.0 * args[model_index_to_index[321]] + 2.0 * args[model_index_to_index[331]]
				+ FLaplassInverse * std::sqrt(
					0.75 * sqr(args[model_index_to_index[311]])
					+ 0.33 * sqr(args[model_index_to_index[321]])
					+ 0.33 * sqr(args[model_index_to_index[331]])
				) - 240.0;
		}

		/**
		 * g5(x) = 2.5 * x311 + 2.0 * x321 + 2.0 * x331 + 1.282 * sqrt( 0.75 * x311^2 + 0.33*x321^2 + 0.33*x331^2 ) - 240 <= 0
		 * v[12]:  dg3/dx311 = 2.5 + 1.282 * 0.5 * ( 0.75 * x311^2 + 0.33*x321^2 + 0.33*x331^2 )^-0.5 * 2 * 0.75 * x311
		 * v[14]:  dg3/dx321 = 2.0 + 1.282 * 0.5 * ( 0.75 * x311^2 + 0.33*x321^2 + 0.33*x331^2 )^-0.5 * 2 * 0.33 * x321
		 * v[16]:  dg3/dx331 = 2.0 + 1.282 * 0.5 * ( 0.75 * x311^2 + 0.33*x321^2 + 0.33*x331^2 )^-0.5 * 2 * 0.33 * x331
		 */
		static VectorT gradient(const VectorT& xargs) {
			VectorT grad;
			memset(&grad[0], 0, sizeof(ValueType) * N);
			//x311
			grad[model_index_to_index[311]] = (2.5 + FLaplassInverse * 0.5
				* std::pow(
					(0.75 * sqr(xargs[model_index_to_index[311]]) + 0.33 * sqr(xargs[model_index_to_index[321]]) + 0.33 * sqr(xargs[model_index_to_index[331]])),
					-0.5
					)
				)
				* 2 * 0.75 * xargs[model_index_to_index[311]];
			// 321
			grad[model_index_to_index[321]] = (2.0 + FLaplassInverse * 0.5
				* std::pow(
					(0.75 * sqr(xargs[model_index_to_index[311]]) + 0.33 * sqr(xargs[model_index_to_index[321]]) + 0.33 * sqr(xargs[model_index_to_index[331]])),
					-0.5
					)
				)
				* 2 * 0.33 * xargs[model_index_to_index[321]];

			// 331
			grad[model_index_to_index[331]] = (2.0 + FLaplassInverse * 0.5
				* std::pow(
					(0.75 * sqr(xargs[model_index_to_index[311]]) + 0.33 * sqr(xargs[model_index_to_index[321]]) + 0.33 * sqr(xargs[model_index_to_index[331]])),
					-0.5
					)
				)
				* 2 * 0.33 * xargs[model_index_to_index[331]];
			return grad;

		}
	};



}// namespace subj_17

int main() {
	assert(subj_17::model_index_to_index.size() == 18);
	using PF = tpr::PenaltyFunction<Fx, size_t, G1, G2, G3, G4> ;
	PF::VectorT x0{ 6.0f, 7.0f };
	PF::VectorT xOpt = PF::evaluate(x0);
	return 0;
}
#pragma once
#include <array>
namespace tpr {
	namespace simplified {
		template<typename T>
		T sqr(T val) {
			return val * val;
		}

		struct  Cfg{
			static constexpr double Resource = 350.0;
			static constexpr int Q1 = 90;
			static constexpr int Q2 = 70;
			static constexpr int Q3 = 70;
		};

		struct Fx {
			static constexpr size_t N = 3;
			using ValueType = double;
			using VectorT = std::array<ValueType, N>;

			static ValueType apply(const VectorT& args) {
				return 3 * args[ 0 ] + 9 * args[ 1 ] + 5 * args[ 2 ];
			}

			static VectorT gradient(const VectorT&) {
				return { 3, 9, 5 };
			}
		};

		struct G1 {
			static constexpr size_t N = 3;
			using ValueType = double;
			using VectorT = std::array<ValueType, N>;

			// g1(x) = 1.5x111 + 0.75x121 + 2.5*x131 + 1.282* sqrt( 0.083 * x111^2 + 0.0208*x121^2 + 0.083*x131^2 ) - 250 <= 0
			static ValueType apply(const VectorT& args) {
				/*auto fff = 1.5 * args[0] + 0.75 * args[1] + 2.5 * args[2]
					+ 1.282 * std::sqrt(0.083 * sqr(args[0])
						+ 0.0208 * sqr(args[1])
						+ 0.083 * sqr(args[2])
					) - 250;

				return 1.5 * args[ 0 ] + 0.75 * args[ 1 ] + 2.5 * args[ 2 ]
					+ 1.282 * std::sqrt(0.083 * sqr(args[0])
						+ 0.0208 * sqr(args[ 1 ])
						+ 0.083 * sqr(args[ 2 ])
					) - 250
					;*/

				auto fff = 1.5 * args[0] + 0.75 * args[1] + 2.5 * args[2] - Cfg::Resource;
				return 1.5 * args[0] + 0.75 * args[1] + 2.5 * args[2] - Cfg::Resource;
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
				// v[0]: dg1/dx111 = (1.5 + 1.282 * 0.5 * ( 0.083x111^2 + 0.0208x121^2 + 0.083x131^2 )^(-0.5)) * 2 * 0.083x111
				//tmp[0] = (1.5 + 1.282 * 0.5
				//	* std::pow(
				//		(0.083 * sqr(xargs[0]) + 0.0208 * sqr(xargs[1]) + 0.083 * sqr(xargs[2])),
				//		-0.5)
				//	)
				//	* 2 * 0.083 * xargs[0];
				//// 121
				//// v[2]: dg1/dx121 = (0.75 + 1.282 * 0.5 * ( 0.083x111^2 + 0.0208x121^2 + 0.083x131^2 )^(-0.5)) * 2 * 0.0208x121
				//tmp[1] = (0.75 + 1.282 * 0.5
				//	* std::pow(
				//		(0.083 * sqr(xargs[0]) + 0.0208 * sqr(xargs[1]) + 0.083 * sqr(xargs[2])),
				//		-0.5)
				//	)
				//	* 2 * 0.0208 * xargs[1];

				//// 131
				//// v[4]: dg1 / dx131 = (2.5 + 1.282 * 0.5 * (0.083x111 ^ 2 + 0.0208x121 ^ 2 + 0.083x131 ^ 2) ^ (-0.5)) * 2 * 0.083x131
				//tmp[2] = (2.5 + 1.282 * 0.5
				//	* std::pow(
				//	(0.083 * sqr(xargs[0]) + 0.0208 * sqr(xargs[1]) + 0.083 * sqr(xargs[2])),
				//		-0.5)
				//	)
				//	* 2 * 0.083 * xargs[2];


				tmp[0] = 1.5;
				// 121
				// v[2]: dg1/dx121 = (0.75 + 1.282 * 0.5 * ( 0.083x111^2 + 0.0208x121^2 + 0.083x131^2 )^(-0.5)) * 2 * 0.0208x121
				tmp[1] = 0.75;

				// 131
				// v[4]: dg1 / dx131 = (2.5 + 1.282 * 0.5 * (0.083x111 ^ 2 + 0.0208x121 ^ 2 + 0.083x131 ^ 2) ^ (-0.5)) * 2 * 0.083x131
				tmp[2] = 2.5;
				return tmp;
			}
		};

		struct G2 {
			static constexpr size_t N = 3;
			using ValueType = double;
			using VectorT = std::array<ValueType, N>;

			// g1(x) = 1.5x111 + 0.75x121 + 2.5*x131 + 1.282* sqrt( 0.083 * x111^2 + 0.0208*x121^2 + 0.083*x131^2 ) - 250 <= 0
			static ValueType apply(const VectorT& args) {
				auto fff = Cfg::Q1 - args[0];
				return Cfg::Q1 - args[0];
			}

			static VectorT gradient(const VectorT& ) {
				return { -1.0, 0.0, 0.0 };
			}
		};

		struct G3 {
			static constexpr size_t N = 3;
			using ValueType = double;
			using VectorT = std::array<ValueType, N>;

			// g1(x) = 1.5x111 + 0.75x121 + 2.5*x131 + 1.282* sqrt( 0.083 * x111^2 + 0.0208*x121^2 + 0.083*x131^2 ) - 250 <= 0
			static ValueType apply(const VectorT& args) {
				auto fff = Cfg::Q2 - args[1];
				return Cfg::Q2 - args[1];
			}

			static VectorT gradient(const VectorT& ) {
				return { 0.0, -1.0, 0.0 };
			}
		};

		struct G4 {
			static constexpr size_t N = 3;
			using ValueType = double;
			using VectorT = std::array<ValueType, N>;

			// g1(x) = 1.5x111 + 0.75x121 + 2.5*x131 + 1.282* sqrt( 0.083 * x111^2 + 0.0208*x121^2 + 0.083*x131^2 ) - 250 <= 0
			static ValueType apply(const VectorT& args) {
				auto fff = Cfg::Q3 - args[2];
				return Cfg::Q3 - args[2];
			}

			static VectorT gradient(const VectorT& ) {
				return { 0.0, 0.0, -1.0 };
			}
		};
	}
}

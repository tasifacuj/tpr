#pragma once
#include <map>
#include <array>
#include <cmath>
#include <string>

namespace tpr {
	namespace subj_17_simplified {
		static std::map<int, int> model_index_to_index{
			{ 11, 0 },
			{ 12, 1 },
			{ 13, 2 },
			{ 21, 3 },
			{ 22, 4 },
			{ 23, 5 },
			{ 31, 6 },
			{ 32, 7 },
			{ 33, 8 }
		};

		static std::map<int, std::string> model_index_to_description_conv{
			{ 11, "factory 1, product A" },
			{ 12, "factory 1, product B" },
			{ 13, "factory 1, product C" },
			{ 21, "factory 2, product A" },
			{ 22, "factory 2, product B" },
			{ 23, "factory 2, product C" },
			{ 31, "factory 3, product A" },
			{ 32, "factory 3, product B" },
			{ 33, "factory 3, product C" }
		};

		static std::map<int, int> index_to_model_index_converter{
			{ 0, 11 },
			{ 1, 12 },
			{ 2, 13 },
			{ 3, 21 },
			{ 4, 22 },
			{ 5, 23 },
			{ 6, 31 },
			{ 7, 32 },
			{ 8, 33 }
		};

		template<typename T>
		T sqr(T val) {
			return val * val;
		}

		class Config {
		public:
			static constexpr double FLaplassInverse = 1.282;
			
			/*static constexpr int Resource11 = 300;
			static constexpr int Resource12 = 320;
			static constexpr int Resource21 = 100 * 3;
			static constexpr int Resource22 = 310 ;
			static constexpr int Resource31 = 240 * 2;
			static constexpr int Resource32 = 300 * 3;

			static constexpr int ASum = 300 / 3.2;
			static constexpr int BSum = 100;
			static constexpr int CSum = 30;*/

			static constexpr int Resource11 = 250 * 8;			// R1
			static constexpr int Resource12 = 150 * 8;		// R2
			static constexpr int Resource21 = 100 * 8;		// R3
			static constexpr int Resource22 = 200 * 8;		// R4
			static constexpr int Resource31 = 240 * 8.0;	// R5
			static constexpr float Resource32 = 300 * 8 ;	// R6

			static constexpr int ASum = 300;				
			static constexpr int BSum = 170;
			static constexpr int CSum = 250;
		};


		/**
		 * f(x) = 3 * x_11 + 9 * x_12 + 5 * x_13 + 3 * x_21 + 6 * x_22 + 8 * x_23 + 8 * x_31 + 2 * x_32 + 5 * x_33
		 */
		struct Fx {
			static constexpr size_t N = 9;
			using ValueType = double;
			using VectorT = std::array<ValueType, N>;

			static ValueType apply(const VectorT& args) {
				return 3 * args[model_index_to_index[11]] + 9 * args[model_index_to_index[12]] + 5 * args[model_index_to_index[13]]
					+ 3 * args[model_index_to_index[21]] + 6 * args[model_index_to_index[22]] + 8 * args[model_index_to_index[23]]
					+ 8 * args[model_index_to_index[31]] + 2 * args[model_index_to_index[32]] + 5 * args[model_index_to_index[33]];
			}

			static VectorT gradient(const VectorT&) {
				return { 3, 9, 5, 3, 6, 8, 8, 2, 5 };
			}
		};

		struct G1 {
			static constexpr size_t N = 9;
			using ValueType = double;
			using VectorT = std::array<ValueType, N>;

			// g1(x) = 1.5 * x_11 + 0.75 * x_12 + 2.5 * x_13 + 1.282 * sqrt( 0.083 * x_11^2 + 0.0208 * x_12^2 + 0.083 * x_13^2 ) - 250 <= 0
			static ValueType apply(const VectorT& args) {
				return 0.75 * args[ model_index_to_index[ 11 ] ] + 0.25 * args[model_index_to_index[12]] + 2.5 * args[model_index_to_index[13]]
					+ Config::FLaplassInverse * std::sqrt( 0.083 * sqr( args[model_index_to_index[11]]) + 0.0208 * sqr(args[model_index_to_index[12]]) + 0.083 * sqr(args[model_index_to_index[13]])) 
					- Config::Resource11
					;
			}

			/**
			 * g1(x) = 1.5 * x_11 + 0.75 * x_12 + 2.5 * x_13 + 1.282 * sqrt( 0.083 * x_11^2 + 0.0208 * x_12^2 + 0.083 * x_13^2 ) - 250 <= 0
			 * dg1/dx11 = (1.5 + 1.282 * 0.5 * ( 0.083x11^2 + 0.0208x12^2 + 0.083x13^2 )^(-0.5)) * 2 * 0.083x11
			 * dg1/dx12 = (0.75 + 1.282 * 0.5 * ( 0.083x11^2 + 0.0208x12^2 + 0.083x13^2 )^(-0.5)) * 2 * 0.0208x12
			 * dg1/dx13 = (2.5 + 1.282 * 0.5 * ( 0.083x11^2 + 0.0208x12^2 + 0.083x13^2 )^(-0.5)) * 2 * 0.083x13
			 */
			static VectorT gradient(const VectorT& xargs) {
				VectorT grad;
				memset(&grad[0], 0, sizeof(ValueType) * N);
				//x11
				// dg1/dx11 = (1.5 + 1.282 * 0.5 * ( 0.083x11^2 + 0.0208x12^2 + 0.083x13^2 )^(-0.5)) * 2 * 0.083x11
				grad[model_index_to_index[11]] = (0.25 + Config::FLaplassInverse * 0.5
					* std::pow(
						(0.083 * sqr(xargs[ model_index_to_index[11] ]) + 0.0208 * sqr(xargs[model_index_to_index[12]]) + 0.083 * sqr(xargs[model_index_to_index[13]])),
						-0.5)
					)
					* 2 * 0.083 * xargs[model_index_to_index[11]];
				// 12
				// dg1/dx12 = (0.75 + 1.282 * 0.5 * ( 0.083x11^2 + 0.0208x12^2 + 0.083x13^2 )^(-0.5)) * 2 * 0.0208x12
				grad[model_index_to_index[12]] = (0.75 + Config::FLaplassInverse * 0.5
					* std::pow(
						(0.083 * sqr(xargs[model_index_to_index[11]]) + 0.0208 * sqr(xargs[model_index_to_index[12]]) + 0.083 * sqr(xargs[model_index_to_index[13]])),
						-0.5)
					)
					* 2 * 0.0208 * xargs[model_index_to_index[12]];

				// 13
				// dg1/dx13 = (2.5 + 1.282 * 0.5 * ( 0.083x11^2 + 0.0208x12^2 + 0.083x13^2 )^(-0.5)) * 2 * 0.083x13
				grad[model_index_to_index[13]] = (2.5 + Config::FLaplassInverse * 0.5
					* std::pow(
					(0.083 * sqr(xargs[model_index_to_index[11]]) + 0.0208 * sqr(xargs[model_index_to_index[12]]) + 0.083 * sqr(xargs[model_index_to_index[13]])),
						-0.5)
					)
					* 2 * 0.083 * xargs[model_index_to_index[13]];

				return grad;
			}
		};

		/**
		 * g2(x) = 3 * x_11 + 3 * x_12 + 3 * x_13 + 1.282 * sqrt( 0.33 * x_11^2 + 0.33 * x_12^2 + 33 * x_13^2 ) - 150 <= 0
		 */
		struct G2 {
			static constexpr size_t N = 9;
			using ValueType = double;
			using VectorT = std::array<ValueType, N>;

			// g2(x) = 3 * x_11 + 3 * x_12 + 3 * x_13 + 1.282 * sqrt( 0.33 * x_11^2 + 0.33 * x_12^2 + 0.33 * x_13^2 ) - 150 <= 0
			static ValueType apply(const VectorT& args) {
				return 2 * args[model_index_to_index[11]] + 3 * args[model_index_to_index[12]] + 3 * args[model_index_to_index[13]]
					+ Config::FLaplassInverse * std::sqrt(0.0208 * sqr(args[model_index_to_index[11]]) + 0.0208 * sqr(args[model_index_to_index[12]]) + 0.33 * sqr(args[model_index_to_index[13]]))
					- Config::Resource12
					;
			}

			static VectorT gradient(const VectorT& xargs) {
				VectorT grad;
				memset(&grad[0], 0, sizeof(ValueType) * N);

				//x11
				// dg2/dx11 = (3 + 1.282 * 0.5 * ( 0.33x11^2 + 0.33x12^2 + 0.33x13^2 )^(-0.5)) * 2 * 0.33x11
				grad[model_index_to_index[11]] = (2 + Config::FLaplassInverse * 0.5
					* std::pow(
					(0.0208 * sqr(xargs[model_index_to_index[11]]) + 0.0208 * sqr(xargs[model_index_to_index[12]]) + 0.33 * sqr(xargs[model_index_to_index[13]])),
						-0.5)
					)
					* 2 * 0.0208 * xargs[model_index_to_index[11]];

				// x12
				// dg2/dx12 = (3 + 1.282 * 0.5 * ( 0.33x11^2 + 0.33x12^2 + 0.33x13^2 )^(-0.5)) * 2 * 0.33x11
				grad[model_index_to_index[12]] = (3 + Config::FLaplassInverse * 0.5
					* std::pow(
					(0.0208 * sqr(xargs[model_index_to_index[11]]) + 0.0208 * sqr(xargs[model_index_to_index[12]]) + 0.33 * sqr(xargs[model_index_to_index[13]])),
						-0.5)
					)
					* 2 * 0.0208 * xargs[model_index_to_index[12]];

				// x13
				// dg2/dx13 = (3 + 1.282 * 0.5 * ( 0.33x11^2 + 0.33x12^2 + 0.33x13^2 )^(-0.5)) * 2 * 0.33x11
				grad[model_index_to_index[13]] = (3 + Config::FLaplassInverse * 0.5
					* std::pow(
					(0.0208 * sqr(xargs[model_index_to_index[11]]) + 0.0208 * sqr(xargs[model_index_to_index[12]]) + 0.33 * sqr(xargs[model_index_to_index[13]])),
						-0.5)
					)
					* 2 * 0.33 * xargs[model_index_to_index[13]];
				return grad;
			}
		};

		/**
		 * g3(x) = 2 * x_21 + 1.25 * x_22 + 4 * x_23 + 1.282 * sqrt( 0.33 * x_21^2 + 0.0208 * x_22^2 + 0.33 * x_23^2 ) - 100 <= 0
		 */
		struct G3 {
			static constexpr size_t N = 9;
			using ValueType = double;
			using VectorT = std::array<ValueType, N>;

			// g3(x) = 2 * x_21 + 1.25 * x_22 + 4 * x_23 + 1.282 * sqrt( 0.33 * x_21^2 + 0.0208 * x_22^2 + 0.33 * x_23^2 ) - 100 <= 0
			static ValueType apply(const VectorT& args) {
				return 2.0 * args[model_index_to_index[21]] + 1.25 * args[model_index_to_index[22]] + 4.0 * args[model_index_to_index[23]]
					+ Config::FLaplassInverse * std::sqrt(0.33 * sqr(args[model_index_to_index[21]]) + 0.0208 * sqr( args[model_index_to_index[22]] ) + 0.33 * sqr(args[model_index_to_index[23]]))
					- Config::Resource21
					;
			}

			static VectorT gradient(const VectorT& xargs ) {
				VectorT grad;
				memset(&grad[0], 0, sizeof(ValueType) * N);

				//x21
				// dg3/dx21 = (2.0 + 1.282 * 0.5 * ( 0.33 * x_21^2 + 0.0208 * x_22^2 + 0.33 * x_23^2 ) * 2 * 0.33x21
				grad[model_index_to_index[21]] = (2.0 + Config::FLaplassInverse * 0.5
					* std::pow(
						(0.33 * sqr(xargs[model_index_to_index[21]]) + 0.0208 * sqr(xargs[model_index_to_index[22]]) + 0.33 * sqr(xargs[model_index_to_index[23]])),
						-0.5)
					)
					* 2 * 0.33 * xargs[model_index_to_index[21]];

				// x22
				// dg3/dx22 = (1.25 + 1.282 * 0.5 * ( 0.33 * x_21^2 + 0.0208 * x_22^2 + 0.33 * x_23^2 )^(-0.5)) * 2 * 0.0208x22
				grad[model_index_to_index[22]] = (1.25 + Config::FLaplassInverse * 0.5
					* std::pow(
						(0.33 * sqr(xargs[model_index_to_index[21]]) + 0.0208 * sqr(xargs[model_index_to_index[22]]) + 0.33 * sqr(xargs[model_index_to_index[23]])),
						-0.5)
					)
					* 2 * 0.0208 * xargs[model_index_to_index[22]];

				// x23
				// dg3/dx23 = (4 + 1.282 * 0.5 *  ( 0.33 * x_21^2 + 0.0208 * x_22^2 + 0.33 * x_23^2 )^(-0.5)) * 2 * 0.33x23
				grad[model_index_to_index[23]] = (4 + Config::FLaplassInverse * 0.5
					* std::pow(
						(0.33 * sqr(xargs[model_index_to_index[21]]) + 0.0208 * sqr(xargs[model_index_to_index[22]]) + 0.33 * sqr(xargs[model_index_to_index[23]])),
						-0.5)
					)
					* 2 * 0.33 * xargs[model_index_to_index[23]];
				return grad;
			}
		};


		/**
		 * g4(x) = 5 * x_21 + 1.5 * x_22 + 5 * x_23 + 1.282 * sqrt( 1.33 * x_21^2 + 0.083 * x_22^2 + 0.33 * x_23^2 ) - 200 <= 0
		 */
		struct G4 {
			static constexpr size_t N = 9;
			using ValueType = double;
			using VectorT = std::array<ValueType, N>;

			// g4(x) = 5 * x_21 + 1.5 * x_22 + 5 * x_23 + 1.282 * sqrt( 1.33 * x_21^2 + 0.083 * x_22^2 + 0.33 * x_23^2 ) - 200 <= 0
			static ValueType apply(const VectorT& args) {
				return 1.5 * args[model_index_to_index[21]] + 1.5 * args[model_index_to_index[22]] + 1.5 * args[model_index_to_index[23]]
					+ Config::FLaplassInverse * std::sqrt( 1.33 * sqr( args[model_index_to_index[21]]) + 0.083 * sqr( args[ model_index_to_index[ 22 ] ] ) + 0.33 * sqr(args[model_index_to_index[23]]) )
					- Config::Resource22
					;
			}

			static VectorT gradient(const VectorT& xargs ) {
				VectorT grad;
				memset(&grad[0], 0, sizeof(ValueType) * N);

				//x21
				// dg4/dx21 = (5.0 + 1.282 * 0.5 * ( 1.33 * x_21^2 + 0.083 * x_22^2 + 0.33 * x_23^2 ) * 2 * 1.33x21
				grad[model_index_to_index[21]] = (1.5 + Config::FLaplassInverse * 0.5
					* std::pow(
						(1.33 * sqr(xargs[model_index_to_index[21]]) + 0.083 * sqr(xargs[model_index_to_index[22]]) + 0.33 * sqr(xargs[model_index_to_index[23]])),
						-0.5)
					)
					* 2 * 1.33 * xargs[model_index_to_index[21]];

				// x22
				// dg4/dx22 = (1.5 + 1.282 * 0.5 * ( 1.33 * x_21^2 + 0.083 * x_22^2 + 0.33 * x_23^2 )^(-0.5)) * 2 * 0.083x22
				grad[model_index_to_index[22]] = (1.5 + Config::FLaplassInverse * 0.5
					* std::pow(
						(1.33 * sqr(xargs[model_index_to_index[21]]) + 0.083 * sqr(xargs[model_index_to_index[22]]) + 0.33 * sqr(xargs[model_index_to_index[23]])), 
						-0.5)
					)
					* 2 * 0.083 * xargs[model_index_to_index[22]];

				// x23
				// dg4/dx23 = (5 + 1.282 * 0.5 *  ( 1.33 * x_21^2 + 0.083 * x_22^2 + 0.33 * x_23^2 )^(-0.5) * 2 * 0.33x23
				grad[model_index_to_index[23]] = (1.5 + Config::FLaplassInverse * 0.5
					* std::pow(
					(1.33 * sqr(xargs[model_index_to_index[21]]) + 0.083 * sqr(xargs[model_index_to_index[22]]) + 0.33 * sqr(xargs[model_index_to_index[23]])),
						-0.5)
					)
					* 2 * 0.33 * xargs[model_index_to_index[23]];
				return grad;
			}
		};


		/**
		 * g5(x) = 2.5 * x_31 + 2 * x_32 + 2 * x_33 + 1.282 * sqrt( 0.75 * x_31^2 + 0.33 * x_32^2 + 0.33 * x_33^2 ) - 240 <= 0
		 */
		struct G5 {
			static constexpr size_t N = 9;
			using ValueType = double;
			using VectorT = std::array<ValueType, N>;

			// g5(x) = 2.5 * x_31 + 2 * x_32 + 2 * x_33 + 1.282 * sqrt( 0.75 * x_31^2 + 0.33 * x_32^2 + 0.33 * x_33^2 ) - 240 <= 0
			static ValueType apply(const VectorT& args) {
				return 1.5 * args[model_index_to_index[31]] + 2 * args[model_index_to_index[32]] + 2 * args[model_index_to_index[33]]
					+ Config::FLaplassInverse * std::sqrt(0.33 * sqr(args[model_index_to_index[31]]) + 0.33 * sqr(args[model_index_to_index[32]]) + 0.33 * sqr(args[model_index_to_index[33]]))
					- Config::Resource31
					;
			}

			static VectorT gradient(const VectorT& xargs) {
				VectorT grad;
				memset(&grad[0], 0, sizeof(ValueType) * N);

				//x31
				// dg5/dx31 = (2.5 + 1.282 * 0.5 * ( 0.75 * x_31^2 + 0.33 * x_32^2 + 0.33 * x_33^2 )^(-0.5) * 2 * 0.75 * x_31
				grad[model_index_to_index[31]] = (1.5 + Config::FLaplassInverse * 0.5
					* std::pow(
						(0.33 * sqr(xargs[model_index_to_index[31]]) + 0.33 * sqr(xargs[model_index_to_index[32]]) + 0.33 * sqr(xargs[model_index_to_index[33]])),
						-0.5)
					)
					* 2 * 0.33 * xargs[model_index_to_index[31]];

				// x32
				// dg5/dx32 = (2 + 1.282 * 0.5 * ( 0.75 * x_31^2 + 0.33 * x_32^2 + 0.33 * x_33^2 )^(-0.5)) * 2 * 0.33x32
				grad[model_index_to_index[32]] = (2.0 + Config::FLaplassInverse * 0.5
					* std::pow(
						(0.33 * sqr(xargs[model_index_to_index[31]]) + 0.33 * sqr(xargs[model_index_to_index[32]]) + 0.33 * sqr(xargs[model_index_to_index[33]])),
						-0.5)
					)
					* 2 * 0.33 * xargs[model_index_to_index[32]];

				// x33
				// dg5/dx33 = (2 + 1.282 * 0.5 *  ( 0.75 * x_31^2 + 0.33 * x_32^2 + 0.33 * x_33^2 )^(-0.5) * 2 * 0.33x33
				grad[model_index_to_index[33]] = (2 + Config::FLaplassInverse * 0.5
					* std::pow(
						(0.33 * sqr(xargs[model_index_to_index[31]]) + 0.33 * sqr(xargs[model_index_to_index[32]]) + 0.33 * sqr(xargs[model_index_to_index[33]])),
						-0.5)
					)
					* 2 * 0.33 * xargs[model_index_to_index[33]];

				return grad;
			}
		};

		/**
		 * g6(x) = 4 * x_31 + 4 * x_32 + 7 * x_33 + 1.282 * sqrt( 1.33 * x_31^2 + 0.33 * x_32^2 + 0.33 * x_33^2 ) - 300 <= 0
		 */
		struct G6 {
			static constexpr size_t N = 9;
			using ValueType = double;
			using VectorT = std::array<ValueType, N>;

			// g6(x) = 4 * x_31 + 4 * x_32 + 7 * x_33 + 1.282 * sqrt( 1.33 * x_31^2 + 0.33 * x_32^2 + 0.33 * x_33^2 ) - 300 <= 0
			static ValueType apply(const VectorT& args) {
				return 0.5 * args[model_index_to_index[31]] + 4 * args[model_index_to_index[32]] + 7 * args[model_index_to_index[33]]
					+ Config::FLaplassInverse * std::sqrt(1.33 * sqr(args[model_index_to_index[31]]) + 0.33 * sqr(args[model_index_to_index[32]]) + 0.33 * sqr(args[model_index_to_index[33]]))
					- Config::Resource32
					;
			}

			static VectorT gradient(const VectorT& xargs) {
				VectorT grad;
				memset(&grad[0], 0, sizeof(ValueType) * N);

				//x31
				// dg6/dx31 = (4 + 1.282 * 0.5 * ( 1.33 * x_31^2 + 0.33 * x_32^2 + 0.33 * x_33^2 )^(-0.5) * 2 * 1.33 * x_31
				grad[model_index_to_index[31]] = (0.5 + Config::FLaplassInverse * 0.5
					* std::pow(
						(1.33 * sqr(xargs[model_index_to_index[31]]) + 0.33 * sqr(xargs[model_index_to_index[32]]) + 0.33 * sqr(xargs[model_index_to_index[33]])),
						-0.5)
					)
					* 2 * 1.33 * xargs[model_index_to_index[31]];

				// x32
				// dg6/dx32 = (4 + 1.282 * 0.5 * ( 1.33 * x_31^2 + 0.33 * x_32^2 + 0.33 * x_33^2 )^(-0.5)) * 2 * 0.33x32
				grad[model_index_to_index[32]] = (4.0 + Config::FLaplassInverse * 0.5
					* std::pow(
						(1.33 * sqr(xargs[model_index_to_index[31]]) + 0.33 * sqr(xargs[model_index_to_index[32]]) + 0.33 * sqr(xargs[model_index_to_index[33]])),
						-0.5)
					)
					* 2 * 0.33 * xargs[model_index_to_index[32]];

				// x33
				// dg6/dx33 = (7 + 1.282 * 0.5 *  ( 1.33 * x_31^2 + 0.33 * x_32^2 + 0.33 * x_33^2 )^(-0.5) * 2 * 0.33 * x_33
				grad[model_index_to_index[33]] = (7.0 + Config::FLaplassInverse * 0.5
					* std::pow(
						(0.33 * sqr(xargs[model_index_to_index[31]]) + 0.33 * sqr(xargs[model_index_to_index[32]]) + 0.33 * sqr(xargs[model_index_to_index[33]])),
						-0.5)
					)
					* 2 * 1.33 * xargs[model_index_to_index[33]];

				return grad;
			}
		};

		/**
		 * g7(x) = 300 - x_11 - x_21 - x_31 <= 0
		 */
		struct G7 {
			static constexpr size_t N = 9;
			using ValueType = double;
			using VectorT = std::array<ValueType, N>;

			// g7(x) = 300 - x_11 - x_21 - x_31 <= 0
			static ValueType apply(const VectorT& args) {
				return Config::ASum - args[model_index_to_index[11]] - args[model_index_to_index[21]] - args[model_index_to_index[31]];
			}

			static VectorT gradient(const VectorT& xargs) {
				VectorT grad;
				memset(&grad[0], 0, sizeof(ValueType) * N);

				//x_11
				// dg7/dx11 = -1
				grad[model_index_to_index[11]] = -1.0;

				// x_21
				// dg7/dx21 = -1
				grad[model_index_to_index[21]] = -1.0;

				// x31
				// dg7/dx31 = -1
				grad[model_index_to_index[31]] = -1.0;

				return grad;
			}
		};

		/**
		 * g8(x) = 170 - x_12 - x_22 - x_32 <= 0
		 */
		struct G8 {
			static constexpr size_t N = 9;
			using ValueType = double;
			using VectorT = std::array<ValueType, N>;

			// g8(x) = 170 - x_12 - x_22 - x_32 <= 0
			static ValueType apply(const VectorT& args) {
				return Config::BSum - args[model_index_to_index[12]] - args[model_index_to_index[22]] - args[model_index_to_index[32]];
			}

			static VectorT gradient(const VectorT& xargs) {
				VectorT grad;
				memset(&grad[0], 0, sizeof(ValueType) * N);

				//x_12
				// dg8/dx12 = -1
				grad[model_index_to_index[12]] = -1.0;

				// x_22
				// dg8/dx22 = -1
				grad[model_index_to_index[22]] = -1.0;

				// x32
				// dg8/dx32 = -1
				grad[model_index_to_index[32]] = -1.0;

				return grad;
			}
		};

		/**
		 * g9(x) = 250 - x_13 - x_23 - x_33 <= 0
		 */
		struct G9 {
			static constexpr size_t N = 9;
			using ValueType = double;
			using VectorT = std::array<ValueType, N>;

			// g9(x) = 250 - x_13 - x_23 - x_33 <= 0
			static ValueType apply(const VectorT& args) {
				return Config::CSum - args[model_index_to_index[13]] - args[model_index_to_index[23]] - args[model_index_to_index[33]];
			}

			static VectorT gradient(const VectorT& xargs) {
				VectorT grad;
				memset(&grad[0], 0, sizeof(ValueType) * N);

				//x_13
				// dg9/dx13 = -1
				grad[model_index_to_index[13]] = -1.0;

				// x_23
				// dg9/dx23 = -1
				grad[model_index_to_index[23]] = -1.0;

				// x33
				// dg9/dx33 = -1
				grad[model_index_to_index[33]] = -1.0;

				return grad;
			}
		};
	}
}

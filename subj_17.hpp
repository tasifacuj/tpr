#pragma once
#include <map>
#include <array>
#include <cmath>
#include <string>

namespace tpr {
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

		static std::map<int, int> index_to_model_index_converter{
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

		static std::map<int, std::string> model_index_to_description_conv{
			{ 111, "factory 1, product A, resource 1" },
			{ 112, "factory 1, product A, resource 2" },
			{ 121, "factory 1, product B, resource 1" },
			{ 122, "factory 1, product B, resource 2" },
			{ 131, "factory 1, product C, resource 1" },
			{ 132, "factory 1, product C, resource 2" },
			{ 211, "factory 2, product A, resource 1" },
			{ 212, "factory 2, product A, resource 2" },
			{ 221, "factory 2, product B, resource 1" },
			{ 222, "factory 2, product B, resource 2" },
			{ 231, "factory 2, product C, resource 1" },
			{ 232, "factory 2, product C, resource 2" },
			{ 311, "factory 3, product A, resource 1" },
			{ 312, "factory 3, product A, resource 2" },
			{ 321, "factory 3, product B, resource 1" },
			{ 322, "factory 3, product B, resource 2" },
			{ 331, "factory 3, product C, resource 1" },
			{ 332, "factory 3, product C, resource 2" }
		};

		class Config {
		public:
			static constexpr double FLaplassInverse = 1.282;
			static constexpr int Resource11 = 250;
			static constexpr int Resource12 = 150;
			static constexpr int Resource21 = 100;
			static constexpr int Resource22 = 200;
			static constexpr int Resource31 = 240;
			static constexpr int Resource32 = 300;

			static constexpr int ASum		= 300;
			static constexpr int BSum		= 170;
			static constexpr int CSum		= 250;
		};

		template<typename T>
		T sqr(T val) {
			return val * val;
		}

		/**
		 * f(x) = 3x111  + 3x112  + 9x121  + 9x122  + 5x131  + 5x132
		 *      + 3x211  + 3x212  + 6x221  + 6x222 + 8x231 + 8x232
		 *		+ 8x311 + 8x312 + 2x321 + 2x322 + 5x331 + 5x332
		 */
		struct Fx {
			static constexpr size_t N = 18;
			using ValueType = double;
			using VectorT = std::array<ValueType, N>;

			static ValueType apply(const VectorT& args) {
				return 3.0 * args[ model_index_to_index[111] ] + 3.0 * args[model_index_to_index[112]] + 9.0 * args[model_index_to_index[121]] + 9.0 * args[model_index_to_index[122]] + 5.0 * args[model_index_to_index[131]] + 5.0 * args[model_index_to_index[132]]
					+ 3.0 * args[model_index_to_index[211]] + 3.0 * args[model_index_to_index[212]] + 6.0 * args[model_index_to_index[221]] + 6.0 * args[model_index_to_index[222]] + 8.0 * args[model_index_to_index[231]] + 8.0 * args[model_index_to_index[232]]
					+ 8.0 * args[model_index_to_index[311]] + 8.0 * args[model_index_to_index[312]] + 2.0 * args[model_index_to_index[321]] + 2.0 * args[model_index_to_index[322]] + 5.0 * args[model_index_to_index[331]] + 5.0 * args[model_index_to_index[332]]
					;
			}

			static VectorT gradient(const VectorT&) {
				VectorT tmp;
				// first row
				tmp[model_index_to_index[111]] = 3.0f;
				tmp[model_index_to_index[112]] = 3.0f;
				tmp[model_index_to_index[121]] = 9.0f;
				tmp[model_index_to_index[122]] = 9.0f;
				tmp[model_index_to_index[131]] = 5.0f;
				tmp[model_index_to_index[132]] = 5.0f;

				//2-nd row
				tmp[model_index_to_index[211]] = 3.0f;
				tmp[model_index_to_index[212]] = 3.0f;
				tmp[model_index_to_index[221]] = 6.0f;
				tmp[model_index_to_index[222]] = 6.0f;
				tmp[model_index_to_index[231]] = 8.0f;
				tmp[model_index_to_index[232]] = 8.0f;

				//3-rd row
				tmp[model_index_to_index[311]] = 8.0f;
				tmp[model_index_to_index[312]] = 8.0f;
				tmp[model_index_to_index[321]] = 2.0f;
				tmp[model_index_to_index[322]] = 2.0f;
				tmp[model_index_to_index[331]] = 5.0f;
				tmp[model_index_to_index[332]] = 5.0f;
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
				auto fff = 1.5 * args[model_index_to_index[111]] + 0.75 * args[model_index_to_index[121]] + 2.5 * args[model_index_to_index[131]]
					+ Config::FLaplassInverse * std::sqrt(0.083 * sqr(args[model_index_to_index[111]])
						+ 0.0208 * sqr(args[model_index_to_index[121]])
						+ 0.083 * sqr(args[model_index_to_index[131]])
					) - Config::Resource11;

				return 1.5 * args[model_index_to_index[111]] + 0.75 * args[model_index_to_index[121]] + 2.5 * args[model_index_to_index[131]]
					+ Config::FLaplassInverse * std::sqrt(0.083 * sqr(args[model_index_to_index[111]])
						+ 0.0208 * sqr(args[model_index_to_index[121]])
						+ 0.083 * sqr(args[model_index_to_index[131]])
					) - Config::Resource11
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
				// v[0]: dg1/dx111 = (1.5 + 1.282 * 0.5 * ( 0.083x111^2 + 0.0208x121^2 + 0.083x131^2 )^(-0.5)) * 2 * 0.083x111
				tmp[ model_index_to_index[ 111 ] ] = (1.5 + Config::FLaplassInverse * 0.5
					* std::pow(
						(0.083 * sqr(xargs[model_index_to_index[111]]) + 0.0208 * sqr(xargs[model_index_to_index[121]]) + 0.083 * sqr(xargs[model_index_to_index[131]])),
						-0.5)
					)
					* 2 * 0.083 * xargs[model_index_to_index[111]];
				// 121
				// v[2]: dg1/dx121 = (0.75 + 1.282 * 0.5 * ( 0.083x111^2 + 0.0208x121^2 + 0.083x131^2 )^(-0.5)) * 2 * 0.0208x121
				tmp[ model_index_to_index[ 121 ] ] = (0.75 + Config::FLaplassInverse * 0.5
					* std::pow(
						(0.083 * sqr(xargs[model_index_to_index[111]]) + 0.0208 * sqr(xargs[model_index_to_index[121]]) + 0.083 * sqr(xargs[model_index_to_index[131]])),
						-0.5)
					)
					* 2 * 0.0208 * xargs[model_index_to_index[121]];

				// 131
				// v[4]: dg1 / dx131 = (2.5 + 1.282 * 0.5 * (0.083x111 ^ 2 + 0.0208x121 ^ 2 + 0.083x131 ^ 2) ^ (-0.5)) * 2 * 0.083x131
				tmp[ model_index_to_index[ 131 ] ] = (2.5 + Config::FLaplassInverse * 0.5
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
				auto fff = 3.0 * xargs[model_index_to_index[112]] + 3.0 * xargs[model_index_to_index[122]] + 3.0 * xargs[model_index_to_index[132]]
					+ Config::FLaplassInverse * std::sqrt(
						0.33 * sqr(xargs[model_index_to_index[112]]) + 0.33 * sqr(xargs[model_index_to_index[122]]) + 0.33 * sqr(xargs[model_index_to_index[132]])
					) - Config::Resource12
					;
				return 3.0 * xargs[model_index_to_index[112]] + 3.0 * xargs[model_index_to_index[122]] + 3.0 * xargs[model_index_to_index[132]]
					+ Config::FLaplassInverse * std::sqrt(
						0.33 * sqr(xargs[model_index_to_index[112]]) + 0.33 * sqr(xargs[model_index_to_index[122]]) + 0.33 * sqr(xargs[model_index_to_index[132]])
					) - Config::Resource12
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
				// v[1]: dg1/dx112 = (3.0 + 1.282 * 0.5 * ( 0.33 * x112^2 + 0.33*x122^2 + 0.33*x132^2 )^(-0.5)) * 2 * 0.33x112
				tmp[ model_index_to_index[ 112 ] ] = (3.0 + Config::FLaplassInverse * 0.5
					* std::pow(
					(0.33 * sqr(xargs[model_index_to_index[112]]) + 0.33 * sqr(xargs[model_index_to_index[122]]) + 0.33 * sqr(xargs[model_index_to_index[132]])),
						-0.5
					)
					)
					* 2 * 0.33 * xargs[model_index_to_index[112]];
				// 122
				// v[3]: dg1/dx122 = (3.0 + 1.282 * 0.5 * ( 0.33 * x112^2 + 0.33*x122^2 + 0.33*x132^2 )^(-0.5)) * 2 * 0.33x122
				tmp[ model_index_to_index[ 122 ] ] = (3.0 + Config::FLaplassInverse * 0.5
					* std::pow(
					(0.33 * sqr(xargs[model_index_to_index[112]]) + 0.33 * sqr(xargs[model_index_to_index[122]]) + 0.33 * sqr(xargs[model_index_to_index[132]])),
						-0.5
					)
					)
					* 2 * 0.33 * xargs[model_index_to_index[122]];

				// 132
				// v[5]: dg1/dx132 = (3.0 + 1.282 * 0.5 * ( 0.33 * x112^2 + 0.33*x122^2 + 0.33*x132^2 )^(-0.5)) * 2 * 0.33x132
				tmp[ model_index_to_index[ 132 ] ] = (3.0 + Config::FLaplassInverse * 0.5
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
				auto fff = 2.0 * args[model_index_to_index[211]] + 1.25 * args[model_index_to_index[221]] + 4.0 * args[model_index_to_index[231]]
					+ Config::FLaplassInverse * std::sqrt(
						0.33 * sqr(args[model_index_to_index[211]])
						+ 0.0208 * sqr(args[model_index_to_index[221]])
						+ 0.33 * sqr(args[model_index_to_index[231]])
					) - Config::Resource21;
				return 2.0 * args[model_index_to_index[211]] + 1.25 * args[model_index_to_index[221]] + 4.0 * args[model_index_to_index[231]]
					+ Config::FLaplassInverse * std::sqrt(
						0.33 * sqr(args[model_index_to_index[211]])
						+ 0.0208 * sqr(args[model_index_to_index[221]])
						+ 0.33 * sqr(args[model_index_to_index[231]])
					) - Config::Resource21
					;
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
				// x211
				// v[6]:  dg3/dx211 = 2 + 1.282*0.5*( 0.33x211^2 + 0.0208x221^2 + 0.33x231^2 )^ (-0.5) * 2 * 0.33x211
				tmp[ model_index_to_index[ 211 ] ] = (2.0 + Config::FLaplassInverse * 0.5
					* std::pow(
					(0.33 * sqr(xargs[model_index_to_index[211]]) 
						+ 0.0208 * sqr(xargs[model_index_to_index[221]]) 
						+ 0.33 * sqr(xargs[model_index_to_index[231]])),
						-0.5
					)
					)
					* 2 * 0.33 * xargs[model_index_to_index[211]];
				// 221
				// v[8]:  dg3/dx221 = 1.25 + 1.282*0.5*( 0.33x211^2 + 0.0208x221^2 + 0.33x231^2 )^ (-0.5) * 2 * 0.0208x221
				tmp[ model_index_to_index[ 221 ] ] = (1.25 + Config::FLaplassInverse * 0.5
					* std::pow(
					(0.33 * sqr(xargs[model_index_to_index[211]]) 
						+ 0.0208 * sqr(xargs[model_index_to_index[221]]) 
						+ 0.33 * sqr(xargs[model_index_to_index[231]])),
						-0.5
					)
					)
					* 2 * 0.0208 * xargs[model_index_to_index[221]];

				// 231
				// v[10]: dg3/dx231 = 4 + 1.282*0.5*( 0.33x211^2 + 0.0208x221^2 + 0.33x231^2 )^ (-0.5) * 2 * 0.33x231
				tmp[ model_index_to_index[ 231 ] ] = (4.0 + Config::FLaplassInverse * 0.5
					* std::pow(
					(0.33 * sqr(xargs[model_index_to_index[211]]) 
						+ 0.0208 * sqr(xargs[model_index_to_index[221]]) 
						+ 0.33 * sqr(xargs[model_index_to_index[231]])),
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
				auto fff = 5.0 * args[model_index_to_index[212]] + 1.5 * args[model_index_to_index[222]] + 5.0 * args[model_index_to_index[232]]
					+ Config::FLaplassInverse * std::sqrt(
						1.33 * sqr(args[model_index_to_index[212]])
						+ 0.083 * sqr(args[model_index_to_index[222]])
						+ 0.33 * sqr(args[model_index_to_index[232]])
					) - Config::Resource22;
				return 5.0 * args[model_index_to_index[212]] + 1.5 * args[model_index_to_index[222]] + 5.0 * args[model_index_to_index[232]]
					+ Config::FLaplassInverse * std::sqrt(
						1.33 * sqr(args[model_index_to_index[212]])
						+ 0.083 * sqr(args[model_index_to_index[222]])
						+ 0.33 * sqr(args[model_index_to_index[232]])
					) - Config::Resource22;
			}

			/**
			 * g4(x) = 5.0x212 + 1.5x222 + 5.0*x232 + 1.282* sqrt( 1.33 * x212^2 + 0.083*x222^2 + 0.33*x232^2 ) - 200 <= 0
			 * v[7]:  dg4/dx212 = 5 + 1.282 * 0.5 * ( 1.33 * x212^2 + 0.083*x222^2 + 0.33*x232^2 )^( -0.5 ) * 2 * 1.33x212
			 * v[9]:  dg4/dx222 = 1.5 + 1.282 * 0.5 * ( 1.33 * x212^2 + 0.083*x222^2 + 0.33*x232^2 )^( -0.5 ) * 2 * 0.083x222
			 * v[11]: dg4/dx232 = 5 + 1.282 * 0.5 * ( 1.33 * x212^2 + 0.083*x222^2 + 0.33*x232^2 )^( -0.5 ) * 2 * 0.33x232
			 */
			static VectorT gradient(const VectorT& xargs) {
				VectorT grad;
				memset(&grad[0], 0, sizeof(ValueType) * N);
				//x212
				// v[7]:  dg4/dx212 = 5 + 1.282 * 0.5 * ( 1.33 * x212^2 + 0.083*x222^2 + 0.33*x232^2 )^( -0.5 ) * 2 * 1.33x212
				grad[model_index_to_index[212]] = (5.0 + Config::FLaplassInverse * 0.5
					* std::pow(
					(1.33 * sqr(xargs[model_index_to_index[212]]) + 0.083 * sqr(xargs[model_index_to_index[222]]) + 0.33 * sqr(xargs[model_index_to_index[232]])),
						-0.5
					)
					)
					* 2 * 1.33 * xargs[model_index_to_index[212]];
				// 222
				grad[model_index_to_index[222]] = (1.5 + Config::FLaplassInverse * 0.5
					* std::pow(
					(1.33 * sqr(xargs[model_index_to_index[212]]) + 0.083 * sqr(xargs[model_index_to_index[222]]) + 0.33 * sqr(xargs[model_index_to_index[232]])),
						-0.5
					)
					)
					* 2 * 0.083 * xargs[model_index_to_index[222]];

				// 232
				grad[model_index_to_index[232]] = (5.0 + Config::FLaplassInverse * 0.5
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
				auto fff = 2.5 * args[model_index_to_index[311]] + 2.0 * args[model_index_to_index[321]] + 2.0 * args[model_index_to_index[331]]
					+ Config::FLaplassInverse * std::sqrt(
						0.75 * sqr(args[model_index_to_index[311]])
						+ 0.33 * sqr(args[model_index_to_index[321]])
						+ 0.33 * sqr(args[model_index_to_index[331]])
					) - Config::Resource31;

				return 2.5 * args[model_index_to_index[311]] + 2.0 * args[model_index_to_index[321]] + 2.0 * args[model_index_to_index[331]]
					+ Config::FLaplassInverse * std::sqrt(
						0.75 * sqr(args[model_index_to_index[311]])
						+ 0.33 * sqr(args[model_index_to_index[321]])
						+ 0.33 * sqr(args[model_index_to_index[331]])
					) - Config::Resource31;
			}

			/**
			 * g5(x) = 2.5 * x311 + 2.0 * x321 + 2.0 * x331 + 1.282 * sqrt( 0.75 * x311^2 + 0.33*x321^2 + 0.33*x331^2 ) - 240 <= 0
			 * v[12]:  dg5/dx311 = 2.5 + 1.282 * 0.5 * ( 0.75 * x311^2 + 0.33*x321^2 + 0.33*x331^2 )^-0.5 * 2 * 0.75 * x311
			 * v[14]:  dg5/dx321 = 2.0 + 1.282 * 0.5 * ( 0.75 * x311^2 + 0.33*x321^2 + 0.33*x331^2 )^-0.5 * 2 * 0.33 * x321
			 * v[16]:  dg5/dx331 = 2.0 + 1.282 * 0.5 * ( 0.75 * x311^2 + 0.33*x321^2 + 0.33*x331^2 )^-0.5 * 2 * 0.33 * x331
			 */
			static VectorT gradient(const VectorT& xargs) {
				VectorT grad;
				memset(&grad[0], 0, sizeof(ValueType) * N);
				//x311
				grad[model_index_to_index[311]] = (2.5 + Config::FLaplassInverse * 0.5
					* std::pow(
					(0.75 * sqr(xargs[model_index_to_index[311]]) + 0.33 * sqr(xargs[model_index_to_index[321]]) + 0.33 * sqr(xargs[model_index_to_index[331]])),
						-0.5
					)
					)
					* 2 * 0.75 * xargs[model_index_to_index[311]];
				// 321
				grad[model_index_to_index[321]] = (2.0 + Config::FLaplassInverse * 0.5
					* std::pow(
					(0.75 * sqr(xargs[model_index_to_index[311]]) + 0.33 * sqr(xargs[model_index_to_index[321]]) + 0.33 * sqr(xargs[model_index_to_index[331]])),
						-0.5
					)
					)
					* 2 * 0.33 * xargs[model_index_to_index[321]];

				// 331
				grad[model_index_to_index[331]] = (2.0 + Config::FLaplassInverse * 0.5
					* std::pow(
						(0.75 * sqr(xargs[model_index_to_index[311]]) + 0.33 * sqr(xargs[model_index_to_index[321]]) + 0.33 * sqr(xargs[model_index_to_index[331]])),
						-0.5
						)
					)
					* 2 * 0.33 * xargs[model_index_to_index[331]];
				return grad;

			}
		};

		/**
		 * g6(x) = 4.0 * x312 + 4.0 * x322 + 7.0 * x332 + 1.282 * sqrt( 1.33 * x312^2 + 0.33*x322^2 + 0.33*x332^2 ) - 300 <= 0
		 */
		struct G6 {
			static constexpr size_t N = 18;
			using ValueType = double;
			using VectorT = std::array<ValueType, N>;

			// g6(x) = 4.0 * x312 + 4.0 * x322 + 7.0 * x332 + 1.282 * sqrt( 1.33 * x312^2 + 0.33*x322^2 + 0.33*x332^2 ) - 300 <= 0
			static ValueType apply(const VectorT& args) {
				auto fff = 4.0 * args[model_index_to_index[312]] + 4.0 * args[model_index_to_index[322]] + 7.0 * args[model_index_to_index[332]]
					+ Config::FLaplassInverse * std::sqrt(
						1.33 * sqr(args[model_index_to_index[312]])
						+ 0.33 * sqr(args[model_index_to_index[322]])
						+ 0.33 * sqr(args[model_index_to_index[332]])
					) - Config::Resource32;

				return 4.0 * args[model_index_to_index[312]] + 4.0 * args[model_index_to_index[322]] + 7.0 * args[model_index_to_index[332]]
					+ Config::FLaplassInverse * std::sqrt(
						1.33 * sqr(args[model_index_to_index[312]])
						+ 0.33 * sqr(args[model_index_to_index[322]])
						+ 0.33 * sqr(args[model_index_to_index[332]])
					) - Config::Resource32;
			}

			/**
			 * g6(x) = 4.0 * x312 + 4.0 * x322 + 7.0 * x332 + 1.282 * sqrt( 1.33 * x312^2 + 0.33*x322^2 + 0.33*x332^2 ) - 300 <= 0
			 * v[13]:  dg6/dx312 = 4 + 1.282 * 0.5 * ( 1.33 * x312^2 + 0.33*x322^2 + 0.33*x332^2 ) ^ -0.5 * 2 * 1.33 * x312
			 * v[15]:  dg6/dx322 = 4 + 1.282 * 0.5 * ( 1.33 * x312^2 + 0.33*x322^2 + 0.33*x332^2 ) ^ -0.5 * 2 * 0.33 * x322
			 * v[17]:  dg6/dx332 = 7 + 1.282 * 0.5 * ( 1.33 * x312^2 + 0.33*x322^2 + 0.33*x332^2 ) ^ -0.5 * 2 * 0.33 * x332
			 */
			static VectorT gradient(const VectorT& xargs) {
				VectorT grad;
				memset(&grad[0], 0, sizeof(ValueType) * N);
				//x312
				grad[model_index_to_index[312]] = (4.0 + Config::FLaplassInverse * 0.5
					* std::pow(
						(1.33 * sqr(xargs[model_index_to_index[312]]) + 0.33 * sqr(xargs[model_index_to_index[322]]) + 0.33 * sqr(xargs[model_index_to_index[332]])),
						-0.5
						)
					)
					* 2 * 1.33 * xargs[model_index_to_index[312]];
				// 322
				grad[model_index_to_index[322]] = (4.0 + Config::FLaplassInverse * 0.5
					* std::pow(
						(1.33 * sqr(xargs[model_index_to_index[312]]) + 0.33 * sqr(xargs[model_index_to_index[322]]) + 0.33 * sqr(xargs[model_index_to_index[332]])),
						-0.5
						)
					)
					* 2 * 0.33 * xargs[model_index_to_index[322]];

				// 332
				grad[model_index_to_index[332]] = (7.0 + Config::FLaplassInverse * 0.5
					* std::pow(
						(1.33 * sqr(xargs[model_index_to_index[312]]) + 0.33 * sqr(xargs[model_index_to_index[322]]) + 0.33 * sqr(xargs[model_index_to_index[332]])),
						-0.5
					 )
					)
					* 2 * 0.33 * xargs[model_index_to_index[332]];
				return grad;

			}
		};

		/**
		 * g7(x) = 300 - x111 - x112 - x211 - x212 - x311 - x312 <= 0
		 */
		struct G7 {
			static constexpr size_t N = 18;
			using ValueType = double;
			using VectorT = std::array<ValueType, N>;

			// g7(x) = 300 - x111 - x112 - x211 - x212 - x311 - x312 <= 0
			static ValueType apply(const VectorT& args) {
				return Config::ASum - args[model_index_to_index[111]] - args[model_index_to_index[112]] 
					- args[model_index_to_index[211]] - args[model_index_to_index[212]]
					- args[model_index_to_index[311]] - args[model_index_to_index[312]];
			}

			/**
			 * g7(x) = 300 - x111 - x112 - x211 - x212 - x311 - x312 <= 0
			 * v[0]:  dg7/dx111 = -1
			 * v[1]:  dg7/dx112 = -1
			 * v[6]:  dg7/dx211 = -1
			 * v[7]:  dg7/dx212 = -1
			 * v[12]: dg7/dx311 = -1
			 * v[13]: dg7/dx312 = -1
			 */
			static VectorT gradient(const VectorT&) {
				VectorT grad;
				memset(&grad[0], 0, sizeof(ValueType) * N);
				grad[model_index_to_index[111]] = -1.0;
				grad[model_index_to_index[112]] = -1.0;
				grad[model_index_to_index[211]] = -1.0;
				grad[model_index_to_index[212]] = -1.0;
				grad[model_index_to_index[311]] = -1.0;
				grad[model_index_to_index[312]] = -1.0;
				return grad;
			}
		};

		/**
		 * g8(x) = 300 - x111 - x112 - x211 - x212 - x311 - x312 <= 0
		 */
		struct G8 {
			static constexpr size_t N = 18;
			using ValueType = double;
			using VectorT = std::array<ValueType, N>;

			// g8(x) = 170 - x121 - x122 - x221 - x222 - x321 - x322 <= 0
			static ValueType apply(const VectorT& args) {
				return Config::BSum - args[model_index_to_index[121]] - args[model_index_to_index[122]]
					- args[model_index_to_index[221]] - args[model_index_to_index[222]]
					- args[model_index_to_index[321]] - args[model_index_to_index[322]];
			}

			/**
			 * g8(x) = 170 - x121 - x122 - x221 - x222 - x321 - x322 <= 0
			 * grad[2]:  dg8/dx121 = -1
			 * grad[3]:  dg8/dx122 = -1
			 * grad[8]:  dg8/dx221 = -1
			 * grad[9]:  dg8/dx222 = -1
			 * grad[14]: dg8/dx321 = -1
			 * grad[15]: dg8/dx322 = -1
			 */
			static VectorT gradient(const VectorT&) {
				VectorT grad;
				memset(&grad[0], 0, sizeof(ValueType) * N);
				grad[model_index_to_index[121]] = -1.0;
				grad[model_index_to_index[122]] = -1.0;
				grad[model_index_to_index[221]] = -1.0;
				grad[model_index_to_index[222]] = -1.0;
				grad[model_index_to_index[321]] = -1.0;
				grad[model_index_to_index[322]] = -1.0;
				return grad;
			}
		};

		/**
		 * g9(x) = 250 - x131 - x132 - x231 - x232 - x331 - x332 <= 0
		 */
		struct G9 {
			static constexpr size_t N = 18;
			using ValueType = double;
			using VectorT = std::array<ValueType, N>;

			// g9(x) = 250 - x131 - x132 - x231 - x232 - x331 - x332 <= 0
			static ValueType apply(const VectorT& args) {
				return Config::CSum - args[model_index_to_index[131]] - args[model_index_to_index[132]]
					- args[model_index_to_index[231]] - args[model_index_to_index[232]]
					- args[model_index_to_index[331]] - args[model_index_to_index[332]];
			}

			/**
			 * g9(x) = 250 - x131 - x132 - x231 - x232 - x331 - x332 <= 0
			 * grad[4]:  dg9/dx131 = -1
			 * grad[5]:  dg9/dx132 = -1
			 * grad[10]:  dg9/dx231 = -1
			 * grad[11]:  dg9/dx232 = -1
			 * grad[16]: dg9/dx331 = -1
			 * grad[17]: dg9/dx332 = -1
			 */
			static VectorT gradient(const VectorT&) {
				VectorT grad;
				memset(&grad[0], 0, sizeof(ValueType) * N);
				grad[model_index_to_index[131]] = -1.0;
				grad[model_index_to_index[132]] = -1.0;
				grad[model_index_to_index[231]] = -1.0;
				grad[model_index_to_index[232]] = -1.0;
				grad[model_index_to_index[331]] = -1.0;
				grad[model_index_to_index[332]] = -1.0;
				return grad;
			}
		};
	}// namespace subj_17

}

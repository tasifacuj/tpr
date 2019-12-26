#pragma once
#include <array>
namespace tpr {
	namespace TrainingModel {
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
				return  (2.0f / 3.0f) * args[0] - args[1] - (4.0f / 3.0f);
			}

			static VectorT gradient(const VectorT&) {
				VectorT tmp;
				tmp[0] = (2.0f / 3.0f);
				tmp[1] = -1.0f;
				return tmp;
			}
		};

	}
}

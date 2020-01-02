#pragma once
#include <array>
#include <cmath>
#include "GradientDescent.hpp"

namespace tpr {
	/**
	 * this is implementation of 2x2
	 * 2 plants, 2 products
	 * TODO: extend this solution to 3 plants, 3 products 1 resource.
	 * TODO: extend this solution to 3 plants, 3 products 2 resources.
	 */
	template<
		typename ValueT,
		typename IndexType = size_t
	>
	class ConstPenaltyFunction {
	public: // == CONSTANTS ==
		static constexpr size_t		N				= 4;
		static constexpr ValueT		Beta			= 2.0f;			//!< growth factor.
		static constexpr ValueT		Epsilon			= 1e-5f;		//!< accuracy
		static constexpr ValueT		DefaultC		= 0.5f;			//!< positive constant
		static constexpr IndexType	MaxPIterations	= 100'000;
		static constexpr ValueT		FLaplassInverse = 1.282f;

		static constexpr ValueT		Resource1		= 250.0f;
		static constexpr ValueT		Resource2		= 100.0f;
		static constexpr int		PCoef			= 2;//!< Power of gi, R1(gi(x)) = max( 0, gi(x) )^P
		static constexpr int		ASum			= 300 / 7;
		static constexpr int		BSum			= 170 / 6;

		static ValueT	sC_k;										//!< rk
	public:// == TYPES ==
		using ValueType = ValueT;
		using VectorT = std::array<ValueType, N>;
		using ThisT = ConstPenaltyFunction< ValueType, IndexType>;
	public: // == Fx interface ==
		template<typename T>
		static T Sqr(T val) {
			return val * val;
		}
		/**
		 * x_11 = args[0]
		 * x_12 = args[1]
		 * x_21 = args[2]
		 * x_22 = args[3]
		 */
		static ValueType apply(const VectorT& xargs) {
			return 3.0 * xargs[ 0 ] + 9.0 * xargs[ 1 ] 	+ 3.0 * xargs[ 2 ] + 6.0 * xargs[ 3 ]
				+ sC_k * (
					  std::pow(std::max(0.0, 1.5 * xargs[ 0 ] + 0.75 * xargs[ 1 ] + FLaplassInverse * std::sqrt( 0.083 * Sqr( xargs[ 0 ] ) + 0.0208 * Sqr( xargs[ 1 ] ) ) - Resource1), PCoef)
					+ std::pow(std::max(0.0, 2.0 * xargs[ 2 ] + 1.25 * xargs[ 3 ] + FLaplassInverse * std::sqrt( 0.33  * Sqr( xargs[ 2 ] ) + 0.0208 * Sqr( xargs[ 3 ] ) ) - Resource2), PCoef)
					+ std::pow(std::max(0.0, ASum - xargs[0] - xargs[2]), PCoef)
					+ std::pow(std::max(0.0, BSum - xargs[1] - xargs[3]), PCoef)
					)
				;
		}

		/**
		 * x_11 = args[0]
		 * x_12 = args[1]
		 * x_21 = args[2]
		 * x_22 = args[3]
		 */
		static VectorT gradient(const VectorT& xargs) {
			ValueType g1 = 1.5 * xargs[0] + 0.75 * xargs[1] + FLaplassInverse * std::sqrt(0.083 * Sqr(xargs[0]) + 0.0208 * Sqr(xargs[1])) - Resource1;
			ValueType g2 = 1.5 * xargs[0] + 0.75 * xargs[1] + FLaplassInverse * std::sqrt(0.083 * Sqr(xargs[0]) + 0.0208 * Sqr(xargs[1])) - Resource1;
			ValueType g3 = ASum - xargs[0] - xargs[2];
			ValueType g4 = BSum - xargs[1] - xargs[3];
			
			ValueType dg1dx11 = 0.0f;
			ValueType dg1dx12 = 0.0f;
			ValueType dg2dx21 = 0.0f;
			ValueType dg2dx22 = 0.0f;
			ValueType dg3dx11 = 0.0f;
			ValueType dg3dx21 = 0.0f;
			ValueType dg4dx12 = 0.0f;
			ValueType dg4dx22 = 0.0f;

			if (g1 > 0.0) {
				dg1dx11 = PCoef * std::pow( (1.5 * xargs[0] + 0.75 * xargs[1] + FLaplassInverse * std::sqrt(0.083 * Sqr(xargs[0]) + 0.0208 * Sqr(xargs[1])) - Resource1), PCoef - 1)
					* ( 1.5 + FLaplassInverse * 0.5 * std::pow((0.083 * Sqr(xargs[0]) + 0.0208 * Sqr(xargs[1])), -0.5) )
					* 2 * 0.083 * xargs[ 0 ]
					;
				dg1dx12 = PCoef * std::pow((1.5 * xargs[0] + 0.75 * xargs[1] + FLaplassInverse * std::sqrt(0.083 * Sqr(xargs[0]) + 0.0208 * Sqr(xargs[1])) - Resource1), PCoef - 1)
					* (0.75 + FLaplassInverse * 0.5 * std::pow((0.083 * Sqr(xargs[0]) + 0.0208 * Sqr(xargs[1])), -0.5))
					* 2 * 0.0208 * xargs[ 1 ]
					;
			}

			if (g2 > 0.0) {
				dg2dx21 = PCoef * std::pow(2.0 * xargs[2] + 1.25 * xargs[3] + FLaplassInverse * std::sqrt(0.33  * Sqr(xargs[2]) + 0.0208 * Sqr(xargs[3])) - Resource2, PCoef - 1)
					* ( 2.0 + FLaplassInverse * 0.5 * std::pow((0.33  * Sqr(xargs[2]) + 0.0208 * Sqr(xargs[3])), -0.5) )
					* 2.0 * 0.33 * xargs[ 2 ]
					;

				dg2dx22 = PCoef * std::pow(2.0 * xargs[2] + 1.25 * xargs[3] + FLaplassInverse * std::sqrt(0.33  * Sqr(xargs[2]) + 0.0208 * Sqr(xargs[3])) - Resource2, PCoef - 1)
					* (1.25 + FLaplassInverse * 0.5 * std::pow((0.33  * Sqr(xargs[2]) + 0.0208 * Sqr(xargs[3])), -0.5))
					* 2.0 * 0.0208 * xargs[3]
					;
			}

			if (g3 > 0.0) {
				dg3dx11 = -2 * (ASum - xargs[0] - xargs[2]);
				dg3dx21 = -2 * (ASum - xargs[0] - xargs[2]);
			}

			if (g4 > 0.0) {
				dg4dx12 = -2 * (BSum - xargs[1] - xargs[3]);
				dg4dx22 = -2 * (BSum - xargs[1] - xargs[3]);
			}

			ValueType dQdx11 = 3.0 + sC_k * (dg1dx11 + dg3dx11);
			ValueType dQdx12 = 9.0 + sC_k * (dg1dx12 + dg4dx12);
			ValueType dQdx21 = 3.0 + sC_k * (dg2dx21 + dg3dx21);
			ValueType dQdx22 = 6.0 + sC_k * (dg2dx22 + dg4dx22);
			
			// x_11, x_12, x_21, x_22
			return { dQdx11, dQdx12, dQdx21, dQdx22 };
		}

		static VectorT evaluate(const VectorT& x0) {
			ThisT::sC_k = DefaultC;
			VectorT xArgs = x0;
			// prepare new penalty function

			//using GradientDescent = StepSplitGradientDescent<ThisT>;
			using GradientDescent = ConstStepGradientDescent<ThisT>;
			IndexType idx = 0;

			for (; idx < MaxPIterations; idx++) {
				IndexType it = 0;

				// find min( F(x, rk) )
				VectorT xOptLoc = GradientDescent::calculate(xArgs, GradientDescent::Lambda, it);
				ValueType eps = std::fabs(ThisT::apply(xOptLoc) - ThisT::apply(xArgs));

				if (eps <= Epsilon) {
					return xOptLoc;
				}
				else {
					// r[k+1] = r[k] * B
					ThisT::sC_k *= ThisT::Beta;
					xArgs = xOptLoc;
				}
			}

			if (idx >= MaxPIterations) {
				assert(0 && "Failure");
			}

			return {};
		}

		static ValueType G1( const VectorT& xargs ) {
			return  1.5 * xargs[0] + 0.75 * xargs[1] + FLaplassInverse * std::sqrt(0.083 * Sqr(xargs[0]) + 0.0208 * Sqr(xargs[1])) - Resource1;
		}

		static ValueType G2(const VectorT& xargs) {
			return  2.0 * xargs[2] + 1.25 * xargs[3] + FLaplassInverse * std::sqrt(0.33  * Sqr(xargs[2]) + 0.0208 * Sqr(xargs[3])) - Resource2;
		}

		static ValueType G3(const VectorT& xargs) {
			return ASum - xargs[0] - xargs[2];
		}

		static ValueType G4(const VectorT& xargs) {
			return BSum - xargs[1] - xargs[3];
		}
	};

	template<
		typename ValueT,
		typename IndexType
	>
	typename ConstPenaltyFunction<ValueT, IndexType>::ValueType ConstPenaltyFunction<ValueT, IndexType>::sC_k = 0.0f;
}// namespace tpr

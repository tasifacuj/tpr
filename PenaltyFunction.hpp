#pragma once
#include <functional>
#include <cmath>

#include "GradientDescent.hpp"

namespace tpr {
	/**
	 * @brief penalty function algorithm
	 * while true
	 * do
	 *     F(x, r[k]) = f(x_opt) + r[k] * alpha(x_opt)
	 *	   x_opt = min( F(x, r[k]) )
	 *	   
	 *     if r[k] * alpha(x_opt) <= Epsilon
	 *     then
	 *        return x_opt
	 *	   else
	 *         r[k+1] = Beta * r[k]
	 *     end
	 * done
	 */
	template<
		typename FT, //minimizing function
		typename IndexType,
		typename ... GiFuncTypes
	>
	class PenaltyFunction {
	public: // == TYPES ==
		using TargetF	= FT;
		using ValueType = typename TargetF::ValueType;
		using VectorT	= typename TargetF::VectorT;
		using ThisT		= PenaltyFunction<FT, IndexType, GiFuncTypes ...>;

		template<typename VecT, int N>
		struct InitArray;

		template<typename VecT>
		struct InitArray<VecT, 1> {
			void initialize(VecT& v) {
				v[0] = typename VecT::value_type();
			}
		};

		template<typename VecT>
		struct InitArray<VecT, 2> {
			void initialize(VecT& v) {
				v[0] = typename VecT::value_type();
				v[1] = typename VecT::value_type();
			}
		};

		template<typename VecT>
		struct InitArray<VecT, 3> {
			void initialize(VecT& v) {
				v[0] = typename VecT::value_type();
				v[1] = typename VecT::value_type();
				v[2] = typename VecT::value_type();
			}
		};

		template<typename ValueT, typename VecT, int PParam, typename G, typename... GiFuncTypes>
		struct R1 : R1<ValueT, VecT, PParam, G>
			, R1< ValueT, VecT, PParam, GiFuncTypes ... > {
			using Tail = R1< ValueT, VecT, PParam, GiFuncTypes ... >;

			static ValueT apply(const VecT& xArgs) {
				return std::pow(std::max(0.0, double(1.0 * G::apply(xArgs))), PParam) + Tail::apply(xArgs);
			}

			static VecT gradient(const VecT& xArgs) {
				ValueT f = G::apply(xArgs);
				ValueT v = std::pow(std::max(0.0, 1.0 * f), PParam);
				VecT g;
				memset(&g[0], 0, sizeof(ValueT) * g.size());

				if (v > 0) {
					/**
					 * f(x) = (x1 + x2 - 7 )^3
					 * dfdx1 = 3*(x1+x2 - 7)^2 * (x1+x2 - 7)' = 3*(x1+x2 - 7)^2 * 1
					 */
					g = G::gradient(xArgs);
					
					for (IndexType idx = 0; idx < g.size(); idx++) {
						g[idx] = PParam * std::pow(1.0 * f, PParam - 1) * g[idx];
					}
				}
				
				VecT tailGrad = Tail::gradient(xArgs);

				for (IndexType idx = 0; idx < g.size(); idx++) {
					g[idx] += tailGrad[idx];
				}

				return g;
			}
		};

		// end of recursion.
		template<typename ValueT, typename VecT, int PParam, typename G>
		struct R1<ValueT, VecT, PParam, G> {
			static ValueT apply(const VecT& xArgs) {
				return std::pow(std::max(0.0, 1.0 * G::apply(xArgs)), PParam );
			}

			static VecT gradient(const VecT& xArgs) {
				ValueT f = G::apply(xArgs);
				ValueT v = std::pow(std::max(0.0, 1.0 * f), PParam);
				VecT g;
				memset(&g[0], 0, sizeof(ValueT) * g.size());

				if (v > 0) {
					/**
					 * f(x) = (x1 + x2 - 7 )^3
					 * dfdx1 = 3*(x1+x2 - 7)^2 * (x1+x2 - 7)' = 3*(x1+x2 - 7)^2 * 1
					 */
					VecT g = G::gradient(xArgs);

					for (IndexType idx = 0; idx < g.size(); idx++) {
						g[idx] = PParam * std::pow(1.0 * f, PParam - 1) * g[idx];
					}
				}

				return g;
			}
		};

		static constexpr int		PCoef = 2;

		using R1Sum = R1<ValueType, VectorT, ThisT::PCoef, GiFuncTypes ...>;

		/**
		 * alpha(x) = sum( R1( gi(x) ) ) + sum( R2( hi(x) ) )
		 */
		template<typename ValueT, typename VecT, typename ROneSum, typename RTwo = void>
		struct AlphaFunc {
			static ValueT apply(const VecT& xArgs) {
				return ROneSum::apply( xArgs );
			}

			static VecT gradient(const VecT& xArgs) {
				return ROneSum::gradient(xArgs);
			}
		};

		using Alpha = AlphaFunc<ValueType, VectorT, R1Sum>;

	public: // == CONSTANTS ==
		static constexpr ValueType	Beta			= 2.0f;	//!< growth factor.
		static constexpr ValueType	Epsilon			= 1e-4f;//!< accuracy
		static constexpr ValueType	DefaultC		= 0.5f; //!< positive constant
		static constexpr IndexType	N				= TargetF::N;
		static constexpr IndexType	MaxPIterations	= 100'000;

		static ValueType	sC;

	public: // == TYPES ==

		/**
		 * Penalty function routine
		 * F(x, r[k]) = f(x) + r[k] * alpha(x)
		 */
		template<
			typename ValueT,
			typename VecT,
			typename F,
			typename A
		>
		struct FxRkFunction {

			using ValueType = ValueT;
			using VectorT	= VecT;
			static constexpr int N = ThisT::N;

			static ValueT apply(const VecT& xArgs) {
				return F::apply(xArgs) + ThisT::sC * A::apply( xArgs );
			}

			static VecT gradient(const VecT& xArgs) {
				VecT fGrad = F::gradient(xArgs);
				VecT alphaGrad = A::gradient(xArgs);

				for( IndexType idx = 0; idx < alphaGrad.size(); idx++)
					alphaGrad[ idx ] *= ThisT::sC;
				
				
				assert(fGrad.size() == alphaGrad.size());
				VecT rval;
				
				for (size_t idx = 0; idx < fGrad.size(); idx++)
					rval[idx] = fGrad[idx] + alphaGrad[idx];
				
				return rval;
			}
		};
		

	public: // == METHODS ==
		static VectorT evaluate(const VectorT& x0) {
			ThisT::sC = DefaultC;
			VectorT xArgs = x0;
			// prepare new penalty function
			using FxRk = FxRkFunction<ValueType, VectorT, TargetF, Alpha>;

			using GradientDescent = StepSplitGradientDescent<FxRk>;
			IndexType idx = 0;

			for (; idx < MaxPIterations; idx++ ) {
				IndexType it = 0;

				// find min( F(x, rk) )
				VectorT xOptLoc = GradientDescent::calculate(xArgs, GradientDescent::Lambda, it);
				ValueType eps = std::fabs(TargetF::apply(xOptLoc) - TargetF::apply(xArgs));

				if (eps <= Epsilon) {
					return xOptLoc;
				}else {
					// r[k+1] = r[k] * B
					ThisT::sC *= ThisT::Beta;
					xArgs = xOptLoc;
				}
			}

			if (idx >= MaxPIterations) {
				assert(0 && "Failure");
			}

			return {};
		}
	};

	template<
		typename FT, //minimizing function
		typename IndexType,
		typename ... GiFuncTypes
	>
	typename PenaltyFunction<FT, IndexType, GiFuncTypes ...>::ValueType PenaltyFunction<FT, IndexType, GiFuncTypes ...>::sC = 0.0f;
}
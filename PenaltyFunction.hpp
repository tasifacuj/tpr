#pragma once
#include <functional>
#include <cmath>

#include "GradientDescent.hpp"

namespace tpr {
	/**
	 * @brief penalty function algorithm
	 * F(x, r[k]) = f(x) + r[k] * alpha(x) -> min
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

		template<typename ValueT, typename VecT, int PParam, typename G, typename... GiFuncTypes>
		struct R1 : R1<ValueT, VecT, PParam, G>
			, R1< ValueT, VecT, PParam, GiFuncTypes ... > {
			using Tail = R1< ValueT, VecT, PParam, GiFuncTypes ... >;

			static ValueT apply(const VecT& xArgs) {
				return std::pow(std::max(0, -1 * G::apply(xArgs)), PParam) + Tail::apply(xArgs);
			}

			static VecT gradient(const VecT& xArgs) {
				ValueT v = std::pow(std::max(0, -1 * G::apply(xArgs)), PParam);
				VecT g = v > 0 ? std::pow(G::gradient(xArgs), PParam) : VecT();
				return g + Tail::gradient( xArgs );
			}
		};

		// end of recursion.
		template<typename ValueT, typename VecT, int PParam, typename G>
		struct R1<ValueT, VecT, PParam, G> {
			static ValueT apply(const VecT& xArgs) {
				return std::pow(std::max(0, -1 * G::apply(xArgs)), PParam );
			}

			static VecT gradient(const VecT& xArgs) {
				ValueT v = std::pow(std::max(0, -1 * G::apply(xArgs)), PParam);
				VecT g = v > 0 ? std::pow(G::gradient(xArgs), PParam) : VecT();
				return g;
			}
		};

		using R1Sum = R1<ValueType, VectorT, ThisT::PCoef, GiFuncTypes ...>;

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
		static constexpr ValueType	Beta	= 2;	//!< growth factor.
		static constexpr ValueType	Epsilon	= 1e-5f;//!< accuracy
		static constexpr ValueType	Rk		= 0.5f; //!< positive constant
		static constexpr int		PCoef		= 2;
		static constexpr IndexType	N		= TargetF::N;
		static constexpr IndexType	MaxPIterations = 100'000;

		static ValueType	sRk;

	public: // == TYPES ==

		///**
		// * Penalty function routine
		// */
		template<
			typename ValueT,
			typename VecT,
			typename F,
			typename A
		>
		struct PFFunc {
			static ValueT apply(const VecT& xArgs) {
				return F::apply(xArgs) + ThisT::sRk * A::apply( xArgs );
			}

			static VecT gradient(const VecT& xArgs) {
				return F::gradient(xArgs) + ThisT::sRk * A::gradient(xArgs);
			}
		};
		

	public: // == METHODS ==
		static VectorT evaluate(const VectorT& x0) {
			ThisT::rk = Rk;
			VectorT xArgs = x0;
			// prepare new penalty function
			using PFRoutine = PFFunc<ValueType, VectorT, TargetF, Alpha>;

			using GradientDescent = StepSplitGradientDescent<PFRoutine>;
			IndexType idx = 0;

			for (; idx < MaxPIterations; idx++ ) {
				IndexType it = 0;

				// find min( F(x, rk) )
				VectorT xOptLoc = GradientDescent::calculate(xArgs, GradientDescent::Lambda, it);

				if (ThisT::sRk * PF::apply(xOptLoc) <= Epsilon) {
					return xOptLoc;
				}else {
					// r[k+1] = r[k] * B
					ThisT::sRk *= ThisT::Beta;
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
	PenaltyFunction<FT, IndexType, GiFuncTypes ...>::ValueType PenaltyFunction<FT, IndexType, GiFuncTypes ...>::sRk = 0.0f;
}
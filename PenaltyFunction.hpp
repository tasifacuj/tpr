#pragma once
#include <functional>
#include <cmath>

#include "GradientDescent.hpp"

namespace tpr {
	/*template<typename ValueType, typename VectorT, typename GFuncT, int N>
	struct WrapGi;

	template<typename ValueType, typename VectorT, typename GFuncT>
	struct WrapGi<ValueType, VectorT, GFuncT, 1> {
		using ApplyF = &GFuncT::apply;

		template<ApplyF g1>
		struct R1
		{
			static ValueType apply(const VectorT& xArgs) {
				return std::pow(std::max(0, -1 * g1(xArgs)), P);
			}
		};
	};

	template<typename ValueType, typename VectorT, typename GFuncT>
	struct WrapGi<ValueType, VectorT, GFuncT, 2> {
		using ApplyF = &GFuncT::apply;
		template<
			ApplyF g1,
			ApplyF g2
		>
		struct R1
		{
			static ValueType apply(const VectorT& xArgs) {
				return std::pow(std::max(0, -1 * g1(xArgs)), P) + std::pow(std::max(0, -1 * g2(xArgs)), P);
			}
		};
	};

	template<typename ValueType, typename VectorT, typename GFuncT>
	struct WrapGi<ValueType, VectorT, GFuncT, 3> {
		using ApplyF = &GFuncT::apply;
		template<
			ApplyF g1,
			ApplyF g2,
			ApplyF g3
		>
			struct R1
		{
			static ValueType apply(const VectorT& xArgs) {
				return std::pow(std::max(0, -1 * g1(xArgs)), P) + std::pow(std::max(0, -1 * g2(xArgs)), P) + std::pow(std::max(0, -1 * g3(xArgs)), P);
			}
		};
	};

	template<typename ValueType, typename VectorT, typename GFuncT>
	struct WrapGi<ValueType, VectorT, GFuncT, 4> {
		using ApplyF = &GFuncT::apply;
		template<
			ApplyF g1,
			ApplyF g2,
			ApplyF g3,
			ApplyF g4
		>
			struct R1
		{
			static ValueType apply(const VectorT& xArgs) {
				return std::pow(std::max(0, -1 * g1(xArgs)), P) + std::pow(std::max(0, -1 * g2(xArgs)), P) + std::pow(std::max(0, -1 * g3(xArgs)), P) + std::pow(std::max(0, -1 * g4(xArgs)), P);
			}
		};
	};

	template<typename ValueType, typename VectorT, typename GFuncT>
	struct WrapGi<ValueType, VectorT, GFuncT, 5> {
		using ApplyF = &GFuncT::apply;
		template<
			ApplyF g1,
			ApplyF g2,
			ApplyF g3,
			ApplyF g4,
			ApplyF g5
		>
			struct R1
		{
			static ValueType apply(const VectorT& xArgs) {
				return std::pow(std::max(0, -1 * g1(xArgs)), P) 
					+ std::pow(std::max(0, -1 * g2(xArgs)), P) 
					+ std::pow(std::max(0, -1 * g3(xArgs)), P) 
					+ std::pow(std::max(0, -1 * g4(xArgs)), P)
					+ std::pow(std::max(0, -1 * g5(xArgs)), P)
					;
			}
		};
	};

	template<typename ValueType, typename VectorT, typename GFuncT>
	struct WrapGi<ValueType, VectorT, GFuncT, 6> {
		using ApplyF = &GFuncT::apply;
		template<
			ApplyF g1,
			ApplyF g2,
			ApplyF g3,
			ApplyF g4,
			ApplyF g5,
			ApplyF g6
		>
			struct R1
		{
			static ValueType apply(const VectorT& xArgs) {
				return std::pow(std::max(0, -1 * g1(xArgs)), P)
					+ std::pow(std::max(0, -1 * g2(xArgs)), P)
					+ std::pow(std::max(0, -1 * g3(xArgs)), P)
					+ std::pow(std::max(0, -1 * g4(xArgs)), P)
					+ std::pow(std::max(0, -1 * g5(xArgs)), P)
					+ std::pow(std::max(0, -1 * g6(xArgs)), P)
					;
			}
		};
	};

	template<typename ValueType, typename VectorT, typename GFuncT>
	struct WrapGi<ValueType, VectorT, GFuncT, 7> {
		using ApplyF = &GFuncT::apply;
		template<
			ApplyF g1,
			ApplyF g2,
			ApplyF g3,
			ApplyF g4,
			ApplyF g5,
			ApplyF g6,
			ApplyF g7
		>
			struct R1
		{
			static ValueType apply(const VectorT& xArgs) {
				return std::pow(std::max(0, -1 * g1(xArgs)), P)
					+ std::pow(std::max(0, -1 * g2(xArgs)), P)
					+ std::pow(std::max(0, -1 * g3(xArgs)), P)
					+ std::pow(std::max(0, -1 * g4(xArgs)), P)
					+ std::pow(std::max(0, -1 * g5(xArgs)), P)
					+ std::pow(std::max(0, -1 * g6(xArgs)), P)
					+ std::pow(std::max(0, -1 * g7(xArgs)), P)
					;
			}
		};
	};

	template<typename ValueType, typename VectorT, typename GFuncT>
	struct WrapGi<ValueType, VectorT, GFuncT, 8> {
		using ApplyF = &GFuncT::apply;
		template<
			ApplyF g1,
			ApplyF g2,
			ApplyF g3,
			ApplyF g4,
			ApplyF g5,
			ApplyF g6,
			ApplyF g7,
			ApplyF g8
		>
			struct R1
		{
			static ValueType apply(const VectorT& xArgs) {
				return std::pow(std::max(0, -1 * g1(xArgs)), P)
					+ std::pow(std::max(0, -1 * g2(xArgs)), P)
					+ std::pow(std::max(0, -1 * g3(xArgs)), P)
					+ std::pow(std::max(0, -1 * g4(xArgs)), P)
					+ std::pow(std::max(0, -1 * g5(xArgs)), P)
					+ std::pow(std::max(0, -1 * g6(xArgs)), P)
					+ std::pow(std::max(0, -1 * g7(xArgs)), P)
					+ std::pow(std::max(0, -1 * g8(xArgs)), P)
					;
			}
		};
	};

	template<typename ValueType, typename VectorT, typename GFuncT>
	struct WrapGi<ValueType, VectorT, GFuncT, 9> {
		using ApplyF = &GFuncT::apply;
		template<
			ApplyF g1,
			ApplyF g2,
			ApplyF g3,
			ApplyF g4,
			ApplyF g5,
			ApplyF g6,
			ApplyF g7,
			ApplyF g8,
			ApplyF g9
		>
			struct R1
		{
			static ValueType apply(const VectorT& xArgs) {
				return std::pow(std::max(0, -1 * g1(xArgs)), P)
					+ std::pow(std::max(0, -1 * g2(xArgs)), P)
					+ std::pow(std::max(0, -1 * g3(xArgs)), P)
					+ std::pow(std::max(0, -1 * g4(xArgs)), P)
					+ std::pow(std::max(0, -1 * g5(xArgs)), P)
					+ std::pow(std::max(0, -1 * g6(xArgs)), P)
					+ std::pow(std::max(0, -1 * g7(xArgs)), P)
					+ std::pow(std::max(0, -1 * g8(xArgs)), P)
					+ std::pow(std::max(0, -1 * g9(xArgs)), P)
					;
			}
		};
	};*/

	/**
	 * @brief penalty function algorithm
	 * F(x, r[k]) = f(x) + r[k] * alpha(x) -> min
	 */
	template<
		typename FT, //minimizing function
		typename IndexType
	>
	class PenaltyFunction {
	public: // == TYPES ==
		using TargetF = FT;
		using ValueType = typename TargetF::ValueType;
		using VectorT	= typename TargetF::VectorT;
		using GType = std::function<ValueType(const VectorT&)>;
		using HType = std::function<ValueType(const VectorT&)>;
	public: // == CONSTANTS ==
		static constexpr ValueType	Beta	= 2;	//!< growth factor.
		static constexpr ValueType	Epsilon	= 1e-5f;//!< accuracy
		static constexpr ValueType	Rk		= 0.5f; //!< positive constant
		static constexpr int		P		= 2;

	public: // == TYPES ==
		// R1(gi(x)) = max( 0, -gi( x ) )^p

		struct R1 {
			const GType& gfunc;

			R1(const GType& g) : gfunc(g) {}

			static ValueType apply( const VectorT& xArgs ) {
				return std::pow(std::max(0, -1 * gfunc(xArgs)), P );
			}
		};

		// R2(gi(x)) = hj(x) ^ ( 2 * P )
		struct R2 {
			const HType& hfunc;

			R2(const HType& h) : hfunc(h) {}

			ValueType apply(const VectorT& xArgs) {
				return std::pow(hfunc(xArgs), 2.0 * P);
			}
		};

		using R1Array = std::array<R1, GSize>;
		using R2Array = std::array<R2, HSize>;

		struct AlphaFunc {
			R1Array r1;
			R2Array r2;

			AlphaFunc(const GArray& gfuncs, const HArray& hfuncs) {
				for (IndexType idx = 0; idx < r1.size(); idx++) {
					r1 = R1(gfuncs[idx]);
				}

				for (IndexType idx = 0; idx < r2.size(); idx++) {
					r2 = R2(hfuncs[idx]);
				}
			}

			ValueType apply(const VectorT& xArgs) {
				ValueType rval = ValueType();

				for (IndexType idx = 0; idx < r1.size(); idx++) {
					rval += r1[idx].apply(xArgs);
				}

				for (IndexType idx = 0; idx < r2.size(); idx++) {
					rval += r2[idx].apply(xArgs);
				}

				return rval;
			}
		};

		/**
		 * F(x, r[k])
		 */
		struct F {
		public:// == CONSTANTS ==
			static constexpr size_t N = TargetF::N;
		public: // == TYPES ==
			using ValueType = ValueType;
			using VectorT = std::array<ValueType, TargetF::N>;
		public:
			const AlphaFunc&	alpha_;
		public: // == CTOR ==
			F(const AlphaFunc&	alpha) : alpha_(alpha) {}
		public: // == METHODS ==
			ValueType apply(const VectorT& xArgs) {
				return TargetF::apply(xArgs) + alpha_.apply( xArgs );
			}
		};

	public: // == METHODS ==
		static VectorT evaluate(const VectorT& x0, GArray garray, HArray harray) {
			ValueType rk = Rk;
			AlphaFunc alpha(garray, harray);
			F f(alpha);
			
			using GradientDescent = StepSplitGradientDescent<F>;
		}
	};
}
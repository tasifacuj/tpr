#pragma once
#include <cmath>
#include <cassert>
#include <iostream>

namespace tpr {
	/**
	 * gradient descent implementation with step splitting
	 * http://www.machinelearning.ru/wiki/index.php?title=%D0%9C%D0%B5%D1%82%D0%BE%D0%B4_%D0%B3%D1%80%D0%B0%D0%B4%D0%B8%D0%B5%D0%BD%D1%82%D0%BD%D0%BE%D0%B3%D0%BE_%D1%81%D0%BF%D1%83%D1%81%D0%BA%D0%B0
	 * TODO: when implementing fast descent use CRTP for fast impl/split impl
	 */
	template< typename F,
		typename IndexType = size_t
	>
	class StepSplitGradientDescent {
	public: // == TYPES ==
		using ValueType = typename F::ValueType;
		using VectorT	= typename F::VectorT;
	public: // == CONSTANTS == 
		static constexpr ValueType	Epsilon			= 0.0001;
		static constexpr IndexType	MaxIterations	= 100'000;
		static constexpr ValueType	SplitEps		= 0.1f;
		static constexpr ValueType  SplitDelta		= 0.98f;
		static constexpr ValueType  Lambda			= 1.0f;
	public:
		static VectorT calculate( const VectorT& x0, ValueType lambda, IndexType& it) {
			IndexType N = F::N;// take num of vars from F
			VectorT oldXVec;
			VectorT currentXVec = x0;
			// || grad( f( x[k] ) )||^2
			ValueType squaredNorm = 0.0f;

			for (it = 0; it < MaxIterations; it++) {
				// save old value
				oldXVec = currentXVec;
				// evaluate gradient
				VectorT gradientVec = F::gradient(currentXVec);
				auto f1 = F::apply(currentXVec);

				bool tmp = false;
				// evaluate new value
				for (IndexType j = 0; j < N; j++)
					currentXVec[j] = currentXVec[j] - lambda * gradientVec[j];

				// evaluate square of gradient norm
				squaredNorm = 0.0f;
				for (IndexType idx = 0; idx < N; idx++)
					squaredNorm += gradientVec[idx] * gradientVec[idx];

				// select lambda from next condition:
				// f( x[k+1] ) = f( x[k] ) - lambda[k] * grad(f[ x[ k ] ]) <= f(x[k]) - eps * lambda[k] * || grad( f( x[k] ) )|| ^ 2
				

				while (F::apply(currentXVec) > (F::apply(oldXVec) - SplitEps * lambda * squaredNorm) ) {
					lambda = SplitDelta * lambda;
					currentXVec = oldXVec;

					for (IndexType j = 0; j < N; j++)
						currentXVec[j] = currentXVec[j] - lambda * gradientVec[j];
				}

				ValueType diff = std::fabs(F::apply(currentXVec) - F::apply(oldXVec));
				
				if(diff < Epsilon)
					return currentXVec;

			}// for

			assert(0 && "Failed");
			return currentXVec;
		}
	};

	template< typename F,
		typename IndexType = size_t
	>
		class FastestGradientDescent {
		public: // == TYPES ==
			using ValueType = typename F::ValueType;
			using VectorT = typename F::VectorT;
		public: // == CONSTANTS == 
			static constexpr ValueType	Epsilon = 0.1;
			static constexpr IndexType	MaxIterations = 100'000;
			static constexpr ValueType	SplitEps = 0.1f;
			static constexpr ValueType  SplitDelta = 0.95f;
			static constexpr ValueType  Lambda = 1.0f;
		public:
			static ValueType MakeSimplefx(ValueType x, const VectorT& grad, const VectorT& xj) {
				VectorT buffer;

				for (IndexType idx = 0; idx < grad.size(); idx++) {
					buffer[ idx ] = xj[ idx ] - x * grad[ idx ];
				}
				

				return F::apply(buffer);
			}

			static ValueType GoldenSelsction(ValueType a, ValueType b, ValueType eps, const VectorT& gradient, const VectorT& x) {
				const ValueType fi = 1.6180339887;
				ValueType x1, x2;
				ValueType y1, y2;

				x1 = b - ((b - a) / fi);
				x2 = a + ((b - a) / fi);
				y1 = MakeSimplefx(x1, gradient, x);
				y2 = MakeSimplefx(x2, gradient, x);
				
				while (std::abs(b - a) > eps){
					if (y1 <= y2)
					{
						b = x2;
						x2 = x1;
						x1 = b - ((b - a) / fi);
						y2 = y1;
						y1 = MakeSimplefx(x1, gradient, x);
					}
					else
					{
						a = x1;
						x1 = x2;
						x2 = a + ((b - a) / fi);
						y1 = y2;
						y2 = MakeSimplefx(x2, gradient, x);
					}
				}

				return (a + b) / 2;
			}

			static VectorT CalculateXVec( const VectorT& x, const VectorT& gradient, ValueType lambda)
			{
				VectorT buffer;
				assert(buffer.size() == gradient.size());
				
				for (IndexType idx = 0; idx < buffer.size(); idx++) {
					buffer[idx] = x[idx] - lambda * gradient[idx];
				}

				return buffer;
			}

			static VectorT calculate(const VectorT& x0, ValueType, IndexType& it) {
				IndexType N = F::N;// take num of vars from F
				VectorT oldXVec;
				VectorT currentXVec = x0;
				it = 0;

				do {
					oldXVec = currentXVec;
					VectorT grad = F::gradient(currentXVec);
					ValueType lambda = GoldenSelsction(0, 0.05, Epsilon, grad, currentXVec);
					currentXVec = CalculateXVec(currentXVec, grad, lambda);
					it++;
				} while (std::abs(F::apply(currentXVec) - F::apply(oldXVec)) > Epsilon && it < MaxIterations);
				
				auto f1 = std::abs(F::apply(currentXVec) );
				auto f2 = std::abs( F::apply(oldXVec) );
				auto d = std::abs(f1 - f2);
				assert(it < MaxIterations);

				return currentXVec;
			}
	};


	template< typename F,
		typename IndexType = size_t
	>
		class ConstStepGradientDescent {
		public: // == TYPES ==
			using ValueType = typename F::ValueType;
			using VectorT = typename F::VectorT;
		public: // == CONSTANTS == 
			static constexpr ValueType	Epsilon = 1e-3f;
			static constexpr IndexType	MaxIterations = 200'000;
			static constexpr ValueType  Lambda = 0.000001f;
		public:
			static VectorT calculate(const VectorT& x0, ValueType lambda, IndexType& it) {
				IndexType N = F::N;// take num of vars from F
				VectorT oldXVec;
				VectorT currentXVec = x0;
				ValueType diff = 0.0f;
				ValueType oldDiff = 0.0f;

				for (it = 0; it < MaxIterations; it++) {
					diff = 0.0f;
					// save old value
					oldXVec = currentXVec;
					// evaluate gradient
					VectorT gradientVec = F::gradient(currentXVec);

					// evaluate new value
					for (IndexType j = 0; j < N; j++)
						currentXVec[j] = currentXVec[j] - lambda * gradientVec[j];

					// evaluate square of gradient norm
					diff = std::fabs(F::apply(currentXVec) - F::apply(oldXVec));
					
					//std::cerr << "diff = " << diff << std::endl;
					if (diff < Epsilon )
						return currentXVec;

					oldDiff = diff;
				}// for

				assert(0 && "Failed");
				return currentXVec;
			}
	};
}// namespace tpr
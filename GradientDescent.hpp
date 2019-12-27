#pragma once
#include <cmath>
#include <cassert>

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
		static constexpr ValueType	Epsilon			= 1e-5f;
		static constexpr IndexType	MaxIterations	= 100'000;
		static constexpr ValueType	SplitEps		= 0.1f;
		static constexpr ValueType  SplitDelta		= 0.95f;
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

#if 0
				squaredNorm = 0;
				for (IndexType j = 0; j < oldXVec.size(); j++)
					squaredNorm += (oldXVec[j] - currentXVec[j])*(oldXVec[j] - currentXVec[j]);
				
				squaredNorm = sqrt(squaredNorm);
				
				if (squaredNorm < Epsilon)
					return currentXVec;
#endif
			}// for

			assert(0 && "Failed");
			return currentXVec;
		}
	};
}// namespace tpr
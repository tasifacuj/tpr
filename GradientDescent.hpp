#pragma once
#include <array>

namespace tpr {
	template<typename ValueT, int VarSize, typename F, typename GradientF>
	class GradientDescent {
	public: // == TYPES ==
		using ValueType = ValueT;
		//using VectorContainerT = std::array<ValueType, VarSize>;
		using VectorT = typename F::VectorT;
	public: // == CONSTANTS == 
		static constexpr ValueT Epsilon = 1e-5;
		static constexpr ValueT Lambda = 1.0f;
		static constexpr size_t MaxIterations = 100'000;
	public:
		static void calculate(F f, GradientF gradF, const GradientContainerT& x0) {
			size_t N = F::NumVariables;// take num of vars from F

			VectorT oldVec;
			VectorT currentVec = x0;

			for (size_t it = 0; it < MaxIterations; it++) {
				oldVec = currentVec;
				VectorT gradientVec = gradF.get();

				for( size_t j = 0; j < VarSize; j++ )
					currentVec[ j ] = currentVec[j] - Lambda * 
			}
		}
	};
}
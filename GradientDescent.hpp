#pragma once
#include <array>

namespace tpr {
	template<typename ValueT, int VarSize, typename F, typename GradientF>
	class GradientDescent {
	public: // == TYPES ==
		using ValueType = ValueT;
		using VectorContainerT = std::array<ValueType, VarSize>;
	public: // == CONSTANTS == 
		static constexpr ValueT Epsilon = 1e-5;
		static constexpr ValueT Lambda = 1.0f;
		static constexpr size_t MaxIterations = 100'000;
	public:
		static void calculate(F f, GradientF gradF, const GradientContainerT& x0) {
			VectorContainerT oldVec;
			VectorContainerT currentVec = x0;

			for (size_t it = 0; it < MaxIterations; it++) {
				oldVec = currentVec;
				VectorContainerT gradientVec = gradF.get();

				for( size_t j = 0; j < VarSize; j++ )
					currentVec[ j ] = currentVec[j] - Lambda * 
			}
		}
	};
}
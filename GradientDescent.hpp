#pragma once
#include <array>

namespace tpr {
	template<typename ValueT, int VarSize, typename F, typename GradientF>
	class GradientDescent {
	public: // == TYPES ==
		using ValueType = ValueT;
		using GradientContainerT = std::array<ValueType, VarSize>;
	public: // == CONSTANTS == 
		static constexpr float Epsilon = 1e-5;
		static constexpr float Lambda = 1.0f;
	public:
		static void calculate(F f, GradientF grad, const GradientContainerT& x0) {
			GradientContainerT old, current = x0;
		}
	};
}
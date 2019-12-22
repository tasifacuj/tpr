#include "GradientDescent.hpp"

#include <iostream>
#include <array>

/**
  * f(x) = 10 * x1^2 + x2 ^ 2
  * df
  * --- = 20 * x1
  * dx1
  * df/dx2 = 2*x2
  */
template<typename ValueT = float>
class QuadF {
public:// == CONSTANTS ==
	static constexpr size_t N = 2;
public: // == TYPES ==
	using ValueType = ValueT;
	using VectorT = std::array<ValueType, N>;
public: // == METHODS ==
	static ValueType apply( const VectorT& args ) {
		return 10 * args[0] * args[0] + args[1] * args[1];
	}

	static VectorT gradient( const VectorT& args ) {
		VectorT tmp;
		tmp[ 0 ] = 20 * args[0];
		tmp[ 1 ] = 2 * args[ 1 ];
		return tmp;
	}
};

int main() {
	using F = QuadF<>;
	using GradientDescent = tpr::StepSplitGradientDescent<F>;
	using Vec = typename F::VectorT;
	Vec x0{ 10.0f, 10.0f };
	size_t it = 0;
	Vec result = GradientDescent::calculate(x0, GradientDescent::Lambda, it);
	/*std::cerr << "f = 10 * x1^2 + x2 ^ 2, min(f) = {";
	
	for (size_t idx = 0; idx < F::N - 1; idx++) {
		std::cerr << result[idx] << ", ";
	}

	std::cerr << result[F::N - 1] << "}\n";*/

	std::cerr << "Value: " << F::apply( result ) << std::endl;
	std::cerr << "Point: ";
	
	for (size_t i = 0; i < result.size(); i++)
		std::cerr << result[i] << ' ';
	std::cerr << std::endl << "Number of iterations:" << it << std::endl;
	return 0;
}
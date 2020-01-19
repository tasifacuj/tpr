#pragma once
#include <array>
#include <cmath>
#include <map>
#include <string>

#include "GradientDescent.hpp"

namespace tpr {
	namespace const_impl {
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
				static constexpr size_t		N = 9;
				static constexpr ValueT		Beta = 2.0f;			//!< growth factor.
				static constexpr ValueT		Epsilon = 1e-5f;		//!< accuracy
				static constexpr ValueT		DefaultC = 0.5f;			//!< positive constant
				static constexpr IndexType	MaxPIterations = 100'000;
				static constexpr ValueT		FLaplassInverse = 1.282f;

				static constexpr ValueT		Resource1 = 250.0f * 4;
				static constexpr ValueT		Resource12 = 150.0f * 4;
				static constexpr ValueT		Resource2 = 100.0f * 4;
				static constexpr ValueT		Resource22 = 200.0f * 4;
				static constexpr ValueT		Resource3 = 240.0f * 4;
				static constexpr ValueT		Resource32 = 300.0f * 4;
				static constexpr int		PCoef = 2;//!< Power of gi, R1(gi(x)) = max( 0, gi(x) )^P
				static constexpr int		ASum = 300;
				static constexpr int		BSum = 170;
				static constexpr int		CSum = 250 ;

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

				static int model_index_2_index(int model_idx) {
					static std::map<int, int> indices{
						{ 11, 0 },
						{ 12, 1 },
						{ 13, 2 },
						{ 21, 3 },
						{ 22, 4 },
						{ 23, 5 },
						{ 31, 6 },
						{ 32, 7 },
						{ 33, 8 }
					};

					auto it = indices.find(model_idx);
					assert(it != indices.end());
					return it->second;
				}

				static std::string model_idx_to_descr(int model_idx) {
					static std::map<int, std::string> model_index_to_description_conv{
						{ 11, "factory 1, product A" },
						{ 12, "factory 1, product B" },
						{ 13, "factory 1, product C" },
						{ 21, "factory 2, product A" },
						{ 22, "factory 2, product B" },
						{ 23, "factory 2, product C" },
						{ 31, "factory 3, product A" },
						{ 32, "factory 3, product B" },
						{ 33, "factory 3, product C" }
					};
					auto it = model_index_to_description_conv.find(model_idx);
					assert(it != model_index_to_description_conv.end());
					return it->second;
				}

				static int idx_to_model_idx(int idx) {
					static std::map<int, int> index_to_model_index_converter{
						{ 0, 11 },
						{ 1, 12 },
						{ 2, 13 },
						{ 3, 21 },
						{ 4, 22 },
						{ 5, 23 },
						{ 6, 31 },
						{ 7, 32 },
						{ 8, 33 }
					};
					auto it = index_to_model_index_converter.find(idx);
					assert(it != index_to_model_index_converter.end());
					return it->second;
				}

				/**
				 * x_11 = args[0]
				 * x_12 = args[1]
				 * x_21 = args[2]
				 * x_22 = args[3]
				 */
				static ValueType apply(const VectorT& xargs) {
					return 3.0 * xargs[model_index_2_index( 11 )] + 9.0 * xargs[model_index_2_index( 12 )] + 5.0 * xargs[model_index_2_index(13)] 
						+ 3.0 * xargs[model_index_2_index( 21 )] + 6.0 * xargs[model_index_2_index( 22 )] + 8.0 * xargs[model_index_2_index(23)]
						+ 8.0 * xargs[model_index_2_index(31)] + 2.0 * xargs[model_index_2_index(32)] + 5 * xargs[model_index_2_index(33)]
						+ sC_k * (
							// g1
							std::pow(std::max(0.0, ThisT::G1( xargs ) ), PCoef )
							// g2
							+ std::pow(std::max(0.0, ThisT::G2(xargs)), PCoef)
							// g3
							+ std::pow(std::max(0.0, ThisT::G3(xargs)), PCoef)
							//g4
							+ std::pow(std::max(0.0, ThisT::G4(xargs)), PCoef)
							// g5
							+ std::pow(std::max(0.0, ThisT::G5(xargs)), PCoef)
							// g6
							+ std::pow(std::max(0.0, ThisT::G6(xargs)), PCoef)
							// g7
							+ std::pow(std::max(0.0, ThisT::G7(xargs)), PCoef)
							// g8
							+ std::pow(std::max(0.0, ThisT::G8(xargs)), PCoef)
							// g9
							+ std::pow(std::max(0.0, ThisT::G9(xargs)), PCoef)
							)
						;
				}

				static VectorT gradient(const VectorT& xargs) {
					ValueType g1 = ThisT::G1(xargs);
					ValueType g2 = ThisT::G2(xargs);

					ValueType g3 = ThisT::G3(xargs);
					ValueType g4 = ThisT::G4(xargs);
					ValueType g5 = ThisT::G5(xargs);
					ValueType g6 = ThisT::G6(xargs);
					ValueType g7 = ThisT::G7(xargs);
					ValueType g8 = ThisT::G8(xargs);
					ValueType g9 = ThisT::G9(xargs);

					ValueType dg1dx11 = 0.0f;
					ValueType dg1dx12 = 0.0f;
					ValueType dg1dx13 = 0.0f;

					ValueType dg2dx21 = 0.0f;
					ValueType dg2dx22 = 0.0f;
					ValueType dg2dx23 = 0.0f;
					
					ValueType dg3dx31 = 0.0f;
					ValueType dg3dx32 = 0.0f;
					ValueType dg3dx33 = 0.0f;
					
					ValueType dg4dx11 = 0.0f;
					ValueType dg4dx21 = 0.0f;
					ValueType dg4dx31 = 0.0f;

					ValueType dg5dx12 = 0.0f;
					ValueType dg5dx22 = 0.0f;
					ValueType dg5dx32 = 0.0f;

					ValueType dg6dx13 = 0.0f;
					ValueType dg6dx23 = 0.0f;
					ValueType dg6dx33 = 0.0f;

					ValueType dg7dx11 = 0.0;
					ValueType dg7dx12 = 0.0;
					ValueType dg7dx13 = 0.0;

					ValueType dg8dx21 = 0.0f;
					ValueType dg8dx22 = 0.0f;
					ValueType dg8dx23 = 0.0f;

					ValueType dg9dx31 = 0.0f;
					ValueType dg9dx32 = 0.0f;
					ValueType dg9dx33 = 0.0f;

					if (g1 > 0.0) {
						dg1dx11 = PCoef * std::pow(g1, PCoef - 1)
							* (1.5 + FLaplassInverse * 0.5 * std::pow(0.083 * Sqr(xargs[model_index_2_index(11)]) + 0.0208 * Sqr(xargs[model_index_2_index(12)]) + 0.083 * Sqr(xargs[model_index_2_index(13)]), -0.5))
							* 2 * 0.083 * xargs[model_index_2_index(11)]
							;
						
						dg1dx12 = PCoef * std::pow(g1, PCoef - 1)
							* (0.75 + FLaplassInverse * 0.5 * std::pow(0.083 * Sqr(xargs[model_index_2_index(11)]) + 0.0208 * Sqr(xargs[model_index_2_index(12)]) + 0.083 * Sqr(xargs[model_index_2_index(13)]), -0.5))
							* 2 * 0.0208 * xargs[model_index_2_index(12)]
							;

						dg1dx13 = PCoef * std::pow(g1, PCoef - 1)
							* (2.5 + FLaplassInverse * 0.5 * std::pow(0.083 * Sqr(xargs[model_index_2_index(11)]) + 0.0208 * Sqr(xargs[model_index_2_index(12)]) + 0.083 * Sqr(xargs[model_index_2_index(13)]), -0.5))
							* 2 * 0.083 * xargs[model_index_2_index(13)]
							;
					}

					if (g7 > 0.0f) {
						dg7dx11 = PCoef * std::pow(g7, PCoef - 1)
							* ( 3 + FLaplassInverse * 0.5 * std::pow(0.33 * Sqr(xargs[model_index_2_index(11)]) + 0.33 * Sqr(xargs[model_index_2_index(12)]) + 0.33 * Sqr(xargs[model_index_2_index(13)]), -0.5) )
							* 2 * 0.33 * xargs[ model_index_2_index( 11 )]
							;
						dg7dx12 = PCoef * std::pow(g7, PCoef - 1)
							* (3 + FLaplassInverse * 0.5 * std::pow(0.33 * Sqr(xargs[model_index_2_index(11)]) + 0.33 * Sqr(xargs[model_index_2_index(12)]) + 0.33 * Sqr(xargs[model_index_2_index(13)]), -0.5))
							* 2 * 0.33 * xargs[model_index_2_index(12)]
							;
						dg7dx13 = PCoef * std::pow(g7, PCoef - 1)
							* (3 + FLaplassInverse * 0.5 * std::pow(0.33 * Sqr(xargs[model_index_2_index(11)]) + 0.33 * Sqr(xargs[model_index_2_index(12)]) + 0.33 * Sqr(xargs[model_index_2_index(13)]), -0.5))
							* 2 * 0.33 * xargs[model_index_2_index(13)]
							;
					}

					if (g2 > 0.0) {
						dg2dx21 = PCoef * std::pow(g2, PCoef - 1)
							* (2.0 + FLaplassInverse * 0.5 * std::pow(0.33  * Sqr(xargs[model_index_2_index(21)]) + 0.0208 * Sqr(xargs[model_index_2_index(22)]) + 0.33 * Sqr(xargs[model_index_2_index(23)]), -0.5))
							* 2.0 * 0.33 * xargs[model_index_2_index(21)]
							;

						dg2dx22 = PCoef * std::pow(g2, PCoef - 1)
							* (1.25 + FLaplassInverse * 0.5 * std::pow(0.33  * Sqr(xargs[model_index_2_index(21)]) + 0.0208 * Sqr(xargs[model_index_2_index(22)]) + 0.33 * Sqr(xargs[model_index_2_index(23)]), -0.5))
							* 2.0 * 0.0208 * xargs[model_index_2_index(22)]
							;

						dg2dx23 = PCoef * std::pow(g2, PCoef - 1)
							* (1.25 + FLaplassInverse * 0.5 * std::pow(0.33  * Sqr(xargs[model_index_2_index(21)]) + 0.0208 * Sqr(xargs[model_index_2_index(22)]) + 0.33 * Sqr(xargs[model_index_2_index(23)]), -0.5))
							* 2.0 * 0.0208 * xargs[model_index_2_index(23)]
							;
					}

					if (g8 > 0.0) {
						dg8dx21 = PCoef * std::pow(g8, PCoef - 1)
							* (5.0 + FLaplassInverse * 0.5 * std::pow(1.33  * Sqr(xargs[model_index_2_index(21)]) + 0.083 * Sqr(xargs[model_index_2_index(22)]) + 0.33 * Sqr(xargs[model_index_2_index(23)]), -0.5))
							* 2.0 * 1.33 * xargs[model_index_2_index(21)]
							;

						dg8dx22 = PCoef * std::pow(g8, PCoef - 1)
							* (1.5 + FLaplassInverse * 0.5 * std::pow(1.33  * Sqr(xargs[model_index_2_index(21)]) + 0.083 * Sqr(xargs[model_index_2_index(22)]) + 0.33 * Sqr(xargs[model_index_2_index(23)]), -0.5))
							* 2.0 * 0.083 * xargs[model_index_2_index(22)]
							;

						dg8dx23 = PCoef * std::pow(g8, PCoef - 1)
							* (5.0 + FLaplassInverse * 0.5 * std::pow(1.33  * Sqr(xargs[model_index_2_index(21)]) + 0.083 * Sqr(xargs[model_index_2_index(22)]) + 0.33 * Sqr(xargs[model_index_2_index(23)]), -0.5))
							* 2.0 * 0.33 * xargs[model_index_2_index(23)]
							;
					}

					if (g3 > 0.0) {
						dg3dx31 = PCoef * std::pow(g3, PCoef - 1)
							* (2.5 + FLaplassInverse * 0.5 * std::pow(0.75  * Sqr(xargs[model_index_2_index(31)]) + 0.33 * Sqr(xargs[model_index_2_index(32)]) + 0.33 * Sqr(xargs[model_index_2_index(33)]), -0.5) )
							* 2.0 * 0.75 * xargs[model_index_2_index(31)]
							;
						dg3dx32 = PCoef * std::pow(g3, PCoef - 1)
							* (2.0 + FLaplassInverse * 0.5 * std::pow(0.75  * Sqr(xargs[model_index_2_index(31)]) + 0.33 * Sqr(xargs[model_index_2_index(32)]) + 0.33 * Sqr(xargs[model_index_2_index(33)]), -0.5))
							* 2.0 * 0.33 * xargs[model_index_2_index(32)]
							;

						dg3dx33 = PCoef * std::pow(g3, PCoef - 1)
							* (2.0 + FLaplassInverse * 0.5 * std::pow(0.75  * Sqr(xargs[model_index_2_index(31)]) + 0.33 * Sqr(xargs[model_index_2_index(32)]) + 0.33 * Sqr(xargs[model_index_2_index(33)]), -0.5))
							* 2.0 * 0.33 * xargs[model_index_2_index(33)]
							;
					}


					if (g9 > 0.0) {
						dg9dx31 = PCoef * std::pow(g9, PCoef - 1)
							* (4.0 + FLaplassInverse * 0.5 * std::pow(1.33  * Sqr(xargs[model_index_2_index(31)]) + 0.33 * Sqr(xargs[model_index_2_index(32)]) + 0.33 * Sqr(xargs[model_index_2_index(33)]), -0.5))
							* 2.0 * 1.33 * xargs[model_index_2_index(31)]
							;
						dg9dx32 = PCoef * std::pow(g9, PCoef - 1)
							* (4.0 + FLaplassInverse * 0.5 * std::pow(1.33  * Sqr(xargs[model_index_2_index(31)]) + 0.33 * Sqr(xargs[model_index_2_index(32)]) + 0.33 * Sqr(xargs[model_index_2_index(33)]), -0.5))
							* 2.0 * 0.33 * xargs[model_index_2_index(32)]
							;

						dg9dx33 = PCoef * std::pow(g9, PCoef - 1)
							* (7.0 + FLaplassInverse * 0.5 * std::pow(1.33  * Sqr(xargs[model_index_2_index(31)]) + 0.33 * Sqr(xargs[model_index_2_index(32)]) + 0.33 * Sqr(xargs[model_index_2_index(33)]), -0.5))
							* 2.0 * 0.33 * xargs[model_index_2_index(33)]
							;
					}

					

					if (g4 > 0.0) {
						dg4dx11 = -2.0 * g4;
						dg4dx21 = -2.0 * g4;
						dg4dx31 = -2.0 * g4;
					}

					if (g5 > 0.0) {
						dg5dx12 = -2.0 * g5;
						dg5dx22 = -2.0 * g5;
						dg5dx32 = -2.0 * g5;
					}

					if (g6 > 0.0) {
						dg6dx13 = -2.0 * g6;
						dg6dx23 = -2.0 * g6;
						dg6dx33 = -2.0 * g6;
					}

					ValueType dQdx11 = 3.0 + sC_k * (dg1dx11 + dg7dx11 + dg4dx11);
					ValueType dQdx12 = 9.0 + sC_k * (dg1dx12 + dg7dx12 + dg5dx12);
					ValueType dQdx13 = 5.0 + sC_k * (dg1dx13 + dg7dx13 + dg6dx13);

					ValueType dQdx21 = 3.0 + sC_k * (dg2dx21 + dg8dx21 + dg4dx21);
					ValueType dQdx22 = 6.0 + sC_k * (dg2dx22 + dg8dx22 + dg5dx22);
					ValueType dQdx23 = 8.0 + sC_k * (dg2dx23 + dg8dx23 + dg6dx23 );

					ValueType dQdx31 = 8.0 + sC_k * (dg3dx31 + dg9dx31 + dg4dx31);
					ValueType dQdx32 = 2.0 + sC_k * (dg3dx32 + dg9dx32 + dg5dx32);
					ValueType dQdx33 = 5.0 + sC_k * (dg3dx33 + dg9dx33 + dg6dx33);

					/**
					{ 11, 0 },
					{ 12, 1 },
					{ 13, 2 },
					{ 21, 3 },
					{ 22, 4 },
					{ 23, 5 },
					{ 31, 6 },
					{ 32, 7 },
					{ 33, 8 }
					 */
					return { dQdx11, dQdx12, dQdx13, dQdx21, dQdx22, dQdx23, dQdx31, dQdx32, dQdx33 };
				}

				static VectorT evaluate(const VectorT& x0) {
					ThisT::sC_k = DefaultC;
					VectorT xArgs = x0;
					// prepare new penalty function

					using GradientDescent = StepSplitGradientDescent<ThisT>;
					//using GradientDescent = ConstStepGradientDescent<ThisT>;
					IndexType idx = 0;
					ValueType l = GradientDescent::Lambda;

					for (; idx < MaxPIterations; idx++) {
						IndexType it = 0;

						// find min( F(x, rk) )
						VectorT xOptLoc = GradientDescent::calculate(xArgs, l, it);
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

				static ValueType G1(const VectorT& xargs) {
					return  1.5 * xargs[model_index_2_index(11)] + 0.75 * xargs[model_index_2_index(12)] + 2.5 * xargs[model_index_2_index(13)] 
						+ FLaplassInverse * sqrt(0.083 * Sqr(xargs[model_index_2_index(11)]) + 0.0208 * Sqr(xargs[model_index_2_index(12)]) + 0.083 * Sqr(xargs[model_index_2_index(13)])) - Resource1;
				}

				static ValueType G2(const VectorT& xargs) {
					return  2.0 * xargs[model_index_2_index(21)] + 1.25 * xargs[model_index_2_index(22)] + 4.0 * xargs[model_index_2_index(23)]
						+ FLaplassInverse * sqrt(0.33 * Sqr(xargs[model_index_2_index(21)]) + 0.0208 * Sqr(xargs[model_index_2_index(22)]) + 0.33 * Sqr(xargs[model_index_2_index(23)])) - Resource2;
				}

				static ValueType G3(const VectorT& xargs) {
					return  2.5 * xargs[model_index_2_index(31)] + 2.0 * xargs[model_index_2_index(32)] + 2.0 * xargs[model_index_2_index(33)]
						+ FLaplassInverse * sqrt(0.75 * Sqr(xargs[model_index_2_index(31)]) + 0.33 * Sqr(xargs[model_index_2_index(32)]) + 0.33 * Sqr(xargs[model_index_2_index(33)])) - Resource3;
				}

				static ValueType G4(const VectorT& xargs) {
					return ASum - xargs[model_index_2_index(11)] - xargs[model_index_2_index(21)] - xargs[model_index_2_index(31)];
				}

				static ValueType G5(const VectorT& xargs) {
					return BSum - xargs[model_index_2_index(12)] - xargs[model_index_2_index(22)] - xargs[model_index_2_index(32)];
				}

				static ValueType G6(const VectorT& xargs) {
					return CSum - xargs[model_index_2_index(13)] - xargs[model_index_2_index(23)] - xargs[model_index_2_index(33)];
				}

				static ValueType G7(const VectorT& xargs) {
					return  3.0 * xargs[model_index_2_index(11)] + 3.0 * xargs[model_index_2_index(12)] + 3.0 * xargs[model_index_2_index(13)]
						+ FLaplassInverse * sqrt(0.33 * Sqr(xargs[model_index_2_index(11)]) + 0.33 * Sqr(xargs[model_index_2_index(12)]) + 0.33 * Sqr(xargs[model_index_2_index(13)])) - Resource12;
				}

				static ValueType G8(const VectorT& xargs) {
					return  5.0 * xargs[model_index_2_index(21)] + 1.5 * xargs[model_index_2_index(22)] + 5.0 * xargs[model_index_2_index(23)]
						+ FLaplassInverse * sqrt(1.33 * Sqr(xargs[model_index_2_index(21)]) + 0.083 * Sqr(xargs[model_index_2_index(22)]) + 0.33 * Sqr(xargs[model_index_2_index(23)])) - Resource22;
				}

				static ValueType G9(const VectorT& xargs) {
					return  4.0 * xargs[model_index_2_index(31)] + 4.0 * xargs[model_index_2_index(32)] + 7.0 * xargs[model_index_2_index(33)]
						+ FLaplassInverse * sqrt(1.33 * Sqr(xargs[model_index_2_index(31)]) + 0.33 * Sqr(xargs[model_index_2_index(32)]) + 0.33 * Sqr(xargs[model_index_2_index(33)])) - Resource32;
				}
		};

		template<
			typename ValueT,
			typename IndexType
		>
			typename ConstPenaltyFunction<ValueT, IndexType>::ValueType ConstPenaltyFunction<ValueT, IndexType>::sC_k = 0.0f;
	}// namespace const_impl
}// namespace tpr

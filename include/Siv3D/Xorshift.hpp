﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <cassert>
# include <array>
# include "Fwd.hpp"
# include "Number.hpp"
# include "HardwareRNG.hpp"

namespace s3d
{
	/// <summary>
	/// SplitMix64 / Pseudo random number generator
	/// Result: 64-bit value
	/// Period: 2^64
	/// Size: 8 bytes
	/// </summary>
	class SplitMix64
	{
	private:

		uint64 x;

	public:

		/// <summary>
		/// 生成される整数値の型
		/// The integral type generated by the engine
		/// </summary>
		using result_type = uint64;

		/// <summary>
		/// 乱数エンジンを作成し、内部状態を初期化します。
		/// Constructs the engine and initializes the state.
		/// </summary>
		/// <param name="seed">
		/// 内部状態の初期化に使われるシード値
		/// seed value to use in the initialization of the internal state
		/// </param>
		explicit SplitMix64(uint64 seed) noexcept
			: x(seed) {}

		/// <summary>
		/// 乱数を生成します。
		/// Generates a pseudo-random value.
		/// </summary>
		/// <returns>
		/// 生成された乱数
		/// A generated pseudo-random value
		/// </returns>
		result_type next() noexcept
		{
			uint64 z = (x += 0x9e3779b97f4a7c15);
			z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
			z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
			return z ^ (z >> 31);
		}
	};

	/// <summary>
	/// xorshift128+ / Pseudo random number generator
	/// Result: 64-bit value
	/// Period: 2^128-1
	/// Size: 16 bytes
	/// </summary>
	class Xorshift128Plus
	{
	private:

		std::array<uint64, 2> s;

	public:

		/// <summary>
		/// 生成される整数値の型
		/// The integral type generated by the engine
		/// </summary>
		using result_type = uint64;

		/// <summary>
		/// 乱数エンジンを作成し、内部状態を非決定的な乱数で初期化します。
		/// Constructs the engine and initializes the state with non-deterministic random numbers
		/// </summary>
		Xorshift128Plus()
		{
			HardwareRNG rng;
			std::uniform_int_distribution<uint64> dist(Smallest<uint64>(), Largest<uint64>());
			for (auto& value : s)
			{
				value = dist(rng);
			}
		}

		/// <summary>
		/// 乱数エンジンを作成し、内部状態を初期化します。
		/// Constructs the engine and initializes the state.
		/// </summary>
		/// <param name="seed">
		/// 内部状態の初期化に使われるシード値
		/// seed value to use in the initialization of the internal state
		/// </param>
		explicit Xorshift128Plus(const uint64 seed) noexcept
		{
			this->seed(seed);
		}

		/// <summary>
		/// 乱数エンジンを作成し、内部状態を初期化します。
		/// Constructs the engine and initializes the state.
		/// </summary>
		/// <param name="seed1">
		/// 内部状態の初期化に使われるシード値
		/// seed value to use in the initialization of the internal state
		/// </param>
		/// <param name="seed2">
		/// 内部状態の初期化に使われるシード値
		/// seed value to use in the initialization of the internal state
		/// </param>
		Xorshift128Plus(const uint64 seed0, const uint64 seed1) noexcept
		{
			this->seed(seed0, seed1);
		}

		/// <summary>
		/// 乱数エンジンを作成し、内部状態を初期化します。
		/// Constructs the engine and initializes the state.
		/// </summary>
		/// <param name="seeds">
		/// 内部状態の初期化に使われるシード値
		/// seed values to use in the initialization of the internal state
		/// </param>
		Xorshift128Plus(const std::array<uint64, 2>& seeds) noexcept
		{
			this->seed(seeds);
		}

		/// <summary>
		/// 新しいシード値で乱数エンジンの内部状態を再初期化します。
		/// Reinitializes the internal state of the random-number engine using a new seed value.
		/// </summary>
		/// <param name="seed">
		/// 内部状態の初期化に使われるシード値
		/// seed value to use in the initialization of the internal state
		/// </param>
		void seed(const uint64 seed) noexcept
		{
			SplitMix64 splitmix64(seed);

			for (auto& value : s)
			{
				value = splitmix64.next();
			}
		}

		/// <summary>
		/// 新しいシード値で乱数エンジンの内部状態を再初期化します。
		/// Reinitializes the internal state of the random-number engine using new seed values.
		/// </summary>
		/// <param name="seed1">
		/// 内部状態の初期化に使われるシード値
		/// seed value to use in the initialization of the internal state
		/// </param>
		/// <param name="seed2">
		/// 内部状態の初期化に使われるシード値
		/// seed value to use in the initialization of the internal state
		/// </param>
		void seed(const uint64 seed0, const uint64 seed1) noexcept
		{
			if (seed0 == 0 || seed1 == 0)
			{
				return seed(0);
			}

			s[0] = seed0;
			s[1] = seed1;
		}

		/// <summary>
		/// 新しいシード値で乱数エンジンの内部状態を再初期化します。
		/// Reinitializes the internal state of the random-number engine using new seed values.
		/// </summary>
		/// <param name="seeds">
		/// 内部状態の初期化に使われるシード値
		/// seed values to use in the initialization of the internal state
		/// </param>
		void seed(const std::array<uint64, 2>& seeds) noexcept
		{
			if (seeds[0] == 0 || seeds[1] == 0)
			{
				return seed(0);
			}

			s = seeds;
		}

		/// <summary>
		/// 生成される乱数の最小値を返します。
		/// Returns the minimum value potentially generated by the random-number engine
		/// </summary>
		/// <returns>
		/// 生成される乱数の最小値
		/// The minimum potentially generated value
		/// </returns>
		[[nodiscard]] static constexpr uint64 min()
		{
			return Smallest<uint64>();
		}

		/// <summary>
		/// 生成される乱数の最大値を返します。
		/// Returns the maximum value potentially generated by the random-number engine.
		/// </summary>
		/// <returns>
		/// 生成される乱数の最大値
		/// The maximum potentially generated value
		/// </returns>
		[[nodiscard]] static constexpr uint64 max()
		{
			return Largest<uint64>();
		}

		/// <summary>
		/// 乱数を生成します。
		/// Generates a pseudo-random value.
		/// </summary>
		/// <returns>
		/// 生成された乱数
		/// A generated pseudo-random value
		/// </returns>
		uint64 operator()() noexcept
		{
			uint64 s1 = s[0];
			const uint64 s0 = s[1];
			const uint64 result = s0 + s1;
			s[0] = s0;
			s1 ^= s1 << 23; // a
			s[1] = s1 ^ s0 ^ (s1 >> 18) ^ (s0 >> 5); // b, c
			return result;
		}

		/// <summary>
		/// 乱数エンジンの内部状態を返します。
		/// Returns the internal state of the random-number engine.
		/// </summary>
		/// <returns>
		/// 乱数エンジンの内部状態
		/// The internal state of the random-number engine
		/// </returns>
		[[nodiscard]] const std::array<uint64, 2>& currentState() const noexcept
		{
			return s;
		}
	};

	/// <summary>
	/// xoroshiro128+ / Pseudo random number generator
	/// Result: 64-bit value
	/// Period: 2^128-1
	/// Size: 16 bytes
	/// </summary>
	class Xoroshiro128Plus
	{
	private:

		std::array<uint64, 2> s;

		static constexpr uint64 rotl(const uint64_t x, int32 k)
		{
			return (x << k) | (x >> (64 - k));
		}

	public:

		/// <summary>
		/// 生成される整数値の型
		/// The integral type generated by the engine
		/// </summary>
		using result_type = uint64;

		/// <summary>
		/// 乱数エンジンを作成し、内部状態を非決定的な乱数で初期化します。
		/// Constructs the engine and initializes the state with non-deterministic random numbers
		/// </summary>
		Xoroshiro128Plus()
		{
			HardwareRNG rng;
			std::uniform_int_distribution<uint64> dist(Smallest<uint64>(), Largest<uint64>());
			for (auto& value : s)
			{
				value = dist(rng);
			}
		}

		/// <summary>
		/// 乱数エンジンを作成し、内部状態を初期化します。
		/// Constructs the engine and initializes the state.
		/// </summary>
		/// <param name="seed">
		/// 内部状態の初期化に使われるシード値
		/// seed value to use in the initialization of the internal state
		/// </param>
		explicit Xoroshiro128Plus(const uint64 seed) noexcept
		{
			this->seed(seed);
		}

		/// <summary>
		/// 乱数エンジンを作成し、内部状態を初期化します。
		/// Constructs the engine and initializes the state.
		/// </summary>
		/// <param name="seed1">
		/// 内部状態の初期化に使われるシード値
		/// seed value to use in the initialization of the internal state
		/// </param>
		/// <param name="seed2">
		/// 内部状態の初期化に使われるシード値
		/// seed value to use in the initialization of the internal state
		/// </param>
		Xoroshiro128Plus(const uint64 seed0, const uint64 seed1) noexcept
		{
			this->seed(seed0, seed1);
		}

		/// <summary>
		/// 乱数エンジンを作成し、内部状態を初期化します。
		/// Constructs the engine and initializes the state.
		/// </summary>
		/// <param name="seeds">
		/// 内部状態の初期化に使われるシード値
		/// seed values to use in the initialization of the internal state
		/// </param>
		Xoroshiro128Plus(const std::array<uint64, 2>& seeds) noexcept
		{
			this->seed(seeds);
		}

		/// <summary>
		/// 新しいシード値で乱数エンジンの内部状態を再初期化します。
		/// Reinitializes the internal state of the random-number engine using a new seed value.
		/// </summary>
		/// <param name="seed">
		/// 内部状態の初期化に使われるシード値
		/// seed value to use in the initialization of the internal state
		/// </param>
		void seed(const uint64 seed) noexcept
		{
			SplitMix64 splitmix64(seed);

			for (auto& value : s)
			{
				value = splitmix64.next();
			}
		}

		/// <summary>
		/// 新しいシード値で乱数エンジンの内部状態を再初期化します。
		/// Reinitializes the internal state of the random-number engine using new seed values.
		/// </summary>
		/// <param name="seed1">
		/// 内部状態の初期化に使われるシード値
		/// seed value to use in the initialization of the internal state
		/// </param>
		/// <param name="seed2">
		/// 内部状態の初期化に使われるシード値
		/// seed value to use in the initialization of the internal state
		/// </param>
		void seed(const uint64 seed0, const uint64 seed1) noexcept
		{
			if (seed0 == 0 || seed1 == 0)
			{
				return seed(0);
			}

			s[0] = seed0;
			s[1] = seed1;
		}

		/// <summary>
		/// 新しいシード値で乱数エンジンの内部状態を再初期化します。
		/// Reinitializes the internal state of the random-number engine using new seed values.
		/// </summary>
		/// <param name="seeds">
		/// 内部状態の初期化に使われるシード値
		/// seed values to use in the initialization of the internal state
		/// </param>
		void seed(const std::array<uint64, 2>& seeds) noexcept
		{
			if (seeds[0] == 0 || seeds[1] == 0)
			{
				return seed(0);
			}

			s = seeds;
		}

		/// <summary>
		/// 生成される乱数の最小値を返します。
		/// Returns the minimum value potentially generated by the random-number engine
		/// </summary>
		/// <returns>
		/// 生成される乱数の最小値
		/// The minimum potentially generated value
		/// </returns>
		[[nodiscard]] static constexpr uint64 min()
		{
			return Smallest<uint64>();
		}

		/// <summary>
		/// 生成される乱数の最大値を返します。
		/// Returns the maximum value potentially generated by the random-number engine.
		/// </summary>
		/// <returns>
		/// 生成される乱数の最大値
		/// The maximum potentially generated value
		/// </returns>
		[[nodiscard]] static constexpr uint64 max()
		{
			return Largest<uint64>();
		}

		/// <summary>
		/// 乱数を生成します。
		/// Generates a pseudo-random value.
		/// </summary>
		/// <returns>
		/// 生成された乱数
		/// A generated pseudo-random value
		/// </returns>
		uint64 operator()() noexcept
		{
			const uint64_t s0 = s[0];
			uint64_t s1 = s[1];
			const uint64_t result = s0 + s1;

			s1 ^= s0;
			s[0] = rotl(s0, 55) ^ s1 ^ (s1 << 14); // a, b
			s[1] = rotl(s1, 36); // c

			return result;
		}

		/// <summary>
		/// 乱数エンジンの内部状態を返します。
		/// Returns the internal state of the random-number engine.
		/// </summary>
		/// <returns>
		/// 乱数エンジンの内部状態
		/// The internal state of the random-number engine
		/// </returns>
		[[nodiscard]] const std::array<uint64, 2>& currentState() const noexcept
		{
			return s;
		}
	};

	/// <summary>
	/// xorshift1024*φ / Pseudo random number generator
	/// Result: 64-bit value
	/// Period: 2^1024-1
	/// Size: 132 bytes
	/// </summary>
	class Xorshift1024StarPhi
	{
	private:

		std::array<uint64, 16> s;

		int32 p = 0;

	public:

		/// <summary>
		/// 生成される整数値の型
		/// The integral type generated by the engine
		/// </summary>
		using result_type = uint64;

		/// <summary>
		/// 乱数エンジンを作成し、内部状態を非決定的な乱数で初期化します。
		/// Constructs the engine and initializes the state with non-deterministic random numbers
		/// </summary>
		Xorshift1024StarPhi()
		{
			HardwareRNG rng;
			std::uniform_int_distribution<uint64> dist(Smallest<uint64>(), Largest<uint64>());
			for (auto& value : s)
			{
				value = dist(rng);
			}
		}

		/// <summary>
		/// 乱数エンジンを作成し、内部状態を初期化します。
		/// Constructs the engine and initializes the state.
		/// </summary>
		/// <param name="seed">
		/// 内部状態の初期化に使われるシード値
		/// seed value to use in the initialization of the internal state
		/// </param>
		explicit Xorshift1024StarPhi(const uint64 seed) noexcept
		{
			this->seed(seed);
		}

		/// <summary>
		/// 乱数エンジンを作成し、内部状態を初期化します。
		/// Constructs the engine and initializes the state.
		/// </summary>
		/// <param name="seeds">
		/// 内部状態の初期化に使われるシード値
		/// seed values to use in the initialization of the internal state
		/// </param>
		explicit Xorshift1024StarPhi(const std::array<uint64, 16>& seeds) noexcept
		{
			this->seed(seeds);
		}

		/// <summary>
		/// 新しいシード値で乱数エンジンの内部状態を再初期化します。
		/// Reinitializes the internal state of the random-number engine using a new seed value
		/// </summary>
		/// <param name="seed">
		/// 内部状態の初期化に使われるシード値
		/// seed value to use in the initialization of the internal state
		/// </param>
		void seed(const uint64 seed) noexcept
		{
			SplitMix64 splitmix64(seed);

			for (auto& value : s)
			{
				value = splitmix64.next();
			}
		}

		/// <summary>
		/// 新しいシード値で乱数エンジンの内部状態を再初期化します。
		/// Reinitializes the internal state of the random-number engine using new seed values
		/// </summary>
		/// <param name="seeds">
		/// 内部状態の初期化に使われるシード値
		/// seed values to use in the initialization of the internal state
		/// </param>
		void seed(const std::array<uint64, 16>& seeds) noexcept
		{
			s = seeds;
		}

		/// <summary>
		/// 生成される乱数の最小値を返します。
		/// Returns the minimum value potentially generated by the random-number engine.
		/// </summary>
		/// <returns>
		/// 生成される乱数の最小値
		/// The minimum potentially generated value.
		/// </returns>
		[[nodiscard]] static constexpr uint64 min()
		{
			return Smallest<uint64>();
		}

		/// <summary>
		/// 生成される乱数の最大値を返します。
		/// Returns the maximum value potentially generated by the random-number engine.
		/// </summary>
		/// <returns>
		/// 生成される乱数の最大値
		/// The maximum potentially generated value
		/// </returns>
		[[nodiscard]] static constexpr uint64 max()
		{
			return Largest<uint64>();
		}

		/// <summary>
		/// 乱数を生成します。
		/// Generates a pseudo-random value.
		/// </summary>
		/// <returns>
		/// 生成された乱数
		/// A generated pseudo-random value
		/// </returns>
		uint64 operator()() noexcept
		{
			const uint64 s0 = s[p];
			uint64 s1 = s[p = (p + 1) & 15];
			s1 ^= s1 << 31; // a
			s[p] = s1 ^ s0 ^ (s1 >> 11) ^ (s0 >> 30); // b,c
			return s[p] * 0x9e3779b97f4a7c13;
		}

		/// <summary>
		/// 乱数エンジンの内部状態を返します。
		/// Returns the internal state of the random-number engine.
		/// </summary>
		/// <returns>
		/// 乱数エンジンの内部状態
		/// The internal state of the random-number engine
		/// </returns>
		[[nodiscard]] const std::array<uint64, 16>& currentState() const noexcept
		{
			return s;
		}
	};
}

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
# include "Fwd.hpp"
# include "PointVector.hpp"
# include "LineString.hpp"
# include "Geometry2D.hpp"

namespace s3d
{
	/// <summary>
	/// 2 次ベジェ曲線
	/// </summary>
	struct Bezier2
	{
		Vec2 p0, p1, p2;

		Bezier2() = default;

		constexpr Bezier2(const Vec2& _p0, const Vec2& _p1, const Vec2& _p2) noexcept
			: p0(_p0)
			, p1(_p1)
			, p2(_p2) {}

		[[nodiscard]] constexpr Vec2 getPos(const double t) const noexcept
		{
			return (1 - t) * (1 - t)* p0 + 2 * (1 - t) * t * p1 + t * t * p2;
		}

		[[nodiscard]] Vec2 getTangent(const double t) const noexcept
		{
			return ((p1 - p0) * 2 * (1 - t) + (p2 - p1) * (2 * t)).normalized();
		}

		[[nodiscard]] LineString getLineString(const uint32 quality = 24) const
		{
			return getLineString(0.0, 1.0, quality);
		}

		[[nodiscard]] LineString getLineString(double start, double end, uint32 quality = 24) const;

		template <class Shape2DType>
		[[nodiscard]] bool intersects(const Shape2DType& shape) const
		{
			return Geometry2D::Intersect(*this, shape);
		}

		template <class Shape2DType>
		[[nodiscard]] Optional<Array<Vec2>> intersectsAt(const Shape2DType& shape) const
		{
			return Geometry2D::IntersectAt(*this, shape);
		}

		// paint, overpaint

		const Bezier2& draw(const ColorF& color = Palette::White) const
		{
			return draw(1.0, color);
		}

		const Bezier2& draw(double thickness, const ColorF& color = Palette::White) const;
	};

	struct Bezier2Path
	{
	private:

		Vec2 m_v0, m_v1;

		double m_t = 0.0;

	public:

		Bezier2Path() = default;

		explicit constexpr Bezier2Path(const Bezier2& bezier) noexcept
			: m_v0(2 * bezier.p0 - 4 * bezier.p1 + 2 * bezier.p2)
			, m_v1(-2 * bezier.p0 + 2 * bezier.p1) {}

		constexpr void setT(const double t) noexcept
		{
			m_t = t;
		}

		[[nodiscard]] constexpr double getT() const noexcept
		{
			return m_t;
		}

		double advance(const double distance, const int32 quality = 8) noexcept
		{
			for (int32 i = 0; i < quality; ++i)
			{
				m_t = m_t + (distance / quality) / (m_t * m_v0 + m_v1).length();
			}

			return m_t;
		}
	};
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const Bezier2& value);

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Bezier2& value)
	{
		return output << CharType('(')
			<< value.p0 << CharType(',') << CharType(' ')
			<< value.p1 << CharType(',') << CharType(' ')
			<< value.p2 << CharType(')');
	}

	template <class CharType>
	inline std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Bezier2& value)
	{
		CharType unused;
		return input >> unused
			>> value.p0 >> unused
			>> value.p1 >> unused
			>> value.p2 >> unused;
	}
}

//////////////////////////////////////////////////
//
//	Hash
//
//////////////////////////////////////////////////

namespace std
{
	template <>
	struct hash<s3d::Bezier2>
	{
		[[nodiscard]] size_t operator ()(const s3d::Bezier2& value) const noexcept
		{
			return s3d::Hash::FNV1a(value);
		}
	};
}

//////////////////////////////////////////////////
//
//	fmt
//
//////////////////////////////////////////////////

namespace fmt
{
	template <>
	struct formatter<s3d::Bezier2, s3d::char32>
	{
		s3d::String tag;

		template <class ParseContext>
		auto parse(ParseContext& ctx)
		{
			return s3d::detail::GetFmtTag(tag, ctx);
		}

		template <class Context>
		auto format(const s3d::Bezier2& value, Context& ctx)
		{
			const s3d::String fmt = s3d::detail::MakeFmtArg(
				U"({:", tag, U"}, {:", tag, U"}, {:", tag, U"})"
			);

			return format_to(ctx.begin(), wstring_view(fmt.data(), fmt.size()), value.p0, value.p1, value.p2);
		}
	};
}

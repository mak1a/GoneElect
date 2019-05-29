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
# include <memory>
# include "Fwd.hpp"
# include "AssetHandle.hpp"
# include "Array.hpp"
# include "String.hpp"
# include "Color.hpp"
# include "PointVector.hpp"
# include "Rectangle.hpp"
# include "TextureRegion.hpp"
# include "NamedParameter.hpp"
# include "OutlineGlyph.hpp"

namespace s3d
{
	enum class Typeface
	{
		Thin,

		Light,

		Regular,

		Medium,

		Bold,

		Heavy,

		Black,

		Default = Regular,
	};

	/// <summary>
	///	フォントスタイルのフラグ
	/// </summary>
	enum class FontStyle : uint32
	{
		Default = 0x0,

		Bold = 0x01,

		Italic = 0x02,

		BoldItalic = Bold | Italic,

		Bitmap = 0x04,

		BoldBitmap = Bold | Bitmap,

		ItalicBitmap = Italic | Bitmap,

		BoldItalicBitmap = Bold | Italic | Bitmap,
	};

	struct Glyph
	{
		TextureRegion texture;

		char32 codePoint = U'\0';

		Point offset = Point(0, 0);

		int32 bearingY = 0;

		int32 xAdvance = 0;

		int32 yAdvance = 0;

		int32 index = 0;

		Glyph()
		{
			texture.uvRect = FloatRect(0.0f, 0.0f, 0.0f, 0.0f);
			
			texture.size.set(0.0f, 0.0f);
		}
	};
	
	class Font
	{
	protected:

		class Handle {};

		using FontHandle = AssetHandle<Handle>;
		
		friend FontHandle::~AssetHandle();

		std::shared_ptr<FontHandle> m_handle;

	public:

		using IDType = FontHandle::IDWrapperType;

		Font();

		explicit Font(int32 fontSize, Typeface typeface = Typeface::Default, FontStyle style = FontStyle::Default);

		Font(int32 fontSize, const FilePath& path, FontStyle style = FontStyle::Default);

		virtual ~Font();

		void release();

		[[nodiscard]] bool isEmpty() const;

		[[nodiscard]] explicit operator bool() const
		{
			return !isEmpty();
		}

		[[nodiscard]] IDType id() const;

		[[nodiscard]] bool operator ==(const Font& font) const;

		[[nodiscard]] bool operator !=(const Font& font) const;

		[[nodiscard]] const String& familyName() const;

		[[nodiscard]] const String& styleName() const;

		[[nodiscard]] int32 fontSize() const;

		[[nodiscard]] int32 ascent() const;

		[[nodiscard]] int32 descent() const;

		[[nodiscard]] int32 height() const;

		[[nodiscard]] Glyph getGlyph(char32 codePoint) const;

		[[nodiscard]] Array<Glyph> getGlyphs(const String& text) const;

		[[nodiscard]] Array<Glyph> getVerticalGlyphs(const String& text) const;

		[[nodiscard]] OutlineGlyph getOutlineGlyph(char32 codePoint) const;

		/// <summary>
		/// 描画するテキストを作成します。
		/// </summary>
		/// <param name="text">
		/// 文字列
		/// </param>
		/// <returns>
		/// DrawableString
		/// </returns>
		[[nodiscard]] DrawableText operator()(const String& text) const;

		/// <summary>
		/// 描画するテキストを作成します。
		/// </summary>
		/// <param name="text">
		/// 文字列
		/// </param>
		/// <returns>
		/// DrawableString
		/// </returns>
		[[nodiscard]] DrawableText operator()(String&& text) const;

		/// <summary>
		/// 描画するテキストを作成します。
		/// </summary>
		/// <param name="args">
		/// 文字列に変換するデータ
		/// </param>
		/// <returns>
		/// DrawableString
		/// </returns>
		template <class ... Args>
		[[nodiscard]] inline DrawableText operator()(const Args& ... args) const;
	};

	class GlyphIterator
	{
	private:

		Font m_font;

		String::const_iterator m_iterator;

		int32 m_index = 0;

	public:

		GlyphIterator() = default;

		GlyphIterator(const GlyphIterator&) = default;

		GlyphIterator(const Font& font, String::const_iterator it, int32 index)
			: m_font(font)
			, m_iterator(it)
			, m_index(index) {}

		GlyphIterator& operator =(const GlyphIterator&) = default;

		GlyphIterator& operator ++()
		{
			++m_iterator;

			++m_index;

			return *this;
		}

		[[nodiscard]] Glyph operator *() const
		{
			Glyph glyph = m_font.getGlyph(*m_iterator);

			glyph.index = m_index;

			return glyph;
		}

		[[nodiscard]] bool operator ==(const GlyphIterator& other) const
		{
			return m_iterator == other.m_iterator;
		}
		
		[[nodiscard]] bool operator !=(const GlyphIterator& other) const
		{
			return m_iterator != other.m_iterator;
		}
	};

	using FontID = Font::IDType;

	struct DrawableText
	{
		Font font;

		String text;

		DrawableText() = default;

		DrawableText(const Font& _font, const String& _text)
			: font(_font)
			, text(_text) {}

		DrawableText(const Font& _font, String&& _text)
			: font(_font)
			, text(std::move(_text)) {}

		[[nodiscard]] GlyphIterator begin() const
		{
			return GlyphIterator(font, text.begin(), 0);
		}

		[[nodiscard]] GlyphIterator end() const
		{
			return GlyphIterator(font, text.end(), static_cast<int32>(text.size()));
		}

		[[nodiscard]] RectF boundingRect(double x, double y) const
		{
			return boundingRect(Vec2(x, y));
		}

		[[nodiscard]] RectF boundingRect(const Vec2& pos = Vec2(0, 0)) const;

		[[nodiscard]] RectF boundingRect(Arg::topLeft_<Vec2> topLeft) const
		{
			return boundingRect(*topLeft);
		}

		[[nodiscard]] RectF boundingRect(Arg::topRight_<Vec2> topRight) const
		{
			return boundingRect(topRight->movedBy(-region().w, 0));
		}

		[[nodiscard]] RectF boundingRect(Arg::bottomLeft_<Vec2> bottomLeft) const
		{
			return boundingRect(bottomLeft->movedBy(0, -region().h));
		}

		[[nodiscard]] RectF boundingRect(Arg::bottomRight_<Vec2> bottomRight) const
		{
			return boundingRect(bottomRight->movedBy(-region().size));
		}

		[[nodiscard]] RectF boundingRect(Arg::topCenter_<Vec2> topCenter) const
		{
			return boundingRect(topCenter->movedBy(-region().w * 0.5, 0));
		}

		[[nodiscard]] RectF boundingRect(Arg::bottomCenter_<Vec2> bottomCenter) const
		{
			return boundingRect(bottomCenter->movedBy(-region().w * 0.5, -region().h));
		}

		[[nodiscard]] RectF boundingRect(Arg::leftCenter_<Vec2> leftCenter) const
		{
			return boundingRect(leftCenter->movedBy(0, -region().h * 0.5));
		}

		[[nodiscard]] RectF boundingRect(Arg::rightCenter_<Vec2> rightCenter) const
		{
			return boundingRect(rightCenter->movedBy(-region().w, -region().h * 0.5));
		}

		[[nodiscard]] RectF boundingRect(Arg::center_<Vec2> center) const
		{
			return boundingRectAt(*center);
		}

		[[nodiscard]] RectF boundingRectAt(double x, double y) const
		{
			return boundingRectAt(Vec2(x, y));
		}

		[[nodiscard]] RectF boundingRectAt(const Vec2& pos = Vec2(0, 0)) const
		{
			const RectF rect = boundingRect();

			return rect.movedBy(pos - rect.center());
		}

		[[nodiscard]] RectF region(double x, double y) const
		{
			return region(Vec2(x, y));
		}

		[[nodiscard]] Rect region(const Point& pos = Point(0, 0)) const;

		[[nodiscard]] RectF region(const Vec2& pos) const;

		[[nodiscard]] RectF region(Arg::topLeft_<Vec2> topLeft) const
		{
			return region(*topLeft);
		}

		[[nodiscard]] RectF region(Arg::topRight_<Vec2> topRight) const
		{
			return region(topRight->movedBy(-region().w, 0));
		}

		[[nodiscard]] RectF region(Arg::bottomLeft_<Vec2> bottomLeft) const
		{
			return region(bottomLeft->movedBy(0, -region().h));
		}

		[[nodiscard]] RectF region(Arg::bottomRight_<Vec2> bottomRight) const
		{
			return region(bottomRight->movedBy(-region().size));
		}

		[[nodiscard]] RectF region(Arg::topCenter_<Vec2> topCenter) const
		{
			return region(topCenter->movedBy(-region().w * 0.5, 0));
		}

		[[nodiscard]] RectF region(Arg::bottomCenter_<Vec2> bottomCenter) const
		{
			return region(bottomCenter->movedBy(-region().w * 0.5, -region().h));
		}

		[[nodiscard]] RectF region(Arg::leftCenter_<Vec2> leftCenter) const
		{
			return region(leftCenter->movedBy(0, -region().h * 0.5));
		}

		[[nodiscard]] RectF region(Arg::rightCenter_<Vec2> rightCenter) const
		{
			return region(rightCenter->movedBy(-region().w, -region().h * 0.5));
		}

		[[nodiscard]] RectF region(Arg::center_<Vec2> center) const
		{
			return regionAt(*center);
		}

		[[nodiscard]] RectF regionAt(double x, double y) const
		{
			return regionAt(Vec2(x, y));
		}

		[[nodiscard]] RectF regionAt(const Vec2& pos = Vec2(0, 0)) const
		{
			const RectF rect = region();

			return rect.movedBy(pos - rect.center());
		}

		[[nodiscard]] Array<int32> getXAdvances() const;

		RectF draw(double x, double y, const ColorF& color = Palette::White) const
		{
			return draw(Vec2(x, y), color);
		}

		RectF draw(const Vec2& pos = Vec2(0, 0), const ColorF& color = Palette::White) const;

		RectF draw(Arg::topLeft_<Vec2> topLeft, const ColorF& color = Palette::White) const
		{
			return draw(*topLeft, color);
		}

		RectF draw(Arg::topRight_<Vec2> topRight, const ColorF& color = Palette::White) const
		{
			return draw(topRight->movedBy(-region().w, 0), color);
		}

		RectF draw(Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& color = Palette::White) const
		{
			return draw(bottomLeft->movedBy(0, -region().h), color);
		}

		RectF draw(Arg::bottomRight_<Vec2> bottomRight, const ColorF& color = Palette::White) const
		{
			return draw(bottomRight->movedBy(-region().size), color);
		}

		RectF draw(Arg::topCenter_<Vec2> topCenter, const ColorF& color = Palette::White) const
		{
			return draw(topCenter->movedBy(-region().w * 0.5, 0), color);
		}

		RectF draw(Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& color = Palette::White) const
		{
			return draw(bottomCenter->movedBy(-region().w * 0.5, -region().h), color);
		}

		RectF draw(Arg::leftCenter_<Vec2> leftCenter, const ColorF& color = Palette::White) const
		{
			return draw(leftCenter->movedBy(0, -region().h * 0.5), color);
		}

		RectF draw(Arg::rightCenter_<Vec2> rightCenter, const ColorF& color = Palette::White) const
		{
			return draw(rightCenter->movedBy(-region().w, -region().h * 0.5), color);
		}

		RectF draw(Arg::center_<Vec2> center, const ColorF& color = Palette::White) const
		{
			return drawAt(*center, color);
		}

		RectF drawAt(double x, double y, const ColorF& color = Palette::White) const
		{				
			return drawAt(Vec2(x, y), color);
		}

		RectF drawAt(const Vec2& pos = Vec2(0, 0), const ColorF& color = Palette::White) const
		{
			return draw(pos - region().center(), color);
		}

		RectF drawBase(double x, double y, const ColorF& color = Palette::White) const
		{
			return drawBase(Vec2(x, y), color);
		}

		RectF drawBase(const Vec2& pos = Vec2(0, 0), const ColorF& color = Palette::White) const
		{
			return draw(pos.movedBy(0, -font.ascent()), color);
		}

		RectF drawBase(Arg::left_<Vec2> left, const ColorF& color = Palette::White) const
		{
			return drawBase(*left, color);
		}

		RectF drawBase(Arg::right_<Vec2> right, const ColorF& color = Palette::White) const
		{
			return drawBase(right->movedBy(-region().w, 0), color);
		}

		RectF drawBase(Arg::center_<Vec2> center, const ColorF& color = Palette::White) const
		{
			return drawBase(center->movedBy(-region().w * 0.5, 0), color);
		}

		RectF drawBaseAt(double x, double y, const ColorF& color = Palette::White) const
		{
			return drawBaseAt(Vec2(x, y), color);
		}

		RectF drawBaseAt(const Vec2& pos = Vec2(0, 0), const ColorF& color = Palette::White) const
		{
			return drawBase(pos - region().center(), color);
		}

		bool draw(const RectF& area, const ColorF& color = Palette::White) const;

		Rect paint(Image& dst, int32 x, int32 y, const Color& color = Palette::White) const
		{
			return paint(dst, Point(x, y), color);
		}

		Rect paint(Image& dst, const Point& pos = Point(0, 0), const Color& color = Palette::White) const;

		RectF paintAt(Image& dst, int32 x, int32 y, const Color& color = Palette::White) const
		{
			return paintAt(dst, Point(x, y), color);
		}

		RectF paintAt(Image& dst, const Point& pos = Point(0, 0), const Color& color = Palette::White) const
		{
			return paint(dst, (pos - region().center()).asPoint(), color);
		}

		Rect overwrite(Image& dst, int32 x, int32 y, const Color& color = Palette::White) const
		{
			return overwrite(dst, Point(x, y), color);
		}

		Rect overwrite(Image& dst, const Point& pos = Point(0, 0), const Color& color = Palette::White) const;

		RectF overwriteAt(Image& dst, int32 x, int32 y, const Color& color = Palette::White) const
		{
			return overwriteAt(dst, Point(x, y), color);
		}

		RectF overwriteAt(Image& dst, const Point& pos = Point(0, 0), const Color& color = Palette::White) const
		{
			return overwrite(dst, (pos - region().center()).asPoint(), color);
		}
	};

	inline DrawableText Font::operator()(const String& text) const
	{
		return{ *this, text };
	}

	inline DrawableText Font::operator()(String&& text) const
	{
		return{ *this, std::move(text) };
	}

	template <class ... Args>
	inline DrawableText Font::operator()(const Args& ... args) const
	{
		return DrawableText(*this, Format(args...));
	}
}

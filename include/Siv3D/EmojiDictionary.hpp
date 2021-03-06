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
# include "String.hpp"

namespace s3d
{
	class EmojiDictionary
	{
	private:

		class CEmojiDictionary;

		std::shared_ptr<CEmojiDictionary> pImpl;

	public:

		EmojiDictionary();
	
		~EmojiDictionary();
		
		bool load(const FilePath& path);

		[[nodiscard]] size_t check(String::const_iterator it, const String::const_iterator& itEnd);

		void clear();
	};
}

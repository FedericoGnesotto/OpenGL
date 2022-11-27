#pragma once

#include <iostream>

namespace libgl
{
	class Bindable
	{
	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual ~Bindable() = default;
	};
}
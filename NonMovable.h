#pragma once

struct NonMovable
{
	NonMovable() = default;
	NonMovable& operator = (NonMovable&&) = delete;	// assignment operator (delete default move operation)
	NonMovable(NonMovable&&) = delete;				// copy constructor
};
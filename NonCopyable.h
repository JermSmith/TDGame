#pragma once

struct NonCopyable
{
	NonCopyable() = default;
	NonCopyable& operator = (const NonCopyable&) = delete;	// assignment operator (delete default copy operation)
	NonCopyable(const NonCopyable&) = delete;				// copy constructor
};
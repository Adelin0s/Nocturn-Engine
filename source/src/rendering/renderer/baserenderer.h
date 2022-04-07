#pragma once

class BaseRenderer
{
public:
	BaseRenderer( ) noexcept			 = default;
	BaseRenderer( const BaseRenderer & ) = delete;
	BaseRenderer( BaseRenderer && )		 = delete;

	BaseRenderer &operator=( const BaseRenderer & ) = delete;
	BaseRenderer &operator=( BaseRenderer && ) = delete;

	~BaseRenderer( ) noexcept = default;
};

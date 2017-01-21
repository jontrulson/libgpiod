/*
 * C++ bindings for libgpiod.
 *
 * Copyright (C) 2017 Bartosz Golaszewski <bartekgola@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 */

#ifndef __GPIOD_CXX_ERROR_HPP__
#define __GPIOD_CXX_ERROR_HPP__

#include "gpiodcxx-internal.hpp"

#include <gpiod.h>

#include <system_error>

namespace gpiod {

class gpio_error_category : public std::error_category
{
public:

	const char * name(void) const noexcept override;

	std::string message(int ec) const override;

	std::error_condition
	default_error_condition(int ec) const noexcept override;
};

class GPIODCXX_API gpio_error : public std::system_error
{
public:

	gpio_error(void);
};

} /* namespace gpiod */

#endif /* __GPIOD_CXX_ERROR_HPP__ */

/*
 * C++ bindings for libgpiod.
 *
 * Copyright (C) 2017 Bartosz Golaszewski <bartekgola@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 */

#include "error.hpp"

namespace gpiod {

const char * gpio_error_category::name(void) const noexcept
{
	return "gpio";
}

std::string gpio_error_category::message(int ec) const
{
	return ::gpiod_strerror(ec);
}

std::error_condition
gpio_error_category::default_error_condition(int ec) const noexcept
{
	return std::error_condition(ec, *this);
}

gpio_error::gpio_error(void)
	: std::system_error(std::error_code(::gpiod_errno(),
					    gpiod::gpio_error_category()))
{

}

} /* namespace gpiod */

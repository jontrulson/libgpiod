/*
 * C++ bindings for libgpiod.
 *
 * Copyright (C) 2017 Bartosz Golaszewski <bartekgola@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 */

#include <cstdlib>
#include <iostream>

#include "../error.hpp"

int main(int argc, char **argv)
{
	try {
		throw gpiod::gpio_error();
	} catch (const std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}

	return EXIT_SUCCESS;
}

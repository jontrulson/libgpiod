/*
 * C++ bindings for libgpiod.
 *
 * Copyright (C) 2017 Bartosz Golaszewski <bartekgola@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 */

#ifndef __GPIOD_CXX_LINE_HPP__
#define __GPIOD_CXX_LINE_HPP__

#include "gpiodcxx-internal.hpp"
#include "line_event.hpp"

#include <string>

namespace gpiod {

class chip;

class line
{
public:

	unsigned int offset(void) throw();

	const char * name(void) throw();

	const char * consumer(void) throw();

	bool input(void) throw();

	bool output(void) throw();

	bool active_low(void) throw();

	bool used_by_kernel(void) throw();

	bool open_drain(void) throw();

	bool open_source(void) throw();

	void update(void);

	bool needs_update(void) throw();

	void request_input(const std::string& consumer,
			   bool active_low = false, int flags = 0);

	void request_output(const std::string& consumer, int default_val = 0,
			    bool active_low = false, int flags = 0);

	int get_value(void);

	void set_value(int val);

	void request_event_rising(const std::string& consumer,
				  bool active_low = false, int flags = 0);

	void request_event_falling(const std::string& consumer,
				   bool active_low = false, int flags = 0);

	void request_event_both(const std::string& consumer,
				bool active_low = false, int flags = 0);

	bool event_wait(unsigned int sec, unsigned int nsec);

	void event_read(gpiod::line_event& ev);

	int get_fd(void);

	void release(void);

	bool reserved(void);

	bool monitored(void);

	bool free(void);

	gpiod::chip * chip(void);

	enum {
		FLAG_OPEN_DRAIN = GPIOD_BIT(0),
		FLAG_OPEN_SOURCE = GPIOD_BIT(1),
	};

private:

	/* Can only be instantiated by gpiod::chip. */
	line(::gpiod_line *line, gpiod::chip *chip) throw();

	void request(int direction, const std::string& consumer,
		     int default_val, bool active_low, int flags);

	void request_event(int event_type, const std::string& consumer,
			   bool active_low, int flags);

	static void throw_from_gpiod_errno(void);

	::gpiod_line *_M_line;
	gpiod::chip *_M_chip;

	friend gpiod::chip;
};

} /* namespace gpiod */

#endif /* __GPIOD_CXX_LINE_HPP__ */

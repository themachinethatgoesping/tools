
// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
// Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief some macros to easily implement common enum capabilities for nanobind classes
 *
 * @authors Peter Urban
 */

#pragma once

// -- c++ library headers
#include <iostream>
#include <memory>
#include <streambuf>
#include <string>

// -- include nanobind headers
#include <nanobind/nanobind.h>


namespace themachinethatgoesping {
namespace tools {
namespace nanobind_helper {

// Custom streambuf that writes to Python sys.stdout
class scoped_python_streambuf : public std::streambuf
{
  private:
    nanobind::object  py_write;
    nanobind::object  py_flush;
    std::string buffer;

  public:
    scoped_python_streambuf(nanobind::object py_stream)
    {
        py_write = py_stream.attr("write");
        py_flush = py_stream.attr("flush");
    }

  protected:
    virtual int_type overflow(int_type c) override
    {
        if (c != EOF)
        {
            buffer += static_cast<char>(c);
            if (c == '\n' || c == '\r')
            {
                py_write(buffer);
                py_flush();
                buffer.clear();
            }
        }
        return c;
    }

    virtual int sync() override
    {
        if (!buffer.empty())
        {
            py_write(buffer);
            py_flush();
            buffer.clear();
        }
        return 0;
    }
};

// scoped_ostream_redirect class to mimic pybind11's scoped_scoped_ostream_redirect
class scoped_ostream_redirect
{
  private:
    std::streambuf*                   orig_cout_buf;
    std::streambuf*                   orig_cerr_buf;
    std::unique_ptr<scoped_python_streambuf> cout_buf;
    std::unique_ptr<scoped_python_streambuf> cerr_buf;

  public:
    scoped_ostream_redirect()
    {
        // Get Python's sys.stdout and sys.stderr
        nanobind::object sys       = nanobind::module_::import_("sys");
        nanobind::object py_stdout = sys.attr("stdout");
        nanobind::object py_stderr = sys.attr("stderr");

        // Save original buffers
        orig_cout_buf = std::cout.rdbuf();
        orig_cerr_buf = std::cerr.rdbuf();

        // Create custom buffers that write to Python
        cout_buf = std::make_unique<scoped_python_streambuf>(py_stdout);
        cerr_buf = std::make_unique<scoped_python_streambuf>(py_stderr);

        // Redirect C++ streams to Python
        std::cout.rdbuf(cout_buf.get());
        std::cerr.rdbuf(cerr_buf.get());
    }

    ~scoped_ostream_redirect()
    {
        // Flush any remaining data
        std::cout.flush();
        std::cerr.flush();

        // Restore original buffers
        std::cout.rdbuf(orig_cout_buf);
        std::cerr.rdbuf(orig_cerr_buf);
    }

    // call_guard requires operator() for function wrapping
    template<typename Func, typename... Args>
    auto operator()(Func&& func, Args&&... args) -> decltype(func(std::forward<Args>(args)...))
    {
        return func(std::forward<Args>(args)...);
    }
};

} // namespace nanobind_helper
} // namespace tools
} // namespace themachinethatgoesping
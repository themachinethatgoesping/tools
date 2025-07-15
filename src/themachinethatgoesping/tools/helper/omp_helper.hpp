// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0
#pragma once

/* generated doc strings */
#include ".docstrings/omp_helper.doc.hpp"

#if defined(_OPENMP)
    // only include OpenMP header if it is defined
    #include <omp.h>
#else
    // If OpenMP is not defined, provide fallback functions that simulate
    // single-threaded behavior
    inline int omp_get_num_threads() { return 1; }
    inline int omp_get_max_threads() { return 1; }
    inline int omp_get_thread_num() { return 0; }
    inline int omp_get_num_procs() { return 1; }
#endif
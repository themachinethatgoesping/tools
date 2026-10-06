project(
  'nanobind',
  'cpp',
  version: run_command(
    'src/version.py',
    check: true,
  ).stdout().strip(),
  meson_version: '>=1.0.0',
  default_options: [
    'cpp_std=c++17',
    'b_ndebug=if-release',
    'default_library=static',
  ],
  license: 'BSD-3-Clause',
)

py_mod = import('python')
py = py_mod.find_installation()
py_dep = py.dependency()

robin_map_dep = dependency(
  'tsl-robin-map',
  version: '>=1.4.0',
)

incdir = include_directories('include')

# Arguments are derived from nanobind_build_library() in CMake configuration.
dep_compile_args = []
dep_link_args = []

compiler = meson.get_compiler('cpp')
if compiler.get_argument_syntax() == 'msvc'
  dep_compile_args += ['/D_CRT_SECURE_NO_WARNINGS']
endif

# Discussion in WrapDB PR #1556 as to whether or not the following is necessary:
# dep_compile_args += ['-fno-strict-aliasing']

freethreaded = py.get_variable('Py_GIL_DISABLED', 0) != 0
if freethreaded
  dep_compile_args += ['-DNB_FREE_THREADED']
endif

if not get_option('debug')
  dep_compile_args += ['-DNB_COMPACT_ASSERTIONS']

  # The following, from nanobind_strip(), applies both to the nanobind shared
  # library (if it's built) and to the developer's extension:
  if host_machine.system() == 'darwin'
    dep_link_args += ['-Wl,-dead_strip', '-Wl,-x', '-Wl,-S']
  elif host_machine.system() != 'windows'
    dep_link_args += ['-Wl,-s']
  endif
endif

if host_machine.system() == 'darwin'
  py_soabi = py.get_variable('SOABI')
  if py_soabi.startswith('cp')
    resp_file = meson.project_source_root() / 'cmake/darwin-ld-cpython.sym'
  else
    resp_file = meson.project_source_root() / 'cmake/darwin-ld-pypy.sym'
  endif
  dep_link_args += ['-Wl,@' + resp_file]
endif

if get_option('default_library') == 'shared'
  dep_compile_args += ['-DNB_SHARED']
  add_project_arguments(
    [dep_compile_args, '-DNB_BUILD'],
    language: 'cpp',
  )
  add_project_link_arguments(
    dep_link_args,
    language: 'cpp',
  )
elif host_machine.system() != 'windows' and host_machine.system() != 'darwin'
  dep_compile_args += ['-ffunction-sections', '-fdata-sections']
  add_project_arguments(
    dep_compile_args,
    language: 'cpp',
  )
  dep_link_args += ['-Wl,--gc-sections']
else
  add_project_arguments(
    dep_compile_args,
    language: 'cpp',
  )
endif

nanobind_sources = files('src/nb_combined.cpp')

nanobind_dep = declare_dependency(
  sources: nanobind_sources,
  include_directories: [incdir],
  dependencies: [py_dep, robin_map_dep],
  compile_args: dep_compile_args,
  link_args: dep_link_args,
  variables: {
    'stubgen': meson.current_source_dir() / 'src/stubgen.py',
  },
)

meson.override_dependency('nanobind', nanobind_dep)

# ---------------------------------------------------------------------------
# Split mode (nanobind >= 3.0): the frontend (binding code) and the backend
# (libnanobind) live in separate Python modules. See
# https://nanobind.readthedocs.io/en/latest/split_mode.html
#
# The frontend dependency below is header-only: it does NOT compile
# 'nb_combined.cpp'. Instead each extension imports a shared backend module at
# runtime (NB_BACKEND_MODULE). The consumer must additionally build its
# extension with 'limited_api: nanobind_stable_abi' so that the module targets
# the Python stable ABI (abi3), which split mode requires. The result is a
# single abi3 wheel per platform that works on every Python >= the floor, and
# multiple independently built extensions reliably share C++ types through the
# common backend.
#
# Backend module name (import name, identical for the PyPI wheel and the conda
# package) and the associated PyPI distribution name (used only to produce a
# helpful "pip install" hint when the backend is missing).
nanobind_backend_module = 'nanobind_backend'
nanobind_backend_pypi = 'nanobind-backend'

# Stable ABI floor for split-mode extensions. Matches the project's
# requires-python (>= 3.11).
nanobind_stable_abi = '3.11'

nanobind_frontend_dep = declare_dependency(
  include_directories: [incdir],
  dependencies: [py_dep, robin_map_dep],
  compile_args: dep_compile_args + [
    '-DNB_BACKEND_MODULE=' + nanobind_backend_module,
    '-DNB_BACKEND_PYPI=' + nanobind_backend_pypi,
  ],
  link_args: dep_link_args,
  variables: {
    'stubgen': meson.current_source_dir() / 'src/stubgen.py',
    'stable_abi': nanobind_stable_abi,
    'backend_module': nanobind_backend_module,
    'backend_pypi': nanobind_backend_pypi,
  },
)

meson.override_dependency('nanobind-frontend', nanobind_frontend_dep)

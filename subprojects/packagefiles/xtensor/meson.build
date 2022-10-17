project('xtensor', 'cpp',
        version:'0.24.3',
        license:'BSD-3-Clause',
        default_options : ['warning_level=3', 'cpp_std=c++14'])

xtl_dep = dependency('xtl',
    version:['>=0.6.12', '<1.0.0'])

json_dep = dependency('nlohmann_json',
    version:'>=3.1.1')

#TODO: currently build error when using xsimd ...
xsimd_dep = dependency('xsimd',
    #required: get_option('xsimd'),
    required: true,
    version: ['>=9.0.1']
    )


if meson.get_compiler('cpp').get_id() == 'msvc'
    xtensor_cpp_arg = ['-DXTENSOR_USE_XSIMD', '/EHsc', '/MP', '/bigobj']
elif meson.get_compiler('cpp').get_id() == 'clang'
    xtensor_cpp_arg = ['-DXTENSOR_USE_XSIMD']
else
    xtensor_cpp_arg = ['-DXTENSOR_USE_XSIMD', '-march=native']
endif

xtensor_dep = declare_dependency(
    include_directories:include_directories('include', is_system: true),
    dependencies: [
    xtl_dep,
    json_dep,
    xsimd_dep
    ],
    compile_args: xtensor_cpp_arg)

extra_cflags = []

# Workaround from issue: https://github.com/mesonbuild/meson/issues/2550
if meson.is_subproject()
    install_dir = get_option('subproj_includedir')
    extra_cflags += '-I' + get_option('prefix') / install_dir
else
    install_dir = get_option('includedir')
endif

install_subdir('include/xtensor', install_dir: install_dir)

pkgconfig = import('pkgconfig')
pkgconfig.generate(name: meson.project_name(),
    version: meson.project_version(),
    description: 'xtensor is a C++ library meant for numerical analysis with multi-dimensional array expressions.',
    extra_cflags: extra_cflags)

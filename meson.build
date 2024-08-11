project(
  'libbst',
  'c',
  default_options: ['c_std=c99', 'optimization=3', 'warning_level=2'],
  version: '0.1.1',
  license: 'MIT',
)

add_project_arguments('-D_DEFAULT_SOURCE', language: 'c')
add_project_arguments('-D_XOPEN_SOURCE=700', language: 'c')
add_project_arguments('-D_XOPEN_SOURCE_EXTENDED', language: 'c')

inc = include_directories('include')

subdir('include')
subdir('src')
subdir('test')

project('libbst', 'c',
        version : '0.1.0',
        license : 'BSD 2-Clause')

inc = include_directories('include')
sources = ['src/errors.c', 'src/bst.c', 'src/demo.c']

build_target('bst',
	     'src/errors.c',
	     'src/bst.c',
	     target_type : 'library',
	     include_directories : inc)

executable('demo',
	   sources,
	   include_directories : inc)

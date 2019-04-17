demo_1_exe = executable('demo_1_int',
			'demo_1_int.c',
			include_directories : inc,
			link_with : libbst)

demo_2_exe = executable('demo_2_string',
			'demo_2_string.c',
			include_directories : inc,
			link_with : libbst)

test('libbst', demo_1_exe)
test('libbst', demo_2_exe)

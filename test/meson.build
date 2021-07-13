demo_1_exe = executable('demo_1_int',
			'demo_1_int.c',
			include_directories : inc,
			link_with : libbst)

demo_2_exe = executable('demo_2_string',
			'demo_2_string.c',
			include_directories : inc,
			link_with : libbst)

demo_3_exe = executable('demo_3_fibonacci',
			'demo_3_fibonacci.c',
			include_directories : inc,
			link_with : libbst)

demo_4_exe = executable('demo_4_primes',
			'demo_4_primes.c',
			include_directories : inc,
			link_with : libbst)

test('libbst', demo_1_exe)
test('libbst', demo_2_exe)
test('libbst', demo_3_exe)
test('libbst', demo_4_exe)

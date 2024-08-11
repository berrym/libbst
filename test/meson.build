test_1_exe = executable(
  'test_bst_int',
  'test_bst_int.c',
  include_directories: inc,
  link_with: libbst,
)

test_2_exe = executable(
  'test_bst_string',
  'test_bst_string.c',
  include_directories: inc,
  link_with: libbst,
)

test('test_int', test_1_exe)
test('test_string', test_2_exe)

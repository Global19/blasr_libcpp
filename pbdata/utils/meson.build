###########
# Sources #
###########

libblasr_sources += files([
  'BitUtils.cpp',
  'SMRTReadUtils.cpp',
  'SMRTTitle.cpp',
  'TimeUtils.cpp'])

###########
# Headers #
###########

meson.is_subproject() and subdir_done()

install_headers(
  files([
    'BitUtils.hpp',
    'SMRTReadUtils.hpp',
    'SMRTTitle.hpp',
    'TimeUtils.hpp']),
  subdir : 'libblasr/pbdata/utils')

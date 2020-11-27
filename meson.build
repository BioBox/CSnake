
project('sfml-hello', 'c',
  license: 'MIT')

cc = meson.get_compiler('c')

window = cc.find_library('libcsfml-window', dirs : ['/usr/lib'])
system = cc.find_library('libcsfml-system', dirs : ['/usr/lib'])
graphics = cc.find_library('libcsfml-graphics', dirs : ['/usr/lib'])

inc = include_directories('include')

sources = files (
  'src/hash_table.c',
  'src/graphics.c',
  'src/snake.c',
  'src/map.c',
  'src/main.c'
)

# Use the dev library. The one with the headers
executable('snake', sources, dependencies: [system, graphics, window],
  include_directories: inc)


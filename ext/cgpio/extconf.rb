require 'mkmf'

find_executable('make') or abort "can't find make. please install it."
find_executable('gcc') or abort "can't find gcc. please install it."

create_makefile 'cgpio/cgpio'

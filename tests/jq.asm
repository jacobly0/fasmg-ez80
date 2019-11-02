include 'ez80.inc'
include 'tiformat.inc'
format ti executable protected program 'JQ'
macro test jump, cond&
	iterate offset, -$81, -$80, -2, -1, 0, 1, $7f, $80
		if -$80 <= offset & offset < $80 | `jump <> 'jr' & \
		     (offset <> -2 & offset | `jump <> 'jq')
			jump cond $ + 2 + offset
		else
			jp cond $ + 2 + offset
		end if
	end iterate

	local	lab
	jump	cond lab
lab:
	jump	cond lab
	jump	cond lab
end macro
iterate jump, jr, jp, jq
	iterate cond, <>, <nz, >, <z, >, <nc, >, <c, >
		test jump, cond
	end iterate
	if `jump <> 'jr'
		iterate cond, <po, >, <pe, >, <p, >, <m, >
			test jump, cond
		end iterate
	end if
end iterate

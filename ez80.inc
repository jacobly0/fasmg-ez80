define ez80

macro ez80.word value
	local val
	val = value
	db val and $ff, val shr 8 and $ff, val shr 16
end macro

long? = 3
macro dl? defs&
	iterate def, defs
		local temp
		match ?, def
			db 3 dup ?
		else match times =dup? ?, def
			temp = times
			db temp * 3 dup ?
		else match times =dup? val, def
			temp = times
			repeat temp
				ez80.word val
			end repeat
		else
			ez80.word def
		end match
	end iterate
end macro
struc dl? expr&
	label . : long
	dl? expr
end struc
macro rl? count
	local temp
	temp = count
	rb temp * 3
end macro
struc rl? defs&
	label . : long
	rl defs&
end struc

macro assume? expr&
	match =adl? == val, expr
		local temp
		temp = val
		if temp and 1 = temp
			ez80.l = temp
			ez80.il = temp
			ez80.adl = temp
		else
			err "illegal value for adl"
		end if
	else
		err "unknown assume statement"
	end match
end macro
assume? adl = 1

element ez80.b
element b?   : ez80.b * $01 + 0
element i?   : ez80.b * $ed + 0
element c?   : ez80.b * $01 + 1
element r?   : ez80.b * $ed + 1
element d?   : ez80.b * $01 + 2
element e?   : ez80.b * $01 + 3
element h?   : ez80.b * $01 + 4
element ixh? : ez80.b * $dd + 4
element iyh? : ez80.b * $fd + 4
element l?   : ez80.b * $01 + 5
element ixl? : ez80.b * $dd + 5
element iyl? : ez80.b * $fd + 5
element a?   : ez80.b * $01 + 7

element ez80.w
element bc?  : ez80.w * $05 + 0
element de?  : ez80.w * $05 + 1
element hl?  : ez80.w * $07 + 2
element ix?  : ez80.w * $dd + 2
element iy?  : ez80.w * $fd + 2
element sp?  : ez80.w * $04 + 3
element af?  : ez80.w * $01 + 3

define ez80

ez80.adl = 1
macro assume? expr&
	match =adl? == val, expr
		local adl
		adl = val
		if adl and 1 = adl
			ez80.adl = adl
		else
			err "illegal value for adl"
		end if
	else
		err "unknown assume statement"
	end match
end macro

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

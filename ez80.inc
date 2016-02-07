define ez80

macro ez80.word val
	v =: value
		db v and 377o, v shr 8 and 377o, v shr 16
	restore v
end macro

long? = 3
macro dl? defs&
	iterate def, defs
		match ?, def
			db 3 dup ?
		else match times =dup? ?, def
			t =: times
				db t * 3 dup ?
			restore t
		else match times =dup? val, def
			t =: times
				repeat t
					ez80.word val
				end repeat
			restore t
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
	c =: count
		rb c * 3
	restore c
end macro
struc rl? defs&
	label . : long
	rl defs&
end struc

macro assume? expr&
	match =adl? == val, expr
		v =: val
			if v and 1 = v
				ez80.l = v
				ez80.il = v
				ez80.adl = v
			else
				err "illegal value for adl"
			end if
		restore v
	else
		err "unknown assume statement"
	end match
end macro
assume? adl = 1

element ez80.b
element b?   : ez80.b * 001o + 030o
element nz?  : ez80.b * 001o + 001o
element z?   : ez80.b * 001o + 011o
element nc?  : ez80.b * 001o + 021o
element c?   : ez80.b * 001o + 031o
element po?  : ez80.b * 001o + 041o
element pe?  : ez80.b * 001o + 051o
element p?   : ez80.b * 001o + 061o
element m?   : ez80.b * 001o + 071o
element d?   : ez80.b * 001o + 032o
element e?   : ez80.b * 001o + 033o
element h?   : ez80.b * 001o + 034o
element ixh? : ez80.b * 335o + 034o
element iyh? : ez80.b * 375o + 034o
element l?   : ez80.b * 001o + 035o
element ixl? : ez80.b * 335o + 035o
element iyl? : ez80.b * 375o + 035o
element a?   : ez80.b * 001o + 037o
element i?   : ez80.b * 355o + 107o
element r?   : ez80.b * 355o + 117o

element ez80.w
element bc?  : ez80.w * 007o + 000o
element de?  : ez80.w * 007o + 020o
element hl?  : ez80.w * 007o + 040o
element ix?  : ez80.w * 335o + 040o
element iy?  : ez80.w * 375o + 040o
element sp?  : ez80.w * 006o + 060o
element af?  : ez80.w * 001o + 060o

macro ez80.prefix s*, is*
	ez80.l = s
	ez80.il = is
	ez80.lil = ez80.l or ez80.il shl 1
	db ez80.lil or ez80.lil shl 3 or 100o
end macro
macro inst name*
	define name?
	macro name?.s? args&
		ez80.prefix 0, ez80.il
		name? args
	end macro
	macro name?.l? args&
		ez80.prefix 1, ez80.il
		name? args
	end macro
	macro name?.is? args&
		ez80.prefix ez80.l, 0
		name? args
	end macro
	macro name?.il? args&
		ez80.prefix ez80.l, 1
		name? args
	end macro
	macro name?.sis? args&
		ez80.prefix 0, 0
		name? args
	end macro
	macro name?.lis? args&
		ez80.prefix 1, 0
		name? args
	end macro
	macro name?.sil? args&
		ez80.prefix 0, 1
		name? args
	end macro
	macro name?.lil? args&
		ez80.prefix 1, 1
		name? args
	end macro
	esc macro name? args&
		local before, after
	before:	if defined after & before = after
			eval 'err "invalid arguments for ', `name, ': ', `args, '"'
		end if
end macro
macro end?.inst!
	after:	assume? adl = ez80.adl
	esc end macro
end macro

iterate <name*, code*>,       \
	 nop,   <000o>,       \
	 rlca,  <007o>,       \
	 rrca,  <017o>,       \
	 rla,   <027o>,       \
	 rra,   <037o>,       \
	 daa,   <047o>,       \
	 cpl,   <057o>,       \
	 scf,   <067o>,       \
	 ccf,   <077o>,       \
	 halt,  <166o>,       \
	 exx,   <331o>,       \
	 di,    <363o>,       \
	 ei,    <373o>,       \
	 neg,   <355o, 104o>, \
	 retn,  <355o, 105o>, \
	 reti,  <355o, 115o>, \
	 rrd,   <355o, 147o>, \
	 rld,   <355o, 157o>, \
	 slp,   <355o, 166o>, \
	 stmix, <355o, 175o>, \
	 rsmix, <355o, 176o>, \
	 inim,  <355o, 202o>, \
	 otim,  <355o, 203o>, \
	 ini2,  <355o, 204o>, \
	 indm,  <355o, 212o>, \
	 otdm,  <355o, 213o>, \
	 ind2,  <355o, 214o>, \
	 inimr, <355o, 222o>, \
	 otimr, <355o, 223o>, \
	 ini2r, <355o, 224o>, \
	 indmr, <355o, 232o>, \
	 otdmr, <355o, 233o>, \
	 ind2r, <355o, 234o>, \
	 ldi,   <355o, 240o>, \
	 cpi,   <355o, 241o>, \
	 ini,   <355o, 242o>, \
	 outi,  <355o, 243o>, \
	 outi2, <355o, 244o>, \
	 ldd,   <355o, 250o>, \
	 cpd,   <355o, 251o>, \
	 ind,   <355o, 252o>, \
	 outd,  <355o, 253o>, \
	 outd2, <355o, 254o>, \
	 ldir,  <355o, 260o>, \
	 cpir,  <355o, 261o>, \
	 inir,  <355o, 262o>, \
	 otir,  <355o, 263o>, \
	 oti2r, <355o, 264o>, \
	 ldd,   <355o, 270o>, \
	 cpd,   <355o, 271o>, \
	 ind,   <355o, 272o>, \
	 otd,   <355o, 273o>, \
	 otd2r, <355o, 274o>
	inst name
		db code
	end inst
end iterate

inst ex
	match arg1 =, arg2, args
		iterate <a1, a2>, arg1, arg2, arg2, arg1
			match =af?, a1
				match =af'?, a2
					db 010o
				end match
			else match ( =sp? ), a1
				r =: a2
					if ~r scale 0 & r relativeto r element 1     \
					  & r metadata 1 element 1 relativeto ez80.w \
					  & r metadata 1 scale 0 = 040o
						if r metadata 1 scale 1 and 370o
							db r metadata 1 scale 1
						end if
						db 343o
					end if
				restore r
			else match =de?, a1
				match =hl?, a2
					db 353o
				end match
			end match
		end iterate
	end match
end inst

inst ret
	match, args
		db 311o
	else match cond, args
		c =: cond
			if ~c scale 0 & c relativeto c element 1     \
			  & c metadata 1 element 1 relativeto ez80.b \
			  & c metadata 1 scale 0 and 7 = 1
				db c metadata 1 scale 0 and 070o or 300o
			end if
		restore c
	end match
end inst

iterate <name*, code*>, pop, <301o>, push, <305o>
	inst name
		match reg, args
			r =: reg
				if ~r scale 0 & r relativeto r element 1     \
				  & r metadata 1 element 1 relativeto ez80.w \
				  & r metadata 1 scale 1 and 1
					if r metadata 1 scale 1 and 370o
						db r metadata 1 scale 1
					end if
					db r metadata 1 scale 0 or code
				end if
			restore r
		end match
	end inst
end iterate

inst rst
	match addr, args
		a =: addr
			if a and 070o = a
				db 307o or a
			end if
		restore a
	end match
end inst

inst im
	match mode, args
		m =: mode
			if m = 0
				db 355o, 106o
			else if m = 1
				db 355o, 126o
			else if m = 2
				db 355o, 136o
			end if
		restore m
	end match
end inst

inst mlt
	match reg, args
		r =: reg
			if ~r scale 0 & r relativeto r element 1     \
			  & r metadata 1 element 1 relativeto ez80.w \
			  & r metadata 1 scale 1 and 2
				db 355o, r metadata 1 scale 0 or 114o
			end if
		restore r
	end match
end inst

inst tstio
	match imm, mode
		i =: imm
			db 355o, 164o, i
		restore i
	end match
end inst

purge end?.inst?
purge inst?

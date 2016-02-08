define ez80

macro ez80.word v
	val =: v
		db val and 377o, val shr 8 and 377o, val shr 16
	restore val
end macro

long? = 3
macro dl? defs&
	iterate def, defs
		match ?, def
			db 3 dup ?
		else match t =dup? ?, def
			times =: t
				db times * 3 dup ?
			restore times
		else match t =dup? v, def
			times =: t
				repeat times
					ez80.word v
				end repeat
			restore times
		else
			ez80.word def
		end match
	end iterate
end macro
struc dl? expr&
	label . : long
	dl? expr
end struc
macro rl? c
	count =: c
		rb count * 3
	restore count
end macro
struc rl? defs&
	label . : long
	rl defs&
end struc

macro assume? expr&
	match =adl? == v, expr
		val =: v
			if val and 1 = val
				ez80.l = val
				ez80.il = val
				ez80.adl = val
			else
				err "illegal value for adl"
			end if
		restore val
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
		match, args
			db code
		end match
	end inst
end iterate

iterate name, inc, dec
	inst name
		match ( a ), args
			adr =: a
				if adr relativeto adr element 1               \
				 & adr metadata 1 element 1 relativeto ez80.w \
				 & adr metadata 1 scale 0 = 040o
					if adr metadata 1 scale 1 and not 007o
						if adr scale 0 >= -200o & adr scale 0 < 200o
							db adr metadata 1 scale 1, % + 063o, adr scale 0
						end if
					else if ~adr scale 0
						db % + 063o
					end if
				end if
			restore adr
		else r, args
			reg =: r
				if ~reg scale 0 & reg relativeto reg element 1
					if reg metadata 1 element 1 relativeto ez80.w \
					 & reg metadata 1 scale 1 and 004o
						if reg metadata 1 scale 1 and not 007o
							db reg metadata 1 scale 1
						end if
						db reg metadata 1 scale 0 or (% - 1) shl 3 or 003o
					else if reg metadata 1 element 1 relativeto ez80.b \
					 & reg metadata 1 scale 0 and 070o = 030o
						if reg metadata 1 scale 1 and not 007o
							db reg metadata 1 scale 1
						end if
						db reg metadata 1 scale 0 shl 3 and 070o + % + 003o
					end if
				end if
			restore reg
		end match
	end inst
end iterate

inst ex
	match left =, right, args
		iterate <arg1, arg2>, left, right, right, left
			match =af?, arg1
				match =af'?, arg2
					db 010o
				end match
			else match ( =sp? ), arg1
				reg =: arg2
					if ~reg scale 0 & reg relativeto reg element 1 \
					  & reg metadata 1 element 1 relativeto ez80.w \
					  & reg metadata 1 scale 0 = 040o
						if reg metadata 1 scale 1 and not 007o
							db reg metadata 1 scale 1
						end if
						db 343o
					end if
				restore reg
			else match =de?, arg1
				match =hl?, arg2
					db 353o
				end match
			end match
		end iterate
	end match
end inst

inst ret
	match, args
		db 311o
	else
		cond =: args
			if ~cond scale 0 & cond relativeto cond element 1 \
			  & cond metadata 1 element 1 relativeto ez80.b   \
			  & cond metadata 1 scale 0 and 007o = 001o
				db cond metadata 1 scale 0 and 070o or 300o
			end if
		restore cond
	end match
end inst

iterate name, pop, push
	inst name
		reg =: args
			if ~reg scale 0 & reg relativeto reg element 1 \
			  & reg metadata 1 element 1 relativeto ez80.w \
			  & reg metadata 1 scale 1 and 1
				if reg metadata 1 scale 1 and not 007o
					db reg metadata 1 scale 1
				end if
				db reg metadata 1 scale 0 + % shl 2 + 275o
			end if
		restore reg
	end inst
end iterate

inst rst
	adr =: args
		if adr and 070o = adr
			db adr or 307o
		end if
	restore adr
end inst

iterate name, srl, rlc, rrc, rl, rr, sla, sra
	inst name
		match ( a ), args
			adr =: a
				if adr relativeto adr element 1               \
				 & adr metadata 1 element 1 relativeto ez80.w \
				 & adr metadata 1 scale 0 = 040o
					if adr metadata 1 scale 1 and not 007o
						if adr scale 0 >= -200o & adr scale 0 < 200o
							db adr metadata 1 scale 1, 313o, adr scale 0, \
							   ((% - 2) and 007o) shl 3 or 006o
						end if
					else if ~adr scale 0
						db 313o, ((% - 2) and 007o) shl 3 or 006o
					end if
				end if
			restore adr
		else match r, args
			reg =: r
				if ~reg scale 0 & reg relativeto reg element 1 \
				  & reg metadata 1 element 1 relativeto ez80.b \
				  & reg metadata 1 scale 0 and 070o = 030o     \
				  & reg metadata 1 scale 1 = 1
					db 313o, reg metadata 1 scale 0 and 007o   \
					      or ((% - 2) and 007o) shl 3
				end if
			restore reg
		end match
	end inst
end iterate
iterate name, bit, res, set
	inst name
		match i =, right, args
			idx =: i
				if idx and 007o = idx
					idx = % shl 6 or idx shl 3
					match ( a ), right
						adr =: a
							if adr relativeto adr element 1               \
							 & adr metadata 1 element 1 relativeto ez80.w \
							 & adr metadata 1 scale 0 = 040o
								if adr metadata 1 scale 1 and not 007o
									if adr scale 0 >= -200o & adr scale 0 < 200o
										db adr metadata 1 scale 1, 313o,  \
										   adr scale 0, idx or 006o
									end if
								else if ~adr scale 0
									db 313o, idx or 006o
								end if
							end if
						restore adr
					else match r, right
						reg =: r
							if ~reg scale 0 & reg relativeto reg element 1 \
							  & reg metadata 1 element 1 relativeto ez80.b \
							  & reg metadata 1 scale 0 and 070o = 030o     \
							  & reg metadata 1 scale 1 = 1
									db 313o, reg metadata 1 scale 0 and 007o or idx
							end if
						restore reg
					end match
				end if
			restore idx
		end match
	end inst
end iterate

inst out
	match ( =bc? ) =, r, args
		reg =: r
			if ~reg scale 0 & reg relativeto reg element 1 \
			  & reg metadata 1 element 1 relativeto ez80.b \
			  & reg metadata 1 scale 1 = 1                 \
			  & reg metadata 1 scale 0 and 070o = 030o
				db 355o, reg metadata 1 scale 0 shl 3 and 070o or 101o
			end if
		restore reg
	else match ( =c? ) =, r, args
		out? (bc), r
	else match ( p ) =, =a?, args
		port =: p
			db 323o, port
		restore port
	end match
end inst
inst in
	match r =, ( =bc? ), args
		reg =: r
			if ~reg scale 0 & reg relativeto reg element 1 \
			  & reg metadata 1 element 1 relativeto ez80.b \
			  & reg metadata 1 scale 1 = 1                 \
			  & reg metadata 1 scale 0 and 070o = 030o
				db 355o, reg metadata 1 scale 0 shl 3 and 070o or 100o
			end if
		restore reg
	else match r =, ( =c? ), args
		in? r, (bc)
	else match =a? =, ( p ), args
		port =: p
			db 333o, port
		restore port
	end match
end inst
inst in0
	match r =, ( p ), args
		reg =: r
		port =: p
			if ~reg scale 0 & reg relativeto reg element 1 \
			  & reg metadata 1 element 1 relativeto ez80.b \
			  & reg metadata 1 scale 1 = 1                 \
			  & reg metadata 1 scale 0 and 070o = 030o
				db 355o, reg metadata 1 scale 0 shl 3 and 070o or 000o, port
			end if
		restore port, reg
	end match
end inst
inst out0
	match ( p ) =, r, args
		port =: p
		reg =: r
			if ~reg scale 0 & reg relativeto reg element 1 \
			  & reg metadata 1 element 1 relativeto ez80.b \
			  & reg metadata 1 scale 1 = 1                 \
			  & reg metadata 1 scale 0 and 070o = 030o
				db 355o, reg metadata 1 scale 0 shl 3 and 070o or 001o, port
			end if
		restore reg, port
	end match
end inst

inst im
	mode =: args
		if mode = 0
			db 355o, 106o
		else if mode = 1
			db 355o, 126o
		else if mode = 2
			db 355o, 136o
		end if
	restore mode
end inst

inst mlt
	reg =: args
		if ~reg scale 0 & reg relativeto reg element 1 \
		  & reg metadata 1 element 1 relativeto ez80.w \
		  & reg metadata 1 scale 1 and 2
			db 355o, reg metadata 1 scale 0 or 114o
		end if
	restore reg
end inst

inst tstio
	imm =: args
		db 355o, 164o, imm
	restore imm
end inst

purge end?.inst?
purge inst?

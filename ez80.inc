define ez80

macro ez80.long v
	val =: v
		db val and 377o, val shr 8 and 377o, val shr 16
	restore val
end macro
macro ez80.word v
	val =: v
		if ez80.il
			ez80.long val
		else
			dw val
		end if
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
					ez80.long v
				end repeat
			restore times
		else
			ez80.long def
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
element i?   : ez80.b
element r?   : ez80.b
element mb?  : ez80.b

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
	ez80.lil = ez80.l + ez80.il shl 1
	db ez80.lil + ez80.lil shl 3 + 100o
end macro
macro inst name*
	define name? name
	namespace name?
		macro s? args&
			ez80.prefix 0, ez80.il
			name? args
		end macro
		macro l? args&
			ez80.prefix 1, ez80.il
			name? args
		end macro
		macro is? args&
			ez80.prefix ez80.l, 0
			name? args
		end macro
		macro il? args&
			ez80.prefix ez80.l, 1
			name? args
		end macro
		macro sis? args&
			ez80.prefix 0, 0
			name? args
		end macro
		macro lis? args&
			ez80.prefix 1, 0
			name? args
		end macro
		macro sil? args&
			ez80.prefix 0, 1
			name? args
		end macro
		macro lil? args&
			ez80.prefix 1, 1
			name? args
		end macro
	end namespace
	esc macro name? args&
		local before, after
	before:	if defined after & before = after
			eval 'err "invalid arguments in ', `name, ' ', `args, '"'
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
						if -200o <= adr scale 0 & adr scale 0 < 200o
							db adr metadata 1 scale 1, % + 063o, adr scale 0
						end if
					else if ~adr scale 0
						db % + 063o
					end if
				end if
			restore adr
		else match r, args
			reg =: r
				if ~reg scale 0 & reg relativeto reg element 1
					if reg metadata 1 element 1 relativeto ez80.w \
					 & reg metadata 1 scale 1 and 004o
						if reg metadata 1 scale 1 and not 007o
							db reg metadata 1 scale 1
						end if
						db reg metadata 1 scale 0 + (% - 1) shl 3 + 003o
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

inst djnz
	match ( a ), args
	else match a, args
		adr =: a
		off =: adr - $ - 2
			if -200o <= off & off < 200o
				db 020o, off
			end if
		restore off, adr
	end match
end inst
inst jr
	match ( c ) =, a, args
	else match c =, ( a ), args
	else match c =, a, args
		cnd =: c
		adr =: a
		off =: adr - $ - 2
			if ~cnd scale 0 & cnd relativeto cnd element 1 \
			  & cnd metadata 1 element 1 relativeto ez80.b \
			  & cnd metadata 1 scale 0 and 007o = 001o     \
			  & cnd metadata 1 scale 0 < 040o              \
			  & -200o <= off & off < 200o
				db cnd metadata 1 scale 0 and 030o + 040o, off
			end if
		restore off, adr, cnd
	else match ( a ), args
	else match a, args
		adr =: a
		off = adr - $ - 2
			if -200o <= off & off < 200o
				db 030o, off
			end if
		restore off, adr
	end match
end inst
inst jq
	match ( c ) =, a, args
	else match c =, ( a ), args
	else match c =, a, args
		cnd =: c
		adr =: a
		off =: adr - $ - 2
			if ~cnd scale 0 & cnd relativeto cnd element 1 \
			  & cnd metadata 1 element 1 relativeto ez80.b \
			  & cnd metadata 1 scale 0 and 007o = 001o     \
			  & cnd metadata 1 scale 0 < 040o
				if -200o <= off & off < 200o
					db cnd metadata 1 scale 0 and 030o + 040o, off
				else
					db cnd metadata 1 scale 0 and 030o + 302o
					ez80.word adr
				end if
			end if
		restore off, adr, cnd
	else match ( a ), args
	else match a, args
		adr =: a
		off =: adr - $ - 2
			if -200o <= off & off < 200o
				db 030o, off
			else
				db 303o
				ez80.word adr
			end if
		restore off, adr
	end match
end inst

inst ld
	match ( d ) =, ( s ), args
	else match d =, ( s ), args
		dst =: d
		src =: s
			if elementsof src
				if ~dst scale 0 & dst relativeto dst element 1 \
				  & src relativeto src element 1               \
				  & src metadata 1 element 1 relativeto ez80.w
					if src metadata 1 scale 0 = 040o
						if dst metadata 1 element 1 relativeto ez80.b \
						 & dst metadata 1 scale 0 and 070o = 030o     \
						 & dst metadata 1 scale 1 = 1
							if src metadata 1 scale 1 and not 007o
								if -200o <= src scale 0 & src scale 0 < 200o
									db src metadata 1 scale 1,                       \
									   dst metadata 1 scale 0 shl 3 and 070o + 106o, \
									   src scale 0
								end if
							else
								db dst metadata 1 scale 0 shl 3 and 070o + 106o
							end if
						else if dst metadata 1 element 1 relativeto ez80.w \
						      & dst metadata 1 scale 1 and 005o = 005o
							code =: dst metadata 1 scale 0 + 007o
								if dst metadata 1 scale 1 and not 007o
									code = code + 020o
									if src metadata 1 scale 1 and 040o \
									 = dst metadata 1 scale 1 and 040o
										code = code - 6
									end if
								end if
								if src metadata 1 scale 1 and not 007o
									if -200o <= src scale 0 & src scale 0 < 200o
										db src metadata 1 scale 1, code, src scale 0
									end if
								else if ~src scale 0
									db 355o, code
								end if
							restore op
						end if
					else if dst eq A? & src metadata 1 scale 1 and 002o
						db src metadata 1 scale 0 + 012o
					end if
				end if
			else if dst eq A?
				db 072o
				ez80.word src
			else if ~dst scale 0 & dst relativeto dst element 1 \
			       & dst metadata 1 element 1 relativeto ez80.w \
			       & dst metadata 1 scale 1 and 004o
				if dst metadata 1 scale 0 = 040o
					if dst metadata 1 scale 1 and not 007o
						db dst metadata 1 scale 1
					end if
					db 052o
				else
					db 355o, dst metadata 1 scale 0 + 113o
				end if
				ez80.word src
			end if
		restore src, dst
	else match ( d ) =, s, args
		dst =: d
		src =: s
			if elementsof dst
				if elementsof src
					if ~src scale 0 & src relativeto src element 1 \
					  & dst relativeto dst element 1               \
					  & dst metadata 1 element 1 relativeto ez80.w
						if dst metadata 1 scale 0 = 040o
							if src metadata 1 element 1 relativeto ez80.b \
							 & src metadata 1 scale 0 and 070o = 030o     \
							 & src metadata 1 scale 1 = 1
								if dst metadata 1 scale 1 and not 007o
									if -200o <= dst scale 0 & dst scale 0 < 200o
										db dst metadata 1 scale 1,                 \
										   src metadata 1 scale 0 and 007o + 160o, \
										   dst scale 0
									end if
								else
									db src metadata 1 scale 0 and 007o + 160o
								end if
							else if src metadata 1 element 1 relativeto ez80.w \
							      & src metadata 1 scale 1 and 005o = 005o
								code =: src metadata 1 scale 0 + 017o
									if src metadata 1 scale 1 and not 017o
										code = code + 020o
										if dst metadata 1 scale 1 and 040o \
										 = src metadata 1 scale 1 and 040o
											code = code - 1
										end if
									end if
									if dst metadata 1 scale 1 and not 007o
										if -200o <= dst scale 0 & dst scale 0 < 200o
											db dst metadata 1 scale 1, code, dst scale 0
										end if
									else if ~dst scale 0
										db 355o, code
									end if
								restore op
							end if
						else if src eq A? & dst metadata 1 scale 1 and 002o
							db dst metadata 1 scale 0 + 002o
						end if
					end if
				else if dst relativeto dst element 1               \
				      & dst metadata 1 element 1 relativeto ez80.w \
					  & dst metadata 1 scale 0 = 040o
					if dst metadata 1 scale 1 and not 007o
						if -200o <= dst scale 0 & dst scale 0 < 200o
							db dst metadata 1 scale 1, 066o, dst scale 0, src
						end if
					else
						db 066o, src
					end if
				end if
			else if src eq A?
				db 062o
				ez80.word dst
			else if ~src scale 0 & src relativeto src element 1 \
			       & src metadata 1 element 1 relativeto ez80.w \
			       & src metadata 1 scale 1 and 004o
				if src metadata 1 scale 0 = 040o
					if src metadata 1 scale 1 and not 007o
						db src metadata 1 scale 1
					end if
					db 042o
				else
					db 355o, src metadata 1 scale 0 + 103o
				end if
				ez80.word dst
			end if
		restore src, dst
	else match d =, s, args
		dst =: d
		src =: s
			if elementsof src
				if ~src scale 0 & src relativeto src element 1       \
				  & src metadata 1 element 1 relativeto ez80.b       \
				  & src metadata 1 scale 0 and 070o = 030o           \
				 & ~dst scale 0 & dst relativeto dst element 1       \
				  & dst metadata 1 element 1 relativeto ez80.b       \
				  & dst metadata 1 scale 0 and 070o = 030o           \
				  & ~(src eq dst & src metadata 1 scale 0 <= 033o)   \
				  & (src metadata 1 scale 1 = dst metadata 1 scale 1 \
				   | src metadata 1 scale 1 and dst metadata 1 scale 1 = 1)
					if src metadata 1 scale 1 or dst metadata 1 scale 1 <> 1
						db src metadata 1 scale 1 or dst metadata 1 scale 1
					end if
					db src metadata 1 scale 0 and 007o \
					 + dst metadata 1 scale 0 shl 3 and 070o + 100o
				else if dst eq SP?
					if ~src scale 0 & src relativeto src element 1 \
					  & src metadata 1 element 1 relativeto ez80.w \
					  & src metadata 1 scale 0 = 040o
						if src metadata 1 scale 1 and not 007o
							db src metadata 1 scale 1
						end if
						db 371o
					end if
				else match =i? =, =a?, args
					db 355o, 107o
				else match =r? =, =a?, args
					db 355o, 117o
				else match =a? =, =i?, args
					db 355o, 127o
				else match =a? =, =r?, args
					db 355o, 137o
				else match =mb? =, =a?, args
					db 355o, 155o
				else match =a? =, =mb?, args
					db 355o, 156o
				else match =i? =, =hl?, args
					db 355o, 307o
				else match =hl? =, =i?, args
					db 355o, 327o
				end match
			else if ~dst scale 0 & dst relativeto dst element 1
				if dst metadata 1 element 1 relativeto ez80.b \
				 & dst metadata 1 scale 0 and 070o = 030o
					if dst metadata 1 scale 1 <> 1
						db dst metadata 1 scale 1
					end if
					db dst metadata 1 scale 0 shl 3 and 070o + 006o, src
				else if dst metadata 1 element 1 relativeto ez80.w \
				      & dst metadata 1 scale 1 and 004o
					if dst metadata 1 scale 1 and not 007o
						db dst metadata 1 scale 1
					end if
					db dst metadata 1 scale 0 + 001o
					ez80.word src
				end if
			end if
		restore src, dst
	end match
end inst

inst add
	match =a? =, ( a ), args
		adr =: a
			if adr relativeto adr element 1               \
			 & adr metadata 1 element 1 relativeto ez80.w \
			 & adr metadata 1 scale 0 = 040o
				if adr metadata 1 scale 1 and not 007o
					if -200o <= adr scale 0 & adr scale 0 < 200o
						db adr metadata 1 scale 1, 206o, adr scale 0
					end if
				else if ~adr scale 0
					db 206o
				end if
			end if
		restore adr
	else match =a? =, r, args
		reg =: r
			if elementsof reg
				if ~reg scale 0 & reg relativeto reg element 1 \
				  & reg metadata 1 element 1 relativeto ez80.b \
				  & reg metadata 1 scale 0 and 070o = 030o
					if reg metadata 1 scale 1 and not 007o
						db reg metadata 1 scale 1
					end if
					db reg metadata 1 scale 0 and 007o + 200o
				end if
			else
				db 306o, reg
			end if
		restore reg
	else match hl =, ( a ), args
	else match hl =, r, args
		dst =: hl
		reg =: r
			if ~dst scale 0 & dst relativeto dst element 1       \
			  & dst metadata 1 element 1 relativeto ez80.w       \
			  & dst metadata 1 scale 0 = 040o                    \
			 & ~reg scale 0 & reg relativeto reg element 1       \
			  & reg metadata 1 element 1 relativeto ez80.w       \
			  & reg metadata 1 scale 1 & 004o                    \
			 & (dst metadata 1 scale 0 <> reg metadata 1 scale 0 \
			  | dst metadata 1 scale 1 =  reg metadata 1 scale 1)
				if dst metadata 1 scale 1 and not 007o
					db dst metadata 1 scale 1
				end if
				db reg metadata 1 scale 0 + 011o
			end if
		restore reg, dst
	else match r, args
		add? a, r
	end match
end inst
iterate name, adc, sbc
	inst name
		match =a? =, ( a ), args
			adr =: a
				if adr relativeto adr element 1               \
				 & adr metadata 1 element 1 relativeto ez80.w \
				 & adr metadata 1 scale 0 = 040o
					if adr metadata 1 scale 1 and not 007o
						if -200o <= adr scale 0 & adr scale 0 < 200o
							db adr metadata 1 scale 1, % shl 4 + 176o, adr scale 0
						end if
					else if ~adr scale 0
						db % shl 4 + 176o
					end if
				end if
			restore adr
		else match =a? =, r, args
			reg =: r
				if elementsof reg
					if ~reg scale 0 & reg relativeto reg element 1 \
					  & reg metadata 1 element 1 relativeto ez80.b \
					  & reg metadata 1 scale 0 and 070o = 030o
						if reg metadata 1 scale 1 and not 007o
							db reg metadata 1 scale 1
						end if
						db reg metadata 1 scale 0 and 007o + % shl 4 + 170o
					end if
				else
					db % shl 4 + 276o, reg
				end if
			restore reg
		else match =hl? =, ( a ), args
		else match =hl? =, r, args
			reg =: r
				if ~reg scale 0 & reg relativeto reg element 1 \
				  & reg metadata 1 element 1 relativeto ez80.w \
				  & reg metadata 1 scale 1 and 002o
					db 355o, reg metadata 1 scale 0 + 122o - % shl 3
				end if
			restore reg
		else match a =, r, args
		else match r, args
			name? a, r
		end match
	end inst
end iterate
iterate <name*, code*>, sub, 020o, and, 040o, xor, 050o, or, 060o, cp, 070o
	inst name
		match =a? =, ( a ), args
			adr =: a
				if adr relativeto adr element 1               \
				 & adr metadata 1 element 1 relativeto ez80.w \
				 & adr metadata 1 scale 0 = 040o
					if adr metadata 1 scale 1 and not 007o
						if -200o <= adr scale 0 & adr scale 0 < 200o
							db adr metadata 1 scale 1, code + 206o, adr scale 0
						end if
					else if ~adr scale 0
						db code + 206o
					end if
				end if
			restore adr
		else match =a? =, r, args
			reg =: r
				if elementsof reg
					if ~reg scale 0 & reg relativeto reg element 1 \
					  & reg metadata 1 element 1 relativeto ez80.b \
					  & reg metadata 1 scale 0 and 070o = 030o
						if reg metadata 1 scale 1 and not 007o
							db reg metadata 1 scale 1
						end if
						db reg metadata 1 scale 0 and 007o + code + 200o
					end if
				else
					db code + 306o, reg
				end if
			restore reg
		else match a =, r, args
		else match r, args
			name? a, r
		end match
	end inst
end iterate

inst ret
	match ( c ), args
	else match c, args
		cnd =: c
			if ~cnd scale 0 & cnd relativeto cnd element 1 \
			  & cnd metadata 1 element 1 relativeto ez80.b \
			  & cnd metadata 1 scale 0 and 007o = 001o
				db cnd metadata 1 scale 0 and 070o + 300o
			end if
		restore cnd
	else
		db 311o
	end match
end inst
iterate name, pop, push
	inst name
		match ( a ), args
		else match r, args
			reg =: r
				if ~reg scale 0 & reg relativeto reg element 1 \
				  & reg metadata 1 element 1 relativeto ez80.w \
				  & reg metadata 1 scale 1 and 1
					if reg metadata 1 scale 1 and not 007o
						db reg metadata 1 scale 1
					end if
					db reg metadata 1 scale 0 + % shl 2 + 275o
				end if
			restore reg
		end match
	end inst
end iterate
inst jp
	match ( c ) =, a, args
	else match c =, ( a ), args
	else match c =, a, args
		cnd =: c
		adr =: a
			if ~cnd scale 0 & cnd relativeto cnd element 1 \
			  & cnd metadata 1 element 1 relativeto ez80.b \
			  & cnd metadata 1 scale 0 and 007o = 001o
				db cnd metadata 1 scale 0 and 070o + 302o
				ez80.word adr
			end if
		restore adr, cnd
	else match ( a ), args
		adr =: a
			if ~adr scale 0 & adr relativeto adr element 1 \
			  & adr metadata 1 element 1 relativeto ez80.w \
			  & adr metadata 1 scale 0 = 040o
				if adr metadata 1 scale 1 and not 007o
					db adr metadata 1 scale 1
				end if
				db 351o
			end if
		restore adr
	else match a, args
		adr =: a
			db 303o
			ez80.word adr
		restore adr
	end match
end inst
inst call
	match ( c ) =, a, args
	else match c =, ( a ), args
	else match c =, a, args
		cnd =: c
		adr =: a
			if ~cnd scale 0 & cnd relativeto cnd element 1 \
			  & cnd metadata 1 element 1 relativeto ez80.b \
			  & cnd metadata 1 scale 0 and 007o = 001o
				db cnd metadata 1 scale 0 and 070o + 304o
				ez80.word adr
			end if
		restore adr, cnd
	else match ( a ), args
	else match a, args
		adr =: a
			db 315o
			ez80.word adr
		restore adr
	end match
end inst
inst rst
	match ( a ), args
	else match a, args
		adr =: args
			if adr and 070o = adr
				db adr + 307o
			end if
		restore adr
	end match
end inst

iterate name, srl, rlc, rrc, rl, rr, sla, sra
	inst name
		match ( a ), args
			adr =: a
				if adr relativeto adr element 1               \
				 & adr metadata 1 element 1 relativeto ez80.w \
				 & adr metadata 1 scale 0 = 040o
					if adr metadata 1 scale 1 and not 007o
						if -200o <= adr scale 0 & adr scale 0 < 200o
							db adr metadata 1 scale 1, 313o, adr scale 0, \
							   ((% - 2) and 007o) shl 3 + 006o
						end if
					else if ~adr scale 0
						db 313o, ((% - 2) and 007o) shl 3 + 006o
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
					 + ((% - 2) and 007o) shl 3
				end if
			restore reg
		end match
	end inst
end iterate
iterate name, bit, res, set
	inst name
		match ( a ) =, right, args
		else match i =, right, args
			imm =: i
				if imm and 007o = imm
					imm = % shl 6 + imm shl 3
					match ( a ), right
						adr =: a
							if adr relativeto adr element 1               \
							 & adr metadata 1 element 1 relativeto ez80.w \
							 & adr metadata 1 scale 0 = 040o
								if adr metadata 1 scale 1 and not 007o
									if -200o <= adr scale 0 & adr scale 0 < 200o
										db adr metadata 1 scale 1, 313o,  \
										   adr scale 0, imm + 006o
									end if
								else if ~adr scale 0
									db 313o, imm + 006o
								end if
							end if
						restore adr
					else match r, right
						reg =: r
							if ~reg scale 0 & reg relativeto reg element 1 \
							  & reg metadata 1 element 1 relativeto ez80.b \
							  & reg metadata 1 scale 0 and 070o = 030o     \
							  & reg metadata 1 scale 1 = 1
									db 313o, reg metadata 1 scale 0 and 007o + imm
							end if
						restore reg
					end match
				end if
			restore imm
		end match
	end inst
end iterate

inst out
	match ( p ) =, ( a ), args
	else match ( =bc? ) =, r, args
		reg =: r
			if ~reg scale 0 & reg relativeto reg element 1 \
			  & reg metadata 1 element 1 relativeto ez80.b \
			  & reg metadata 1 scale 1 = 1                 \
			  & reg metadata 1 scale 0 and 070o = 030o
				db 355o, reg metadata 1 scale 0 shl 3 and 070o + 101o
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
	match =f? =, ( =bc? ), args
		port =: p
			db 355o, 160o
		restore port
	else match ( a ) =, ( p ), args
	else match r =, ( =bc? ), args
		reg =: r
			if ~reg scale 0 & reg relativeto reg element 1 \
			  & reg metadata 1 element 1 relativeto ez80.b \
			  & reg metadata 1 scale 1 = 1                 \
			  & reg metadata 1 scale 0 and 070o = 030o
				db 355o, reg metadata 1 scale 0 shl 3 and 070o + 100o
			end if
		restore reg
	else match r =, ( =c? ), args
		in? r, (bc)
	else match =a? =, ( p ), args
		port =: p
			db 333o, port
		restore port
	else match ( p ), args
		in? f, (p)
	end match
end inst
inst in0
	match =f? =, ( p ), args
		port =: p
			db 355o, 060o, p
		restore port
	else match ( a ) =, ( p ), args
	else match r =, ( p ), args
		reg =: r
		port =: p
			if ~reg scale 0 & reg relativeto reg element 1 \
			  & reg metadata 1 element 1 relativeto ez80.b \
			  & reg metadata 1 scale 1 = 1                 \
			  & reg metadata 1 scale 0 and 070o = 030o
				db 355o, reg metadata 1 scale 0 shl 3 and 070o + 000o, port
			end if
		restore port, reg
	else match ( p ), args
		in0? f, (p)
	end match
end inst
inst out0
	match ( p ) =, ( a ), args
	else match ( p ) =, r, args
		port =: p
		reg =: r
			if ~reg scale 0 & reg relativeto reg element 1 \
			  & reg metadata 1 element 1 relativeto ez80.b \
			  & reg metadata 1 scale 1 = 1                 \
			  & reg metadata 1 scale 0 and 070o = 030o
				db 355o, reg metadata 1 scale 0 shl 3 and 070o + 001o, port
			end if
		restore reg, port
	end match
end inst

inst lea
	match ( l ) =, r, args
	else match l =, ( r ), args
	else match l =, r, args
		left =: l
		right =: r
			if ~left scale 0 & left relativeto left element 1 \
			               & right relativeto right element 1 \
			  & left metadata 1 element 1 relativeto ez80.w   \
			  & right metadata 1 element 1 relativeto ez80.w  \
			  & left metadata 1 scale 0 <> 060o               \
			  & right metadata 1 scale 1 and not 007o         \
			  & -200o <= right scale 0 & right scale 0 < 200o
				if left metadata 1 scale 1 and 002o
					db 355o, right metadata 1 scale 1 shr 5 and 1 \
					 + left metadata 1 scale 0 + 002o, right scale 0
				else if left relativeto right
					db 355o, left metadata 1 scale 1 shr 5 and 1 + 062o, right scale 0
				else
					db 355o, left metadata 1 scale 1 shr 5 and 1 + 124o, right scale 0
				end if
			end if
		restore right, left
	end match
end inst

inst tst
	match =a? =, ( =hl? ), args
		db 355o, 064o
	else match =a? =, r, args
		reg =: r
			if ~reg scale 0 & reg relativeto reg element 1 \
			  & reg metadata 1 element 1 relativeto ez80.b \
			  & reg metadata 1 scale 1 = 1                 \
			  & reg metadata 1 scale 0 and 070o = 030o
				db 355o, reg metadata 1 scale 0 shl 3 and 070o + 004o
			end if
		restore reg
	end match
end inst

inst im
	match ( a ), args
	else match i, args
		imm =: i
			if imm = 0
				db 355o, 106o
			else if imm = 1
				db 355o, 126o
			else if imm = 2
				db 355o, 136o
			end if
		restore imm
	end match
end inst

inst mlt
	match ( a ), args
	else match r, args
		reg =: r
			if ~reg scale 0 & reg relativeto reg element 1 \
			  & reg metadata 1 element 1 relativeto ez80.w \
			  & reg metadata 1 scale 1 and 2
				db 355o, reg metadata 1 scale 0 + 114o
			end if
		restore reg
	end match
end inst

inst pea
	match ( a ), args
	else match r, args
		reg =: r
			if reg relativeto reg element 1               \
			 & reg metadata 1 element 1 relativeto ez80.w \
			 & reg metadata 1 scale 1 and not 007o        \
			 & -200o <= reg scale 0 & reg scale 0 < 200o
				db 355o, reg metadata 1 scale 1 shr 5 and 1 + 145o, reg scale 0
			end if
		restore reg
	end match
end inst

inst tstio
	match ( a ), args
	else match i, args
		imm =: i
			db 355o, 164o, imm
		restore imm
	end match
end inst

purge end?.inst?
purge inst?

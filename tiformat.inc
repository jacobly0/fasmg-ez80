macro format?.ti? clause&
	local all, checkloc, checksum, cplx, data, exec, flag, head, name, process, prot, temp, type, var
	macro process setting
		match first rest, setting
			process first
			process rest
		else match =ARCHIVED?, setting
			flag = flag or 1 shl 7
		else match =EXECUTABLE?, setting
			define exec
		else match =PROTECTED?, setting
			type = 6
			define prot
		else match =REAL?, setting
			type = 0
		else match =LIST?, setting
			if defined cplx
				type = 13
			else
				type = 2
			end if
		else match =MATRIX?, setting
			type = 2
		else match =EQUATION?, setting
			type = 3
		else match =STRING?, setting
			type = 4
		else match =PROGRAM?, setting
			if defined prot
				type = 6
			else
				type = 5
			end if
		else match =PICTURE?, setting
			type = 7
		else match =GDB?, setting
			type = 1
		else match =COMPLEX?, setting
			type = 12
			define cplx
		else match =APPVAR?, setting
			type = 21
		else if setting eqtype 'name'
			name = setting
		else if setting eqtype 0
			type = setting
		end if
	end macro
	name = 'A'
	type = 6
	flag = 0
	process clause
	dq '**TI83F*'
	db 26, 10, 0
	rb 42
	dw sizeof all
	org $ ; checksum from here
	label all : checkloc - $%
	dw sizeof head, sizeof data
	label head : data - $
	db type
	dq name
	db 0, flag
	dw sizeof data
	label data : checkloc - $%
	dw sizeof var
	label var : checkloc - $%
	if defined exec
		dw 07BEFh
	end if
	checksum = 0
	macro org? address
		repeat $@ - $$
			load temp : byte from $$ + % - 1
			checksum = (checksum + temp) and 0FFFFh
		end repeat
		org address
	end macro
	org 0D1A881h
	postpone ?
		org $ ; compute checksum
		dw checksum
	end postpone
	postpone
		checkloc = $%
	end postpone
end macro

macro .list?
end macro
macro .nolist?
end macro
macro #ifdef? any&
end macro
macro #ifndef? any&
end macro
macro #endif?
end macro
macro #define? any&
end macro
macro assign var, val&
	     match left & right, val
		assign var, left and right
	else match left | right, val
		assign var, left or right
	else match left =^ right, val
		assign var, left xor right
	else match left << right, val
		assign var, left shl right
	else match left >> right, val
		assign var, left shr right
	else
		var = val
	end match
end macro
struc equ? val&
	assign ., val
end struc
macro Ld args&
	match =equ? val, args
		assign Ld, val
	end match
end macro

include 'ti84pce.inc'

purge Ld
restruc equ?
purge assign
purge #define?
purge #endif?
purge #ifndef?
purge #ifdef?
purge .nolist?
purge .list?

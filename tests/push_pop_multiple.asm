include 'ez80.inc'
	push     af
	push.sis bc de
	push.lis hl ix iy
	pop.sil  iy ix hl
	pop.lil  de bc
	pop      af

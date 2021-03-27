include 'ez80.inc'

	jq	c, lab
	rb	124
	jq	m, lab
unused:
	jq	z, lab
lab:
	jq	p, lab


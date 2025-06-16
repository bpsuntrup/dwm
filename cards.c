void
cards(Monitor *mon) {
	unsigned int i, n, nw, nh;
	Client *c;

	for(n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++);
	if(n == 0)
		return;
	
	nw = mon->ww;
	nh = mon->wh;

    unsigned int gap = mon->gap->gappx * 2; /* quirky default, makes this change dependent on gaps */
	
	for(i = 1, c = nexttiled(mon->clients); c; c = nexttiled(c->next)) {
		resize(c, 
            ((n-i) * (gap + c->bw)) + mon->wx + mon->gap->gappx,  
            ((n-i) * (gap + c->bw)) + mon->wy + mon->gap->gappx,
            nw - (n * (gap + c->bw)),
            nh - (n * (gap + c->bw)),
            0
        );
        i++;

	}
}

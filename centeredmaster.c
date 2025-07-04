void
centeredmaster(Monitor *m)
{
	unsigned int i, n, h, mw, mx, my, oty, ety, tw;
	Client *c;

	/* count number of clients in the selected monitor */
	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;

	/* initialize areas */
	mw = m->ww;
	mx = 0;
	my = 0;
	tw = mw;

	if (n > m->nmaster) {
		/* go mfact box in the center if more than nmaster clients */
		mw = m->nmaster ? m->ww * m->mfact : 0;
		mw -= m->gap->gappx;
		tw = m->ww - mw;

		if (n - m->nmaster > 1) {
			/* only one client */
			mx = (m->ww - mw + m->gap->gappx) / 2;
			tw = (m->ww - mw - 1.5*m->gap->gappx) / 2;
		}
	}

	oty = 0;
	ety = 0;
	for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
	if (i < m->nmaster) {
		/* nmaster clients are stacked vertically, in the center
		 * of the screen */
		h = (m->wh - my) / (MIN(n, m->nmaster) - i);
		resize(c, m->wx + mx, m->wy + my + m->gap->gappx, mw - (2*c->bw) - m->gap->gappx/2,
		       h - (2*c->bw) - 2*m->gap->gappx, 0);
		my += HEIGHT(c) + m->gap->gappx;
	} else {
		/* stack clients are stacked vertically */
		if ((i - m->nmaster) % 2 ) {
			h = (m->wh - ety - 2*m->gap->gappx) / ( (1 + n - i) / 2) - m->gap->gappx;
			resize(c, m->wx + m->gap->gappx, m->wy + m->gap->gappx + ety, tw - (2*c->bw) - m->gap->gappx / 2,
			       h - (2*c->bw), 0);
			ety += HEIGHT(c) + m->gap->gappx;
		} else {
			h = (m->wh - oty - 2*m->gap->gappx) / ((1 + n - i) / 2) - m->gap->gappx;
			resize(c, m->wx + mx + mw + m->gap->gappx / 2, m->wy + oty + m->gap->gappx,
			       tw - (2*c->bw) - m->gap->gappx / 2, h - (2*c->bw), 0);
			oty += HEIGHT(c) + m->gap->gappx;
		}
	}
}

void
centeredfloatingmaster(Monitor *m)
{
	unsigned int i, n, w, mh, mw, mx, mxo, my, myo, tx;
	Client *c;

	/* count number of clients in the selected monitor */
	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;

	/* initialize nmaster area */
	if (n > m->nmaster) {
		/* go mfact box in the center if more than nmaster clients */
		if (m->ww > m->wh) {
			mw = m->nmaster ? m->ww * m->mfact : 0;
			mh = m->nmaster ? m->wh * 0.9 : 0;
		} else {
			mh = m->nmaster ? m->wh * m->mfact : 0;
			mw = m->nmaster ? m->ww * 0.9 : 0;
		}
		mx = mxo = (m->ww - mw) / 2;
		my = myo = (m->wh - mh) / 2;
	} else {
		/* go fullscreen if all clients are in the master area */
		mh = m->wh;
		mw = m->ww;
		mx = mxo = 0;
		my = myo = 0;
	}

	for(i = tx = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
	if (i < m->nmaster) {
		/* nmaster clients are stacked horizontally, in the center
		 * of the screen */
		w = (mw + mxo - mx) / (MIN(n, m->nmaster) - i);
		resize(c, m->wx + mx, m->wy + my, w - (2*c->bw),
		       mh - (2*c->bw), 0);
		mx += WIDTH(c);
	} else {
		/* stack clients are stacked horizontally */
		w = (m->ww - tx) / (n - i);
		resize(c, m->wx + tx, m->wy, w - (2*c->bw),
		       m->wh - (2*c->bw), 0);
		tx += WIDTH(c);
	}
}

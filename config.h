/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 7;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */

/* previous fonts: "Cherry:size=10" "Liberation Mono:size=13" */
static const char *fonts[]          = {"Terminus:size=9", "TerminessTTF Nerd Font:size=11"};
static const char *logo_font[]          = {"TerminessTTF Nerd Font:size=15"};
static const char dmenufont[]       = {"Terminus:size=9"};
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray5[]       = "#919191"; /* was #696969 */
static const char col_gray3[]       = "#bfbfbf"; /* was #bbbbbb */
static const char col_gray4[]       = "#eeeeee"; /* was #eeeeee */
static const char col_white[]	    = "#f5f5f5";
static const char col_cyan[]        = "#87ceff";
static const char col_lime[]        = "#4eee94";
static const char col_blue[]	    = "#1c86ee";
static const char col_gold[]	    = "#deb887";
static const char col_brownish[]    = "#775544";
static const char col_bluegray[]    = "#708090";
static const char col_purplish[]    = "#8470ff";
static const char col_grayish[]     = "#4f5b66";
static const char col_reddish[]	    = "#ff6a6a";
static const char col_lightgray[]   = "#cdc9c9";

static const char *colors[][3]      = {
	/*			    fg         bg         border   */
	[SchemeNorm] =		{ col_gray3, col_gray1, col_gray3},
	[SchemeSel]  =		{ col_purplish, col_purplish, col_purplish },
	[SchemeSelCustom] =	{ col_gray4, col_gray1, col_gray2 },
	[SchemeSpotify] =	{ col_lime,  col_gray1, col_lime},
	[SchemeLogo] =		{ col_blue,  col_gray1, col_blue},
	[SchemeBrowser] =	{ col_cyan,  col_gray1, col_cyan},
	[SchemeEditor]  =	{ col_gold, col_gray1, col_gold},
	[SchemeGithub]  =       { col_white, col_gray1, col_white},
	[SchemeProgs]   =	{ col_reddish, col_gray1, col_reddish},
	[SchemeMisc]    =       { col_bluegray, col_gray1, col_bluegray },
	[SchemeMode]    =       { col_lightgray, col_gray1, col_gray3}
};

/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4"}; */
static const char  *tags[] = {"", "", "ﯽ", "", "", "ﳁ"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ " " /* "[]=" */,      tile },    /* first entry is default */
	{ " " /* "><>" */,      NULL },    /* no layout function means floating behavior */
	{ "类 " /* "[M]" */,      monocle },
 	{ " ",      spiral },
 	{ "𧻓 ",      dwindle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_purplish, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *emacscmd[] = { "emacsclient", "-c", "--eval", "(org-agenda-list)", "(delete-other-windows)", NULL};
static const char *ffoxcmd[] = {"firefox", NULL};
static const char *spotifycmd[] = {"spotify", NULL};
static const char *nnncmd[] = {"st", "-e", "/home/newtion/.config/nnn/nwrap", NULL};
static const char *zathura[] = {"zathura", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,			XK_z,	   spawn,	   {.v = zathura}},
	{ MODKEY,			XK_a,	   spawn,	   {.v = nnncmd}},
	{ MODKEY,	                XK_n,	   spawn,	   {.v = spotifycmd}},
	{ MODKEY,			XK_w,	   spawn,          {.v = ffoxcmd} },
	{ MODKEY,                       XK_e,      spawn,          {.v = emacscmd} },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_s,	   setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_s,	   togglefloating, {0} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },
	/* { MODKEY,                       XK_space,  setlayout,      {0} }, */
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      1)
	TAGKEYS(                        XK_2,                      2)
	TAGKEYS(                        XK_3,                      3)
	TAGKEYS(                        XK_4,                      4)
	TAGKEYS(                        XK_5,                      5)
	TAGKEYS(                        XK_6,                      6)
	TAGKEYS(                        XK_7,                      7)
	TAGKEYS(                        XK_8,                      8)
	TAGKEYS(                        XK_9,                      9)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

